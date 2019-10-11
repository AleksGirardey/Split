#include "SpriteManager.h"
#include "LevelManager.h"
#include <random>
#include "Pair.h"
#include "Expo.h"

SpriteManager::SpriteManager(SpriteSheet* spritesheet) :
	_spritesheet(spritesheet)
{
	_staticElements = std::list<Sprite*>();
	_sortedList = std::list<Sprite*>();
}

void SpriteManager::Load(Level* level) {
	int windowSize = level->ChunkSize * SPRITESHEET_CELL_SIZE * level->Scale;
	sf::RenderWindow* window;
	std::vector<Pair> staticListPair = std::vector<Pair>();

	Global::Scale = level->Scale;
	Global::ChunkSize = level->ChunkSize;
	Global::ChunkCount = level->ChunkCount;

	for (int i = 0; i < level->ChunkCount; i++) {
		for (int j = 0; j < level->ChunkCount; j++) {
			staticListPair.push_back(Pair(i, j));
		}
	}
	int index = 0;
	
	unsigned int desktopWidth = sf::VideoMode::getDesktopMode().width;
	unsigned int desktopHeight = sf::VideoMode::getDesktopMode().height;
	int windowOffset = 30;
	int offsetPosX = 0;
	int offsetPosY = 0;
	int offsetMinimapX = 0;
	int offsetMinimapY = 0;

	offsetPosY = (desktopHeight / 2) - ((level->ChunkCount * (windowSize + windowOffset) - windowOffset) / 2);
	offsetMinimapY = offsetPosY;

	if (!Global::Easy) {
		offsetPosX = (desktopWidth / 2) - ((level->ChunkCount * (windowSize + windowOffset) - windowOffset) / 2);
	} else {
		offsetPosX = (desktopWidth / 2) - (2 * (level->ChunkCount * (windowSize + windowOffset) - windowOffset) / 3);
		offsetMinimapX = (desktopWidth / 2) + ((level->ChunkCount * (windowSize + windowOffset) - windowOffset) / 3) + windowOffset;

		_miniMap = new sf::RenderWindow(sf::VideoMode(windowSize * level->ChunkCount, windowSize * level->ChunkCount),
			"Mini Map", sf::Style::None);
		_miniMap->setPosition(sf::Vector2i(offsetMinimapX, offsetMinimapY));
	}
	_timeAnim = 0;

	_chunks = new Chunk *[level->ChunkCount];
	for (int i = 0; i < level->ChunkCount; i++) {
		_chunks[i] = new Chunk[level->ChunkCount];
		for (int j = 0; j < level->ChunkCount; j++) {
			offsetPosX = (desktopWidth / 2) - (windowSize / 2);
			offsetPosY = (desktopHeight / 2) - (windowSize / 2);
			window = new sf::RenderWindow(
				sf::VideoMode(windowSize, windowSize),
				"SFML",
				sf::Style::None);
			window->setPosition(sf::Vector2i(
				(0 * (windowSize + windowOffset)) + offsetPosX ,
				(0 * (windowSize + windowOffset)) + offsetPosY));
			_chunks[i][j] = Chunk(window,_miniMap, _spritesheet);
			if (!LevelManager::menuActive) {
				if (i == floor(level->SpawnPoint->GetKey() / level->ChunkSize)
					&& j == floor(level->SpawnPoint->GetValue() / level->ChunkSize)) {
					_mainChunk = _chunks[i][j];
					MainChunkX = i;
					MainChunkY = j;
				}
			}
			else {
				MainChunkX = 0;
				MainChunkY = 0;
				_mainChunk = _chunks[MainChunkX][MainChunkY];
			}
			
			if (i > 0) {
				_chunks[i][j].LeftNeighbor = &_chunks[i - 1][j];
				_chunks[i - 1][j].RightNeighbor = &_chunks[i][j];
			}
			if (j > 0) {
				_chunks[i][j].TopNeighbor = &_chunks[i][j - 1];
				_chunks[i][j - 1].BotNeighbor = &_chunks[i][j];
			}

			staticListPair.erase(staticListPair.begin() + index);
			if (staticListPair.size() != 0)
				index = rand() % staticListPair.size();			
		}
	}
	
	std::list<Sprite*> levelSprites = level->Load();

	_staticElements = std::list<Sprite*>(levelSprites.begin(), levelSprites.end());
}

SpriteManager::~SpriteManager() {
	DeleteChunks();
}

void SpriteManager::AddPlayer(Sprite* sprite) {
	_player = sprite;
}

void SpriteManager::DrawAll() {
	DistributeSprites();

	for (int i = 0; i < Global::ChunkCount; i++) {
		for (int j = 0; j < Global::ChunkCount; j++) {
			_chunks[i][j].Draw();
		}
	}

	if (_miniMap != NULL) _miniMap->display();
}

void SpriteManager::ClearWindow() {
	_sortedList.clear();

	for (int i = 0; i < Global::ChunkCount; i++) {
		for (int j = 0; j < Global::ChunkCount; j++) {
			_chunks[i][j].Clear();
		}
	}
	if (_miniMap != NULL) _miniMap->clear(sf::Color(71, 45, 60, 255));
}

void SpriteManager::SortStaticElements() {
	_staticElements.sort();
}

void SpriteManager::Sort() {
	_sortedList = std::list<Sprite*>(_staticElements.begin(), _staticElements.end());
}

void SpriteManager::DistributeSprites() {
	int chunkX;
	int chunkY;
	float chunkSize = Global::ChunkSize * SPRITESHEET_CELL_SIZE * Global::Scale;

	Sort();

	for (auto it = _sortedList.begin(); it != _sortedList.end(); it++) {
		chunkX = (int)floor((*it)->getPosX() / chunkSize);
		chunkY = (int)floor((*it)->getPosY() / chunkSize);

		_chunks[chunkX][chunkY].AddSprite(**it);
	}
	chunkX = (int)floor((_player->getPosX() + SPRITESHEET_CELL_SIZE / 2 * Global::Scale) / chunkSize);
	chunkY = (int)floor((_player->getPosY() + SPRITESHEET_CELL_SIZE / 2 * Global::Scale) / chunkSize);
	_chunks[chunkX][chunkY].AddPlayer(_player);
	MainChunkX = chunkX;
	MainChunkY = chunkY;
	_mainChunk = _chunks[chunkX][chunkY];
}

sf::RenderWindow* SpriteManager::GetMainWindow() {
	return _mainChunk.GetWindow();
}

void SpriteManager::CloseWindows() {
	int size = Global::ChunkCount;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			_chunks[i][j].GetWindow()->close();
		}
	}
	if (_miniMap != NULL) _miniMap->close();
}

void SpriteManager::DeleteChunks() {
	for (int i = (Global::ChunkCount / 2) - 1; i >= 0; --i) {
		delete[] _chunks[i];
	}
	delete[] _chunks;
}

void SpriteManager::NextLevel() {
	CloseWindows();
	DeleteChunks();
	_staticElements.clear();
	_sortedList.clear();
}

void SpriteManager::PlacementChunk(float deltaTime) {
	int windowSize = Global::ChunkSize * SPRITESHEET_CELL_SIZE * Global::Scale;
	unsigned int desktopWidth = sf::VideoMode::getDesktopMode().width;
	unsigned int desktopHeight = sf::VideoMode::getDesktopMode().height;
	int windowOffset = 30;
	int offsetPosX = 0;
	int offsetPosY = 0;
	
	offsetPosX = (desktopWidth / 2) - ((Global::ChunkCount*(windowSize + windowOffset) - windowOffset) / 2);
	offsetPosY = (desktopHeight / 2) - ((Global::ChunkCount*(windowSize + windowOffset) - windowOffset) / 2);

	int multiply = 2000*Global::Scale;
	if (_timeAnim >= multiply)
		return;
	_timeAnim += deltaTime;
	if (!LevelManager::menuActive) {
		for (int i = 0; i < Global::ChunkCount; i++) {
			for (int j = 0; j < Global::ChunkCount; j++) {
				int posx = 0;
				int posy = 0;
				if (Global::Easy) {
					posx = Expo::easeInOut(_timeAnim, (desktopWidth / 2) - (windowSize / 2), i*((windowSize + windowOffset)) - ((Global::ChunkCount*(windowSize + windowOffset) - windowOffset) / 2) + windowSize / 2 - windowSize, multiply);
					posy = Expo::easeInOut(_timeAnim, (desktopHeight / 2) - (windowSize / 2), j*((windowSize + windowOffset)) - ((Global::ChunkCount*(windowSize + windowOffset) - windowOffset) / 2) + windowSize / 2, multiply);
				}
				else {
					posx = Expo::easeInOut(_timeAnim, (desktopWidth / 2) - (windowSize / 2), i*((windowSize + windowOffset)) - ((Global::ChunkCount*(windowSize + windowOffset) - windowOffset) / 2) + windowSize / 2, multiply);
					posy = Expo::easeInOut(_timeAnim, (desktopHeight / 2) - (windowSize / 2), j*((windowSize + windowOffset)) - ((Global::ChunkCount*(windowSize + windowOffset) - windowOffset) / 2) + windowSize / 2, multiply);
				}
				_chunks[i][j].GetWindow()->setPosition(sf::Vector2i(posx,posy));
			}
		}
	}
}