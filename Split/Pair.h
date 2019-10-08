#pragma once
class Pair
{
private:
	int _key;
	int _value;
public:
	Pair(int key, int value);
	~Pair();

	int GetKey();
	int GetValue();
};