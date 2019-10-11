#pragma once
#include "Global.h"
#include "SpriteManager.h"
#include "Animator.h"
#include "Sprite.h"
#include "Physics.h"

#include <string>
#include <iostream>

enum Movements {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Player
{
private:
	Sprite* _sprite;
	SpriteManager* _spriteManager;
	Animator* _animator;
	Physics* _physics;

	Pair* _spawnPoint;
	Pair* _exitPoint;
	Pair* _quitPoint;

	bool _left;
	bool _right;
	bool _up;
	bool _down;
	bool _idle;
	bool _jump;
	float _jumpValue;
	float _timeToSpawn = 0;
	bool _isDead = false;
	AnimationState _state;

	void ClampX(Sprite*);
	void ClampY(Sprite*);
public:
	Player(SpriteManager* spriteManager, Animator* animator, Physics* physics);
	Player(SpriteManager* spriteManager, Animator* animator, Physics* physics, Pair* spawn, Pair* exit);
	~Player();

	void goingRight();
	void goingLeft();
	void goingUp();
	void goingDown();
	void idle(Movements);

	void SetAnimator(Animator*);
	void SetObstacles(std::vector<Obstacle*>);
	void SetTraps(std::vector<Obstacle*>);
	void SetSpawn(Pair*);
	void SetExitPoint(Pair*);
	void SetQuitPoint(Pair*);
	void SetEasyDifficultyPoint(Pair*);
	void SetHardDifficultyPoint(Pair*);
	void SetPlayerOnePoint(Pair*);
	void SetPlayerTwoPoint(Pair*);
	void SetPlayerThreePoint(Pair*);

	void GoSpawn();
	void Draw(float deltaTime);
};