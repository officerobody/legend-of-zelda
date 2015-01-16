#include "Octorok.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <glut.h>
#include <gl/GL.h>

const float PI = 3.141593;

Octorok::Octorok(float x, float z, int area){
  this->x = x;
  y = 2.5;
  this->z = z;
  this->area = area;
  ang = 0;
  action = 0;
  frame = 0;
  shoot = false;
}

//Draws the octorok model
void Octorok::Draw(){
	glPushMatrix();

	float m_diff[4] = {0.35, 0.35, 0.35, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);

	glTranslatef(x, y, z);
	glRotatef(ang,0,1,0);
	DrawModel();
	
	glPopMatrix();
}

void Octorok::DrawModel(){
	glColor3f(1, 0, 0);
	float m_amb[4] = {0.5, 0, 0.0, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	
	glutSolidSphere(2,16,16);	//draw body

	//draw eye
	glPushMatrix();
	glColor3f(0, 1, 0);
	float m_spec[4] = {0.5, 0.5, 0.5, 1};		
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,m_spec);
	float m_ambGreen[4] = {0.0, 0.5, 0.0, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_ambGreen);
	glTranslatef(1.5, 1, 0.5);
	glutSolidSphere(0.3,16,16);
	glPopMatrix();

	//draw eye
	glPushMatrix();
	glColor3f(0, 1, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,m_spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_ambGreen);
	glTranslatef(1.5, 1, -0.5);
	glutSolidSphere(0.3,16,16);
	glPopMatrix();

	float m_ambBlack[4] = {0, 0, 0, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,m_ambBlack);

	//draw mouth
	glPushMatrix();
	glColor3f(0.9, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(3, 0, 0);
	glRotatef(-90, 0, 1, 0);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj,0.5,0.5,1.2,16,16);

	//draw mouth opening
	glPushMatrix();
	glColor3f(0, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_ambBlack);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_ambBlack);
	glRotatef(-90, 0, 1, 0);
	DrawCircle();
	glPopMatrix();
	glPopMatrix();

	float m_diff[4] = {0.25, 0.25, 0.25, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);

	//draw left tentacles
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(-0.75, -1.7, -2.5);
	glRotatef(-45, 1, 0, 0);
	GLUquadricObj *obj1 = gluNewQuadric();
	gluCylinder(obj1,0.2,0.3,2,16,16);	
	glPopMatrix();

	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(0, -1.7, -2.5);
	glRotatef(-45, 1, 0, 0);
	GLUquadricObj *obj2 = gluNewQuadric();
	gluCylinder(obj2,0.2,0.3,2,16,16);	
	glPopMatrix();

	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(0.75, -1.7, -2.5);
	glRotatef(-45, 1, 0, 0);
	GLUquadricObj *obj3 = gluNewQuadric();
	gluCylinder(obj3,0.2,0.3,2,16,16);	
	glPopMatrix();

	//draw right tentacles
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(-0.75, -1.7, 2.5);
	glRotatef(-135, 1, 0, 0);
	GLUquadricObj *obj4 = gluNewQuadric();
	gluCylinder(obj4,0.2,0.3,2,16,16);	
	glPopMatrix();

	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(0, -1.7, 2.5);
	glRotatef(-135, 1, 0, 0);
	GLUquadricObj *obj5 = gluNewQuadric();
	gluCylinder(obj5,0.2,0.3,2,16,16);	
	glPopMatrix();

	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(0.75, -1.7, 2.5);
	glRotatef(-135, 1, 0, 0);
	GLUquadricObj *obj6 = gluNewQuadric();
	gluCylinder(obj6,0.2,0.3,2,16,16);	
	glPopMatrix();

}

//draws a circle of radius 0.5 and 16 edges
void Octorok::DrawCircle(){
	glBegin(GL_POLYGON);	
		glVertex3f(0, 0.5, 0);
		glVertex3f(0, 0.5*sin(112.5*PI/180), 0.5*cos(112.5*PI/180));
		glVertex3f(0, 0.5*sin(135*PI/180), 0.5*cos(135*PI/180));
		glVertex3f(0, 0.5*sin(157.5*PI/180), 0.5*cos(157.5*PI/180));
		glVertex3f(0, 0, -0.5);
		glVertex3f(0, 0.5*sin(202.5*PI/180), 0.5*cos(202.5*PI/180));
		glVertex3f(0, 0.5*sin(225*PI/180), 0.5*cos(225*PI/180));
		glVertex3f(0, 0.5*sin(247.5*PI/180), 0.5*cos(247.5*PI/180));
		glVertex3f(0, -0.5, 0);
		glVertex3f(0, 0.5*sin(292.5*PI/180), 0.5*cos(292.5*PI/180));
		glVertex3f(0, 0.5*sin(315*PI/180), 0.5*cos(315*PI/180));
		glVertex3f(0, 0.5*sin(337.5*PI/180), 0.5*cos(337.5*PI/180));
		glVertex3f(0, 0, 0.5);
		glVertex3f(0, 0.5*sin(22.5*PI/180), 0.5*cos(22.5*PI/180));
		glVertex3f(0, 0.5*sin(45.0*PI/180), 0.5*cos(45.0*PI/180));
		glVertex3f(0, 0.5*sin(67.5*PI/180), 0.5*cos(67.5*PI/180));
	glEnd();

}

//Determines the octorocks actions randomly and animates it accordingly
// 0 = new path, 1 = +x, 2 = +z, 3 = -x, 4 = -z, 5 = shoot
void Octorok::Animate(){
	if (action == 0){
		float random = ((float) rand()/RAND_MAX);
		if (random <= 0.2){
			ang = 0;
			action = 1;
		}
		else if ((random > 0.2) && (random <= 0.4)){
			ang = 270;
			action = 2;
		}
		else if ((random > 0.4) && (random <= 0.6)){
			ang = 180;
			action = 3;
		}
		else if ((random > 0.6) && (random <= 0.8)){
			ang = 90;
			action = 4;
		}
		else{
			action = 5;
		}
	}

	if (action == 1){
		BoundaryCheck();
		x += 0.1;
		frame++;
		if (frame == 100){
			frame = 0;
			action = 0;
		}
	}

	if (action == 2){
		BoundaryCheck();
		z += 0.1;
		frame++;
		if (frame == 100){
			frame = 0;
			action = 0;
		}
	}

	if (action == 3){
		BoundaryCheck();
		x -= 0.1;
		frame++;
		if (frame == 100){
			frame = 0;
			action = 0;
		}
	}

	if (action == 4){
		BoundaryCheck();
		z -= 0.1;
		frame++;
		if (frame == 100){
			frame = 0;
			action = 0;
		}
	}

	if (action == 5){
		frame++;
		if (frame == 50){
			shoot = true;
		}else{
			shoot = false;
		}
		if (frame == 100){
			frame = 0;
			action = 0;
		}
	}
}

//Determines if the octorok collides with a wall and reroutes it if it does.
void Octorok::BoundaryCheck(){
	if (area == 0){		//check boundaries for upper area
		if (x <= 113){
			x+= 0.05;
			action = 0;
			frame = 0;
		}else if (x >= 187){
			x-= 0.05;
			action = 0;
			frame = 0;
		}else if (z <= 13){
			z+= 0.05;
			action = 0;
			frame = 0;
		}else if (z >= 72){
			z-= 0.05;
			action = 0;
			frame = 0;
		}
	}else if (area == 1){	//check boundaries for right area
		if (x <= 228){
			x+= 0.05;
			action = 0;
			frame = 0;
		}else if (x >= 287){
			x-= 0.05;
			action = 0;
			frame = 0;
		}else if (z <= 88){
			z+= 0.05;
			action = 0;
			frame = 0;
		}else if (z >= 142){
			z-= 0.05;
			action = 0;
			frame = 0;
		}
	}
}

