#include "CameraControl.h" 
#include "HUD.h"
#include "Terrain.h" 
#include "Octorok.h"
#include "Bullet.h"
#include "Projectile.h"
#include "Bomb.h"
#include <windows.h>
#include <time.h> 
#include <stdio.h>
#include "Tektite.h"
#include <glut.h>
#include <gl/gl.h>
#include <math.h>
#include <iostream>
#include <list>

using namespace std;
CameraControl camera;
Terrain terrain;
HeadsUpDisp hud;
list<Projectile> projectiles;


//Creates two lists for the enemies and their projectiles
list<Bullet> bullets;
list<Tektite> tektites;
list<Octorok> octoroks;  
list<Bomb> bombs;  

//create two arrays that will be used for the camera placement and the direction that the camera is facing
float eye[3];
float direction[3];

int projectileCounter=0;
//set boolean values
bool playGame=false;
bool spawn=false;
bool inCave=false;
bool attackAnimation=false;
int attackCounter = 0;
int flash = 0;
//set position of lights
float position[4] = {150,100,75, 1};
float flame_position[4] = {147.5,1,63, 1};
float flame2_position[4] = {122.5,1,63, 1};

//creates a 2x2 hit box
int hitbox = 2;

//keeps track of the time the player is invulnerable for. 0 = not invulnerable
int invulntime = 0;

//initiates the outside lighting
void initLighting(){
	float m_amb[4] = {1, 1, 1, 1};
	float m_diff[4] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT3, GL_POSITION, position);
	glLightfv(GL_LIGHT3, GL_AMBIENT, m_amb);	
	glLightfv(GL_LIGHT3, GL_DIFFUSE, m_diff);	

}


//initiates the lighting inside the cave
void initFlameLighting(){
	float m_amb[4] = {1, 1, 1, 1};
	float m_amb_Orange[4] = {0.25, 0.125, 0, 0.25};
	
	glLightfv(GL_LIGHT1, GL_POSITION, flame_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, m_amb);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_amb_Orange);	
	glLightfv(GL_LIGHT2, GL_POSITION, flame2_position);
	glLightfv(GL_LIGHT2, GL_AMBIENT, m_amb);	
	glLightfv(GL_LIGHT2, GL_DIFFUSE, m_amb_Orange);
}

void menuScreen(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 500, 500, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glClear(GL_DEPTH_BUFFER_BIT);
	flash++;

	hud.Font(150, 200, "= Instructions =", 0.2, -0.2, 1,1,1);
	hud.Font(100, 220, "- Move with the arrow keys", 0.1, -0.1, 1,1,1);
	hud.Font(100, 240, "- WASD to look around", 0.1, -0.1, 1,1,1);
	hud.Font(100, 260, "- Spacebar to swing your sword", 0.1, -0.1, 1,1,1);
	hud.Font(150, 280, "- At full health, you also shoot", 0.1, -0.1, 1,1,1);
	hud.Font(100, 300, "- Press B to place a bomb", 0.1, -0.1, 1,1,1);
	hud.Font(100, 320, "- Esc to quit", 0.1, -0.1, 1,1,1);
	hud.Font(60, 360, "- The sword is inside the cave!", 0.12, -0.12, 1,1,1);
	hud.Font(60, 380, "- Enemies only spawn when you enter the area", 0.12, -0.12, 1,1,1);

	if (flash < 60){
		hud.Font(160, 450, "PRESS ENTER", 0.2, -0.2, 1,1,1);
	}
	if (flash == 90){
		flash = 0;
	}

	hud.Font(154,66,"THE LEGEND OF", 0.1, -0.1, .7,0.7,0.7);
	hud.Font(150,120,"ZELDA", 0.5, -0.5, 1,0.1,0);
	glColor3f(0.9,0.9,0);
	glBegin(GL_TRIANGLES);
		glVertex2f(190.0, 50.0);
		glVertex2f(310.0, 50.0);
		glVertex2f(250.0, 170.0);
	glEnd();
	glColor3f(0,0,0);
	glRectf(0.0, 0.0, 500.0, 500.0);

	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	
}

//draws the ground 
void drawPlane(){
	float m_amb[4] = {0.378, 0.253, 0.096, 1};
	float m_diffuse[4] = {1, 0.8588, 0.678, 1};
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,m_diffuse);
	
	glBegin(GL_QUADS);
			glColor3f(0,0,0);
			glNormal3f(0,1,0);
			glVertex3f(0,1,0);
			glNormal3f(0,1,0);
			glVertex3f(0,1,150);
			glNormal3f(0,1,0);
			glVertex3f(300,1,150);
			glNormal3f(0,1,0);
			glVertex3f(300,1,0);
	glEnd();
}

void drawSword(){
	float m_hilt[4] = {0.0,0.5,0, 1};	
		float m_hilt2[4] = {0.55,0.27,0.08, 1};	
		float m_sword[4] = {0.2,0.2,0.2, 1};	
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_hilt);
		glTranslatef(135, 0.5, 63);
		glutSolidCube(0.5);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_hilt2);
		glTranslatef(0, 0.5, 0);
		glutSolidCube(0.5);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_hilt);
		glTranslatef(0, 0.5, 0);
		glutSolidCube(0.5);
		glTranslatef(-0.5,0,0);
		glutSolidCube(0.5);
		glTranslatef(-0.5,0,0);
		glutSolidCube(0.5);
		glTranslatef(0,-0.45,0);
		glutSolidCube(0.45);
		glTranslatef(1.5,0.45,0);
		glutSolidCube(0.5);
		glTranslatef(0.5,0,0);
		glutSolidCube(0.5);
		glTranslatef(0,-0.45,0);
		glutSolidCube(0.45);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_sword);
		glTranslatef(-1.25,0.95,0);
		glutSolidCube(0.5);
		glTranslatef(0.50,0.0,0);
		glutSolidCube(0.5);
		glTranslatef(0.0,0.5,0);
		glutSolidCube(0.5);
		glTranslatef(-0.50,0.0,0);
		glutSolidCube(0.5);
		glTranslatef(0.0,0.5,0);
		glutSolidCube(0.5);
		glTranslatef(0.50,0.0,0);
		glutSolidCube(0.5);
		glTranslatef(0.0,0.5,0);
		glutSolidCube(0.5);
		glTranslatef(-0.50,0.0,0);
		glutSolidCube(0.5);
		glTranslatef(0.25,0.25,0);
		glBegin(GL_TRIANGLES);
	// Top 1
    		glNormal3f(0.5,0,0.25); 
    		glVertex3f(0.5,0,0.25); 
    		glNormal3f(0,1,0); 
    		glVertex3f(0,1,0); 
    		glNormal3f(-0.5,0,0.25); 
    		glVertex3f(-0.5,0,0.25); 
    		glNormal3f(-0.5,0,0.25); 
    // Top 2
    		glVertex3f(-0.5,0,0.25); 
    		glNormal3f(0,1,0); 
    		glVertex3f(0,1,0); 
    		glNormal3f(-0.5,0,-0.25); 
    		glVertex3f(-0.5,0,-0.25); 
    		glNormal3f(-0.5,0,-0.25); 
    // Top 3
    		glVertex3f(-0.5,0,-0.25); 
    		glNormal3f(0,1,0);
    		glVertex3f(0,1,0); 
    		glNormal3f(0.5,0,-0.25); 
    		glVertex3f(0.5,0,-0.25);
    		glNormal3f(0.5,0,-0.25); 
    // Top 4
    		glVertex3f(0.5,0,-0.25);  
    		glNormal3f(0,1,0); 
    		glVertex3f(0,1,0); 
    		glNormal3f(0.5,0,0.25); 
    		glVertex3f(0.5,0,0.25); 
    	glEnd();
		glPopMatrix();
}

void drawOldMan(){
	float m_skin[4] = {0.5,0.3,0.2, 1};	
	float m_cloth[4] = {0.25, 0.0, 0.0, 1};	
	float m_black[4] = {0.0,0.0,0.0, 1};
	float m_hair[4] = {0.5,0.5,0.5, 1};

	//head
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_skin);
	glTranslatef(135, 7, 45);
	glutSolidSphere(1.5,16,16);

	//right eye
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_black);
	glTranslatef(0.4, 0.2, 1.3);
	glutSolidSphere(0.2,16,16);
	glPopMatrix();

	//left eye
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_black);
	glTranslatef(-0.4, 0.2, 1.3);
	glutSolidSphere(0.2,16,16);
	glPopMatrix();

	//nose
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_skin);
	glTranslatef(0, -0.1, 1.4);
	glutSolidSphere(0.3,16,16);
	glPopMatrix();

	//beard
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_hair);
	glBegin(GL_POLYGON);
	glVertex3f(0,-1.5,1.5);
	glVertex3f(-0.5,-1.3,1.35);
	glVertex3f(-1,-0.3,1.2);
	glVertex3f(-0.5,-0.3,1.35);
	glVertex3f(0,-0.3,1.5);
	glVertex3f(0.5,-0.3,1.35);
	glVertex3f(1,-0.3,1.2);
	glVertex3f(0.5,-1.3,1.35);
	glEnd();
	glPopMatrix();

	//mouth
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_black);
	glBegin(GL_POLYGON);
	glVertex3f(-0.4,-0.45,1.5);
	glVertex3f(-0.4,-0.6,1.5);
	glVertex3f(0.4,-0.6,1.5);
	glVertex3f(0.4,-0.45,1.5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_skin);
	glTranslatef(0, -0.1, 1.4);
	glutSolidSphere(0.3,16,16);
	glPopMatrix();

	//torso
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_cloth);
	glTranslatef(0, -3.5, 0);
	glutSolidSphere(2.5,16,16);
	
	//legs
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_cloth);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj,2.5,3,4,16,16);	
	glPopMatrix();

	//left arm
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_cloth);
	glTranslatef(1.7, 1, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(40, 1, 0, 0);
	GLUquadricObj *obj1 = gluNewQuadric();
	gluCylinder(obj1,0.5,0.8,3,16,16);	
	
	//left hand
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_skin);
	glTranslatef(0, 0.2, 3);
	glutSolidSphere(0.5,16,16);	
	glPopMatrix();
	glPopMatrix();

	//right arm
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_cloth);
	glTranslatef(-1.7, 1, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(40, 1, 0, 0);
	GLUquadricObj *obj2 = gluNewQuadric();
	gluCylinder(obj2,0.5,0.8,3,16,16);	
	
	//right hand
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_skin);
	glTranslatef(0, 0.2, 3);
	glutSolidSphere(0.5,16,16);	
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	//collision detection
	if (eye[0] <= 139 && eye[0] >= 131 && eye[2] <= 49 && eye[2] >= 48){
		eye[2]++;
	}

	else if (eye[0] <= 139 && eye[0] >= 131 && eye[2] <= 42 && eye[2] >= 41){
		eye[2]--;
	}

	else if (eye[0] <= 139 && eye[0] >= 138 && eye[2] <= 49 && eye[2] >= 41){
		eye[0]++;
	}

	else if (eye[0] <= 132 && eye[0] >= 131 && eye[2] <= 49 && eye[2] >= 41){
		eye[0]--;
	}
}

//draws the insides of the cave
void drawCave(){
	
	float m_amb[4] = {0.0, 0, 0.0, 1};	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);
	glBegin(GL_QUADS); //Floor
			glColor3f(0,0,0);
			glVertex3f(110,0,89);
			glVertex3f(160,0,89);
			glVertex3f(160,0,38);
			glVertex3f(110,0,38);
	glEnd();

	glBegin(GL_QUADS); //Ceiling
			glColor3f(0,0,0);
			glNormal3f(0,1,0);
			glVertex3f(110,20,89);
			glNormal3f(0,1,0);
			glVertex3f(160,20,89);
			glNormal3f(0,1,0);
			glVertex3f(160,20,38);
			glNormal3f(0,1,0);
			glVertex3f(110,20,38);
	glEnd();

	float m_amb2[4] = {0.11, 0.066, 0.0266, 1};
	float m_Diffuse[4] = {0.11, 0.066, 0.0266, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_Diffuse);
	
	glBegin(GL_QUADS); //Left wall
			glColor3f(0,0,0);
			glNormal3f(1,0,0);
			glVertex3f(110,0,89);
			glNormal3f(1,0,0);
			glVertex3f(110,0,38);
			glNormal3f(1,0,0);
			glVertex3f(110,50,38);
			glNormal3f(1,0,0);
			glVertex3f(110,50,89);
	glEnd();

	glBegin(GL_QUADS);
			glColor3f(0,0,0); //Right wall
			glNormal3f(-1,0,0);
			glVertex3f(160,0,89);
			glNormal3f(-1,0,0);
			glVertex3f(160,0,38);
			glNormal3f(-1,0,0);
			glVertex3f(160,50,38);
			glNormal3f(-1,0,0);
			glVertex3f(160,50,89);
	glEnd();

	glBegin(GL_QUADS); //Near wall
			glColor3f(0,0,0);
			glNormal3f(0,0,-1);
			glVertex3f(110,0,89);
			glNormal3f(0,0,-1);
			glVertex3f(160,0,89);
			glNormal3f(0,0,-1);
			glVertex3f(160,50,89);
			glNormal3f(0,0,-1);
			glVertex3f(110,50,89);
	glEnd();
	
	glBegin(GL_QUADS);//Far wall
			glColor3f(0,0,0);
			glNormal3f(0,0,1);
			glVertex3f(110,0,38);
			glNormal3f(0,0,1);
			glVertex3f(160,0,38);
			glNormal3f(0,0,1);
			glVertex3f(160,50,38);
			glNormal3f(0,0,1);
			glVertex3f(110,50,38);
	glEnd();
	
	//creates the two flames inside of the cave
	float m_amb_Red[4] = {0.8, 0, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb_Red);
	float m_amb_Orange[4] = {1.0, 0.5, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,m_amb_Orange);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(122.5,1,63);
	glutSolidSphere(3,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(147.5,1,63);
	glutSolidSphere(3,20,20);
	glPopMatrix();

	if (hud.sword == 0){
		drawSword();
		drawOldMan();
	}
	
}
//draws the entrance to the cave
void cave(){
	
	float m_amb[4] = {0.0, 0, 0.0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb);

	glPushMatrix();
		glBegin(GL_POLYGON);
			glColor3f(0,0,0);
			
			glNormal3f(0,0,1);
			glVertex3f(130,0,88);
			glNormal3f(0,0,1);
			glVertex3f(130,6,88);
			glNormal3f(0,0,1);
			glVertex3f(140,6,88);
			glNormal3f(0,0,1);
			glVertex3f(140,0,88);
		glEnd();
	glPopMatrix();
	
}

//spawns the tektites in random locations within the left area
void spawnTektites(){
	int randomx = ((((float) rand()/RAND_MAX)*79)+8);
	int randomz = ((((float) rand()/RAND_MAX)*54)+88);
	Tektite tek(randomx,randomz);
	tektites.push_back(tek);

	randomx = ((((float) rand()/RAND_MAX)*79)+8);
	randomz = ((((float) rand()/RAND_MAX)*54)+88);
	Tektite tek2(randomx,randomz);
	tektites.push_back(tek2);

	randomx = ((((float) rand()/RAND_MAX)*79)+8);
	randomz = ((((float) rand()/RAND_MAX)*54)+88);
	Tektite tek3(randomx,randomz);
	tektites.push_back(tek3);

	randomx = ((((float) rand()/RAND_MAX)*79)+8);
	randomz = ((((float) rand()/RAND_MAX)*54)+88);
	Tektite tek4(randomx,randomz);
	tektites.push_back(tek4);
}

void spawnOctoroksU(){
	//creates four enemies starting at random positions
	int randomx = ((((float) rand()/RAND_MAX)*74)+113);
	int randomz = ((((float) rand()/RAND_MAX)*59)+13);
	Octorok octo(randomx,randomz,0);
	octoroks.push_back(octo);

	randomx = ((((float) rand()/RAND_MAX)*74)+113);
	randomz = ((((float) rand()/RAND_MAX)*59)+13);
	Octorok octo2(randomx,randomz,0);
	octoroks.push_back(octo2);

	randomx = ((((float) rand()/RAND_MAX)*74)+113);
	randomz = ((((float) rand()/RAND_MAX)*59)+13);
	Octorok octo3(randomx,randomz,0);
	octoroks.push_back(octo3);

	randomx = ((((float) rand()/RAND_MAX)*74)+113);
	randomz = ((((float) rand()/RAND_MAX)*59)+13);
	Octorok octo4(randomx,randomz,0);
	octoroks.push_back(octo4);
}


//load the octorocks on the right screen depending on players x value
void spawnOctoroksR(){
	//creates four enemies in random positions
	int randomx = ((((float) rand()/RAND_MAX)*59)+228);
	int randomz = ((((float) rand()/RAND_MAX)*54)+88);
	Octorok octo(randomx,randomz,1);
	octoroks.push_back(octo);

	randomx = ((((float) rand()/RAND_MAX)*59)+228);
	randomz = ((((float) rand()/RAND_MAX)*54)+88);
	Octorok octo2(randomx,randomz,1);
	octoroks.push_back(octo2);

	randomx = ((((float) rand()/RAND_MAX)*59)+228);
	randomz = ((((float) rand()/RAND_MAX)*54)+88);
	Octorok octo3(randomx,randomz,1);
	octoroks.push_back(octo3);

	randomx = ((((float) rand()/RAND_MAX)*59)+228);
	randomz = ((((float) rand()/RAND_MAX)*54)+88);
	Octorok octo4(randomx,randomz,1);
	octoroks.push_back(octo4);
}

//keeps track of how long the player is invulnerable after taking a hit
void invulnCounter(){
	if (invulntime == 100){
		invulntime = 0;
	}else if (invulntime > 0){
		invulntime++;
	}
}

//Deals damage to a player after they're hit and moves them back slightly depending on the given angle
void playerHit(float ang){
	if (invulntime == 0){
		hud.decreaseHP();
		invulntime = 1;
	}
	if (ang == 0){
		eye[0] += 1;
	}

	if (ang == 90){
		eye[2] -= 1;
	}

	if (ang == 180){
		eye[0] -= 1;
	}

	if (ang == 270){
		eye[2] += 1;
	}
}


//update the position of the enemies and their projectiles
void tektiteUpdate(){
	if (!tektites.empty()){
		for (list<Tektite>::iterator it = tektites.begin(); it != tektites.end(); it++){
			(*it).Animate();
			(*it).Draw();
			if ((*it).x >= (eye[0]-hitbox) && (*it).x <= (eye[0]+hitbox) && (*it).z >= (eye[2]-hitbox) && (*it).z <= (eye[2]+hitbox)){
				(*it).action = 2;
				playerHit((*it).ang);
			}
		}
	}
	
}

void octorokUpdate(){
	if (!octoroks.empty()){
			for (list<Octorok>::iterator it = octoroks.begin(); it != octoroks.end(); it++){
				(*it).Animate();
				(*it).Draw();
				if ((*it).shoot){
					Bullet bullet((*it).x,(*it).z,(*it).ang); //add a bullet to the list
					bullets.push_back(bullet);
				}
				if ((*it).x >= (eye[0]-hitbox) && (*it).x <= (eye[0]+hitbox) && (*it).z >= (eye[2]-hitbox) && (*it).z <= (eye[2]+hitbox)){	//damage player if collides with octo
					playerHit((*it).ang);
					if ((*it).ang == 0){
						(*it).action = 3;
					}else if((*it).ang == 90){
						(*it).action = 2;
					}else if((*it).ang == 180){
						(*it).action = 1;
					}else if((*it).ang == 270){
						(*it).action = 4;
					}
				}
			}
		}
		if (!bullets.empty()){
			for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++){
				(*it).Animate();
				(*it).Draw();
				
			}
		}

		if (!bullets.empty()){
			list<Bullet>::iterator it = bullets.begin();
			while (it != bullets.end()){
				if ((*it).x >= (eye[0]-hitbox) && (*it).x <= (eye[0]+hitbox) && (*it).z >= (eye[2]-hitbox) && (*it).z <= (eye[2]+hitbox)){	//hitbox is 4x4
					playerHit((*it).ang);
					bullets.erase(it++);
				}
				else if ((*it).distance > 40){				//distance before a bullet disappears
					bullets.erase(it++);
				}else{
					++it;
				}
			}
		}
	}

//Determines when enemies spawn and despawn depending on location
void spawnBoundaries(){
	if (eye[0]<163&&eye[0]>150&&eye[2]<87&&eye[2]>85&&spawn==false){		//Spawn octoroks on top screen
		spawn=true;
		spawnOctoroksU();
	}else if (eye[0]<163&&eye[0]>150&&eye[2]<90&&eye[2]>88&&spawn==true){
		spawn=false;
		octoroks.clear();
	}

	if (eye[0]<193&&eye[0]>191&&eye[2]<125&&eye[2]>113&&spawn==false){		
		spawn=true;
		spawnOctoroksR();
	}else if (eye[0]<190&&eye[0]>188&&eye[2]<125&&eye[2]>113&&spawn==true){
		spawn=false;
		octoroks.clear();
	}

	if (eye[0]<107&&eye[0]>105&&eye[2]<125&&eye[2]>113&&spawn==false){		//Spawn tektites on left screen	
		spawn=true;
		spawnTektites();
	}else if (eye[0]<110&&eye[0]>108&&eye[2]<125&&eye[2]>113&&spawn==true){
		spawn=false;
		tektites.clear();
	}
}

void animateAttack(){
	if (attackCounter==0){
		hud.sword=1;
	}
	else if (attackCounter==5){
		hud.sword=2;
	}
	else if (attackCounter==10){
		hud.sword=3;
	}
	else if (attackCounter==15){
		hud.sword=4;
	}
	else if (attackCounter==20){
		hud.sword=5;
	}
	else if (attackCounter==25){
		hud.sword=6;
	}
	else if (attackCounter==30){
		hud.sword=7;
	}
	else if (attackCounter==35){
		attackAnimation = false;
		attackCounter=false;
		hud.sword=1;
	}
	hud.attack();
}

void display()
{

	if (playGame == false){
		menuScreen();
	}

	if (playGame == true){
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	eye[1] = 5; //restricts the camera to a height of 5. 
	gluLookAt(eye[0],eye[1],eye[2],eye[0]+direction[0],eye[1]+direction[1],eye[2]+direction[2],0,1,0); //Set the camera to look at a specific location in the scene

	//initialize lighting
	initLighting();
	initFlameLighting();

	//increments the invulnerability counter
	invulnCounter();
	
	//conditionals that checks to see if the player enters/leaves the cave
	if (eye[0]<140&&eye[0]>130&&eye[2]>86&&eye[2]<92&&inCave==false){
		inCave=true;
		eye[2] = 85;
	}
	else if (eye[0]<140&&eye[0]>130&&eye[2]>86&&eye[2]<89&&inCave==true){
		inCave=false;
		eye[2] = 92;
	}
	// if player is currently in the cave
	if (inCave==true){
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		drawCave();
	}
	else{ // player is not in the cave
		glEnable(GL_LIGHT3);
		glDisable(GL_LIGHT1);
    	glDisable(GL_LIGHT2);
		
		//call the drawTerrain function
		terrain.drawTerrain();
		spawnBoundaries();
		//updaet all the enemies
		octorokUpdate();
		tektiteUpdate();
		//draw the ground
		drawPlane();
	}
	//draw the door to the cave
	cave();
	
	if (!projectiles.empty()){
			for (list<Projectile>::iterator it = projectiles.begin(); it != projectiles.end(); it++){
				(*it).Animate();
				(*it).Draw();
				if ((*it).distance>100){
					it=projectiles.erase(it);
					if(it==projectiles.end()){
						break;
					}
				}
			}
	}
	if (!bombs.empty()){
			for (list<Bomb>::iterator it =bombs.begin(); it !=bombs.end(); it++){
				(*it).Draw();
				(*it).Timer();
			}
	}
	if (tektites.empty()&&octoroks.empty()){
		for (list<Bomb>::iterator it =bombs.begin(); it !=bombs.end(); it++){
			if ((*it).timer>295){
				(*it).Explode();
			}
			if ((*it).timer>300){
				it=bombs.erase(it);
			}
			if (it==bombs.end()){
				break;
			}
		}
	}
	if (!bombs.empty()&&!tektites.empty()){
			for (list<Bomb>::iterator it =bombs.begin(); it !=bombs.end(); it++){
				for (list<Tektite>::iterator it2 = tektites.begin(); it2 != tektites.end(); it2++){
					if((*it).timer>300&&(*it2).x<(*it).x+13&&(*it2).x>(*it).x-13&&(*it2).z<(*it).z+13&&(*it2).z>(*it).z-13&&(*it2).y<5){
						it2 = tektites.erase(it2);
						float randomNum = ((((float) rand()/RAND_MAX)*50)+1);
						if (randomNum>40){
							hud.bombs+=1;
						}
						else if(randomNum<10){
							hud.increaseHP();
						}
						else if(randomNum>=10&&randomNum<=20){
							hud.increaseRupees();
						}
						
						if (it2==tektites.end()){
							break;
						}
					}
				}
				if ((*it).timer>295){
					(*it).Explode();
				}
				if ((*it).timer>300){
					it = bombs.erase(it);
				}
				if (it==bombs.end()){
					break;
				}	
			}
		}
	if (!bombs.empty()&&!octoroks.empty()){
			for (list<Bomb>::iterator it =bombs.begin(); it !=bombs.end(); it++){
				for (list<Octorok>::iterator it2 = octoroks.begin(); it2 != octoroks.end(); it2++){
					if((*it).timer>300&&(*it2).x<(*it).x+13&&(*it2).x>(*it).x-13&&(*it2).z<(*it).z+13&&(*it2).z>(*it).z-13){
						it2 = octoroks.erase(it2);
						float randomNum = ((((float) rand()/RAND_MAX)*50)+1);
						if (randomNum>40){
							hud.bombs+=1;
						}
						else if(randomNum<10){
							hud.increaseHP();
						}
						else if(randomNum>=10&&randomNum<=20){
							hud.increaseRupees();
						}
						if (it2==octoroks.end()){
							break;
						}
					}
				}
				if ((*it).timer>295){
					(*it).Explode();
				}
				if ((*it).timer>300){
					it =bombs.erase(it);
				}
				if (it==bombs.end()){
					break;
				}	
			}
		}
	if(!octoroks.empty()&&!projectiles.empty()){
		for (list<Octorok>::iterator it = octoroks.begin(); it != octoroks.end(); it++){
			for (list<Projectile>::iterator it2 = projectiles.begin(); it2 != projectiles.end(); it2++){
				if ((*it2).x>(*it).x-hitbox&&(*it2).x<(*it).x+hitbox &&(*it2).y>1&&(*it2).y<5&&(*it2).z>(*it).z-hitbox&&(*it2).z<(*it).z+hitbox){
					
					it2 = projectiles.erase(it2);
					it = octoroks.erase(it);
					float randomNum = ((((float) rand()/RAND_MAX)*50)+1);
					if (randomNum>40){
						hud.bombs+=1;
					}
					else if(randomNum<10){
						hud.increaseHP();
					}
					else if(randomNum>=10&&randomNum<=20){
						hud.increaseRupees();
					}
					if (it2==projectiles.end()||it==octoroks.end()){
						break;
					}
				}

			}
			if (it==octoroks.end()){
				break;
			}
		}
	}
	
	if(!tektites.empty()&&!projectiles.empty()){
		for (list<Tektite>::iterator it = tektites.begin(); it != tektites.end(); it++){
			for (list<Projectile>::iterator it2 = projectiles.begin(); it2 != projectiles.end(); it2++){
				if ((*it2).x>(*it).x-hitbox&&(*it2).x<(*it).x+hitbox &&(*it2).y>(*it).y-hitbox&&(*it2).y<(*it).y+hitbox&&(*it2).z>(*it).z-hitbox&&(*it2).z<(*it).z+hitbox){
					it2 = projectiles.erase(it2);
					it = tektites.erase(it);
					float randomNum = ((((float) rand()/RAND_MAX)*50)+1);
					if (randomNum>40){
						hud.bombs+=1;
					}
					else if(randomNum<10){
						hud.increaseHP();
					}
					else if(randomNum>=10&&randomNum<=20){
						hud.increaseRupees();
					}
					if (it2==projectiles.end()||it==tektites.end()){
						break;
					}
				}

			}
			if (it==tektites.end()){
				break;
			}
		}
	}

	if (attackAnimation ==true){
		animateAttack();
		attackCounter++;
	}
	
	projectileCounter++;
	//draw the hud
	hud.HUD(eye,inCave);
	}
	glutSwapBuffers();
	
}

// Attacking function attack hits enemy, then enemy is removed
void attack(){
	float hp = hud.getHP();
	if (projectileCounter>50&&hp==3){
		Projectile projectile(eye[0],eye[1]-1,eye[2],direction[0],direction[1],direction[2]); //add a projectile to the list
		projectiles.push_back(projectile);
		projectileCounter=0;
	}
	
	if(!octoroks.empty()){
		for (list<Octorok>::iterator it = octoroks.begin(); it != octoroks.end(); it++){
			if (abs(eye[0] + 5*direction[0] - (*it).x) <5 &&abs(eye[2] + 5*direction[2] - (*it).z) <5){
					it = octoroks.erase(it);
					float randomNum = ((((float) rand()/RAND_MAX)*50)+1);
					if (randomNum>40){
						hud.bombs+=1;
					}
					else if(randomNum<10){
						hud.increaseHP();
					}
					else if(randomNum>=10&&randomNum<=20){
						hud.increaseRupees();
					}
					if (it==octoroks.end()){
						break;
					}
			}
		}
	}
	if(!tektites.empty()){
		for (list<Tektite>::iterator it = tektites.begin(); it != tektites.end(); it++){
			if (abs(eye[0] + 5*direction[0] - (*it).x) <5 &&abs(eye[2] + 5*direction[2] - (*it).z) <5&&(*it).y<5){
					it = tektites.erase(it);
					float randomNum = ((((float) rand()/RAND_MAX)*50)+1);
					if (randomNum>40){
						hud.bombs+=1;
					}
					else if(randomNum<10){
						hud.increaseHP();
					}
					else if(randomNum>=10&&randomNum<=20){
						hud.increaseRupees();
					}
					if (it==tektites.end()){
						break;
					}
			}
		}
	}
	attackAnimation=true;
	
}

void addBomb(){
		int bombAmount = hud.bombs;
		if (bombAmount>0){
			Bomb bomb(eye[0],eye[2],direction[0],direction[2]); //add a bomb to the list
			bombs.push_back(bomb);
			hud.bombs=bombAmount-1;
		}
}

//keyboard function
void kbd(unsigned char key, int x, int y){
	camera.kbd(key,x,y,direction,eye);
	//hud.kbd(key,x,y,direction,eye);
	if (key=='b'||key=='B'){
		addBomb();
	}
	if (key==(char)32&&hud.sword!=0){
		attack();
		
	}
	if (key==(char)13){
		if (playGame == false){
			playGame = true;
		}
	}
}

//special keyboard function
void specialKbd(int key, int x, int y){
	if (inCave==true){ // if player is in cave, restrict movement inside
		if(eye[0]>112&&eye[0]<158&&eye[2]<87&&eye[2]>40){
			camera.specialKbd(key,x,y,direction,eye,terrain,inCave);
		}
		else{ //if outside of bounds, move player back inside.
			if(eye[0]<=112){
				eye[0]=113;
			}
			if(eye[0]>=158){
				eye[0]=157;
			}
			if(eye[2]<=40){
				eye[2]=41;
			}
			if(eye[2]>=87){
				eye[2]=86;
			}
		}
	}
	else{
		camera.specialKbd(key,x,y,direction,eye,terrain,inCave); //otherwise move around environment
	}

}

/* timer function
 *   Will delay the program from redisplaying until the specified time has elapsed.
 */
void timer(int x)
{
	 // draw it and reinitialise the timer
	glutPostRedisplay();
	glutTimerFunc(15,timer,0);
}

//function that displays the instructions in the console window
void Instructions(){
	printf(" ------------------------------------------\n");
	printf("|        Legend of Zelda - Controls        |\n");
	printf("|------------------------------------------|\n");
	printf("|                                          |\n");
	printf("| - Use the arrow keys to move / strafe    |\n");
	printf("| - Use WASD to look around                |\n");
	printf("|                                          |\n");
	printf("| - Spacebar will swing your sword         |\n");
	printf("|   - When at full health, you will also   |\n");
	printf("|     shoot a projectile.                  |\n");
	printf("|                                          |\n");
	printf("| - Press B to place a bomb                |\n");
	printf("|                                          |\n");
	printf("|------------------------------------------|\n");
	printf("| - To get your sword, you must enter the  |\n");
	printf("|   cave and grab it.                      |\n");
	printf("|                                          |\n");
	printf("| - Enemies will only spawn when you enter |\n");
	printf("|   the area.                              |\n");
	printf(" ------------------------------------------\n");
}
//Main function
int main(int argc, char** argv)
{
	srand(time(NULL)); //initialize random values
	Instructions(
		); //Display Instructions
	
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
	//Initialize 3D generated terrain window values
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Legend of Zelda");
	glutDisplayFunc(display);
	
	//enable culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50,2,1,500);

	//set clear colour to blue
	glClearColor(0, 0, 1, 0);

	//change back to modelView mode
	glMatrixMode(GL_MODELVIEW);

	terrain.initializeArray();	
	
	//call circles algorithm for the initial terrain
	for(int i=0;i<300;i++){
		float r1 = ((double) rand() / (RAND_MAX))*300;
		float r2 = ((double) rand() / (RAND_MAX))*150;	
		terrain.circleAlgorithm(2.5,50,r1,r2);
	}
	//gets the cross product of all the vertices
	terrain.crossProduct();
	camera.initializeValues(direction,eye);
	glutKeyboardFunc(kbd);
	glutSpecialFunc(specialKbd);
	
	
	//initialize lighting
	initLighting();
	initFlameLighting();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	
	hud.bombs=1;

	timer(0);

	//start the program!
	glutMainLoop();
	return 0;
}