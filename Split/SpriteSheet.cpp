#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(sf::RenderWindow* window, std::string texturePath) :
	_window(window)
{
	if (!_texture.loadFromFile(texturePath))
		printf("[SpriteSheet] Cannot load image '%s'\n", texturePath.c_str());
}

SpriteSheet::~SpriteSheet() {}

void SpriteSheet::DrawSprite(Sprite sprite)
{
	int spriteGridX = sprite.getIndex() % SPRITESHEET_CELL_COUNT_PER_ROW;
	int spriteGridY = (int)floor(sprite.getIndex() / SPRITESHEET_CELL_COUNT_PER_ROW);
	float rotation = 0.f;

	int rectLeft = spriteGridX * (SPRITESHEET_CELL_SIZE + SPRITESHEET_OFFSET);
	int rectTop = spriteGridY * (SPRITESHEET_CELL_SIZE + SPRITESHEET_OFFSET);
	int width = SPRITESHEET_CELL_SIZE;
	int height = SPRITESHEET_CELL_SIZE;
	float offset = SPRITESHEET_CELL_SIZE / 2;

	sf::IntRect srcRect(rectLeft, rectTop, width, height);

	_sprite.setTexture(_texture);
	_sprite.setOrigin(sf::Vector2f(offset, offset));
	if (sprite.isFlipD()) {
		if (sprite.isFlipH()) rotation = 90.f;
		if (sprite.isFlipV()) rotation = 270.f;
	} else {
		if (sprite.isFlipH() && !sprite.isFlipV()) {
			srcRect = sf::IntRect(rectLeft + width, rectTop, -width, height);
		} else if (sprite.isFlipV() && !sprite.isFlipH()) {
			srcRect = sf::IntRect(rectLeft, rectTop + height, width, -height);
		} else if (sprite.isFlipH() && sprite.isFlipV()) {
			srcRect = sf::IntRect(rectLeft + width, rectTop + height, -width, -height);
		}
	}
	_sprite.setTextureRect(srcRect);

	_sprite.setPosition(sf::Vector2f((offset * SCALE) + sprite.getPosX(), (offset * SCALE) + sprite.getPosY()));
	_sprite.setScale(sf::Vector2f(SCALE, SCALE));
	_sprite.setRotation(rotation);
	_window->draw(_sprite);
}