#pragma once

class Bomb
{
public:
	Bomb(float x,float z, float direcX, float direcZ);
	void Draw();
	void Timer();
	void Explode();
	int timer;
	float x,y, z;
	float direcX,direcZ;
	int size;
};
