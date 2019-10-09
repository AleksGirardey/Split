#include "Player.h"

Player::Player(SpriteManager* spriteManager, Animator* animator, Physics* physics) :
	_state(IDLE),
	_idle(true),
	_left(false),
	_right(false),
	_up(false),
	_down(false),
	_spriteManager(spriteManager),
	_animator(animator),
	_physics(physics)
{
	_sprite = new Sprite(0, 0.f, 0.f, false, false, false, 1);
}

Player::Player(SpriteManager* spriteManager, Animator* animator, Physics* physics, int posX, int posY) :
	_state(IDLE),
	_idle(true),
	_left(false),
	_right(false),
	_up(false),
	_jump(false),
	_down(false),
	_spriteManager(spriteManager),
	_animator(animator),
	_physics(physics)
{
	_sprite = new Sprite(
		0,
		(float)(posX * SPRITESHEET_CELL_SIZE * SCALE), 
		(float)(posY * SPRITESHEET_CELL_SIZE * SCALE),
		false,
		false,
		false,
		1);
}

Player::~Player() {
	delete _sprite;
}

void Player::goingRight() {
	_right = true;
	_left = false;
	_state = MOVE;
	_idle = false;
}

void Player::goingLeft() {
	_right = false;
	_left = true;
	_state = MOVE;
	_idle = false;
}

void Player::goingUp() {
	_up = true;
	_down = false;
	_state = MOVE;
	_idle = false;
}

void Player::goingDown() {
	_up = false;
	_down = true;
	_state = MOVE;
	_idle = false;
}

void Player::idle(Movements movement) {
	switch (movement) {
		case UP: _up = false; break;
		case DOWN: _down = false; break;
		case LEFT: _left = false; break;
		case RIGHT: _right = false; break;
		default: break;
	}
	if (!_up && !_down && !_left && !_right) {
		_state = IDLE;
		_idle = true;
	}
}

void Player::Draw(float deltaTime) {
	bool goingLeft = false;

	//Movement
	if (_left) _physics->MoveX(_sprite,-(PLAYER_SPEED * deltaTime));
	if (_right) _physics->MoveX(_sprite, (PLAYER_SPEED * deltaTime));
	if (_up && !_jump) {
		_jump = true;
		_physics->AddForce(PLAYER_JUMP);
	}
	//if (_down) _sprite->setPosY(_sprite->getPosY() + (PLAYER_SPEED * deltaTime));
	if (_physics->GetVelocity() <= 0) {
		if (!_physics->CheckObstacle(_sprite->getPosX(),_sprite->getPosY()+PLAYER_MASS*deltaTime)) {
			_jump = false;
		}
	}
	 _physics->UpdateGravity(_sprite, deltaTime);

	//Clamp
	ClampX(_sprite);
	ClampY(_sprite);

	_sprite->setFlipH(_left);

	_sprite->setIndex(_animator->GetTile(_state, deltaTime));
	_spriteManager->AddPlayer(*_sprite);
}

void	Player::ClampX(Sprite* sprite) {
	if (sprite->getPosX() < 0) sprite->setPosX(0);
	else if (sprite->getPosX() > (float)((SCREEN_WIDTH - 1) * SPRITESHEET_CELL_SIZE * SCALE))
		sprite->setPosX((SCREEN_WIDTH - 1) * SPRITESHEET_CELL_SIZE * SCALE);
}

void 	Player::ClampY(Sprite* sprite) {
	if (sprite->getPosY() < 0) sprite->setPosY(0);
	else if (sprite->getPosY() > (float)((SCREEN_HEIGHT - 1) * SPRITESHEET_CELL_SIZE * SCALE))
		sprite->setPosY((SCREEN_HEIGHT - 1) * SPRITESHEET_CELL_SIZE * SCALE);
}

void Player::GoSpawn() {
	_sprite->setPosX(0);
	_sprite->setPosY(0);
}