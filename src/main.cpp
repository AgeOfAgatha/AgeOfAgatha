////////////////////////////////////////////////////////////////////
//Main driver file - Gets everything started
////////////////////////////////////////////////////////////////////
using namespace std;

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

/*--------------------------------------------//
Globals
//--------------------------------------------*/
	GLint currWindowSize[2];//Size of the window
	int window;
	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
	//input specifics
	double viewerAltitude = 1; 
	double viewerAzimuth = 1;
	double viewerDistance = VIEWER_DISTANCE;
	bool lbutton = false;
	bool wireframe = false;

	// build and compile shaders
	// -------------------------
	GLuint shadowMapTexture;
	Shader* shader;
	Shader* simpleDepthShader;

/*--------------------------------------------//
GLUT functions - passes down class stack
//--------------------------------------------*/
	// renderCube() renders a 1x1 3D cube in NDC
	// -----------------------------------------
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	void renderCube()
	{
	    // initialize (if necessary)
	    if (cubeVAO == 0)
	    {
	        float vertices[] = {
	            // back face
	            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
	             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
	            // front face
	            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
	             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
	            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	            // left face
	            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
	            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	            // right face
	             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
	             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
	            // bottom face
	            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
	             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	            // top face
	            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
	             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
	        };
	        glGenVertexArrays(1, &cubeVAO);
	        glGenBuffers(1, &cubeVBO);
	        // fill buffer
	        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	        // link vertex attributes
	        glBindVertexArray(cubeVAO);
	        glEnableVertexAttribArray(0);
	        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	        glEnableVertexAttribArray(1);
	        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	        glEnableVertexAttribArray(2);
	        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	        glBindBuffer(GL_ARRAY_BUFFER, 0);
	        glBindVertexArray(0);
	    }
	    // render Cube
	    glBindVertexArray(cubeVAO);
	    glDrawArrays(GL_TRIANGLES, 0, 36);
	    glBindVertexArray(0);
	}

	// renderQuad() renders a 1x1 XY quad in NDC
	// -----------------------------------------
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	void renderQuad()
	{
	    if (quadVAO == 0)
	    {
	        float quadVertices[] = {
	            // positions        // texture Coords
	            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
	            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
	             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	        };
	        // setup plane VAO
	        glGenVertexArrays(1, &quadVAO);
	        glGenBuffers(1, &quadVBO);
	        glBindVertexArray(quadVAO);
	        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	        glEnableVertexAttribArray(0);
	        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	        glEnableVertexAttribArray(1);
	        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	    }
	    glBindVertexArray(quadVAO);
	    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	    glBindVertexArray(0);
	}

	// renders the 3D scene
	// --------------------
	void renderScene(Shader* shader)
	{
	    // cubes
	    Mat4 model;
	    for (int i = 0; i < 3; i++){
		    for (int j = 0; j < 3; j++){
			    for (int k = 0; k < 3; k++){
				    model = Mat4(1.0f);
				    model.Translate(Vec3(i*1.0f, j*1.0f, k*1.0f));
				    //model = Rotate(model, Radians(60.0f), Normalize(Vec3(1.0, 0.0, 1.0)));
				    //model = Scale(model, Vec3(0.25));
				    //shader->setMat4("model", model);
				    renderCube();
				}
			}
		}
	}

	void Draw(){
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		// //Position and orient camera.
		// glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f );
		// glm::quat quat = glm::quat(vec3(viewerAltitude, viewerAzimuth, 0.0));
		// glm::mat4 looking = glm::toMat4(quat);
		// glm::vec4 camera = looking * glm::vec4(position.x + 0.0f, position.y + 0.0f, position.z + 1.0f*viewerDistance, 1.0f);
		// glm::vec4 up = looking * glm::vec4(0,1,0,1);

		// //Create project matrix
		// glm::mat4 projection = glm::perspective(glm::radians(FRUSTUM_FIELD_OF_VIEW), (float)currWindowSize[0]/currWindowSize[1], (float)FRUSTUM_NEAR_PLANE, (float)FRUSTUM_FAR_PLANE);
		// glm::mat4 lightprojection = glm::perspective(glm::radians(90.0f), (float)1, (float)2, (float)8);

		// //Create view matrix
		// glm::mat4 view = glm::lookAt(
		// 	glm::vec3(camera[0], camera[1], camera[2]),
		// 	position,
		// 	glm::vec3(up[0], up[1], up[2])
		// );
		// glm::mat4 lightview = glm::lookAt(
		// 	glm::vec3(lightPos[0], lightPos[1], lightPos[2]),
		// 	position,
		// 	glm::vec3(0.0f, 1.0f, 0.0f)
		// );


		// //angle of spheres in scene. Calculate from time
		// float angle=0;

		// //First pass - from light's point of view
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glMatrixMode(GL_PROJECTION);
		// glLoadMatrixf(lightProjectionMatrix);

		// glMatrixMode(GL_MODELVIEW);
		// glLoadMatrixf(lightViewMatrix);

		// //Use viewport the same size as the shadow map
		// glViewport(0, 0, shadowMapSize, shadowMapSize);

		// //Draw back faces into the shadow map
		// glCullFace(GL_FRONT);

		// //Disable color writes, and use flat shading for speed
		// glShadeModel(GL_FLAT);
		// glColorMask(0, 0, 0, 0);

		// //Draw the scene
		// DrawScene(angle);

		// //Read the depth buffer into the shadow map texture
		// glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
		// glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);

		// //restore states
		// glCullFace(GL_BACK);
		// glShadeModel(GL_SMOOTH);
		// glColorMask(1, 1, 1, 1);

		// //2nd pass - Draw from camera's point of view
		// glClear(GL_DEPTH_BUFFER_BIT);

		// glMatrixMode(GL_PROJECTION);
		// glLoadMatrixf(cameraProjectionMatrix);

		// glMatrixMode(GL_MODELVIEW);
		// glLoadMatrixf(cameraViewMatrix);

		// glViewport(0, 0, windowWidth, windowHeight);

		// //Use dim light to represent shadowed areas
		// glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(lightPosition));
		// glLightfv(GL_LIGHT1, GL_AMBIENT, white*0.2f);
		// glLightfv(GL_LIGHT1, GL_DIFFUSE, white*0.2f);
		// glLightfv(GL_LIGHT1, GL_SPECULAR, black);
		// glEnable(GL_LIGHT1);
		// glEnable(GL_LIGHTING);

		// DrawScene(angle);

		// //3rd pass
		// //Draw with bright light
		// glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
		// glLightfv(GL_LIGHT1, GL_SPECULAR, white);

		// //Calculate texture matrix for projection
		// //This matrix takes us from eye space to the light's clip space
		// //It is postmultiplied by the inverse of the current view matrix when specifying texgen
		// static MATRIX4X4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
		// 							0.0f, 0.5f, 0.0f, 0.0f,
		// 							0.0f, 0.0f, 0.5f, 0.0f,
		// 							0.5f, 0.5f, 0.5f, 1.0f);	//bias from [-1, 1] to [0, 1]
		// MATRIX4X4 textureMatrix=biasMatrix*lightProjectionMatrix*lightViewMatrix;

		// //Set up texture coordinate generation.
		// glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		// glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
		// glEnable(GL_TEXTURE_GEN_S);

		// glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		// glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
		// glEnable(GL_TEXTURE_GEN_T);

		// glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		// glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
		// glEnable(GL_TEXTURE_GEN_R);

		// glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		// glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
		// glEnable(GL_TEXTURE_GEN_Q);

		// //Bind & enable shadow map texture
		// glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
		// glEnable(GL_TEXTURE_2D);

		// //Enable shadow comparison
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

		// //Shadow comparison should be true (ie not in shadow) if r<=texture
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

		// //Shadow comparison should generate an INTENSITY result
		// glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

		// //Set alpha test to discard false comparisons
		// glAlphaFunc(GL_GEQUAL, 0.99f);
		// glEnable(GL_ALPHA_TEST);

		// DrawScene(angle);

		// //Disable textures and texgen
		// glDisable(GL_TEXTURE_2D);

		// glDisable(GL_TEXTURE_GEN_S);
		// glDisable(GL_TEXTURE_GEN_T);
		// glDisable(GL_TEXTURE_GEN_R);
		// glDisable(GL_TEXTURE_GEN_Q);

		// //Restore other states
		// glDisable(GL_LIGHTING);
		// glDisable(GL_ALPHA_TEST);

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

		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);

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
		glTexImage2D(	GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, INIT_WINDOW_SIZE_X, INIT_WINDOW_SIZE_Y, 0,
						GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		//Use the color as the ambient and diffuse material
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		
		//White specular material color, shininess 16
		//glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

		//start the game
		glutMainLoop();

		return 0;
	}
