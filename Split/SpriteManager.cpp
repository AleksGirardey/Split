#include "SpriteManager.h"

SpriteManager::SpriteManager(sf::RenderWindow* window, std::string texturePath) {
	_staticElements = std::list<Sprite>();
	_entities = std::list<Sprite>();
	_sortedList = std::list<Sprite>();
	_spriteSheet = new SpriteSheet(window, texturePath);
}

SpriteManager::~SpriteManager() {}

void SpriteManager::AddStaticElement(Sprite* sprite) {
	_staticElements.push_back(*sprite);
}

void SpriteManager::AddEntity(Sprite* sprite) {
	_entities.push_back(*sprite);
}

void SpriteManager::DrawAll() {
	Sort();
	for (std::list<Sprite>::iterator it = _sortedList.begin(); it != _sortedList.end(); it++) {
		_spriteSheet->DrawSprite(*it);
	}
}

void SpriteManager::ClearEntities() {
	_entities.clear();
}

void SpriteManager::ClearWindow() {
	_sortedList.clear();
}

void SpriteManager::SortStaticElements() {
	_staticElements.sort();
}

void SpriteManager::Sort() {
	_sortedList = std::list<Sprite>(_staticElements);
	_entities.sort();
	_sortedList.merge(_entities);
}