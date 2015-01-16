#include "CameraControl.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glut.h>
#include <gl/gl.h>

float angle=-(3.14/2);
float angley=0.0;

void CameraControl::kbd(unsigned char key, int x, int y,float direction[3],float eye[3])
{
	
	// if the "w" key is pressed rotate the camera to look upwards
	if(key == 'w' || key == 'W')
	{		
		if (angley<1.5){
			angley = angley +0.1;
			direction[1] =   sin(angley);
		}
}
	
	// if the "a" key is pressed rotate the camera to look left
	if(key == 'a' || key == 'A')
	{
		angle = angle -0.1;
		direction[0] =   sin(angle);
		direction[2] = - cos(angle);
			
	}
	
	// if the "s" key is pressed rotate the camera to look downwards
	if(key == 's' || key == 'S')
	{
		if (angley>-1.5){
			angley = angley -0.1;
			direction[1] =   sin(angley);
		}
	}
	
	// if the "d" key is pressed rotate the camera to look right
	if(key == 'd' || key == 'D')

	{
		angle = angle + 0.1;
		direction[0] =   sin(angle);
		direction[2] =  -cos(angle);
	}

	if(key == 27){	// If the Esc key is pressed, exit the program.
		exit(0);
	}
}

//Function for when the arrow keys are pressed
void CameraControl::specialKbd(int key, int x, int y,float direction[3],float eye[3],Terrain terrain,bool inCave)
{
	float zoom = 0.5;

	//If the up arrow key is pressed, move forward
	if(key == GLUT_KEY_UP)
	{
		
		eye[0] += direction[0]*zoom;
		eye[1] += direction[1]*zoom;
		eye[2] += direction[2]*zoom;
		

		//Checks to see if user is walking into part of the terrain, and if so restricting their movement
		if (!inCave){
			int x2=eye[0];
			int y2=eye[2];
			if (direction[0]!=0){
				x2 = (int)(eye[0]+ 2*(direction[0]/abs(direction[0])));
			}
			if (direction[2]!=0){
				y2 = (int)(eye[2]+2*(direction[2]/abs(direction[2])));
			}
			if (terrain.hMapArray[x2][y2]!=0){
				eye[0] -= direction[0]*zoom;
				eye[1] -= direction[1]*zoom;
				eye[2] -= direction[2]*zoom;
			}
		}
	}
	
	//If the left arrow key is pressed, strafe left
	if(key == GLUT_KEY_LEFT)
	{
		eye[0] += sin(angle-3.14/2)*zoom;
		eye[2] += -cos(angle-3.14/2)*zoom;
		
		//Checks to see if user is walking into part of the terrain, and if so restricting their movement
		if (!inCave){
		
			int x = (int)(eye[0]+ 2*((sin(angle-3.14/2))/abs(sin(angle-3.14/2))));
			int y = (int)(eye[2]+2*((-cos(angle-3.14/2))/abs(-cos(angle-3.14/2))));
			if (terrain.hMapArray[x][y]!=0){
				eye[0] -= sin(angle-3.14/2)*zoom;
				eye[2]  -= -cos(angle-3.14/2)*zoom;
			}
		}
	}
	
	//If the down arrow key is pressed, move backward
	if(key == GLUT_KEY_DOWN)
	{
		
		eye[0] -= direction[0]*zoom;
		eye[1] -= direction[1]*zoom;
		eye[2] -= direction[2]*zoom;
		
		//Checks to see if user is walking into part of the terrain, and if so restricting their movement
		if (!inCave){
			int x2=eye[0];
			int y2=eye[2];
			if (direction[0]!=0){
				x2 = (int)(eye[0]- 2*(direction[0]/abs(direction[0])));
			}
			if (direction[2]!=0){
				y2 = (int)(eye[2]-2*(direction[2]/abs(direction[2])));
			}
			if (terrain.hMapArray[x2][y2]!=0){
				eye[0] += direction[0]*zoom;
				eye[1] += direction[1]*zoom;
				eye[2] += direction[2]*zoom;
			}
		}
	}
	
	//If the right arrow key is pressed, strafe right
	if(key ==GLUT_KEY_RIGHT)
	{	eye[0] -= sin(angle-3.14/2)*zoom;
		eye[2] -= -cos(angle-3.14/2)*zoom;
		
		//Checks to see if user is walking into part of the terrain, and if so restricting their movement
		if (!inCave){
			int x = (int)(eye[0]- 2*((sin(angle-3.14/2))/abs(sin(angle-3.14/2))));
			int y = (int)(eye[2]-2*((-cos(angle-3.14/2))/abs(-cos(angle-3.14/2))));
			if (terrain.hMapArray[x][y]!=0){
				eye[0] += sin(angle-3.14/2)*zoom;
				eye[2]  += -cos(angle-3.14/2)*zoom;
			}
		}
	}
}

//Initialize the values at teh beginning of the game
void CameraControl::initializeValues(float direction[3], float eye[3]){
	eye[0] = 150.0;
	eye[1] = 0;	
	eye[2] = 115;
	direction[0] = -1.0;
	direction[1] = 0;
	direction[2] = 0;
}