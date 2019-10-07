#pragma once
#include "Global.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include <list>
#include <SFML/Graphics.hpp>

class SpriteManager
{
private:
	SpriteSheet* _spriteSheet;

	std::list<Sprite> _staticElements;
	std::list<Sprite> _entities;
	std::list<Sprite> _sortedList;

	void Sort();
public:
	SpriteManager(sf::RenderWindow* window, std::string texturePath);
	~SpriteManager();

	void AddStaticElement(Sprite* sprite);
	void AddEntity(Sprite* sprite);
	void DrawAll();
	void ClearEntities();
	void ClearWindow();
	void SortStaticElements();
};