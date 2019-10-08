#include "Pair.h"


Pair::Pair(int key, int value) : _key(key), _value(value) {}

Pair::~Pair() {}

int Pair::GetKey() { return _key; }
int Pair::GetValue() { return _value; }