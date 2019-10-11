#include "SpriteManager.h"
#include "LevelManager.h"
#include <random>
#include "Pair.h"

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

	_chunks = new Chunk *[level->ChunkCount];
	for (int i = 0; i < level->ChunkCount; i++) {
		_chunks[i] = new Chunk[level->ChunkCount];
		for (int j = 0; j < level->ChunkCount; j++) {
			window = new sf::RenderWindow(
				sf::VideoMode(windowSize, windowSize),
				"SFML",
				sf::Style::None);
			window->setPosition(sf::Vector2i(
				staticListPair[index].GetKey() * (windowSize + 30),
				staticListPair[index].GetValue() * (windowSize + 30)));
			_chunks[i][j] = Chunk(window, _spritesheet);
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
}

void SpriteManager::ClearWindow() {
	_sortedList.clear();

	for (int i = 0; i < Global::ChunkCount; i++) {
		for (int j = 0; j < Global::ChunkCount; j++) {
			_chunks[i][j].Clear();
		}
	}
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
		chunkX = (int) floor((*it)->getPosX() / chunkSize);
		chunkY = (int) floor((*it)->getPosY() / chunkSize);

		_chunks[chunkX][chunkY].AddSprite(**it);
	}
	if (!LevelManager::menuActive) {
		chunkX = (int) floor((_player->getPosX()+SPRITESHEET_CELL_SIZE/2*Global::Scale) / chunkSize);
		chunkY = (int) floor((_player->getPosY() + SPRITESHEET_CELL_SIZE / 2 * Global::Scale) / chunkSize);
	}
	else {
		chunkX = 0;
		chunkY = 0;
	}
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