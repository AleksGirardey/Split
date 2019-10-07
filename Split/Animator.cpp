#include "Animator.h"

Animator::Animator(const char idle[],const char move[],const char jump[],const char death[], float speed) :
	_lastState(IDLE),
	_tileCount(0),
	_elapsedTime(0),
	_speed(speed)
{
	_idle = ParseArg(idle);
	_move = ParseArg(move);
	_jump = ParseArg(jump);
	_death = ParseArg(death);
}

Animator::~Animator() {
	delete _idle.frames;
	delete _move.frames;
	delete _jump.frames;
	delete _death.frames;
}

Animation	Animator::ParseArg(const char args[]) {
	std::string arguments(args);
	int count = std::count(arguments.begin(), arguments.end(), ',') + 1;
	Animation animation = { new int[count], count };
	int lastPos = 0;
	int separatorPos = 0;

	for (int i = 0; i < count; i++) {
		separatorPos = arguments.find(",");
		if (separatorPos != std::string::npos) {
			animation.frames[i] = std::stoi(arguments.substr(lastPos, separatorPos - lastPos));
			lastPos = separatorPos + 1;
		} else
			animation.frames[i] = std::stoi(arguments.substr(lastPos));
	}
	animation.count = count;
	
	return animation;
}

int Animator::GetTile(AnimationState state, float deltaTime) {
	if (state != _lastState) {
		_tileCount = 0;
		_elapsedTime = 0.f;
		_lastState = state;
	} else {
		_elapsedTime += _speed * deltaTime;
		if (_elapsedTime >= ANIMATION_FRAMERATE) {
			_tileCount++;
			_elapsedTime = 0.f;
		}
	}

	switch (state) {
		case IDLE:
			return GetIdle(); break;
		case MOVE:
			return GetMove(); break;
		case JUMP:
			return GetJump(); break;
		case DEATH:
			return GetDeath(); break;
		default:
			return GetIdle(); break;
	}
}

int Animator::GetIdle() {
	if (_tileCount > _idle.count - 1) {
		_tileCount = 0;
	}
	return _idle.frames[_tileCount];
}

int Animator::GetMove() {
	if (_tileCount > _move.count - 1) {
		_tileCount = 0;
	}
	return _move.frames[_tileCount];
}

int Animator::GetJump() {
	if (_tileCount > _jump.count - 1) {
		_tileCount = 0;
	}
	return _jump.frames[_tileCount];
}

int Animator::GetDeath() {
	if (_tileCount > _death.count - 1) {
		_tileCount = 0;
	}
	return _death.frames[_tileCount];
}