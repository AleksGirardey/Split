#pragma once
#include "Level.h"

typedef struct levelParams {
	std::string path;
	int chunkSize;
	int chunkCount;
	int scale;
} LevelParams;

class LevelManager {
private:
	static LevelParams Menu;
	static LevelParams LevelOne;
	static LevelParams LevelTwo;
	static LevelParams LevelThree;

	Level* firstLevel;

public:
	LevelManager();
	~LevelManager();

	Level* CurrentLevel;
	static bool menuActive;
};