#pragma once
#include "Global.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "Chunk.h"
#include "Level.h"

class SpriteManager {
private:
	SpriteSheet* _spritesheet;
	sf::RenderWindow* _miniMap;
	Chunk** _chunks;
	Sprite* _player;
	Chunk _mainChunk;
	std::list<Sprite*> _staticElements;
	std::list<Sprite*> _sortedList;

	void Sort();
	void CloseWindows();
	void DeleteChunks();
public:
	SpriteManager(SpriteSheet*);
	~SpriteManager();

	int MainChunkX;
	int MainChunkY;

	void AddPlayer(Sprite* sprite);
	void DrawAll();
	void ClearWindow();
	void SortStaticElements();
	void DistributeSprites();
	sf::RenderWindow* GetMainWindow();

	void NextLevel();
	void Load(Level* level);
};