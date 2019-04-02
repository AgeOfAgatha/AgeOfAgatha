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
	#include "shader/shader.h"
	#include "objects/texture.h"
	#include "objects/light/spotlight.h"
	#include "objects/light/pointlight.h"
	#include "objects/light/direclight.h"

	#include <stdlib.h>
	#include <string.h>

/*--------------------------------------------//
Globals
//--------------------------------------------*/
	GLint currWindowSize[2];//Size of the window
	GLint currViewportSize[2];//Size of the viewport
	game* session;//The game object
	unsigned int window;//The window object

	//init shaders and buffer
	Shader *GeometryShader, *StencilShader, *PointLightShader, *DirecLightShader, *TransparencyShader;
	unsigned int gPosition, gNormal, gDiffuse, gResult, gDepth, gBuffer, gDepthBuff;
	unsigned int tDiffuse, tBuffer;

	//init lights
	spotlight *spot = new spotlight();
	pointlight *point = new pointlight();
	direclight *direc = new direclight();

	//init shapes
	texture *materials;
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO[6] = {0,0,0,0,0,0};
	unsigned int quadVAO = 0;
	unsigned int quadVBO[5] = {0,0,0,0,0};

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
		//session->keypressASCII(pressedKey, mouseXPosition, mouseYPosition);
	}

/*--------------------------------------------//
Non ASCII Keyboard Press Event Handler
Handles any Non ASCII keyboard key inputs from user
This will catch certain events unable to be caught
normally
//--------------------------------------------*/
	void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition){
		glutIgnoreKeyRepeat(false);
		//session->keypressNonASCII(pressedKey, mouseXPosition, mouseYPosition);
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
		//value = session->update(value);
	}

/*--------------------------------------------//
Renders a 1x1 cube
//--------------------------------------------*/
	void renderCube(){
	    // initialize (if necessary)
	    if (cubeVAO == 0){
	    	double vert[36][4] = {
				// back face
	            {-1.0f, -1.0f, -1.0f, 1.0f}, // bottom-left
	            { 1.0f,  1.0f, -1.0f, 1.0f}, // top-right
	            { 1.0f, -1.0f, -1.0f, 1.0f}, // bottom-right         
	            { 1.0f,  1.0f, -1.0f, 1.0f}, // top-right
	            {-1.0f, -1.0f, -1.0f, 1.0f}, // bottom-left
	            {-1.0f,  1.0f, -1.0f, 1.0f}, // top-left
	            // front face
	            {-1.0f, -1.0f,  1.0f, 1.0f}, // bottom-left
	            { 1.0f, -1.0f,  1.0f, 1.0f}, // bottom-right
	            { 1.0f,  1.0f,  1.0f, 1.0f}, // top-right
	            { 1.0f,  1.0f,  1.0f, 1.0f}, // top-right
	            {-1.0f,  1.0f,  1.0f, 1.0f}, // top-left
	            {-1.0f, -1.0f,  1.0f, 1.0f}, // bottom-left
	            // left face
	            {-1.0f,  1.0f,  1.0f, 1.0f}, // top-right
	            {-1.0f,  1.0f, -1.0f, 1.0f}, // top-left
	            {-1.0f, -1.0f, -1.0f, 1.0f}, // bottom-left
	            {-1.0f, -1.0f, -1.0f, 1.0f}, // bottom-left
	            {-1.0f, -1.0f,  1.0f, 1.0f}, // bottom-right
	            {-1.0f,  1.0f,  1.0f, 1.0f}, // top-right
	            // right face
	            { 1.0f,  1.0f,  1.0f, 1.0f}, // top-left
	            { 1.0f, -1.0f, -1.0f, 1.0f}, // bottom-right
	            { 1.0f,  1.0f, -1.0f, 1.0f}, // top-right         
	            { 1.0f, -1.0f, -1.0f, 1.0f}, // bottom-right
	            { 1.0f,  1.0f,  1.0f, 1.0f}, // top-left
	            { 1.0f, -1.0f,  1.0f, 1.0f}, // bottom-left     
	            // bottom face
	            {-1.0f, -1.0f, -1.0f, 1.0f}, // top-right
	            { 1.0f, -1.0f, -1.0f, 1.0f}, // top-left
	            { 1.0f, -1.0f,  1.0f, 1.0f}, // bottom-left
	            { 1.0f, -1.0f,  1.0f, 1.0f}, // bottom-left
	            {-1.0f, -1.0f,  1.0f, 1.0f}, // bottom-right
	            {-1.0f, -1.0f, -1.0f, 1.0f}, // top-right
	            // top face
	            {-1.0f,  1.0f, -1.0f, 1.0f}, // top-left
	            { 1.0f,  1.0f , 1.0f, 1.0f}, // bottom-right
	            { 1.0f,  1.0f, -1.0f, 1.0f}, // top-right     
	            { 1.0f,  1.0f,  1.0f, 1.0f}, // bottom-right
	            {-1.0f,  1.0f, -1.0f, 1.0f}, // top-left
	            {-1.0f,  1.0f,  1.0f, 1.0f}  // bottom-left   
			};
			//normal array
			double norm[36][3] = {
				// back face
	            { 0.0f,  0.0f, -1.0f}, // bottom-left
	            { 0.0f,  0.0f, -1.0f}, // top-right
	            { 0.0f,  0.0f, -1.0f}, // bottom-right         
	            { 0.0f,  0.0f, -1.0f}, // top-right
	            { 0.0f,  0.0f, -1.0f}, // bottom-left
	            { 0.0f,  0.0f, -1.0f}, // top-left
	            // front face
	            { 0.0f,  0.0f,  1.0f}, // bottom-left
	            { 0.0f,  0.0f,  1.0f}, // bottom-right
	            { 0.0f,  0.0f,  1.0f}, // top-right
	            { 0.0f,  0.0f,  1.0f}, // top-right
	            { 0.0f,  0.0f,  1.0f}, // top-left
	            { 0.0f,  0.0f,  1.0f}, // bottom-left
	            // left face
	            {-1.0f,  0.0f,  0.0f}, // top-right
	            {-1.0f,  0.0f,  0.0f}, // top-left
	            {-1.0f,  0.0f,  0.0f}, // bottom-left
	            {-1.0f,  0.0f,  0.0f}, // bottom-left
	            {-1.0f,  0.0f,  0.0f}, // bottom-right
	            {-1.0f,  0.0f,  0.0f}, // top-right
	            // right face
	            { 1.0f,  0.0f,  0.0f}, // top-left
	            { 1.0f,  0.0f,  0.0f}, // bottom-right
	            { 1.0f,  0.0f,  0.0f}, // top-right         
	            { 1.0f,  0.0f,  0.0f}, // bottom-right
	            { 1.0f,  0.0f,  0.0f}, // top-left
	            { 1.0f,  0.0f,  0.0f}, // bottom-left     
	            // bottom face
	            { 0.0f, -1.0f,  0.0f}, // top-right
	            { 0.0f, -1.0f,  0.0f}, // top-left
	            { 0.0f, -1.0f,  0.0f}, // bottom-left
	            { 0.0f, -1.0f,  0.0f}, // bottom-left
	            { 0.0f, -1.0f,  0.0f}, // bottom-right
	            { 0.0f, -1.0f,  0.0f}, // top-right
	            // top face
	            { 0.0f,  1.0f,  0.0f}, // top-left
	            { 0.0f,  1.0f,  0.0f}, // bottom-right
	            { 0.0f,  1.0f,  0.0f}, // top-right     
	            { 0.0f,  1.0f,  0.0f}, // bottom-right
	            { 0.0f,  1.0f,  0.0f}, // top-left
	            { 0.0f,  1.0f,  0.0f}  // bottom-left   
			};
			//color array
			double col[36][4]  = {
				// back face
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right         
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            // front face
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            // left face
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            // right face
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right         
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left     
	            // bottom face
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            // top face
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right     
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            {1.0f, 1.0f, 1.0f, 1.0f}  // bottom-left 
			};
			//texture coordinate array
			double st[36][2]  = {
				// back face
	            {0.0f, 0.0f}, // bottom-left
	            {1.0f, 1.0f}, // top-right
	            {1.0f, 0.0f}, // bottom-right         
	            {1.0f, 1.0f}, // top-right
	            {0.0f, 0.0f}, // bottom-left
	            {0.0f, 1.0f}, // top-left
	            // front face
	            {0.0f, 0.0f}, // bottom-left
	            {1.0f, 0.0f}, // bottom-right
	            {1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f}, // top-right
	            {0.0f, 1.0f}, // top-left
	            {0.0f, 0.0f}, // bottom-left
	            // left face
	            {1.0f, 0.0f}, // top-right
	            {1.0f, 1.0f}, // top-left
	            {0.0f, 1.0f}, // bottom-left
	            {0.0f, 1.0f}, // bottom-left
	            {0.0f, 0.0f}, // bottom-right
	            {1.0f, 0.0f}, // top-right
	            // right face
	            {1.0f, 0.0f}, // top-left
	            {0.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f}, // top-right         
	            {0.0f, 1.0f}, // bottom-right
	            {1.0f, 0.0f}, // top-left
	            {0.0f, 0.0f}, // bottom-left     
	            // bottom face
	            {0.0f, 1.0f}, // top-right
	            {1.0f, 1.0f}, // top-left
	            {1.0f, 0.0f}, // bottom-left
	            {1.0f, 0.0f}, // bottom-left
	            {0.0f, 0.0f}, // bottom-right
	            {0.0f, 1.0f}, // top-right
	            // top face
	            {0.0f, 1.0f}, // top-left
	            {1.0f, 0.0f}, // bottom-right
	            {1.0f, 1.0f}, // top-right     
	            {1.0f, 0.0f}, // bottom-right
	            {0.0f, 1.0f}, // top-left
	            {0.0f, 0.0f}  // bottom-left 
			};
			//texture blending array
			double blend[36][1]  = {
				// back face
	            {1.0f}, // bottom-left
	            {1.0f}, // top-right
	            {1.0f}, // bottom-right         
	            {1.0f}, // top-right
	            {1.0f}, // bottom-left
	            {1.0f}, // top-left
	            // front face
	            {1.0f}, // bottom-left
	            {1.0f}, // bottom-right
	            {1.0f}, // top-right
	            {1.0f}, // top-right
	            {1.0f}, // top-left
	            {1.0f}, // bottom-left
	            // left face
	            {1.0f}, // top-right
	            {1.0f}, // top-left
	            {1.0f}, // bottom-left
	            {1.0f}, // bottom-left
	            {1.0f}, // bottom-right
	            {1.0f}, // top-right
	            // right face
	            {1.0f}, // top-left
	            {1.0f}, // bottom-right
	            {1.0f}, // top-right         
	            {1.0f}, // bottom-right
	            {1.0f}, // top-left
	            {1.0f}, // bottom-left     
	            // bottom face
	            {1.0f}, // top-right
	            {1.0f}, // top-left
	            {1.0f}, // bottom-left
	            {1.0f}, // bottom-left
	            {1.0f}, // bottom-right
	            {1.0f}, // top-right
	            // top face
	            {1.0f}, // top-left
	            {1.0f}, // bottom-right
	            {1.0f}, // top-right     
	            {1.0f}, // bottom-right
	            {1.0f}, // top-left
	            {1.0f}  // bottom-left 
			};
			//Vertex Transparency array
			double trans[36][1]  = {
				// back face
	            {0.2f}, // bottom-left
	            {0.2f}, // top-right
	            {0.2f}, // bottom-right         
	            {0.2f}, // top-right
	            {0.2f}, // bottom-left
	            {0.2f}, // top-left
	            // front face
	            {0.2f}, // bottom-left
	            {0.2f}, // bottom-right
	            {0.2f}, // top-right
	            {0.2f}, // top-right
	            {0.2f}, // top-left
	            {0.2f}, // bottom-left
	            // left face
	            {0.2f}, // top-right
	            {0.2f}, // top-left
	            {0.2f}, // bottom-left
	            {0.2f}, // bottom-left
	            {0.2f}, // bottom-right
	            {0.2f}, // top-right
	            // right face
	            {0.2f}, // top-left
	            {0.2f}, // bottom-right
	            {0.2f}, // top-right         
	            {0.2f}, // bottom-right
	            {0.2f}, // top-left
	            {0.2f}, // bottom-left     
	            // bottom face
	            {0.2f}, // top-right
	            {0.2f}, // top-left
	            {0.2f}, // bottom-left
	            {0.2f}, // bottom-left
	            {0.2f}, // bottom-right
	            {0.2f}, // top-right
	            // top face
	            {0.2f}, // top-left
	            {0.2f}, // bottom-right
	            {0.2f}, // top-right     
	            {0.2f}, // bottom-right
	            {0.2f}, // top-left
	            {0.2f}  // bottom-left 
			};

		    glGenVertexArrays(1, &cubeVAO);
		    glBindVertexArray(cubeVAO);
		    glGenBuffers(6, cubeVBO);

		    //position
		    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[0]);
			glBufferData(GL_ARRAY_BUFFER, 36*4*sizeof(double), vert, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, (GLuint)4, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)0);

		    //normal
		    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[1]);
			glBufferData(GL_ARRAY_BUFFER, 36*3*sizeof(double), norm, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)1, (GLuint)3, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)1);

		    //color
		    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[2]);
			glBufferData(GL_ARRAY_BUFFER, 36*4*sizeof(double), col, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)2, (GLuint)4, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)2);

		    //texture coordinate
		    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[3]);
			glBufferData(GL_ARRAY_BUFFER, 36*2*sizeof(double), st, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)3, (GLuint)2, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)3);

		    //texture blend
		    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[4]);
			glBufferData(GL_ARRAY_BUFFER, 36*1*sizeof(double), blend, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)4, (GLuint)1, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)4);

		    //transparency
		    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[5]);
			glBufferData(GL_ARRAY_BUFFER, 36*1*sizeof(double), trans, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)5, (GLuint)1, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)5);
	    }
	    // render Cube
	    glBindVertexArray(cubeVAO);
	    glDrawArrays(GL_TRIANGLES, 0, 36);
	    glBindVertexArray(0);
	}

/*--------------------------------------------//
Renders a 1x1 quad
//--------------------------------------------*/
	void renderQuad(){
	    if (quadVAO == 0){
	        double vert[6][4] = {
	            // front face
	            {-1.0f, -1.0f,  0.0f, 1.0f}, // bottom-left
	            { 1.0f, -1.0f,  0.0f, 1.0f}, // bottom-right
	            { 1.0f,  1.0f,  0.0f, 1.0f}, // top-right
	            { 1.0f,  1.0f,  0.0f, 1.0f}, // top-right
	            {-1.0f,  1.0f,  0.0f, 1.0f}, // top-left
	            {-1.0f, -1.0f,  0.0f, 1.0f}, // bottom-left  
			};
			//normal array
			double norm[6][3] = {
	            // front face
	            { 0.0f,  0.0f,  1.0f}, // bottom-left
	            { 0.0f,  0.0f,  1.0f}, // bottom-right
	            { 0.0f,  0.0f,  1.0f}, // top-right
	            { 0.0f,  0.0f,  1.0f}, // top-right
	            { 0.0f,  0.0f,  1.0f}, // top-left
	            { 0.0f,  0.0f,  1.0f}, // bottom-left 
			};
			//color array
			double col[6][4]  = {
	            // front face
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f, 1.0f, 1.0f}, // top-left
	            {1.0f, 1.0f, 1.0f, 1.0f}, // bottom-left
			};
			//texture coordinate array
			double st[6][2]  = {
	            // front face
	            {0.0f, 0.0f}, // bottom-left
	            {1.0f, 0.0f}, // bottom-right
	            {1.0f, 1.0f}, // top-right
	            {1.0f, 1.0f}, // top-right
	            {0.0f, 1.0f}, // top-left
	            {0.0f, 0.0f}, // bottom-left
			};
			//texture blending array
			double blend[6][1]  = {
	            // front face
	            {1.0f}, // bottom-left
	            {1.0f}, // bottom-right
	            {1.0f}, // top-right
	            {1.0f}, // top-right
	            {1.0f}, // top-left
	            {1.0f}, // bottom-left
			};

		    glGenVertexArrays(1, &quadVAO);
		    glBindVertexArray(quadVAO);
		    glGenBuffers(5, quadVBO);

		    //position
		    glBindBuffer(GL_ARRAY_BUFFER, quadVBO[0]);
			glBufferData(GL_ARRAY_BUFFER, 6*4*sizeof(double), vert, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, (GLuint)4, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)0);

		    //normal
		    glBindBuffer(GL_ARRAY_BUFFER, quadVBO[1]);
			glBufferData(GL_ARRAY_BUFFER, 6*3*sizeof(double), norm, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)1, (GLuint)3, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)1);

		    //color
		    glBindBuffer(GL_ARRAY_BUFFER, quadVBO[2]);
			glBufferData(GL_ARRAY_BUFFER, 6*4*sizeof(double), col, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)2, (GLuint)4, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)2);

		    //texture coordinate
		    glBindBuffer(GL_ARRAY_BUFFER, quadVBO[3]);
			glBufferData(GL_ARRAY_BUFFER, 6*2*sizeof(double), st, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)3, (GLuint)2, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)3);

		    //texture blend
		    glBindBuffer(GL_ARRAY_BUFFER, quadVBO[4]);
			glBufferData(GL_ARRAY_BUFFER, 6*1*sizeof(double), blend, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)4, (GLuint)1, GL_DOUBLE, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)4);
	    }
	    glBindVertexArray(quadVAO);
	    glDrawArrays(GL_TRIANGLES, 0, 6);
	    glBindVertexArray(0);
	}

/*--------------------------------------------//
Display Function
This is the main rendering hook
All graphically related tasks start here
Must handle things like drawing each element,
lights, shading, depth, etc etc
//--------------------------------------------*/
	void GeometryPass(glm::mat4 projection, glm::mat4 view){
		GeometryShader->use();
		glDepthMask(GL_TRUE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		GeometryShader->setMat4("ProjectionMatrix", projection);
		GeometryShader->setMat4("ViewMatrix", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(10,0.5,10));
		model = glm::translate(model, glm::vec3(0,0,0));
		GeometryShader->setMat4("ModelMatrix", model);
		renderCube();

		glDepthMask(GL_FALSE);
	}

	void StencilPass(glm::vec4 camera, glm::mat4 projection, glm::mat4 view, unsigned int PosTex, unsigned int DifTex, unsigned int NorTex){
		StencilShader->use();

		glActiveTexture(GL_TEXTURE0 + PosTex);
        glBindTexture(GL_TEXTURE_2D, PosTex);
        glActiveTexture(GL_TEXTURE0 + DifTex);
        glBindTexture(GL_TEXTURE_2D, DifTex);
        glActiveTexture(GL_TEXTURE0 + NorTex);
        glBindTexture(GL_TEXTURE_2D, NorTex);

		StencilShader->setVec4("ViewPos", camera);
		StencilShader->setMat4("ProjectionMatrix", projection);
		StencilShader->setMat4("ViewMatrix", view);   

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glClear(GL_STENCIL_BUFFER_BIT);
		glStencilFunc(GL_ALWAYS, 0, 0);
		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, (glm::vec3)point->position);
		model = glm::scale(model, glm::vec3(10.f,10.f,1.0f));
		StencilShader->setMat4("ModelMatrix", model);
		renderCube();
	}

	void PointLightingPass(glm::vec4 camera, glm::mat4 projection, glm::mat4 view, unsigned int PosTex, unsigned int DifTex, unsigned int NorTex){
		PointLightShader->use();

		PointLightShader->setInt("PositionMap", PosTex);
		PointLightShader->setInt("ColorMap", DifTex);
		PointLightShader->setInt("NormalMap", NorTex);

		glActiveTexture(GL_TEXTURE0 + PosTex);
        glBindTexture(GL_TEXTURE_2D, PosTex);
        glActiveTexture(GL_TEXTURE0 + DifTex);
        glBindTexture(GL_TEXTURE_2D, DifTex);
        glActiveTexture(GL_TEXTURE0 + NorTex);
        glBindTexture(GL_TEXTURE_2D, NorTex);

		PointLightShader->setVec4("ViewPos", camera);
		PointLightShader->setMat4("ProjectionMatrix", projection);
		PointLightShader->setMat4("ViewMatrix", view);      

		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		//float BBoxScale = CalcPointLightBSphere(m_pointLight[PointLightIndex]);        
		//p.Scale(BBoxScale, BBoxScale, BBoxScale);

		PointLightShader->setVec3("PointLight.base.color", (glm::vec3)point->color);
		PointLightShader->setFloat("PointLight.base.ambientIntensity", point->ambientIntensity);
		PointLightShader->setFloat("PointLight.base.diffuseIntensity", point->diffuseIntensity);
		PointLightShader->setVec3("PointLight.position", (glm::vec3)point->position);
		PointLightShader->setFloat("PointLight.falloff.constant", point->falloff.constant);
		PointLightShader->setFloat("PointLight.falloff.linear", point->falloff.linear);
		PointLightShader->setFloat("PointLight.falloff.exponential", point->falloff.exponential);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, (glm::vec3)point->position);
		model = glm::scale(model, glm::vec3(10.f,10.f,1.0f));
		PointLightShader->setMat4("ModelMatrix", model);
		renderCube();

		glCullFace(GL_BACK);
		glDisable(GL_BLEND);
	}

	void DirecLightingPass(glm::vec4 camera, unsigned int PosTex, unsigned int DifTex, unsigned int NorTex){
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		DirecLightShader->use();

		DirecLightShader->setInt("PositionMap", PosTex);
		DirecLightShader->setInt("ColorMap", DifTex);
		DirecLightShader->setInt("NormalMap", NorTex);

		glActiveTexture(GL_TEXTURE0 + PosTex);
        glBindTexture(GL_TEXTURE_2D, PosTex);
        glActiveTexture(GL_TEXTURE0 + DifTex);
        glBindTexture(GL_TEXTURE_2D, DifTex);
        glActiveTexture(GL_TEXTURE0 + NorTex);
        glBindTexture(GL_TEXTURE_2D, NorTex);

		DirecLightShader->setVec4("ViewPos", camera);
        glm::mat4 model = glm::mat4(1.0f);
		DirecLightShader->setMat4("ProjectionMatrix", model);
        DirecLightShader->setMat4("ViewMatrix", model);
        DirecLightShader->setMat4("ModelMatrix", model);

        DirecLightShader->setVec3("DirecLight.base.color", (glm::vec3)direc->color);
        DirecLightShader->setFloat("DirecLight.base.ambientIntensity", direc->ambientIntensity);
        DirecLightShader->setFloat("DirecLight.base.diffuseIntensity", direc->diffuseIntensity);
        DirecLightShader->setVec3("DirecLight.direction", (glm::vec3)direc->direction);

        renderQuad();

		glDisable(GL_BLEND);
	}

	void TransparencyPass(glm::vec4 camera, glm::mat4 projection, glm::mat4 view, unsigned int DifTex, int y){
		TransparencyShader->use();

		glDepthMask(GL_FALSE);
		glEnable(GL_DEPTH_TEST);

		TransparencyShader->setInt("ColorMap", DifTex); 

		glActiveTexture(GL_TEXTURE0 + DifTex);
        glBindTexture(GL_TEXTURE_2D, DifTex);

		TransparencyShader->setMat4("ProjectionMatrix", projection);
		TransparencyShader->setMat4("ViewMatrix", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(5,0.1,5));
		model = glm::translate(model, glm::vec3(0,y*5,0));
		TransparencyShader->setMat4("ModelMatrix", model);
		renderCube();
	}

	void FinalPass(GLint width, GLint height){
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);

		glReadBuffer(GL_COLOR_ATTACHMENT3);
        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

	void Display(){
		glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Pre light source draw
		//session->predraw();

		//Render 3D objects
		//session->draw(currWindowSize[0]/currWindowSize[1]);

		//Post 3D objects draw
		//session->postdraw();

		//Position and orient camera.
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f );
		glm::quat quat = glm::quat(glm::vec3(-PI/8, PI/8, 0));
		glm::mat4 looking = glm::toMat4(quat);
		glm::vec4 camera = looking * glm::vec4(position.x + 0.0f, position.y + 0.0f, position.z + 3.0f*VIEWER_DISTANCE, 1.0f);

		//Create project matrix
        glm::mat4 projection;
	    projection = glm::perspective(glm::radians(FRUSTUM_FIELD_OF_VIEW), ASPECT_RATIO, FRUSTUM_NEAR_PLANE, FRUSTUM_FAR_PLANE);
	    
	    //Find up vector
	    glm::vec4 up = looking * glm::vec4(0,1,0,1);
	    //Create view matrix
        glm::mat4 view;
	    view = glm::lookAt(
		    glm::vec3(camera[0], camera[1], camera[2]), 		// Camera is at in World Space
		    position, 											// and looks at
		   	glm::vec3(up[0], up[1], up[2]) 						// up is
	    );

	    //Start deferred pass with geometry
	    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);
	    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	    glDrawBuffers(3, attachments);
	    GLuint clearColor[4] = {BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 1.0f};
	    glClearBufferuiv(GL_COLOR, 0, clearColor);
			GeometryPass(projection, view);

		glDrawBuffer(GL_COLOR_ATTACHMENT3);
		glClear(GL_COLOR_BUFFER_BIT);

		//point lighting
		glEnable(GL_STENCIL_TEST);
			glDrawBuffer(GL_NONE);
			StencilPass(camera, projection, view, gPosition, gDiffuse, gNormal);
			glDrawBuffer(GL_COLOR_ATTACHMENT3);
			PointLightingPass(camera, projection, view, gPosition, gDiffuse, gNormal);
		glDisable(GL_STENCIL_TEST);

		//directional lighting
		glDrawBuffer(GL_COLOR_ATTACHMENT3);
			DirecLightingPass(camera, gPosition, gDiffuse, gNormal);

		//transparency pass
	    for (int i = 20; i > 0; i-=2){
			//copy diffuse data into transparency buffer
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, tBuffer);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);

			glReadBuffer(GL_COLOR_ATTACHMENT3);
			glDrawBuffer(GL_COLOR_ATTACHMENT2);
	        glBlitFramebuffer(0, 0, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, 0, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], GL_COLOR_BUFFER_BIT, GL_LINEAR);

	        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);
		    glDrawBuffers(3, attachments);
		    	TransparencyPass(camera, projection, view, tDiffuse, i);

	    	//clear result buffer
			glDrawBuffer(GL_COLOR_ATTACHMENT3);
			glClear(GL_COLOR_BUFFER_BIT);

		    //point lighting
			glEnable(GL_STENCIL_TEST);
				glDrawBuffer(GL_NONE);
				StencilPass(camera, projection, view, gPosition, gDiffuse, gNormal);
				glDrawBuffer(GL_COLOR_ATTACHMENT3);
				PointLightingPass(camera, projection, view, gPosition, gDiffuse, gNormal);
			glDisable(GL_STENCIL_TEST);

			//directional lighting
			glDrawBuffer(GL_COLOR_ATTACHMENT3);
				DirecLightingPass(camera, gPosition, gDiffuse, gNormal);
	    }

		//final pass
		FinalPass(INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]);

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
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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
		//session = new game();

		materials = new texture("textures/test.png", 1);

		// configure lighting settings
	    // ------------------------------
		spot->ambientIntensity = 0.0f;
		spot->diffuseIntensity = 0.9f;
		spot->color = vec3(1.0f, 0.0f, 0.0f);
		spot->position  = vec3(5.0f, 1.5f, 0.0f);
		spot->direction = vec3(-1.0f, 0.0f, 0.0f);
		spot->falloff.linear = 0.01f;
		spot->cutoff =  20.0f;
		point->ambientIntensity = 0.0f;
		point->diffuseIntensity = 0.2f;
		point->color = vec3(0.0f, 0.0f, 1.0f);
		point->position = vec3(0.0f, 1.5f, 5.0f);
		point->falloff.constant = 0.0f;
		point->falloff.linear = 0.0f;
		point->falloff.exponential = 0.3f;
		direc->ambientIntensity = 0.1f;
		direc->diffuseIntensity = 0.5f;
		direc->color = vec3(0.0f, 1.0f, 0.0f);
		direc->direction = vec3(0.0f, -0.5f, 0.5f);

		// configure g-buffer framebuffer
	    // ------------------------------
	    glGenFramebuffers(1, &gBuffer);
	    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	    // position color buffer
	    glGenTextures(1, &gPosition);
	    glBindTexture(GL_TEXTURE_2D, gPosition);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_RGB, GL_FLOAT, NULL);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
	    // normal color buffer
	    glGenTextures(1, &gNormal);
	    glBindTexture(GL_TEXTURE_2D, gNormal);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_RGB, GL_FLOAT, NULL);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
	    // diffuse color buffer
	    glGenTextures(1, &gDiffuse);
	    glBindTexture(GL_TEXTURE_2D, gDiffuse);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_RGB, GL_FLOAT, NULL);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gDiffuse, 0);
	    // depth color buffer
	    glGenTextures(1, &gDepth);
	    glBindTexture(GL_TEXTURE_2D, gDepth);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);
	    // final result buffer
	    glGenTextures(1, &gResult);
	    glBindTexture(GL_TEXTURE_2D, gResult);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_RGB, GL_FLOAT, NULL);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gResult, 0);	    
	    // create and attach depth buffer (renderbuffer)
	    glGenRenderbuffers(1, &gDepthBuff);
	    glBindRenderbuffer(GL_RENDERBUFFER, gDepthBuff);
	    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]);
	    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gDepthBuff);
	    // finally check if framebuffer is complete
	    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	        std::cout << "Framebuffer not complete!" << std::endl;
	    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	    // configure t-buffer framebuffer
	    // ------------------------------
	    glGenFramebuffers(1, &tBuffer);
	    glBindFramebuffer(GL_FRAMEBUFFER, tBuffer);
	    // position color buffer
	    glBindTexture(GL_TEXTURE_2D, gPosition);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_RGB, GL_FLOAT, NULL);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
	    // normal color buffer
	    glBindTexture(GL_TEXTURE_2D, gNormal);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_RGB, GL_FLOAT, NULL);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
	    // diffuse color buffer
	    glGenTextures(1, &tDiffuse);
	    glBindTexture(GL_TEXTURE_2D, tDiffuse);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_RGB, GL_FLOAT, NULL);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, tDiffuse, 0);
	    // depth color buffer
	    glBindTexture(GL_TEXTURE_2D, gDepth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);
	    // final result buffer
	    glBindTexture(GL_TEXTURE_2D, gResult);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1], 0, GL_RGB, GL_FLOAT, NULL);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gResult, 0);	    
	    // create and attach depth buffer (renderbuffer)
	    glBindRenderbuffer(GL_RENDERBUFFER, gDepthBuff);
	    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]);
	    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gDepthBuff);
	    // finally check if framebuffer is complete
	    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	        std::cout << "Framebuffer not complete!" << std::endl;
	    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	    // configure shaders
	    // ------------------------------
		GeometryShader = new Shader("shader/geometry_pass.vertex", "shader/geometry_pass.fragment", NULL);
		GeometryShader->use();
		GeometryShader->setInt("texture1set", 1);
		GeometryShader->setInt("texture1", materials->index);
		glActiveTexture(GL_TEXTURE0 + materials->index);
		materials->use();
		GeometryShader->setInt("texture2set", 0);

		StencilShader = new Shader("shader/null_pass.vertex", "shader/null_pass.fragment", NULL);

		PointLightShader = new Shader("shader/light_pass.vertex", "shader/pnt_light_pass.fragment", NULL);
		PointLightShader->use();
		PointLightShader->setFloat("SpecularPower", 1);
		PointLightShader->setFloat("MatSpecularIntensity", 1);
		PointLightShader->setVec2("ScreenSize", (glm::vec2)vec2(INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]));

		DirecLightShader = new Shader("shader/light_pass.vertex", "shader/dir_light_pass.fragment", NULL);
		DirecLightShader->use();
		DirecLightShader->setFloat("SpecularPower", 1);
		DirecLightShader->setFloat("MatSpecularIntensity", 1);
		DirecLightShader->setVec2("ScreenSize", (glm::vec2)vec2(INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]));

		TransparencyShader = new Shader("shader/transparency_pass.vertex", "shader/transparency_pass.fragment", NULL);
		TransparencyShader->use();
		TransparencyShader->setVec2("ScreenSize", (glm::vec2)vec2(INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1]));

	    glUseProgram(0);

		//hook in the proper routines to OpenGL
        glutReshapeFunc(ResizeWindow);
        glutKeyboardFunc(KeyboardPress);
        glutSpecialFunc(NonASCIIKeyboardPress);
        glutDisplayFunc(Display);
        glutTimerFunc(TIMER, TimerFunction, 0);

        //start the game
        glutMainLoop();

        return 0;// normal exit
	}
