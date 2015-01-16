#pragma once

class Octorok
{
public:
	Octorok(float x, float z, int area);
	void Draw();	//draws the octorok model
	void Animate();	//determines behaviour of octorok and animates it
	float x, z;		//location of octorok
	bool shoot;		//true = shot fired
	float ang;		//the angle the octorok is facing
	int action;		//the current behaviour of the octorok
private:
	void DrawModel();
	void DrawCircle();
	void BoundaryCheck();
	int frame;
	float y;
	int area;	//0 = upper area, 1 = right area
};