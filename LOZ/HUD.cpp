#include "HUD.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include<iostream>
#include<sstream>
#include <glut.h>
#include <gl/gl.h>

using namespace std;
int sword = 0;
int bombs = 0;
int delay = 0;
float HP = 3.0;
int Rupees = 0;
int counter = 0;
const float DEG2RAD = 3.14159/180;

void HeadsUpDisp::Font(float x, float y, char *text, float scaleX, float scaleY, float col1, float col2, float col3){
	char *p;

    glPushMatrix();
	glNormal3f(0,1,0);
			
    glTranslatef(x, y, 0);
	glScalef(scaleX, scaleY, 0.0);
	glColor3f(col1, col2, col3);
	
	glLineWidth(1.5f);
    for (p = text; *p; p++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
}

void HeadsUpDisp::GameOverMan(){
	Font(132, 200, "Game Over", 0.3, -0.25, 0.7, 0, 0);
	glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(500.0, 0.0);
		glVertex2f(500.0, 500.0);
		glVertex2f(0.0, 500.0);
	glEnd();

	 
}
void HeadsUpDisp::decreaseHP(){
	if (HP!=0.0){
		HP -= 0.5;
	}

}
void HeadsUpDisp::increaseHP(){
	if (HP!=3.0){
		HP += 0.5;
	}

}
void HeadsUpDisp::increaseRupees(){
	float randomNum = ((((float) rand()/RAND_MAX)*5)+1);
	if(randomNum<2){
		Rupees+=10;
	}
	else if(randomNum>=2 && randomNum<3){
		Rupees+=5;
	}
	else{
		Rupees++;
	}
}
void HeadsUpDisp::drawHeart(int x, int y){
	Font(10, 23, "-LIFE-", 0.15, -0.15, 1, 0, 0);

	// Hearts
	glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(18 + x,  35.0);
		glVertex2f(10.0 + x, 32.0);
		glVertex2f(10.0 + x, 46.0);
		glVertex2f(18.0 + x, 50.0);
		glVertex2f(26.0 + y, 46.0);
		glVertex2f(26.0 + y, 32.0);
		
	glEnd();
	
}

void HeadsUpDisp::checkHP(){
	if (HP == 0.5){
		drawHeart(0, -8);
	}
	if (HP == 1.0){
		drawHeart(0, 0);
	}
	if (HP == 1.5){
		drawHeart(0, 0);
		drawHeart(26, 18);
	}
	if (HP == 2.0){
		drawHeart(0, 0);
		drawHeart(26, 26);
	}
	if (HP == 2.5){
		drawHeart(0, 0);
		drawHeart(26,26);
		drawHeart(52, 44);
	}
	if (HP == 3.0){
		drawHeart(0, 0);
		drawHeart(26,26);
		drawHeart(52, 52);
	}

	if (HP == 0.0){
		GameOverMan();
	}
}
float HeadsUpDisp::getHP(){
	return HP;
	}
void HeadsUpDisp::drawCoin(float x, float y, float radius) { 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    static const int circle_points = 100;
    static const float angle = 2.0f * 3.1416f / circle_points;

    glBegin(GL_POLYGON);
    double angle1=0.0;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    for (int i=0; i<circle_points; i++){       
        glVertex2d(radius * cos(angle1), radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();
    glPopMatrix();
}

void HeadsUpDisp::checkRupees(){
	char Amount[50];
	char Amount2[50];
	
	sprintf(Amount,"%d",Rupees);
	sprintf(Amount2,"%d",bombs);

	glColor3f(1.0, 1.0, 0.0);
	
	drawCoin(10.0, 486.0, 6.5);
	Font(18, 491, "X", 0.09, -0.09, 0.5, 0.0, 0.0);
	Font(30, 490, Amount, 0.09, -0.09, 0.5, 0.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	
	drawCoin(10.0, 466.0, 6.5);
	Font(18, 471, "X", 0.09, -0.09, 0.5, 0.0, 0.0);
	Font(30, 470, Amount2, 0.09, -0.09, 0.5, 0.0, 0.0);
}

void HeadsUpDisp::weaponInd(){
	Font(375, 404, "B", 0.09, -0.09, 1.0, 1.0, 1.0);
	Font(450, 404, "A", 0.09, -0.09, 1.0, 1.0, 1.0);
	glColor3f(0.5, 1.0, 0.0);
	if (sword != 0){
		glRectf(446.0, 485.0, 460.0, 480.0);
		glRectf(446.0, 475.0, 460.0, 470.0);
		glRectf(438.0, 465.0, 468.0, 460.0);
		glRectf(434.0, 470.0, 438.0, 460.0);
		glRectf(468.0, 470.0, 472.0, 460.0);
		glColor3f(0,0,1.0);
	}
	
	glColor3f(0,0,1);
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2f(345, 490);
		glVertex2f(415, 490);
		glVertex2f(415, 400);
		glVertex2f(345, 400);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(420, 490);
		glVertex2f(490, 490);
		glVertex2f(490, 400);
		glVertex2f(420, 400);
	glEnd();

	if (HP == 3.0){
		glColor3f(1.0, 0.75, 0.0);
		
	}else{
		glColor3f(0.62, 0.31, 0.08);
	}
	if (sword != 0){
		glBegin(GL_TRIANGLES);
			
			glVertex2f(446.0, 418.0);
			glVertex2f(460.0, 418.0);
			glVertex2f(453.0, 408.0);
		glEnd();
		glRectf(446.0, 418.0, 460.0, 480.0);
	}

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(388, 433);
		glVertex2f(392, 426);
		glVertex2f(388, 422);
		glVertex2f(388, 418);
	glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2f(363, 445);
		glVertex2f(367.5, 445);
		glVertex2f(365, 443);
		glVertex2f(365, 447.5);
	glEnd();
	glColor3f(0.19, 0.38, 1.00);
	drawCoin(368, 450, 10);
	glColor3f(0.0, 0.0, 0.8);

	drawCoin(380, 460, 25);
	glColor3f(0.0, 0.0, 0.0);
	
	drawCoin(380, 460, 28);
}

void HeadsUpDisp::weapon(){
	glColor3f(0.5,0.5,0.5);
	glRectf(280.0, 520.0, 330.0, 400.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(280.0, 400.0);
		glVertex2f(330.0, 400.0);
		glVertex2f(305.0, 350.0);
	glEnd();
}

void HeadsUpDisp::weapon2(){
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_QUADS);
		glVertex2f(280.0, 520.0);
		glVertex2f(330.0, 520.0);
		glVertex2f(315.0, 380.0);
		glVertex2f(295.0, 380.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(295.0, 380.0);
		glVertex2f(315.0, 380.0);
		glVertex2f(305.0, 330.0);
	glEnd();
	glutSwapBuffers();
}

void HeadsUpDisp::attack(){
	
	if (sword == 1){
		glColor3f(0.5,0.5,0.5);
		glRectf(280.0, 520.0, 330.0, 400.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(280.0, 400.0);
			glVertex2f(330.0, 400.0);
			glVertex2f(305.0, 350.0);
		glEnd();
	}
	
	else if (sword == 2){
		glColor3f(0.5,0.5,0.5);
		glRotatef(-5,0,0,1);
		glTranslatef(-80,30,0);
		glRectf(280.0, 520.0, 330.0, 400.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(280.0, 400.0);
			glVertex2f(330.0, 400.0);
			glVertex2f(305.0, 350.0);
		glEnd();
		}
	
	else if (sword == 3){
		glColor3f(0.5,0.5,0.5);
		glRotatef(-10,0,0,1);
		glTranslatef(-160,35,0);
		glRectf(280.0, 520.0, 330.0, 400.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(280.0, 400.0);
			glVertex2f(330.0, 400.0);
			glVertex2f(305.0, 350.0);
		glEnd();
		}
	
	else if (sword == 4){
		glColor3f(0.5,0.5,0.5);
		glRotatef(-15,0,0,1);
		glTranslatef(-240,40,0);
		glRectf(280.0, 520.0, 330.0, 400.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(280.0, 400.0);
			glVertex2f(330.0, 400.0);
			glVertex2f(305.0, 350.0);
		glEnd();
		}
	
	else if (sword == 5){
		glColor3f(0.5,0.5,0.5);
		glRotatef(-20,0,0,1);
		glTranslatef(-320,45,0);
		glRectf(280.0, 520.0, 330.0, 400.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(280.0, 400.0);
			glVertex2f(330.0, 400.0);
			glVertex2f(305.0, 350.0);
		glEnd();
	}
	
	else if (sword == 6){
		glColor3f(0.5,0.5,0.5);
		glRotatef(-25,0,0,1);
		glTranslatef(-400,50,0);
		glRectf(280.0, 520.0, 330.0, 400.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(280.0, 400.0);
			glVertex2f(330.0, 400.0);
			glVertex2f(305.0, 350.0);
		glEnd();
		}
	
	else if (sword == 7){
		glColor3f(0.5,0.5,0.5);
		glRotatef(-30,0,0,1);
		glTranslatef(-460,55,0);
		glRectf(280.0, 520.0, 330.0, 400.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(280.0, 400.0);
			glVertex2f(330.0, 400.0);
			glVertex2f(305.0, 350.0);
		glEnd();
		}	
	

	/*
		glTranslatef(50,0,0);
		for (counter = 0; counter < 22; counter++){
			glTranslatef(-15,0,0);
			weapon2();
			//glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
		}
		//sword = 1;
	}*/
}

void HeadsUpDisp::pickupWep(float eye[3],bool inCave){
	if (inCave==true&&60 <= eye[2] && eye[2] <= 65 && 133 <= eye[0] && eye[0] <= 137){
		sword = 1;
	}
}

void HeadsUpDisp::swordText(bool inCave){
	if(inCave==true && sword==0){
		Font(20,430,"IT'S DANGEROUS TO GO",0.2,-0.2,1,1,1);
		Font(50,460,"ALONE! TAKE THIS.",0.2,-0.2,1,1,1);
		 
	}
}
void HeadsUpDisp::HUD(float eye[3],bool inCave){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 500, 500, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glClear(GL_DEPTH_BUFFER_BIT);

	pickupWep(eye,inCave);

	checkHP();
	swordText(inCave);
	checkRupees();
	weaponInd();
	attack();

	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}

void HeadsUpDisp::kbd(unsigned char key, int x, int y,float direction[3],float eye[3])
{

	if(key == 'o' || key == 'O'){	
		if (HP != 0.0){
			HP -= 0.5;
		}
	}
	if(key == 'p' || key == 'P'){	
		if (HP != 3.0){
			HP += 0.5;
		}
	}
	//if (key == 32){
	//	if (sword == 1){
	//		sword = 2;
	//	}else if (sword == 2){
	//		sword = 1;
	//	}
	//}
}