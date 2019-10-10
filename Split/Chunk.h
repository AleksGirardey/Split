#pragma once
#include "Global.h"
#include "SpriteSheet.h"
#include <list>

class Chunk {
private:


	SpriteSheet* _spriteSheet;
	sf::RenderWindow* _window;
	sf::Color _background;

	std::list<Sprite> _sprites;

public:
	Chunk(sf::RenderWindow* window, SpriteSheet* spritesheet);
	Chunk();
	~Chunk();

	void AddSprite(Sprite sprite);
	void AddPlayer(Sprite* sprite);

	void Draw();
	void Clear();
	sf::RenderWindow* GetWindow();
};