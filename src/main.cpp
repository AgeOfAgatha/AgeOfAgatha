////////////////////////////////////////////////////////////////////
//Main driver file - Gets everything started
////////////////////////////////////////////////////////////////////
using namespace std;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "globals.h"
	#include "simulation/game.h"

	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>

/*--------------------------------------------//
Globals
//--------------------------------------------*/
		game* app;

/*--------------------------------------------//
Error Message Callback for opengl
//--------------------------------------------*/
	void GLAPIENTRY MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ){
		//convert enums to strings
		char *csource, *ctype, *cseverity;
		switch(source){
			case 0x8246:{
				csource = "API";
				break;
			}
			case 0x8247:{
				csource = "WINDOW_SYSTEM";
				break;
			}
			case 0x8248:{
				csource = "SHADER_COMPILER";
				break;
			}
			case 0x8249:{
				csource = "THIRD_PARTY";
				break;
			}
			case 0x824A:{
				csource = "APPLICATION";
				break;
			}
			case 0x824B:{
				csource = "OTHER";
				break;
			}
			default:{
				csource = "UNKNOWN";
			}
		}
		switch(type){
			case 0x824C:{
				ctype = "ERROR";
				break;
			}
			case 0x824D:{
				ctype = "DEPRECATED_BEHAVIOR";
				break;
			}
			case 0x824E:{
				ctype = "UNDEFINED_BEHAVIOR";
				break;
			}
			case 0x824F:{
				ctype = "PORTABILITY";
				break;
			}
			case 0x8250:{
				ctype = "PERFORMANCE";
				break;
			}
			case 0x8251:{
				ctype = "OTHER";
				break;
			}
			case 0x8268:{
				ctype = "MARKER";
				break;
			}
			case 0x8269:{
				ctype = "PUSH_GROUP";
				break;
			}
			case 0x826A:{
				ctype = "POP_GROUP";
				break;
			}
			default:{
				ctype = "UNKNOWN";
			}
		}
		switch(severity){
			case 0x9146:{
				cseverity = "HIGH";
				break;
			}
			case 0x9147:{
				cseverity = "MEDIUM";
				break;
			}
			case 0x9148:{
				cseverity = "LOW";
				break;
			}
			case 0x826B :{
				cseverity = "NOTIFICATION";
				break;
			}
			default:{
				cseverity = "UNKNOWN";
			}
		}
		//print error message if high enough priority
		if (strcmp(cseverity, "NOTIFICATION") != 0)
			fprintf(stderr, "GL Error Callback:\tsource = %s,\ttype = %s,\tid = 0x%x\tseverity = %s,\n\tmessage:\t%s\n\n", csource, ctype, id, cseverity, message );
	}

/*--------------------------------------------//
GLUT functions - passes down class stack
//--------------------------------------------*/
	void Draw(){app->PreDraw(); app->Draw(); app->PostDraw(); glutSwapBuffers(); glFlush();}
	void Update(int value){value = app->Update(value); glutTimerFunc(TIMER, Update, value);}
	void KeypressASCII(unsigned char pressedKey, int mouseXPosition, int mouseYPosition){app->KeypressASCII(pressedKey,mouseXPosition,mouseYPosition);}
	void KeypressNonASCII(int pressedKey, int mouseXPosition, int mouseYPosition){app->KeypressNonASCII(pressedKey,mouseXPosition,mouseYPosition);}
	void Visible(int v){app->Visible(v);}
	void Reshape(int w, int h){app->Reshape(w,h);}
	void MenuUse(int v){app->MenuUse(v);}
	void HandleButton(int button, int state, int x, int y){app->HandleButton(button,state,x,y);}
	void HandleMotion(int x, int y){app->HandleMotion(x,y);}
	void HandleScroll(int wheel, int direc, int x, int y){app->HandleScroll(wheel, direc, x, y);}
	void ExitFunction(int value){}

/*--------------------------------------------//
Main - Entry point for program
//--------------------------------------------*/
	int main(int argc, char **argv) {
		glutInit(&argc, argv);

		//setup default window size
		GLint currWindowSize[2];//Size of the window
		currWindowSize[0] = INIT_WINDOW_SIZE_X;
		currWindowSize[1] = INIT_WINDOW_SIZE_Y;
		
		//create glut window
		int window;
	    glutInitWindowPosition(INIT_WINDOW_POSITION_X, INIT_WINDOW_POSITION_Y);
		glutInitWindowSize(currWindowSize[0], currWindowSize[1]);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	    glClearColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, 1.0f);
		window = __glutCreateWindowWithExit("Age of Agatha", ExitFunction);
		glViewport(0, 0, currWindowSize[0], currWindowSize[1]);

		glewExperimental = true;
		GLint GlewInitResult = glewInit();
		if (GlewInitResult != GLEW_OK) {
			printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
		}

		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);

		app = new game();

		glutTimerFunc(TIMER, Update, 0);
		glutMouseFunc(HandleButton);
		glutMotionFunc(HandleMotion);
		glutMouseWheelFunc(HandleScroll);
		glutPassiveMotionFunc(HandleMotion);
		glutKeyboardFunc(KeypressASCII);
        glutSpecialFunc(KeypressNonASCII);

        glutReshapeFunc(Reshape);
		glutDisplayFunc(Draw);
		glutVisibilityFunc(Visible);
		glutMenuStateFunc(MenuUse);

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(MessageCallback, 0);

		cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) << " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

		//start the game
		glutMainLoop();

		return 0;
	}
