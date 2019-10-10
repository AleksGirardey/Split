#pragma once
class Pair
{
private:
	int _key;
	int _value;
public:
	Pair(int key, int value);
	Pair();
	~Pair();

	int GetKey();
	int GetValue();
};