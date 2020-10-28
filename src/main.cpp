////////////////////////////////////////////////////////////////////
//Main driver file - Gets everything started
////////////////////////////////////////////////////////////////////
using namespace std;
#define STB_IMAGE_WRITE_IMPLEMENTATION

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "globals.h"
	#include "simulation/game.h"

	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>
	#include <sstream>

/*--------------------------------------------//
Globals
//--------------------------------------------*/
	GLint currWindowSize[2];//Size of the window
	int window;
	game* app;
	
/*--------------------------------------------//
GLUT functions - passes down class stack
//--------------------------------------------*/
	void Draw(){app->PreDraw(); app->Draw(); app->PostDraw(); glFinish(); glutPostRedisplay();}
	void Update(int value){value = app->Update(value); glutTimerFunc(UPDATE_TIMER, Update, value);}
	void KeypressASCII(unsigned char pressedKey, int mouseXPosition, int mouseYPosition){app->KeypressASCII(pressedKey,mouseXPosition,mouseYPosition);}
	void KeypressNonASCII(int pressedKey, int mouseXPosition, int mouseYPosition){app->KeypressNonASCII(pressedKey,mouseXPosition,mouseYPosition);}
	void Visible(int v){app->Visible(v);}
	void Reshape(int w, int h){app->Reshape(w,h);}
	void MenuUse(int v){app->MenuUse(v);}
	void HandleButton(int button, int state, int x, int y){app->HandleButton(button,state,x,y);}
	void HandleMotion(int x, int y){app->HandleMotion(x,y);}

/*--------------------------------------------//
Main - Entry point for program
//--------------------------------------------*/
	int main(int argc, char **argv) {
		glutInit(&argc, argv);

		//setup default window size
		currWindowSize[0] = INIT_WINDOW_SIZE_X;
		currWindowSize[1] = INIT_WINDOW_SIZE_Y;

		//create glut window
		glutInitWindowPosition(INIT_WINDOW_POSITION_X, INIT_WINDOW_POSITION_Y);
		glutInitWindowSize(currWindowSize[0], currWindowSize[1]);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glClearColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, 1.0f);
		window = glutCreateWindow("Age of Agatha");
		glViewport(0, 0, currWindowSize[0], currWindowSize[1]);

		glClearDepth(1.0f);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glutTimerFunc(UPDATE_TIMER, Update, 0);
		glutMouseFunc(HandleButton);
		glutMotionFunc(HandleMotion);
		glutPassiveMotionFunc(HandleMotion);
		glutKeyboardFunc(KeypressASCII);
		glutSpecialFunc(KeypressNonASCII);

		glutReshapeFunc(Reshape);
		glutDisplayFunc(Draw);
		glutVisibilityFunc(Visible);
		glutMenuStateFunc(MenuUse);

		app = new game(window);

		//start the game
		glutMainLoop();

		return 0;
	}
