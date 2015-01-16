#pragma once

#include "Terrain.h"
class CameraControl
{
public:
	void initializeValues(float direction[3],float eye[3]);
	void kbd(unsigned char key, int x, int y,float direction[3],float eye[3]);
	void specialKbd(int key, int x, int y,float direction[3],float eye[3],Terrain terrain,bool inCave);
};