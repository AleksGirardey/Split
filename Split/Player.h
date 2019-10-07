#pragma once
#include "Global.h"
#include "SpriteManager.h"
#include "Animator.h"
#include "Sprite.h"

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
	bool _left;
	bool _right;
	bool _up;
	bool _down;
	bool _idle;
	bool _jump;
	float _jumpValue;
	AnimationState _state;

	void ClampX(Sprite*);
	void ClampY(Sprite*);
public:
	Player(SpriteManager* spriteManager, Animator* animator);
	Player(SpriteManager* spriteManager, Animator* animator, int posX, int posY);
	~Player();

	void goingRight();
	void goingLeft();
	void goingUp();
	void goingDown();
	void idle(Movements);

	void Draw(float deltaTime);
};