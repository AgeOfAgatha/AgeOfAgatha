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
		fprintf( stderr, "GL CALLBACK: %s source = 0x%x, type = 0x%x, id = 0x%x severity = 0x%x, message = %s\n",( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), source, type, id, severity, message );
		
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

		//Set up the properties of the surface material.
		GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matShininess[] = { 1.0f };
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
		session->predraw();

		//Set up the properties of the light source.
		GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat lightPosition[] = { 2.0f, 5.0f, 2.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		//Post light source draw
		session->postdraw(currWindowSize[0]/currWindowSize[1]);

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

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
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
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glEnable(GL_CULL_FACE);

		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_DITHER);
		glDisable(GL_STENCIL_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glReadBuffer(GL_BACK);
		glDrawBuffer(GL_BACK);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(TRUE);
		glFrontFace(GL_CCW);

		glClearStencil(0);
		glStencilMask(0xFFFFFFFF);
		glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		
		glCullFace(GL_BACK);
		glClearColor(1.0, 0.0, 0.0, 0.0);
		glClearDepth(1.0);

        //start the game
        glutMainLoop();

        return 0;// normal exit
	}
