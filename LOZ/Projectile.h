#pragma once

class Projectile
{
public:
	Projectile(float x,float y, float z, float direcX,float direcY, float direcZ);
	void Draw();
	void Animate();
	float x,y, z;
	float distance;
	float direcX,direcY,direcZ;
};
