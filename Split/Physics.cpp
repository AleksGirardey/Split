#include "Physics.h"

Physics::Physics()
{
	_strenght = 0;
}


Physics::~Physics()
{
}
float Physics::boxPlayer = 10 * Global::Scale;

void Physics::AddObstacle(float posX, float posY, float sizeX, float sizeY) {
	Obstacle* obs = new Obstacle();
	obs->posX = posX;
	obs->posY = posY;
	obs->sizeX = sizeX;
	obs->sizeY = sizeY;
	obstacleList.push_back(obs);
}
void Physics::AddTrap(float posX, float posY, float sizeX, float sizeY) {
	Obstacle* obs = new Obstacle();
	obs->posX = posX;
	obs->posY = posY;
	obs->sizeX = sizeX;
	obs->sizeY = sizeY;
	trapList.push_back(obs);
}
void Physics::AddForce(float strenght) {
	if (_strenght < 0) {
		_strenght = 0;
	}
	_strenght += strenght;
}
bool Physics::UpdateGravity(Sprite* sprite, float deltaTime) {
	if (_strenght > 0) {
		_strenght -= (PLAYER_MASS*deltaTime* Global::Scale);
		if (MoveY(sprite, -PLAYER_MASS*deltaTime* Global::Scale* 2)) {
			_strenght = 0;
		}
	}
	else {
		MoveY(sprite, PLAYER_MASS*deltaTime* Global::Scale*2);
	}
	return false;
}
void Physics::MoveX(Sprite* sprite, float speed) {
	if(CheckObstacle(sprite->getPosX() + speed,sprite->getPosY()))
		sprite->setPosX(sprite->getPosX() + speed);
}
bool Physics::MoveY(Sprite* sprite, float speed) {
	int diviser = 10 * PLAYER_MASS*2;

	if (CheckObstacle(sprite->getPosX(), sprite->getPosY() + speed)) {
		for (int i = 1; i <= diviser; i++) {
			if (CheckObstacle(sprite->getPosX(), sprite->getPosY() + (speed / diviser))) {
				sprite->setPosY(sprite->getPosY() + (speed / diviser));
				return false;
			}
		}
	}
	else {
		for (int i = 1; i <= diviser;i++) {
			if (CheckObstacle(sprite->getPosX(), sprite->getPosY() + (speed/ diviser))) {
				sprite->setPosY(sprite->getPosY() + (speed /diviser));
				return false;
			}
		}
	}
	return true;
}

bool Physics::CheckObstacle(float posX, float posY) {
	for (int i = 0; i < obstacleList.size();i++) {
		bool xCheck = posX+ Physics::boxPlayer < obstacleList[i]->posX + obstacleList[i]->sizeX && posX+ Physics::boxPlayer >= obstacleList[i]->posX;
		xCheck = xCheck ||  posX+ obstacleList[i]->sizeX- Physics::boxPlayer < obstacleList[i]->posX + obstacleList[i]->sizeX && posX+ obstacleList[i]->sizeX - Physics::boxPlayer >= obstacleList[i]->posX;
		bool yCheck = posY+ Physics::boxPlayer >= obstacleList[i]->posY && posY+ Physics::boxPlayer < obstacleList[i]->posY + obstacleList[i]->sizeY;
		yCheck = yCheck || posY + obstacleList[i]->sizeY >= obstacleList[i]->posY && posY + obstacleList[i]->sizeY < obstacleList[i]->posY + obstacleList[i]->sizeY;
		if (xCheck && yCheck) {
			return false;
		}
	}
	return true;
}
bool Physics::CheckTrigger(float posX, float posY) {
	for (int i = 0; i < trapList.size(); i++) {
		bool xCheck = posX + Physics::boxPlayer < trapList[i]->posX + trapList[i]->sizeX && posX + Physics::boxPlayer >= trapList[i]->posX;
		xCheck = xCheck || posX + trapList[i]->sizeX - Physics::boxPlayer < trapList[i]->posX + trapList[i]->sizeX && posX + trapList[i]->sizeX - Physics::boxPlayer >= trapList[i]->posX;
		bool yCheck = posY + Physics::boxPlayer >= trapList[i]->posY && posY + Physics::boxPlayer < trapList[i]->posY + trapList[i]->sizeY;
		yCheck = yCheck || posY + trapList[i]->sizeY >= trapList[i]->posY && posY + trapList[i]->sizeY < trapList[i]->posY + trapList[i]->sizeY;
		if (xCheck && yCheck) {
			return false;
		}
	}
	return true;
}

bool Physics::CheckExit(float posX, float posY) {
	int size = SPRITESHEET_CELL_SIZE * Global::Scale;
	bool xCheck = (posX + Physics::boxPlayer < _exitPoint->GetKey() * size + size) && (posX + Physics::boxPlayer >= _exitPoint->GetKey() * size);
	bool yCheck = (posY + Physics::boxPlayer >= _exitPoint->GetValue() * size) && (posY + Physics::boxPlayer < _exitPoint->GetValue() * size + size);

	xCheck = xCheck || 
		(posX + size - Physics::boxPlayer < _exitPoint->GetKey() * size + size) && (posX + size - Physics::boxPlayer >= _exitPoint->GetKey() * size);

	yCheck = yCheck || 
		(posY + size >= _exitPoint->GetValue() * size) && (posY + size < _exitPoint->GetValue() * size + size);
	
	if (xCheck && yCheck) return true;
	return false;
}

bool Physics::CheckQuit(float posX, float posY) {
	int size = SPRITESHEET_CELL_SIZE * Global::Scale;
	bool xCheck = (posX + Physics::boxPlayer < _quitPoint->GetKey() * size + size) && (posX + Physics::boxPlayer >= _quitPoint->GetKey() * size);
	bool yCheck = (posY + Physics::boxPlayer >= _quitPoint->GetValue() * size) && (posY + Physics::boxPlayer < _quitPoint->GetValue() * size + size);

	xCheck = xCheck || 
		(posX + size - Physics::boxPlayer< _quitPoint->GetKey() * size + size) && (posX + size - Physics::boxPlayer >= _quitPoint->GetKey() * size);

	yCheck = yCheck || 
		(posY + size >= _quitPoint->GetValue() * size) && (posY + size < _quitPoint->GetValue() * size + size);
	
	if (xCheck && yCheck) return true;
	return false;
}

bool Physics::CheckEasy(float posX, float posY) {
	if (_p3Point == NULL) return false;
	int size = SPRITESHEET_CELL_SIZE * Global::Scale;
	bool xCheck = (posX + Physics::boxPlayer < _easyPoint->GetKey() * size + size) && (posX + Physics::boxPlayer >= _easyPoint->GetKey() * size);
	bool yCheck = (posY + Physics::boxPlayer >= _easyPoint->GetValue() * size) && (posY + Physics::boxPlayer < _easyPoint->GetValue() * size + size);

	xCheck = xCheck ||
		(posX + size - Physics::boxPlayer < _easyPoint->GetKey() * size + size) && (posX + size - Physics::boxPlayer >= _easyPoint->GetKey() * size);

	yCheck = yCheck ||
		(posY + size >= _easyPoint->GetValue() * size) && (posY + size < _easyPoint->GetValue() * size + size);

	if (xCheck && yCheck) return true;
	return false;
}

bool Physics::CheckHard(float posX, float posY) {
	if (_hardPoint == NULL) return false;
	int size = SPRITESHEET_CELL_SIZE * Global::Scale;
	bool xCheck = (posX + Physics::boxPlayer < _hardPoint->GetKey() * size + size) && (posX + Physics::boxPlayer >= _hardPoint->GetKey() * size);
	bool yCheck = (posY + Physics::boxPlayer >= _hardPoint->GetValue() * size) && (posY + Physics::boxPlayer < _hardPoint->GetValue() * size + size);

	xCheck = xCheck ||
		(posX + size - Physics::boxPlayer < _hardPoint->GetKey() * size + size) && (posX + size - Physics::boxPlayer >= _hardPoint->GetKey() * size);

	yCheck = yCheck ||
		(posY + size >= _hardPoint->GetValue() * size) && (posY + size < _hardPoint->GetValue() * size + size);

	if (xCheck && yCheck) return true;
	return false;
}

bool Physics::CheckPlayerOne(float posX, float posY) {
	if (_p1Point == NULL) return false;
	int size = SPRITESHEET_CELL_SIZE * Global::Scale;
	bool xCheck = (posX + Physics::boxPlayer < _p1Point->GetKey() * size + size) && (posX + Physics::boxPlayer >= _p1Point->GetKey() * size);
	bool yCheck = (posY + Physics::boxPlayer >= _p1Point->GetValue() * size) && (posY + Physics::boxPlayer < _p1Point->GetValue() * size + size);

	xCheck = xCheck ||
		(posX + size - Physics::boxPlayer < _p1Point->GetKey() * size + size) && (posX + size - Physics::boxPlayer >= _p1Point->GetKey() * size);

	yCheck = yCheck ||
		(posY + size >= _p1Point->GetValue() * size) && (posY + size < _p1Point->GetValue() * size + size);

	if (xCheck && yCheck) return true;
	return false;
}

bool Physics::CheckPlayerTwo(float posX, float posY) {
	if (_p2Point == NULL) return false;
	int size = SPRITESHEET_CELL_SIZE * Global::Scale;
	bool xCheck = (posX + Physics::boxPlayer < _p2Point->GetKey() * size + size) && (posX + Physics::boxPlayer >= _p2Point->GetKey() * size);
	bool yCheck = (posY + Physics::boxPlayer >= _p2Point->GetValue() * size) && (posY + Physics::boxPlayer < _p2Point->GetValue() * size + size);

	xCheck = xCheck ||
		(posX + size - Physics::boxPlayer < _p2Point->GetKey() * size + size) && (posX + size - Physics::boxPlayer >= _p2Point->GetKey() * size);

	yCheck = yCheck ||
		(posY + size >= _p2Point->GetValue() * size) && (posY + size < _p2Point->GetValue() * size + size);

	if (xCheck && yCheck) return true;
	return false;
}

bool Physics::CheckPlayerThree(float posX, float posY) {
	if (_p3Point == NULL) return false;
	int size = SPRITESHEET_CELL_SIZE * Global::Scale;
	bool xCheck = (posX + Physics::boxPlayer < _p3Point->GetKey() * size + size) && (posX + Physics::boxPlayer >= _p3Point->GetKey() * size);
	bool yCheck = (posY + Physics::boxPlayer >= _p3Point->GetValue() * size) && (posY + Physics::boxPlayer < _p3Point->GetValue() * size + size);

	xCheck = xCheck ||
		(posX + size - Physics::boxPlayer < _p3Point->GetKey() * size + size) && (posX + size - Physics::boxPlayer >= _p3Point->GetKey() * size);

	yCheck = yCheck ||
		(posY + size >= _p3Point->GetValue() * size) && (posY + size < _p3Point->GetValue() * size + size);

	if (xCheck && yCheck) return true;
	return false;
}

float Physics::GetVelocity() {
	return _strenght;
}

void Physics::SetObstacles(std::vector<Obstacle*> list) {
	obstacleList = list;
}

void Physics::SetTraps(std::vector<Obstacle*> list) {
	trapList = list;
}

void Physics::SetExitPoint(Pair* pair) { _exitPoint = pair; }
void Physics::SetQuitPoint(Pair* pair) { _quitPoint = pair; }
void Physics::SetEasyDifficultyPoint(Pair* pair) { _easyPoint = pair; }
void Physics::SetHardDifficultyPoint(Pair* pair) { _hardPoint = pair; }
void Physics::SetPlayerOnePoint(Pair* pair) { _p1Point = pair; }
void Physics::SetPlayerTwoPoint(Pair* pair) { _p2Point = pair; }
void Physics::SetPlayerThreePoint(Pair* pair) { _p3Point = pair; }