#include "LevelManager.h"

LevelParams LevelManager::Menu = { "./Assets/Menu.csv", 12, 1, 5 };
LevelParams LevelManager::LevelOne = { "./Assets/LevelOne.csv", 4, 2, 4 };
LevelParams LevelManager::LevelTwo = { "./Assets/LevelTwo.csv", 4, 4, 2 };
LevelParams LevelManager::LevelThree = { "./Assets/LevelThree.csv", 4, 6, 1 };
bool LevelManager::menuActive = true;

LevelManager::LevelManager() {
	Level* three = new Level(LevelThree.path, LevelThree.chunkSize, LevelThree.chunkCount, LevelThree.scale, NULL);
	Level* two = new Level(LevelTwo.path, LevelTwo.chunkSize, LevelTwo.chunkCount, LevelTwo.scale, three);
	Level* one = new Level(LevelOne.path, LevelOne.chunkSize, LevelOne.chunkCount, LevelOne.scale, two);
	Level* menu = new Level(Menu.path, Menu.chunkSize, Menu.chunkCount, Menu.scale, one);
	firstLevel = menu;
	CurrentLevel = menu;
}

LevelManager::~LevelManager() {
	delete firstLevel;
}