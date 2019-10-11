#pragma once
class Sprite
{
private:
	int _index;
	float _posX;
	float _posY;
	bool _flipH;
	bool _flipV;
	bool _flipD;
	int _layer;
public:
	Sprite(int index, float posX, float posY, bool flipH, bool flipV, bool flipD, int layer);
	Sprite();
	~Sprite();

	void setIndex(int index);
	void setPosX(float pos);
	void setPosY(float pos);
	void setLayer(int layer);
	void setFlipH(bool value);
	void setFlipV(bool value);
	void setFlipD(bool value);

	int getIndex();
	float getPosX();
	float getPosY();
	int getLayer();
	bool isFlipH();
	bool isFlipV();
	bool isFlipD();

	bool IsPlayer;

	bool operator<(const Sprite& other);
};