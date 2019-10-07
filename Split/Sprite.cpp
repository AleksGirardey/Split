#include "Sprite.h"

Sprite::Sprite(int index, float posX, float posY, bool flipH, bool flipV, bool flipD, int layer) :
	_index(index),
	_posX(posX),
	_posY(posY),
	_flipH(flipH),
	_flipV(flipV),
	_flipD(flipD),
	_layer(layer)
{}

Sprite::~Sprite() {}

void Sprite::setIndex(int index) { _index = index; }
void Sprite::setPosX(float pos) { _posX = pos; }
void Sprite::setPosY(float pos) { _posY = pos; }
void Sprite::setLayer(int layer) { _layer = layer; }
void Sprite::setFlipH(bool value) { _flipH = value; }
void Sprite::setFlipV(bool value) { _flipV = value; }
void Sprite::setFlipD(bool value) { _flipD = value; }

int Sprite::getIndex() { return _index; }
float Sprite::getPosX() { return _posX; }
float Sprite::getPosY() { return _posY; }
int Sprite::getLayer() { return _layer; }
bool Sprite::isFlipH() { return _flipH; }
bool Sprite::isFlipV() { return _flipV; }
bool Sprite::isFlipD() { return _flipD; }

bool Sprite::operator<(const Sprite& other) {
	if (_layer < other._layer) return true;
	else if (_layer > other._layer) return false;
	else {
		if (_posY < other._posY) return true;
		else if (_posY > other._posY) return false;
		else {
			if (_posX < other._posX) return true;
			else return false;
		}
	}
}