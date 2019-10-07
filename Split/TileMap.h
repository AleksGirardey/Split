#pragma once
#include <iostream>
#include <fstream>

#include "SpriteManager.h"

class TileMap
{
private:
	SpriteManager* _spriteManager;
	int _width;
	int _height;
	unsigned** _map;
	std::list<int> _layerZero;
	std::list<int> _layerTwo;
public:
	TileMap(SpriteManager* spriteManager);
	~TileMap();

	void LoadFromCSV(std::string path);
	void DrawMap();
};