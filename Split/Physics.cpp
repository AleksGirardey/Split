#include "Physics.h"

Physics::Physics()
{
	_strenght = 0;
}


Physics::~Physics()
{
}

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
		_strenght -= (PLAYER_MASS*deltaTime);
		if (MoveY(sprite, -PLAYER_MASS*deltaTime-1.5f)) {
			_strenght = 0;
		}
	}
	else {
		MoveY(sprite, PLAYER_MASS*deltaTime+1.5f);
	}
	return false;
}
void Physics::MoveX(Sprite* sprite, float speed) {
	if(CheckObstacle(sprite->getPosX() + speed,sprite->getPosY()))
		sprite->setPosX(sprite->getPosX() + speed);
}
bool Physics::MoveY(Sprite* sprite, float speed) {
	int diviser = 10 * PLAYER_MASS;
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
		bool xCheck = posX+6 < obstacleList[i]->posX + obstacleList[i]->sizeX && posX+6 >= obstacleList[i]->posX;
		xCheck = xCheck ||  posX+ obstacleList[i]->sizeX-6 < obstacleList[i]->posX + obstacleList[i]->sizeX && posX+ obstacleList[i]->sizeX - 6 >= obstacleList[i]->posX;
		bool yCheck = posY+6 >= obstacleList[i]->posY && posY+6 < obstacleList[i]->posY + obstacleList[i]->sizeY;
		yCheck = yCheck || posY + obstacleList[i]->sizeY >= obstacleList[i]->posY && posY + obstacleList[i]->sizeY < obstacleList[i]->posY + obstacleList[i]->sizeY;
		if (xCheck && yCheck) {
			return false;
		}
	}
	return true;
}
bool Physics::CheckTrigger(float posX, float posY) {
	for (int i = 0; i < trapList.size(); i++) {
		bool xCheck = posX + 6 < trapList[i]->posX + trapList[i]->sizeX && posX + 6 >= trapList[i]->posX;
		xCheck = xCheck || posX + trapList[i]->sizeX - 6 < trapList[i]->posX + trapList[i]->sizeX && posX + trapList[i]->sizeX - 6 >= trapList[i]->posX;
		bool yCheck = posY + 6 >= trapList[i]->posY && posY + 6 < trapList[i]->posY + trapList[i]->sizeY;
		yCheck = yCheck || posY + trapList[i]->sizeY >= trapList[i]->posY && posY + trapList[i]->sizeY < trapList[i]->posY + trapList[i]->sizeY;
		if (xCheck && yCheck) {
			return false;
		}
	}
	return true;
}

bool Physics::CheckExit(float posX, float posY) {
	int size = SPRITESHEET_CELL_SIZE * Global::Scale;
	bool xCheck = (posX + 6 < _exitPoint->GetKey() + size) && (posX + 6 >= _exitPoint->GetKey());
	bool yCheck = (posY + 6 >= _exitPoint->GetValue()) && (posY + 6 < _exitPoint->GetValue() + size);

	xCheck = xCheck || 
		(posX + size - 6 < _exitPoint->GetKey() + size) && (posX + size - 6 >= _exitPoint->GetKey());

	yCheck = yCheck || 
		(posY + size >= _exitPoint->GetValue()) && (posY + size < _exitPoint->GetValue() + size);
	
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