#include "Terrain.h"
#include <math.h>
#include <glut.h>
#include <gl/gl.h>

float normalArray[300][150][3];
float hMapArray[300][150];


//Calculate the cross product of all the vertices
void Terrain::crossProduct(){
	for (int i=0; i<300; i++){		
		for (int j=0; j<150; j++){
			float bx = 0;
			float by = hMapArray[i][j+1]-hMapArray[i][j];
			float bz = 1;

			float cx = 1;
			float cy = hMapArray[i+1][j]-hMapArray[i][j];
			float cz = 0;
			
			float nx = by*cz - bz*cy;
			float ny = bz*cx - bx*cz;
			float nz = bx*cy - by*cx;

			float magnitude = sqrt((nx*nx) +(ny*ny)+(nz*nz));

			normalArray[i][j][0] = nx/magnitude;
			normalArray[i][j][1]= ny/magnitude;
			normalArray[i][j][2] = nz/magnitude;
		}
	}
	
}

//calls circle algorithm to generate the terrain
void Terrain::circleAlgorithm(float maxHeight, int circSize,float r1,float r2){
	for (int i=0; i<300; i++){
		for (int j=0;j<150;j++){
			float pd=0;
			pd = (sqrt(pow((i-r1),2)+pow((j-r2),2)))*2/circSize;
			if (fabs(pd)<=1){
				hMapArray[i][j] += (maxHeight/2) + cos(pd*3.14)*(maxHeight/2);
			}
		}
	}
	setZeros();
}

//Initialize the terrain to all zeros
void Terrain::initializeArray(){
	for (int i=0; i<300; i++){
		for (int j=0;j<150;j++){
			hMapArray[i][j] = 0;
		}
	}
}

//Set what parts of the terrain will be flt
void Terrain::setZeros(){

	//Farthest Left Screen

	//Creates a rectangle of flat ground
	for (int i=5; i<=90; i++){
		for (int j=85;j<=145;j++){
			hMapArray[i][j] = 0;
		}
	}
	// creates the opening to get to the next screen
	for (int i=90; i<=100; i++){
		for (int j=113;j<125;j++){
			hMapArray[i][j] = 0;
		}
	}


	// MAIN SCREEN 

	//Creates the path to the top screen
	for (int i=150; i<163; i++){
		for (int j=75;j<88;j++){
			hMapArray[i][j] = 0;
		}
	}
	
	//creates the opening where the cave goes
	for (int i=113; i<163; i++){
		for (int j=88;j<113;j++){
			hMapArray[i][j] = 0;
		}
	}
	
	//Always have the hill behind the cave be tall
	for (int i=113; i<150; i++){
		for (int j=75;j<88;j++){
			hMapArray[i][j] = 10;
		}
	}
	//Creates the main middle opening
	for (int i=113; i<188; i++){
		for (int j=113;j<138;j++){
			hMapArray[i][j] = 0;
		}
	}

	//creates the path to the right screen
	for (int i=188; i<200; i++){
		for (int j=113;j<125;j++){
			hMapArray[i][j] = 0;
		}
	}

	//creates the path to the left sceen
	for (int i=100; i<113; i++){
		for (int j=113;j<125;j++){
			hMapArray[i][j] = 0;
		}
	}

	//Farthest Right Screen

	//Creates a large rectangle of flat ground
	for (int i=225; i<=290; i++){
		for (int j=85;j<=145;j++){
			hMapArray[i][j] = 0;
		}
	}
	//creates the pathway to the middle screen
	for (int i=200; i<=225; i++){
		for (int j=113;j<125;j++){
			hMapArray[i][j] = 0;
		}
	}
	//Top Screen
	//Rectangle

	for (int i=110; i<190; i++){
		for (int j = 10; j<75;j++){
			hMapArray[i][j] = 0;
		}
	}

	//creates path to main screen

	for (int i=150; i<163; i++){
		for (int j=62;j<=75;j++){
			hMapArray[i][j] = 0;
		}
	}
	

}

//Algorithm that draws the terrain on the screen
void Terrain::drawTerrain(){
	float m_amb[4] = {0.0, 0.3, 0.0, 1};
	float m_dif[4] = {0, 0.37, 0.03, 1.0};
	float shiny = 27;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	for (int i=0; i<300; i++){
		glBegin(GL_TRIANGLE_STRIP);
		for (int j=0;j<150;j++){
			
			glNormal3fv(normalArray[i+1][j]);
			glVertex3f(i+1,hMapArray[i+1][j],j);	

			
			glNormal3fv(normalArray[i][j]); //Normals used for lighting
			glVertex3f(i,hMapArray[i][j],j);
		
			
			
			
		}
		glEnd();
	}

}