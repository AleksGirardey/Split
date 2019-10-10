#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Global.h"
#include "Sprite.h"

class SpriteSheet
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
public:
	SpriteSheet(std::string texturePath);
	~SpriteSheet();

	void DrawSprite(sf::RenderWindow* window, Sprite Sprite);
};