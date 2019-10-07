#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Global.h"
#include "Sprite.h"

const unsigned FLIPPED_H = 0x80000000;
const unsigned FLIPPED_V = 0x40000000;
const unsigned FLIPPED_D = 0x20000000;

class SpriteSheet
{
private:
	sf::RenderWindow* _window;
	sf::Texture _texture;
	sf::Sprite _sprite;
public:
	SpriteSheet(sf::RenderWindow* renderer, std::string texturePath);
	~SpriteSheet();

	void DrawSprite(Sprite Sprite);
};