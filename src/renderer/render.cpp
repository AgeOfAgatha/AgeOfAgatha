////////////////////////////////////////////////////////////////////
//Renderer object
//Acts as a pipeline for render calls
//Developed from source code on www.paulsprojects.net
////////////////////////////////////////////////////////////////////
#ifndef RENDERER_CPP
#define RENDERER_CPP
#endif
/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "render.h"

/*--------------------------------------------//
Functions
//--------------------------------------------*/
	/*--------------------------------------------//
	Constructor
	//--------------------------------------------*/
		renderer::renderer(){
			//Check for necessary extensions
			if(!GLEE_ARB_depth_texture || !GLEE_ARB_shadow){
				printf("I require ARB_depth_texture and ARB_shadow extensionsn\n");
				exit(1);
			}
			
			//Load identity modelview
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			//Shading states
			glShadeModel(GL_SMOOTH);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

			//Depth states
			glClearDepth(1.0f);
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_DEPTH_TEST);

			glEnable(GL_CULL_FACE);

			//We use glScale when drawing the scene
			glEnable(GL_NORMALIZE);

			//Create the shadow map texture
			glGenTextures(1, &shadowMapTexture);
			glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
			glTexImage2D(	GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0,
							GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			//Use the color as the ambient and diffuse material
			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			glEnable(GL_COLOR_MATERIAL);
			
			//White specular material color, shininess 16
			glMaterialfv(GL_FRONT, GL_SPECULAR, white);
			glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

			//Calculate & save matrices
			glPushMatrix();
			
			glLoadIdentity();
			gluPerspective(45.0f, (float)windowWidth/windowHeight, 1.0f, 100.0f);
			glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
			
			glLoadIdentity();
			gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
						0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f);
			glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);
			
			glLoadIdentity();
			gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
			glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);
			
			glLoadIdentity();
			gluLookAt(	lightPosition.x, lightPosition.y, lightPosition.z,
						0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f);
			glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);
			
			glPopMatrix();
		}

	/*--------------------------------------------//
	Called to draw scene
	//--------------------------------------------*/
	void renderer::draw(void){
		//angle of spheres in scene. Calculate from time
		float angle=updates;

		//First pass - from light's point of view
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(lightProjectionMatrix);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(lightViewMatrix);

		//Use viewport the same size as the shadow map
		glViewport(0, 0, shadowMapSize, shadowMapSize);

		//Draw back faces into the shadow map
		glCullFace(GL_FRONT);

		//Disable color writes, and use flat shading for speed
		glShadeModel(GL_FLAT);
		glColorMask(0, 0, 0, 0);
		
		//Draw the scene
		DrawScene(angle);

		//Read the depth buffer into the shadow map texture
		glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);

		//restore states
		glCullFace(GL_BACK);
		glShadeModel(GL_SMOOTH);
		glColorMask(1, 1, 1, 1);
		

		

		//2nd pass - Draw from camera's point of view
		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(cameraProjectionMatrix);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(cameraViewMatrix);

		glViewport(0, 0, windowWidth, windowHeight);

		//Use dim light to represent shadowed areas
		glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(lightPosition));
		glLightfv(GL_LIGHT1, GL_AMBIENT, white*0.2f);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, white*0.2f);
		glLightfv(GL_LIGHT1, GL_SPECULAR, black);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);

		DrawScene(angle);
		


		//3rd pass
		//Draw with bright light
		glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
		glLightfv(GL_LIGHT1, GL_SPECULAR, white);

		//Calculate texture matrix for projection
		//This matrix takes us from eye space to the light's clip space
		//It is postmultiplied by the inverse of the current view matrix when specifying texgen
		static MATRIX4X4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.5f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.5f, 0.0f,
									0.5f, 0.5f, 0.5f, 1.0f);	//bias from [-1, 1] to [0, 1]
		MATRIX4X4 textureMatrix=biasMatrix*lightProjectionMatrix*lightViewMatrix;

		//Set up texture coordinate generation.
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
		glEnable(GL_TEXTURE_GEN_S);

		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
		glEnable(GL_TEXTURE_GEN_T);

		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
		glEnable(GL_TEXTURE_GEN_R);

		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
		glEnable(GL_TEXTURE_GEN_Q);

		//Bind & enable shadow map texture
		glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
		glEnable(GL_TEXTURE_2D);

		//Enable shadow comparison
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

		//Shadow comparison should be true (ie not in shadow) if r<=texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

		//Shadow comparison should generate an INTENSITY result
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

		//Set alpha test to discard false comparisons
		glAlphaFunc(GL_GEQUAL, 0.99f);
		glEnable(GL_ALPHA_TEST);

		DrawScene(angle);

		//Disable textures and texgen
		glDisable(GL_TEXTURE_2D);

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_GEN_Q);

		//Restore other states
		glDisable(GL_LIGHTING);
		glDisable(GL_ALPHA_TEST);
	}

	/*--------------------------------------------//
	Called on window resize
	//--------------------------------------------*/
	void renderer::reshape(int w, int h){
		//Save new window size
		windowWidth=w, windowHeight=h;
		//Update the camera's projection matrix
		glPushMatrix();
		glLoadIdentity();
		gluPerspective(45.0f, (float)windowWidth/windowHeight, 1.0f, 100.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
		glPopMatrix();
	}

	/*--------------------------------------------//
	Called on update scene
	//--------------------------------------------*/
	void renderer::update(){
		updates++;
	}
