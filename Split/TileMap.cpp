#include "TileMap.h"

TileMap::TileMap(SpriteManager* spriteSheet) :
	_spriteManager(spriteSheet),
	_width(SCREEN_WIDTH),
	_height(SCREEN_HEIGHT)
{
	// Insertion des tiles concerné par le layer 0 et 2
	_layerZero = std::list<int>();
	_layerTwo = std::list<int>();

	_layerZero.push_back(0);
	_layerZero.push_back(1);
	_layerZero.push_back(2);
	_layerZero.push_back(3);
	_layerZero.push_back(4);
	_layerZero.push_back(5);
	_layerZero.push_back(6);
	_layerZero.push_back(7);
	_layerZero.push_back(8);
	_layerZero.push_back(9);
	_layerZero.push_back(10);
	_layerZero.push_back(11);
	_layerZero.push_back(12);
	_layerZero.push_back(40);
	_layerZero.push_back(41);
	_layerZero.push_back(42);
	_layerZero.push_back(43);
	_layerZero.push_back(44);
	_layerZero.push_back(166);
	_layerZero.push_back(196);

	_layerTwo.push_back(357);
	_layerTwo.push_back(358);
	_layerTwo.push_back(359);
	_layerTwo.push_back(384);
	_layerTwo.push_back(385);
	_layerTwo.push_back(490);
	_layerTwo.push_back(491);
	_layerTwo.push_back(492);

	_map = new unsigned* [_height + 1];
	for (int i = 0; i < _height; ++i) {
		_map[i] = new unsigned[_width + 1];
		for (int j = 0; j < _width; j++)
			_map[i][j] = 35l;
	}
}

TileMap::~TileMap() {
	for (int i = _height - 1; i >= 0; --i) {
		delete[] _map[i];
	}
	delete[] _map;
}

void TileMap::LoadFromCSV(std::string path) {
	std::ifstream stream(path);
	std::string line = "";
	std::string strTileIndex = "";
	int endPos = 0;
	int tileX = 0;
	int tileY = 0;
	if (stream.is_open()) {
		while (std::getline(stream, line)) {
			tileX = 0;
			while (endPos != std::string::npos && tileX < _width) {
				endPos = line.find(",");
				strTileIndex = line.substr(0, endPos);
				line = line.substr(endPos + 1);
				//std::cout << "TileIndex : " << strTileIndex << std::endl;
				_map[tileY][tileX] = std::stoul(strTileIndex);
				tileX++;
			}
			//_map[tileY][tileX] = std::stol(line);
			tileY++;
			endPos = 0;
		}
	}

	stream.close();
}

void TileMap::DrawMap(Physics* physic) {
	Sprite* sprite;
	int tileIndex = 0;
	float posX = 0;
	float posY = 0;
	unsigned rawIndex = 0;
	bool flipH = false;
	bool flipV = false;
	bool flipD = false;
	int layer = 1;

	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			layer = 1;
			rawIndex = _map[i][j];
			flipH = rawIndex & FLIPPED_H;
			flipV = rawIndex & FLIPPED_V;
			flipD = rawIndex & FLIPPED_D;
			rawIndex &= ~(FLIPPED_H | FLIPPED_V | FLIPPED_D);
			tileIndex = (int)rawIndex;
			
			posX = (float)(j * SPRITESHEET_CELL_SIZE * SCALE);
			posY = (float)(i * SPRITESHEET_CELL_SIZE * SCALE);

			for (std::list<int>::iterator it = _layerZero.begin(); it != _layerZero.end(); it++) {
				if ((tileIndex - 1) == *it)
					layer = 0;
			}
			for (std::list<int>::iterator it = _layerTwo.begin(); it != _layerTwo.end(); it++) {
				if ((tileIndex - 1) == *it)
					layer = 2;
			}
			if (tileIndex == 417) {
				physic->AddObstacle(posX, posY, SPRITESHEET_CELL_SIZE * SCALE, SPRITESHEET_CELL_SIZE * SCALE);
			}
			if (tileIndex == 166) {
				physic->AddTrap(posX, posY, SPRITESHEET_CELL_SIZE * SCALE, SPRITESHEET_CELL_SIZE * SCALE);
			}
			sprite = new Sprite(tileIndex - 1, posX, posY, flipH, flipV, flipD, layer);
			_spriteManager->AddStaticElement(*sprite);
		}
	}
}