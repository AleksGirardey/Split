#include "SpriteManager.h"
#include <random>
#include "Pair.h"

SpriteManager::SpriteManager(SpriteSheet* spritesheet) {
	_staticElements = std::list<Sprite>();
	_sortedList = std::list<Sprite>();
	int chunkSizeX = SCREEN_WIDTH / CHUNK_SIZE;
	int chunkSizeY = SCREEN_HEIGHT / CHUNK_SIZE;
	int windowWidth = CHUNK_SIZE * SPRITESHEET_CELL_SIZE * SCALE;
	int windowHeight = CHUNK_SIZE * SPRITESHEET_CELL_SIZE * SCALE;
	sf::RenderWindow* window;
	std::vector<Pair> staticListPair = std::vector<Pair>();

	for (int i = 0; i < chunkSizeX; i++) {
		for (int j = 0; j < chunkSizeY; j++) {
			staticListPair.push_back(Pair(i, j));
		}
	}
	int index = 0;

	_chunks = new Chunk *[chunkSizeX + 1];
	for (int i = 0; i < chunkSizeX; i++) {
		_chunks[i] = new Chunk[chunkSizeY + 1];
		for (int j = 0; j < chunkSizeY; j++) {
			window = new sf::RenderWindow(
				sf::VideoMode(windowWidth, windowHeight),
				"SFML",
				sf::Style::None);
			window->setPosition(sf::Vector2i(
				staticListPair[index].GetKey() * (windowWidth + 30),
				staticListPair[index].GetValue() * (windowHeight + 30)));
			_chunks[i][j] = Chunk(window, spritesheet);
			if (i == 0 && j == 0)
				_mainChunk = _chunks[i][j];

			staticListPair.erase(staticListPair.begin() + index);
			if (staticListPair.size() != 0)
				index = rand() % staticListPair.size();			
		}
	}
}

SpriteManager::~SpriteManager() {
	int chunkSizeY = SCREEN_HEIGHT / CHUNK_SIZE;

	for (int i = chunkSizeY - 1; i >= 0; --i) {
		delete[] _chunks[i];
	}
	delete[] _chunks;
}

void SpriteManager::AddStaticElement(Sprite sprite) {
	_staticElements.push_back(sprite);
}

void SpriteManager::AddPlayer(Sprite sprite) {
	_player = sprite;
}

void SpriteManager::DrawAll() {
	int chunkSizeX = SCREEN_WIDTH / CHUNK_SIZE;
	int chunkSizeY = SCREEN_HEIGHT / CHUNK_SIZE;

	DistributeSprites();

	for (int i = 0; i < chunkSizeX; i++) {
		for (int j = 0; j < chunkSizeY; j++) {
			_chunks[i][j].Draw();
		}
	}
	chunkSizeY = 1;
}

void SpriteManager::ClearWindow() {
	_sortedList.clear();

	int chunkSizeX = SCREEN_WIDTH / CHUNK_SIZE;
	int chunkSizeY = SCREEN_HEIGHT / CHUNK_SIZE;

	for (int i = 0; i < chunkSizeX; i++) {
		for (int j = 0; j < chunkSizeY; j++) {
			_chunks[i][j].Clear();
		}
	}
}

void SpriteManager::SortStaticElements() {
	_staticElements.sort();
}

void SpriteManager::Sort() {
	_sortedList = std::list<Sprite>(_staticElements.begin(), _staticElements.end());
}

void SpriteManager::DistributeSprites() {
	int chunkX;
	int chunkY;
	float chunkSize = CHUNK_SIZE * SPRITESHEET_CELL_SIZE * SCALE;

	Sort();

	for (std::list<Sprite>::iterator it = _sortedList.begin(); it != _sortedList.end(); it++) {
		chunkX = floor((*it).getPosX() / chunkSize);
		chunkY = floor((*it).getPosY() / chunkSize);

		_chunks[chunkX][chunkY].AddSprite(*it);
	}

	chunkX = floor(_player.getPosX() / chunkSize);
	chunkY = floor(_player.getPosY() / chunkSize);
	_chunks[chunkX][chunkY].AddPlayer(_player);
	_mainChunk = _chunks[chunkX][chunkY];
}

sf::RenderWindow* SpriteManager::GetMainWindow() {
	return _mainChunk.GetWindow();
}