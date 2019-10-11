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

Player::Player(SpriteManager* spriteManager, Animator* animator, Physics* physics, Pair* spawn, Pair* exit) :
	_state(IDLE),
	_idle(true),
	_left(false),
	_right(false),
	_up(false),
	_jump(false),
	_down(false),
	_spriteManager(spriteManager),
	_animator(animator),
	_physics(physics),
	_spawnPoint(spawn),
	_exitPoint(exit)
{
	float newPosY = (float)(spawn->GetValue() * SPRITESHEET_CELL_SIZE * Global::Scale);

	_sprite = new Sprite(
		0,
		(float)(spawn->GetKey() *SPRITESHEET_CELL_SIZE * Global::Scale),
		newPosY - 1.f,
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

void Player::SetObstacles(std::vector<Obstacle*> obstacles) {
	_physics->SetObstacles(obstacles);
}

void Player::SetTraps(std::vector<Obstacle*> traps) {
	_physics->SetTraps(traps);
}

void Player::Draw(float deltaTime) {
	bool goingLeft = false;

	//Movement
	if (_left) _physics->MoveX(_sprite,-(PLAYER_SPEED * deltaTime*Global::Scale));
	if (_right) _physics->MoveX(_sprite, (PLAYER_SPEED * deltaTime*Global::Scale));
	if (_up && !_jump) {
		_jump = true;
		_physics->AddForce(PLAYER_JUMP*Global::Scale);
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

	_spriteManager->AddPlayer(_sprite);

	if (!_physics->CheckTrigger(_sprite->getPosX(),_sprite->getPosY())) {
		GoSpawn();
	}

	if (_physics->CheckExit(_sprite->getPosX(), _sprite->getPosY())) {
		std::cout << "Exit triggered" << std::endl;
		Global::Win = true;
	}

	if (_quitPoint != NULL && _physics->CheckQuit(_sprite->getPosX(), _sprite->getPosY()))
		exit(EXIT_SUCCESS);
}

void	Player::ClampX(Sprite* sprite) {
	if (sprite->getPosX() < 0) sprite->setPosX(0);
	else if (sprite->getPosX() > (float)(Global::ChunkCount * Global::ChunkSize * SPRITESHEET_CELL_SIZE * Global::Scale))
		sprite->setPosX(Global::ChunkCount * (Global::ChunkSize - 1) * SPRITESHEET_CELL_SIZE * Global::Scale);
}

void 	Player::ClampY(Sprite* sprite) {
	if (sprite->getPosY() < 0) sprite->setPosY(0);
	else if (sprite->getPosY() > (float)(Global::ChunkCount * Global::ChunkSize * SPRITESHEET_CELL_SIZE * Global::Scale))
		sprite->setPosY(Global::ChunkCount * (Global::ChunkSize - 1) * SPRITESHEET_CELL_SIZE * Global::Scale);
}

void Player::SetSpawn(Pair* pair) { _spawnPoint = pair; }

void Player::SetExitPoint(Pair* pair) {
	_exitPoint = pair;
	_physics->SetExitPoint(pair);
}

void Player::SetQuitPoint(Pair* pair) {
	_quitPoint = pair;
	_physics->SetQuitPoint(pair);
}

void Player::GoSpawn() {
	_sprite->setPosX(_spawnPoint->GetKey() * SPRITESHEET_CELL_SIZE * Global::Scale);
	_sprite->setPosY((_spawnPoint->GetValue() * SPRITESHEET_CELL_SIZE * Global::Scale) - 1.f);
}