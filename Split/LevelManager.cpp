#include "LevelManager.h"

LevelParams LevelManager::LevelOne = { "./Assets/LevelOne.csv", 4, 2, 4 };
LevelParams LevelManager::LevelTwo = { "./Assets/LevelTwo.csv", 4, 4, 2 };
LevelParams LevelManager::LevelThree = { "./Assets/LevelThree.csv", 4, 6, 1 };

LevelManager::LevelManager() {
	Level* three = new Level(LevelThree.path, LevelThree.chunkSize, LevelThree.chunkCount, LevelThree.scale, NULL);
	Level* two = new Level(LevelTwo.path, LevelTwo.chunkSize, LevelTwo.chunkCount, LevelTwo.scale, three);
	Level* one = new Level(LevelOne.path, LevelOne.chunkSize, LevelOne.chunkCount, LevelOne.scale, two);

	firstLevel = one;
	CurrentLevel = one;
}

LevelManager::~LevelManager() {
	delete firstLevel;
}