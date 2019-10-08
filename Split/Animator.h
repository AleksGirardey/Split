#pragma once
#include <string>
#include "Global.h"

#define ANIMATION_FRAMERATE 60
#define ANIMATION_SPEED 0.2

enum AnimationState {
	IDLE,
	MOVE,
	JUMP,
	DEATH
};

typedef struct Animation {
	int* frames;
	int count;
} Animation;

class Animator {
private:
	AnimationState _lastState;
	int _tileCount;
	Animation _idle;
	Animation _move;
	Animation _jump;
	Animation _death;
	float _elapsedTime;
	float _speed;

	Animation ParseArg(const char args[]);
public:
	Animator(const char idle[], const char move[], const char jump[], const char death[], float speed);
	~Animator();

	int GetTile(AnimationState state, float deltaTime);
	int GetIdle();
	int GetMove();
	int GetJump();
	int GetDeath();
};