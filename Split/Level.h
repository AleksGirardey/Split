#pragma once
#include <fstream>
#include "Pair.h"
#include "Physics.h"
#include <list>

#define SPAWNINDEX 294
#define EXITINDEX 241
#define TRAPINDEX 165

class Level {
private:
	int _width;
	int _height;
	unsigned** _map;
	std::list<int> _layerZero;
	std::list<int> _layerTwo;

	void CheckTile(unsigned rawIndex, int posX, int posY);
	void LoadFromCSV(std::string path);

public:
	Level(std::string path, int chunkSize, int chunkCount, int scale, Level* nextLevel);
	~Level();

	int ChunkCount;
	int ChunkSize;
	int Scale;
	Pair* SpawnPoint;
	Pair* ExitPoint;
	Level* NextLevel;
	std::vector<Obstacle*> ObstacleList;
	std::vector<Obstacle*> TrapList;

	std::list<Sprite*> Load();
};