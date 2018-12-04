////////////////////////////////////////////////////////////////////
//Main driver file - Gets everything started
////////////////////////////////////////////////////////////////////
using namespace std;

/*--------------------------------------------//
Includes

//--------------------------------------------*/
	#include <stdlib.h>
    #include "../deps/gl/glut.h"
	#include "../deps/stb/stb_image.h"

    #include "GLOBALS.h"
	#include "simulation/game.h"

/*--------------------------------------------//
Globals
//--------------------------------------------*/
	GLint currWindowSize[2];//Size of the window
	GLint currViewportSize[2];//Size of the viewport
	game* session;
	unsigned int window;
	unsigned int index;

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
        glClear(GL_COLOR_BUFFER_BIT);

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
		session->predraw();

		//Set up the properties of the light source.
		GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat lightPosition[] = { 2.0f, 5.0f, 2.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		//Post light source draw
		session->postdraw();

		//Display a square
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, index);
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.0, 0.0);
				glVertex3d(-0.5f, -0.5f, 0.0f);
				glTexCoord2f(1.0, 0.0);
				glVertex3d( 0.5f, -0.5f, 0.0f);
				glTexCoord2f(1.0, 1.0);
				glVertex3d( 0.5f,  0.5f, 0.0f);
			glEnd();
			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.0, 0.0);
				glVertex3d(-0.5f, -0.5f, 0.0f);
				glTexCoord2f(1.0, 1.0);
				glVertex3d( 0.5f,  0.5f, 0.0f);
				glTexCoord2f(0.0, 1.0);
				glVertex3d(-0.5f,  0.5f, 0.0f);
			glEnd();
		glPopMatrix();

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
Main program entry point
//--------------------------------------------*/
	int main(int argc, char* argv[]){
		//setup default window size
		currWindowSize[0] = INIT_WINDOW_SIZE[0];
		currWindowSize[1] = INIT_WINDOW_SIZE[1];

		//setup session
		session = new game();

		//setup window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	    glutInitWindowPosition(INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1]);
		glutInitWindowSize(INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]);
        window = glutCreateWindow("Age of Agatha");
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 1.0f);
		glViewport(0, 0, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]);

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

		char* ImagePath = "textures/test.png";
		glGenTextures(1, &index);
	    glBindTexture(GL_TEXTURE_2D, index); 
	     // set the texture wrapping parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    // set texture filtering parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    // load image, create texture and generate mipmaps
	    int width, height, nrChannels;
	    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	    unsigned char *data = stbi_load((ImagePath), &width, &height, &nrChannels, 0);
	    if (data){
	    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	    }else{
	        printf("Failed to load texture %s\n", ImagePath);
	    }
	    stbi_image_free(data);

        //start the game
        glutMainLoop();

        return 0;// normal exit
	}