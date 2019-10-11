#pragma once
#include "Global.h"
#include "SpriteSheet.h"
#include <list>
#include "Pair.h"

class Chunk {
private:


	SpriteSheet* _spriteSheet;
	sf::RenderWindow* _window;
	sf::RenderWindow* _minimap;
	sf::Color _background;

	bool _drawMinimap;

	std::list<Sprite> _sprites;

public:
	Chunk(sf::RenderWindow* window, sf::RenderWindow* minimap, SpriteSheet* spritesheet);
	Chunk();
	~Chunk();

	Chunk* TopNeighbor;
	Chunk* BotNeighbor;
	Chunk* LeftNeighbor;
	Chunk* RightNeighbor;
	Pair randMemory;

	void AddSprite(Sprite sprite);
	void AddPlayer(Sprite* sprite);

	void Draw();
	void Clear();
	sf::RenderWindow* GetWindow();
};