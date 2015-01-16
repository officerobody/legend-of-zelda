#pragma once

class Tektite
{
public:
	Tektite(float x, float z);
	void Draw();	//draws the tektite model
	void Animate();	//determines behaviour of tektite and animates it
	float x, z;		//tektites location
	float ang;		//angle of tektites jump
	float modelang;	//angle of tektites model
	int action;		//current behaviour of tektite
	float y;
private:
	void DrawModel();
	int frame;
	float stepx, stepz;
	int wait;
};