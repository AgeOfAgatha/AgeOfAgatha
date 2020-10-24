////////////////////////////////////////////////////////////////////
//Main driver file - Gets everything started
////////////////////////////////////////////////////////////////////
using namespace std;
#define STB_IMAGE_WRITE_IMPLEMENTATION

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "common/matrix.h"
	#include "common/quaternion.h"
	#include "objects/texture.h"
	#include "shaders/shader.h"
	#include "globals.h"

	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>
	#include <sstream>

/*--------------------------------------------//
Globals
//--------------------------------------------*/
	GLint currWindowSize[2];//Size of the window
	int window;
	Vec3 lightPos = Vec3(3.0f, 3.0f, 3.0f);
	//input specifics
	double viewerAltitude = 1; 
	double viewerAzimuth = 1;
	double viewerDistance = VIEWER_DISTANCE;
	bool lbutton = false;
	bool wireframe = false;
	int mx = 0, my = 0;

	Shader *DepthShader, *ShadowMapping;
	unsigned int depthMapFBO, shadowMapTexture;
	const Vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
	const Vec4 black(0.0f, 0.0f, 0.0f, 0.0f);
	Mat4 BiasMatrix = Mat4(
		0.5, 0.0, 0.0, 0.0, 
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
/*--------------------------------------------//
GLUT functions - passes down class stack
//--------------------------------------------*/
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO[6] = {0,0,0,0,0,0};

	unsigned int quadVAO = 0;
	unsigned int quadVBO[5] = {0,0,0,0,0};
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


	// renders the 3D scene
	// --------------------
	void RenderScene(Mat4 ViewMatrix, Shader* shade){
	    // cubes
	    Mat4 model;
	    for (int i = -1; i < 2; i++){
		    for (int j = -1; j < 2; j++){
			    for (int k = -1; k < 2; k++){
					model = Mat4(1.0f);
					model.Translate(Vec3(i*1.0f, j*1.0f, k*1.0f));
					model.Rotate((Vec3(1.0, 0.0, 1.0)).GetNormalized(), TORAD(60.0f));
					model.Scale(Vec3(0.4));
					if (shade == NULL){
						glMatrixMode(GL_MODELVIEW);
						glLoadMatrixf(ViewMatrix * model);
					}else{
						shade->setMat4("ModelMatrix", model);
					}
					//glutSolidSphere(1.0, 24, 24);
					renderCube();
				}
			}
		}
	}

	void Draw(){
		// Clear the screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Position and orient camera.
		Mat4 LightProjectionMatrix, LightViewMatrix, CameraProjectionMatrix, CameraViewMatrix;
		std::vector<Mat4> shadowTransforms;
		Vec3 position = Vec3(0.0f, 0.0f, 0.0f );
		Quat quat = Quat(Vec3(viewerAltitude, viewerAzimuth, 0.0));
		Mat4 looking = Mat4(quat);
		Vec4 camera = looking * Vec4(position.x + 0.0f, position.y + 0.0f, position.z + 1.0f*viewerDistance, 1.0f);
		Vec4 up = looking * Vec4(0,1,0,1);

		//Calculate & save matrices
		CameraProjectionMatrix.Perspective(FRUSTUM_FIELD_OF_VIEW, (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, (float)FRUSTUM_NEAR_PLANE, (float)FRUSTUM_FAR_PLANE);
		CameraViewMatrix.LookAt(camera, position, up);
		LightProjectionMatrix.Perspective(FRUSTUM_FIELD_OF_VIEW, (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, (float)FRUSTUM_NEAR_PLANE, (float)FRUSTUM_FAR_PLANE);
		LightViewMatrix.LookAt(lightPos, position, Vec3(0,1,0));

		DepthShader->use();
		DepthShader->setMat4("CameraProjectionMatrix", LightProjectionMatrix);
		DepthShader->setMat4("CameraViewMatrix", LightViewMatrix);
		DepthShader->setMat4("LightProjectionMatrix", LightProjectionMatrix);
		DepthShader->setMat4("LightViewMatrix", LightViewMatrix);
		DepthShader->setVec3("LightPosition", lightPos);
		DepthShader->setVec3("FarPlane", FRUSTUM_FAR_PLANE);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
		RenderScene(LightViewMatrix, DepthShader);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, currWindowSize[0], currWindowSize[1]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render from camera
		ShadowMapping->use();
		ShadowMapping->setMat4("CameraProjectionMatrix", CameraProjectionMatrix);
		ShadowMapping->setMat4("CameraViewMatrix", CameraViewMatrix);
		ShadowMapping->setVec4("ViewPos", camera);
		ShadowMapping->setVec3("SpotLight.position", lightPos);
		ShadowMapping->setFloat("SpotLight.fov", FRUSTUM_FIELD_OF_VIEW);
		ShadowMapping->setFloat("SpotLight.constant", 0.1f);
		ShadowMapping->setFloat("SpotLight.linear", 0.1f);
		ShadowMapping->setFloat("SpotLight.exponential", 0.1f);
		ShadowMapping->setVec3("SpotLight.direc.direction", (-lightPos).GetNormalized());
		ShadowMapping->setVec3("SpotLight.direc.base.color", Vec3(white));
		ShadowMapping->setVec3("DirecLight.base.color", Vec3(white));
		ShadowMapping->setVec3("DirecLight.direction", (-lightPos).GetNormalized());
		ShadowMapping->setMat4("LightProjectionMatrix", LightProjectionMatrix);
		ShadowMapping->setMat4("LightViewMatrix", LightViewMatrix);
		ShadowMapping->setInt("DepthMap", 1);
		ShadowMapping->setInt("LightType", 0);
		ShadowMapping->setInt("texture1set", 0);
		ShadowMapping->setInt("texture2set", 0);
		ShadowMapping->setInt("ALIAS", 10);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shadowMapTexture);

		RenderScene(CameraViewMatrix, ShadowMapping);

		glUseProgram(0);

		//Post new frame buffer
		glFinish();
		glutSwapBuffers();
		glutPostRedisplay();
	}
	void Update(int value){
		glutTimerFunc(UPDATE_TIMER, Update, value);
	}
	void KeypressASCII(unsigned char pressedKey, int mouseXPosition, int mouseYPosition){
	}
	void KeypressNonASCII(int pressedKey, int mouseXPosition, int mouseYPosition){
		switch (pressedKey){
			case GLUT_KEY_F1:{
				glutDestroyWindow(window);
				break;
			}
			case GLUT_KEY_F2:{
				if (wireframe){
					wireframe = false;
        			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        		}else{
					wireframe = true;
        			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}break;
			}
			case GLUT_KEY_RIGHT:{
				viewerAzimuth += VIEWER_ANGLE_INCREMENT;
				if (viewerAzimuth > 2 * PI)
					viewerAzimuth -= 2 * PI;
				break;
			}
			case GLUT_KEY_LEFT:{
				viewerAzimuth -= VIEWER_ANGLE_INCREMENT;
				if (viewerAzimuth < 0.0)
					viewerAzimuth += 2 * PI;
				break;
			}
			case GLUT_KEY_DOWN:{
				viewerAltitude += VIEWER_ANGLE_INCREMENT;
				if (viewerAltitude > 2 * PI)
					viewerAltitude -= 2 * PI;
				break;
			}
			case GLUT_KEY_UP:{
				viewerAltitude -= VIEWER_ANGLE_INCREMENT;
				if (viewerAltitude < 0.0)
					viewerAltitude += 2 * PI;
				break;
			}
		}
	}
	void Visible(int v){
	}
	void Reshape(int w, int h){
	}
	void MenuUse(int v){
	}
	void HandleButton(int button, int state, int x, int y){
		if(button == GLUT_LEFT_BUTTON){
			if (state == GLUT_DOWN)
				lbutton = true;
			else
				lbutton = false;
		}
		if(button == GLUT_LEFT_BUTTON){
			if (state == GLUT_DOWN)
		       		lbutton = true;
	        	else
	        		lbutton = false;
		}
		if (lbutton && state == GLUT_DOWN){
			viewerDistance += int(button == 4) - int(button == 3);
		}
	}
	void HandleMotion(int x, int y){
		static bool lstate = false;
		if (lbutton){
			static int oldx = x;
			static int oldy = y;

			if (!lstate){
				oldx = x;
				oldy = y;
				lstate = true;
			}

			if (oldx != x){
				double difx = oldx - x;

				viewerAzimuth += difx / 100;
			}

			if (oldy != y){
				double dify = oldy - y;

				viewerAltitude += dify / 100;
			}

			oldx = x;
			oldy = y;
		}else{
			lstate = false;
		}
		mx = x;
		my = currWindowSize[1] - y;
	}

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
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

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

		//Create the shadow map frame buffer
		glGenFramebuffers(1, &depthMapFBO);

		//Create the shadow map texture
		glGenTextures(1, &shadowMapTexture);
		glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
		glTexImage2D(	GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
						GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTexture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Use the color as the ambient and diffuse material
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);

		//White specular material color, shininess 16
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);
		//Shading states
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		DepthShader = new Shader("DepthShader", "shaders/depth.vertex", "shaders/depth.fragment", NULL);
		ShadowMapping = new Shader("ShadowMapping", "shaders/shadow.vertex", "shaders/shadow.fragment", NULL);

		//start the game
		glutMainLoop();

		return 0;
	}
