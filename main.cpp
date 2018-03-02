////////////////////////////////////////////////////////////////////
/*
//Main driver file - Initializes everything else
*/
////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <ctime>

#include "globals.h"
#include "objects/world.cpp"

using namespace std;
/********************/
/* CONSTANT DEFINES */
/********************/
	#define TIMESTEP 3 //how often do we calculate physics?
	#define TIMEOUT 3 //how many iterations before an object is considered 'asleep'

/********************/
/* GLOBAL VARIABLES */
/********************/
	world simulation = world(TIMESTEP, TIMEOUT);

	// The initial window and viewport sizes (in pixels), set to ensure that
	// the aspect ration for the viewport, will be a constant. If the window
	// is resized, the viewport will be adjusted to preserve the aspect ratio.
	GLint currWindowSize[2]   = { INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1] };
	GLint currViewportSize[2] = { INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1] };

	// Application-specific variables
	float viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
	float viewerAltitude = INITIAL_VIEWER_ALTITUDE;

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
	void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
	void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition);
	void TimerFunction(int value);
	void Display();

	void ResizeWindow(GLsizei w, GLsizei h);
	float GenerateRandomNumber(float lowerBound, float upperBound);

/****************************/
/* Function implementations */
/****************************/
	// The main function sets up the data and the  //
	// environment to display the scene's objects. //
	int main(int argc, char* argv[])
	{
		// Set up the display window.
		glutInit(&argc, argv);
		glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	    glutInitWindowPosition( INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1] );
		glutInitWindowSize( currWindowSize[0], currWindowSize[1] );
		glutCreateWindow("Testing");world(TIMESTEP, TIMEOUT);

		mesh* obj = (mesh*) malloc(sizeof(mesh));
		*obj = mesh();

		vertex* a = (vertex*) malloc(sizeof(vertex));
		vertex* b = (vertex*) malloc(sizeof(vertex));
		vertex* c = (vertex*) malloc(sizeof(vertex));
		vertex* d = (vertex*) malloc(sizeof(vertex));

		*a = vertex(0,0,0);
		*b = vertex(1,0,0);
		*c = vertex(0,1,0);
		*d = vertex(1,1,0);

		obj->addTri(a,b,c);
		obj->addTri(d,b,c);
		simulation.addMesh(obj);
		

		// Specify the resizing and refreshing routines.
		glutReshapeFunc( ResizeWindow );
		glutKeyboardFunc( KeyboardPress );
		glutSpecialFunc( NonASCIIKeyboardPress );
		glutDisplayFunc( Display );
		glutTimerFunc( TIMER, TimerFunction, 0 );
		
		/* Set up standard lighting, shading, and depth testing. */
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 0.0f);
		glViewport(0, 0, currWindowSize[0], currWindowSize[1]);
		glutMainLoop();
		return 0;
	}

	// Function to react to ASCII keyboard keys pressed by the user. //
	// Used to alter arms/legs body speed                            //
	void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
	{
		// char pressedChar = char(pressedKey);
		// switch(pressedKey)
		// {
		// }
	}

	// Function to react to non-ASCII keyboard keys pressed by the user. //
	// This rotates the viewer giving different angles of the hopper.    //
	void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition)
	{
		glutIgnoreKeyRepeat(false);
		switch (pressedKey)
		{
			case GLUT_KEY_RIGHT: {
				viewerAzimuth += VIEWER_ANGLE_INCREMENT;
				if (viewerAzimuth > 2 * PI)
					viewerAzimuth -= 2 * PI;
				break;
			}
			case GLUT_KEY_LEFT: {
				viewerAzimuth -= VIEWER_ANGLE_INCREMENT;
				if (viewerAzimuth < 0.0)
					viewerAzimuth += 2 * PI;
				break;
			}
			case GLUT_KEY_UP: {
				viewerAltitude += VIEWER_ANGLE_INCREMENT;
				if (viewerAltitude > PI - VIEWER_ANGLE_INCREMENT)
					viewerAltitude = PI - VIEWER_ANGLE_INCREMENT;
				break;
			}
			case GLUT_KEY_DOWN: {
				viewerAltitude -= VIEWER_ANGLE_INCREMENT;
				if (viewerAltitude < VIEWER_ANGLE_INCREMENT)
					viewerAltitude = VIEWER_ANGLE_INCREMENT;
				break;
			}
		}
	}

	// Function to update any animation. //
	void TimerFunction(int value)
	{
		value++;
		//update
		glutPostRedisplay();
		glutTimerFunc(TIMER, TimerFunction, value);

		if (value % simulation.getTimeStep() == 0){
			simulation.update();
			value = 0;
		}
	}

	// Principal display routine: sets up material, lighting, //
	// and camera properties, clears the frame buffer, and    //
	// draws all objects within the window.                   //
	void Display()
	{
		/* Set up the properties of the surface material. */
		GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matShininess[] = { 200.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

		/* Set up the properties of the light source. */
		GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat lightPosition[] = { 2.0f, 5.0f, 2.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		// Set up the properties of the viewing camera.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Position and orient viewer.
		float position[] = { 0.0f, 0.0f, 0.0f };
		gluLookAt(position[0] + VIEWER_DISTANCE * sin(viewerAltitude) * sin(viewerAzimuth),
			position[1] + VIEWER_DISTANCE * cos(viewerAltitude),
			position[2] + VIEWER_DISTANCE * sin(viewerAltitude) * cos(viewerAzimuth),
			position[0], position[1], position[2],
			0.0, 1.0, 0.0);

		// Draw the objects
		simulation.draw();

		// Do the buffer swap.
		glutSwapBuffers();

		// Tell GLUT to do it again.
		glutPostRedisplay();
	}

	// Window-reshaping callback, adjusting the viewport to be as large  //
	// as possible within the window, without changing its aspect ratio. //
	void ResizeWindow(GLsizei w, GLsizei h)
	{
		currWindowSize[0] = w;
		currWindowSize[1] = h;
		if (ASPECT_RATIO > w / h)
		{
			currViewportSize[0] = w;
			currViewportSize[1] = int(w / ASPECT_RATIO);
		}
		else
		{
			currViewportSize[1] = h;
			currViewportSize[0] = int(h * ASPECT_RATIO);
		}

		glViewport(int(0.5f*(w - currViewportSize[0])), int(0.5f*(h - currViewportSize[1])), currViewportSize[0], currViewportSize[1]);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	// Generate a random floating-point value between the two parameterized values. //
	float GenerateRandomNumber(float lowerBound, float upperBound)
	{
		static bool firstTime = true;
		static time_t randomNumberSeed;

		if (firstTime)
		{
			time(&randomNumberSeed);
			firstTime = false;
			srand(int(randomNumberSeed));
		}

		return (lowerBound + ((upperBound - lowerBound) * (float(rand()) / RAND_MAX)));
	}