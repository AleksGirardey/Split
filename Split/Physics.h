#pragma once
#include <vector>
#include "Sprite.h"
#include "Global.h"
#include "Pair.h"

typedef struct obstacle{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
} Obstacle;

class Physics
{
	std::vector<Obstacle*> obstacleList;
	std::vector<Obstacle*> trapList;
	Pair* _exitPoint;
	Pair* _quitPoint;

	float _strenght = 0;
public:
	static float boxPlayer;
	Physics();
	~Physics();
	void AddObstacle(float posX,float posY,float sizeX,float sizeY);
	void AddTrap(float posX, float posY, float sizeX, float sizeY);

	void AddForce(float strenght);
	bool UpdateGravity(Sprite* sprite, float deltaTime);
	void MoveX(Sprite* sprite,float speed);
	bool MoveY(Sprite* sprite, float speed);
	bool CheckObstacle(float posX, float posY);
	bool CheckTrigger(float posX, float posY);
	bool CheckExit(float posX, float posY);
	bool CheckQuit(float posX, float posY);
	float GetVelocity();

	void SetObstacles(std::vector<Obstacle*> list);
	void SetTraps(std::vector<Obstacle*> list);
	void SetExitPoint(Pair* pair);
	void SetQuitPoint(Pair* pair);
};

