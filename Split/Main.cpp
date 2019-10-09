#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "SpriteManager.h"
#include "TileMap.h"
#include "Animator.h"
#include "Player.h"
#include "Physics.h"

void HandleKeyPressed(Player* player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player->goingLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player->goingRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player->goingUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		player->GoSpawn();
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

int main(int argc, char** argv) {
	sf::Time deltaTime;
	
	SpriteSheet* spritesheet = new SpriteSheet("./Assets/colored_transparent.png");

	std::string tileMapPath = "./Assets/chunked.csv";

	SpriteManager spriteManager(spritesheet);
	TileMap tileMap(&spriteManager);

	tileMap.LoadFromCSV(tileMapPath);

	sf::Clock clock;

	Physics physics;
	Animator animPlayerOne("242", "243,244", "245,246", "247", 0.5f);
	Player playerOne(&spriteManager, &animPlayerOne, &physics);

	tileMap.DrawMap(&physics);
	spriteManager.SortStaticElements();
	sf::RenderWindow* window = spriteManager.GetMainWindow();

	while (window->isOpen()) {
		sf::Event event;
		//sf::Joystick::update();
		deltaTime = clock.restart();

		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					exit(EXIT_SUCCESS);
				HandleKeyPressed(&playerOne);
			}

			if (event.type == sf::Event::KeyReleased) {
				HandleKeyReleased(&playerOne, event.key.code);
			}

			//JOYSTICK
			float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

			if (x > 20) {
				playerOne.goingRight();
			}
			else if (x < -20) {
				playerOne.goingLeft();
			}
			else {
				playerOne.idle(LEFT);
				playerOne.idle(RIGHT);
			}
			if (event.type == sf::Event::JoystickButtonPressed) {
				if (sf::Joystick::isButtonPressed(0, 0)) {
					playerOne.goingUp();
				}
				else {
					playerOne.idle(UP);
				}
			}
			else {
				playerOne.idle(UP);
			}
			
		}
		spriteManager.ClearWindow();
		playerOne.Draw((float)deltaTime.asMilliseconds());
		spriteManager.DrawAll();
		window = spriteManager.GetMainWindow();
	}

	return 0;
}