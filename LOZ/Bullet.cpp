#include "Bullet.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <glut.h>
#include <gl/GL.h>

const float PI = 3.141593;
extern int x,y,z;

Bullet::Bullet(float x, float z, float ang){
  this->x = x;
  y = 2.5;
  this->z = z;
  this->ang = ang;
  distance = 0;
}

void Bullet::Draw(){
	glPushMatrix();

	float m_amb[4] = {0.3, 0.1, 0.1, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);

	glColor3f(1, 1, 0);
	glTranslatef(x, y, z);
	glutSolidSphere(0.5,16,16);
	
	glPopMatrix();
}

void Bullet::Animate(){
	if (ang == 0){
		x += 0.5;
		distance += 0.5;
	}

	if (ang == 90){
		z -= 0.5;
		distance += 0.5;
	}

	if (ang == 180){
		x -= 0.5;
		distance += 0.5;
	}

	if (ang == 270){
		z += 0.5;
		distance += 0.5;
	}

}