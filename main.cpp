////////////////////////////////////////////////////////////////////
//Main driver file - Gets everything started
////////////////////////////////////////////////////////////////////
using namespace std;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "simulation/game.h"

/*--------------------------------------------//
Globals
//--------------------------------------------*/
	GLint currWindowSize[2];//Size of the window
	GLint currViewportSize[2];//Size of the viewport
	game session;

/*--------------------------------------------//
Keyboard Press Event Handler
Handles any keyboard key inputs from user
//--------------------------------------------*/
	void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition){
		glutIgnoreKeyRepeat(false);
		session.keypressASCII(pressedKey, mouseXPosition, mouseYPosition);
	}

/*--------------------------------------------//
Non ASCII Keyboard Press Event Handler
Handles any Non ASCII keyboard key inputs from user
This will catch certain events unable to be caught
normally
//--------------------------------------------*/
	void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition){
		glutIgnoreKeyRepeat(false);
		session.keypressNonASCII(pressedKey, mouseXPosition, mouseYPosition);
	}

/*--------------------------------------------//
Timer Function
This serves as our clock for the game
All updates to animation or changes in the game's
state should start here
//--------------------------------------------*/
	void TimerFunction(int value){
		glutPostRedisplay();//Update
		glutTimerFunc(TIMER, TimerFunction, value);//Reschedule ourselves
		value = session.update(value);
	}

/*--------------------------------------------//
Display Function
This is the main rendering hook
All graphically related tasks start here
Must handle things like drawing each element,
lights, shading, depth, etc etc
//--------------------------------------------*/
	void Display(){
		//Set up the properties of the surface material.
		GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matShininess[] = { 200.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

		//Set up the properties of the viewing camera.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Pre light source draw
		session.predraw();

		//Set up the properties of the light source.
		GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat lightPosition[] = { 2.0f, 5.0f, 2.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		//Post light source draw
		session.postdraw();

		//Do the buffer swap.
		glutSwapBuffers();

		//Tell GLUT to do it again.
		glutPostRedisplay();
	}

/*--------------------------------------------//
Resize Window Funciton
This hook needs to detect and resolve changes
in resolution and aspect ratio due to resizing
//--------------------------------------------*/
	void ResizeWindow(GLsizei w, GLsizei h){
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

/*--------------------------------------------//
Main program entry point
//--------------------------------------------*/
	int main(int argc, char* argv[]){
		//setup default window size
		currWindowSize[0] = INIT_WINDOW_SIZE[0];
		currWindowSize[1] = INIT_WINDOW_SIZE[1];
		//setup session
		session = game();

		//set up the display window.
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	    glutInitWindowPosition(INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1]);
		glutInitWindowSize(currWindowSize[0], currWindowSize[1]);
		glutCreateWindow("Testing");//Placeholder window name here for now

		//hook in the proper routines to OpenGL
		glutReshapeFunc(ResizeWindow);
		glutKeyboardFunc(KeyboardPress);
		glutSpecialFunc(NonASCIIKeyboardPress);
		glutDisplayFunc(Display);
		glutTimerFunc(TIMER, TimerFunction, 0);
		
		//setup lighting parameters
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 0.0f);
		glViewport(0, 0, currWindowSize[0], currWindowSize[1]);

		//start the game
		glutMainLoop();
		return 0;
	}