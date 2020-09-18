////////////////////////////////////////////////////////////////////
//Renderer object
//Acts as a pipeline for render calls
//Developed from source code on www.paulsprojects.net
////////////////////////////////////////////////////////////////////
#ifndef RENDERER_H
#define RENDERER_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <stdio.h>
	#include <cstring>

	#ifdef RENDERER_CPP
		#define GLUT_DISABLE_ATEXIT_HACK
		#define GLX_GLXEXT_LEGACY
		#include <GL/GLee.h>	//GL header file, including extensions
		#include <GL/glut.h>
	#endif

	#include "Maths/Maths.h"
	#include "scene.h"
	#include <time.h>

class renderer{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			//Camera & light positions
			VECTOR3D cameraPosition = VECTOR3D(-2.5f, 3.5f,-2.5f);
			VECTOR3D lightPosition = VECTOR3D(2.0f, 3.0f,-2.0f);
			//Size of shadow map
			const int shadowMapSize = 512;
			//Textures
			GLuint shadowMapTexture;
			//window size
			int windowWidth, windowHeight;
			//Matrices
			MATRIX4X4 lightProjectionMatrix, lightViewMatrix;
			MATRIX4X4 cameraProjectionMatrix, cameraViewMatrix;
			int updates = 0;
		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			//Constructor
			renderer();
			//Called to draw scene
			void draw(void);
			//Called on window resize
			void reshape(int w, int h);
			//Update call
			void update();
};
#endif
