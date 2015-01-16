#include "Bomb.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <glut.h>
#include <gl/GL.h>

const float PI = 3.141593;
extern int x,y,z;

Bomb::Bomb(float x, float z, float direcX,float direcZ){
  this->x = x;
  y = 2;
  this->z = z;
  this->direcX = direcX;
  this->direcZ = direcZ;
  timer = 0;
  size = 0;
}

void Bomb::Draw(){
	glPushMatrix();

	float m_amb[4] = {0, 0, 0.5, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);

	glTranslatef(x+5*direcX, y, z+5*direcZ);
	glutSolidSphere(1,16,16);
	glPopMatrix();
}

void Bomb::Timer(){
	timer++;	
}

void Bomb::Explode(){
	size++;
	
	glPushMatrix();

	float m_amb[4] = {1, 1, 0, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);

	glColor3f(0, 0, 1);
	glTranslatef(x+5*direcX, y, z+5*direcZ);
	glutSolidSphere(size*1.5,16,16);
	glPopMatrix();
}