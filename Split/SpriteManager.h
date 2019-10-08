#pragma once
#include "Global.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "Chunk.h"

class SpriteManager
{
private:
	Chunk** _chunks;
	std::list<Sprite> _staticElements;
	Sprite _player;
	Chunk _mainChunk;
	std::list<Sprite> _sortedList;

	void Sort();
public:
	SpriteManager(SpriteSheet*);
	~SpriteManager();

	void AddStaticElement(Sprite sprite);
	void AddPlayer(Sprite sprite);
	void DrawAll();
	void ClearWindow();
	void SortStaticElements();
	void DistributeSprites();
	sf::RenderWindow* GetMainWindow();
};