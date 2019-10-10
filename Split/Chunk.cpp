#include "Chunk.h"
#include "SpriteManager.h"
#include <iostream>

Chunk::Chunk(sf::RenderWindow* window, SpriteSheet* spritesheet) :
	_window(window),
	_spriteSheet(spritesheet) {
	_sprites = std::list<Sprite>();
	_background = sf::Color(71, 45, 60, 255);
}

Chunk::Chunk() : _window(NULL), _spriteSheet(NULL) {
	_sprites = std::list<Sprite>();
}

Chunk::~Chunk() {}

void Chunk::AddSprite(Sprite sprite) {
	_sprites.push_back(sprite);
}

void Chunk::AddPlayer(Sprite* sprite) {
	_sprites.push_back(*sprite);
	_window->requestFocus();
}

void Chunk::Draw() {
	float chunkSize = Global::ChunkSize * SPRITESHEET_CELL_SIZE * Global::Scale;
	float chunkPosX;
	float chunkPosY;

	_window->clear(_background);

	for (std::list<Sprite>::iterator it = _sprites.begin(); it != _sprites.end(); it++) {
		chunkPosX = floorf((*it).getPosX() / chunkSize);
		chunkPosY = floorf((*it).getPosY() / chunkSize);
		
		if (chunkPosX != 0)
			(*it).setPosX((*it).getPosX() - ((chunkPosX) * chunkSize));
		if (chunkPosY != 0)
			(*it).setPosY((*it).getPosY() - ((chunkPosY) * chunkSize));

		_spriteSheet->DrawSprite(_window, *it);
	}

	_window->display();
}

void Chunk::Clear() {
	_sprites.clear();
}

sf::RenderWindow* Chunk::GetWindow() { return _window; }