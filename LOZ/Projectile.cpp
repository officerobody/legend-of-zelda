#include "Projectile.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <glut.h>
#include <gl/GL.h>

const float PI = 3.141593;
extern int x,y,z;

Projectile::Projectile(float x, float y, float z, float direcX,float direcY,float direcZ){
  this->x = x;
  this->y = y;
  this->z = z;
  this->direcX = direcX;
  this->direcY = direcY;
  this->direcZ = direcZ;
  distance = 0;
}

void Projectile::Draw(){
	glPushMatrix();

	float m_amb[4] = {1, 1, 0.1, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);

	glColor3f(1, 1, 0);
	glTranslatef(x, y, z);
	glutSolidSphere(0.5,16,16);
	
	glPopMatrix();
}

void Projectile::Animate(){
	x += direcX;
		
	y+=direcY;

	z+=direcZ;
	
	distance += sqrt(direcX/2*direcX/2+direcY/2*direcY/2+direcZ/2*direcZ/2);
	
}