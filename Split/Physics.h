#pragma once
#include <vector>
#include "Sprite.h"
#include "Global.h"
typedef struct obstacle{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
} Obstacle;

class Physics
{
	std::vector<Obstacle*> obstacleList;
	float _strenght = 0;
public:
	Physics();
	~Physics();
	void AddObstacle(float posX,float posY,float sizeX,float sizeY);
	void AddForce(float strenght);
	bool UpdateGravity(Sprite* sprite, float deltaTime);
	void MoveX(Sprite* sprite,float speed);
	bool MoveY(Sprite* sprite, float speed);
	bool CheckObstacle(float posX, float posY);
	float GetVelocity();
};
