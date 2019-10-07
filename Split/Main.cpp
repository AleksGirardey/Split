#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "SpriteManager.h"
#include "TileMap.h"
#include "Animator.h"
#include "Player.h"

void HandleKeyPressed(Player* player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player->goingLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player->goingRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player->goingUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		player->goingDown();
}

void HandleKeyReleased(Player* player, sf::Keyboard::Key code) {
	switch (code) {
		case sf::Keyboard::Left: player->idle(LEFT); break;
		case sf::Keyboard::Right: player->idle(RIGHT); break;
		case sf::Keyboard::Up: player->idle(UP); break;
		case sf::Keyboard::Down: player->idle(DOWN); break;
		default:break;
	}
}

int main(int argc, char** argv)
{
	sf::Time deltaTime;

	sf::RenderWindow window(
		sf::VideoMode(SCREEN_WIDTH * SPRITESHEET_CELL_SIZE * SCALE,
			SCREEN_HEIGHT * SPRITESHEET_CELL_SIZE * SCALE),
		"Hello SFML");

	std::string tileMapPath = "./Assets/sample_fantasy.csv";

	SpriteManager spriteManager(&window, "./Assets/colored_transparent.png");
	TileMap tileMap(&spriteManager);

	tileMap.LoadFromCSV(tileMapPath);

	window.setFramerateLimit(FRAME_RATE);
	sf::Clock clock;

	Animator animPlayerOne("242", "243,244", "245,246", "247", 0.5f);
	Player playerOne(&spriteManager, &animPlayerOne);

	tileMap.DrawMap();
	spriteManager.SortStaticElements();

	sf::Color background = sf::Color(71, 45, 60, 255);

	while (window.isOpen()) {
		sf::Event event;

		deltaTime = clock.restart();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				HandleKeyPressed(&playerOne);
			}
			if (event.type == sf::Event::KeyReleased) {
				HandleKeyReleased(&playerOne, event.key.code);
			}
		}

		window.clear(background);
		spriteManager.ClearEntities();
		spriteManager.ClearWindow();

		playerOne.Draw((float) deltaTime.asMilliseconds());
		spriteManager.DrawAll();

		window.display();
	}

	return 0;
}