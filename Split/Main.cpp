#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "SpriteManager.h"
#include "Animator.h"
#include "Player.h"
#include "Physics.h"
#include "LevelManager.h"

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
	sf::Clock clock;

	SpriteSheet* spritesheet = new SpriteSheet("./Assets/colored_transparent.png");
	SpriteManager spriteManager(spritesheet);
	LevelManager levelManager;
	LevelManager::menuActive = false;
	spriteManager.Load(levelManager.CurrentLevel);

	Physics physics;
	Animator animPlayerOne("242", "243,244", "245,246", "247", 0.5f);
	Player playerOne(
		&spriteManager,
		&animPlayerOne,
		&physics,
		levelManager.CurrentLevel->SpawnPoint,
		levelManager.CurrentLevel->ExitPoint);

	spriteManager.SortStaticElements();
	sf::RenderWindow* window = spriteManager.GetMainWindow();
	playerOne.SetObstacles(levelManager.CurrentLevel->ObstacleList);
	playerOne.SetTraps(levelManager.CurrentLevel->TrapList);
	playerOne.SetExitPoint(levelManager.CurrentLevel->ExitPoint);
	playerOne.SetQuitPoint(levelManager.CurrentLevel->QuitPoint);

	Global::Init = true;
	
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
			else {
				if (event.type == sf::Event::KeyReleased) {
					HandleKeyReleased(&playerOne, event.key.code);
				}
				else {
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
			}

			

			
			
		}

		spriteManager.ClearWindow();
		playerOne.Draw((float)deltaTime.asMilliseconds());
		if (Global::Init) {
			playerOne.GoSpawn();
			Global::Init = false;
		}
		spriteManager.DrawAll();
		window = spriteManager.GetMainWindow();

		if (Global::Win) {
			if (levelManager.CurrentLevel->NextLevel == NULL)
				exit(EXIT_SUCCESS);
			spriteManager.NextLevel();
			levelManager.CurrentLevel = levelManager.CurrentLevel->NextLevel;
			spriteManager.Load(levelManager.CurrentLevel);
			window = spriteManager.GetMainWindow();
			playerOne.SetSpawn(levelManager.CurrentLevel->SpawnPoint);
			playerOne.GoSpawn();
			playerOne.SetExitPoint(levelManager.CurrentLevel->ExitPoint);
			playerOne.SetQuitPoint(levelManager.CurrentLevel->QuitPoint);
			playerOne.SetObstacles(levelManager.CurrentLevel->ObstacleList);
			playerOne.SetTraps(levelManager.CurrentLevel->TrapList);
			Physics::boxPlayer = 5 * Global::Scale;
			Global::Win = false;
			Global::Init = true;
		}
	}

	return 0;
}