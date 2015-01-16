#pragma once

class Terrain
{
public:
	float hMapArray[300][150];
	void circleAlgorithm(float maxHeight, int circSize,float r1,float r2);
	void initializeArray();
	void setZeros();
	void drawTerrain();
	void crossProduct();
};