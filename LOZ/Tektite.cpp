#include "Tektite.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <glut.h>
#include <gl/GL.h>

const float PI = 3.141593;

Tektite::Tektite(float x, float z){
  this->x = x;
  y = 3;
  this->z = z;
  ang = 0;
  action = 0;
  frame = 0;
  modelang = 0;
  wait = 0;
}

//Draws the tektite model
void Tektite::Draw(){
	glPushMatrix();

	float m_diff[4] = {0.4, 0.4, 0.4, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);

	glTranslatef(x, y, z);
	glRotatef(modelang,0,1,0);
	DrawModel();
	
	glPopMatrix();
}

void Tektite::DrawModel(){
	glColor3f(1, 1, 0);
	float m_amb[4] = {1, 0.5, 0.0, 0.5};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	
	glutSolidSphere(1.5,16,16);	//draw body

	glPushMatrix();
	float m_spec[4] = {0.5, 0.5, 0.5, 1};		
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,m_spec);
	float m_ambRed[4] = {1.0, 0.0, 0.0, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_ambRed);
	glTranslatef(1.3, 0.1, 0);
	glutSolidSphere(0.3,16,16);	//draw eye
	glPopMatrix();

	float m_ambBlack[4] = {0, 0, 0, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,m_ambBlack);

	//draw front left leg
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(0.75, -0.8, 0.5);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj,0.2,0.2,2,16,16);	
	glPopMatrix();

	//draw front left foot
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(0.75, -0.8, 2.3);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *obj1 = gluNewQuadric();
	gluCylinder(obj1,0.2,0.1,1.3,16,16);
	glPopMatrix();

	//draw back left leg
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(-0.75, -0.8, 0.5);
	GLUquadricObj *obj2 = gluNewQuadric();
	gluCylinder(obj2,0.2,0.2,2,16,16);	
	glPopMatrix();

	//draw back left foot
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(-0.75, -0.8, 2.3);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *obj3 = gluNewQuadric();
	gluCylinder(obj3,0.2,0.1,1.3,16,16);
	glPopMatrix();

	//draw front right leg
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(0.75, -0.8, -2.5);
	GLUquadricObj *obj4 = gluNewQuadric();
	gluCylinder(obj4,0.2,0.2,2,16,16);	
	glPopMatrix();

	//draw front right foot
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(0.75, -0.8, -2.3);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *obj5 = gluNewQuadric();
	gluCylinder(obj5,0.2,0.1,1.3,16,16);
	glPopMatrix();

	//draw back right leg
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(-0.75, -0.8, -2.5);
	GLUquadricObj *obj6 = gluNewQuadric();
	gluCylinder(obj6,0.2,0.2,2,16,16);	
	glPopMatrix();

	//draw back right foot
	glPushMatrix();	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glTranslatef(-0.75, -0.8, -2.3);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *obj7 = gluNewQuadric();
	gluCylinder(obj7,0.2,0.1,1.3,16,16);
	glPopMatrix();
}

//Determines the octorocks actions randomly and animates it accordingly
// 0 = calculate jump destination, 1 = animate jump, 2 = when hits a player
void Tektite::Animate(){
	if (action == 0){
		frame++;
		if (frame == (10+wait)){
			
			int destx = ((((float) rand()/RAND_MAX)*20)+(x-10));
			int destz = ((((float) rand()/RAND_MAX)*20)+(z-10));
			
			if (destx >= x){
				destx += 5;
			}else{
				destx -= 5;
			}

			if (destz >= z){
				destz += 5;
			}else{
				destz -= 5;
			}

			//prevent tektite from jumping over boundaries
			if (destx < 8){
				destx = x + 10;
			}if (destx > 87){
				destx = x - 10;
			}if (destz < 88){
				destz = z + 10;
			}if (destz > 142){
				destz = z - 10;
			}

			//determine angle of tektite
			if ((destx >= x) && (destz >= z)){
				ang = 0;
			}else if ((destx >= x) && (destz < z)){
				ang = 90;
			}else if ((destx < x) && (destz >= z)){
				ang = 270;
			}else {
				ang = 180;
			}

			//determine angle of model
			float deltax = destx - x;
			float deltaz = destz - z;
			modelang = (atan2(deltax,deltaz)-90)*180/PI;

			//determine how much time the tektite will stand for
			wait = ((float) rand()/RAND_MAX)*150;

			//determine tektite step size
			stepx = (destx - x)/50;
			stepz = (destz - z)/50;
			frame = 0;
			action = 1;
		}
	}

	if (action == 1){
		x += stepx;
		z += stepz;
		if (frame < 25){
			y += 0.2;		//2.5/100
		}else{
			y -= 0.2;
		}
		frame++;
		if (frame == 50){
			frame = 0;
			action = 0;
		}
	}
	if (action == 2){
		if (y > 3){
			y -=0.2;
		}else{
			y = 3;
			action = 0;
		}
	}
}
