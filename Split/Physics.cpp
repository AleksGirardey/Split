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
void Physics::AddForce(float strenght) {
	if (_strenght < 0) {
		_strenght = 0;
	}
	_strenght += strenght;
}
bool Physics::UpdateGravity(Sprite* sprite, float deltaTime) {
	if (_strenght > 0) {
		_strenght -= (PLAYER_MASS*deltaTime);
		if (MoveY(sprite, -PLAYER_MASS*deltaTime)) {
			_strenght = 0;
		}
	}
	else {
		MoveY(sprite, PLAYER_MASS*deltaTime);
	}
	return false;
}
void Physics::MoveX(Sprite* sprite, float speed) {
	if(CheckObstacle(sprite->getPosX() + speed,sprite->getPosY()))
		sprite->setPosX(sprite->getPosX() + speed);
}
bool Physics::MoveY(Sprite* sprite, float speed) {
	if (CheckObstacle(sprite->getPosX(), sprite->getPosY() + speed)) {
		sprite->setPosY(sprite->getPosY() + speed);
		return false;
	}
	else {
		for (int i = 1; i < 10;i++) {
			if (CheckObstacle(sprite->getPosX(), sprite->getPosY() + (speed/10))) {
				sprite->setPosY(sprite->getPosY() + (speed / 10));
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
float Physics::GetVelocity() {
	return _strenght;
}


