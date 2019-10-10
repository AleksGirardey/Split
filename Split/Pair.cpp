#include "Pair.h"


Pair::Pair(int key, int value) : _key(key), _value(value) {}
Pair::Pair() : _key(0), _value(0) {}

Pair::~Pair() {}

int Pair::GetKey() { return _key; }
int Pair::GetValue() { return _value; }