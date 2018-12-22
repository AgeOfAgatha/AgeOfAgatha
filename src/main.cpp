////////////////////////////////////////////////////////////////////
//Main driver file - Gets everything started
////////////////////////////////////////////////////////////////////
using namespace std;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../deps/stb/stb_image.h"
	#include "../deps/gl/glew.h"
	#include "../deps/gl/freeglut.h"
	#include "common/vector.h"

    #include "GLOBALS.h"
	#include "simulation/game.h"

	#include <stdlib.h>
	#include <string.h>

/*--------------------------------------------//
Globals
//--------------------------------------------*/
	GLint currWindowSize[2];//Size of the window
	GLint currViewportSize[2];//Size of the viewport
	game* session;//The game object
	unsigned int window;//The window object

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
Keyboard Press Event Handler
Handles any keyboard key inputs from user
//--------------------------------------------*/
	void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition){
		if (pressedKey == 'q' || pressedKey == 'Q'){
            glutDestroyWindow(window);
        	exit(EXIT_SUCCESS);
        }
		glutIgnoreKeyRepeat(false);
		session->keypressASCII(pressedKey, mouseXPosition, mouseYPosition);
	}

/*--------------------------------------------//
Non ASCII Keyboard Press Event Handler
Handles any Non ASCII keyboard key inputs from user
This will catch certain events unable to be caught
normally
//--------------------------------------------*/
	void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition){
		glutIgnoreKeyRepeat(false);
		session->keypressNonASCII(pressedKey, mouseXPosition, mouseYPosition);
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
		value = session->update(value);
	}

/*--------------------------------------------//
Display Function
This is the main rendering hook
All graphically related tasks start here
Must handle things like drawing each element,
lights, shading, depth, etc etc
//--------------------------------------------*/
	void Display(){
		glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Pre light source draw
		session->predraw();

		//Render 3D objects
		session->draw(currWindowSize[0]/currWindowSize[1]);

		//Post 3D objects draw
		session->postdraw();

		//Do the buffer swap.
		glutSwapBuffers();

		//flush the drawing to screen
		glFlush(); 
	}

/*--------------------------------------------//
Resize Window Funciton
This hook needs to detect and resolve changes
in resolution and aspect ratio due to resizing
//--------------------------------------------*/
	void ResizeWindow(GLsizei w, GLsizei h){
		currWindowSize[0] = w;
		currWindowSize[1] = h;
		if (ASPECT_RATIO > (float(w) / float(h))){
			currViewportSize[0] = w;
			currViewportSize[1] = int(w / ASPECT_RATIO);
		}
		else{
			currViewportSize[1] = h;
			currViewportSize[0] = int(h * ASPECT_RATIO);
		}

		glViewport(int(0.5f*(w - currViewportSize[0])), int(0.5f*(h - currViewportSize[1])), currViewportSize[0], currViewportSize[1]);
	}

/*--------------------------------------------//
Exit program hook
called when the window is being closed
//--------------------------------------------*/
	void ExitFunction(int value){
	}

/*--------------------------------------------//
Main program entry point
//--------------------------------------------*/
	int main(int argc, char* argv[]){
		//setup default window size
		currWindowSize[0] = INIT_WINDOW_SIZE[0];
		currWindowSize[1] = INIT_WINDOW_SIZE[1];

		//setup window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	    glutInitWindowPosition(INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1]);
		glutInitWindowSize(INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]);
        window = __glutCreateWindowWithExit("Age of Agatha", ExitFunction);
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 1.0f);
		glViewport(0, 0, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]);

		glewExperimental=TRUE;
		GLenum err=glewInit();
		if(err!=GLEW_OK){
			//Problem: glewInit failed, something is seriously wrong.
			cout<<"glewInit failed, aborting."<<endl;
			exit(1);
		}
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(MessageCallback, 0);

		//setup session
		session = new game();

		//hook in the proper routines to OpenGL
        glutReshapeFunc(ResizeWindow);
        glutKeyboardFunc(KeyboardPress);
        glutSpecialFunc(NonASCIIKeyboardPress);
        glutDisplayFunc(Display);
        glutTimerFunc(TIMER, TimerFunction, 0);

        //setup lighting parameters
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

        //start the game
        glutMainLoop();

        return 0;// normal exit
	}
