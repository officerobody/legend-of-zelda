#pragma once

class Bullet
{
public:
	Bullet(float x, float z, float ang);
	void Draw();
	void Animate();
	float x, z;
	float distance;
	float ang;
private:
	//void BoundaryCheck();
	float y;
};