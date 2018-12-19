/*--------------------------------------------//
Game Defintion
This is the scene controller for the physics world
and the ui interface.
//--------------------------------------------*/
#ifndef GAME
#define GAME
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "game.h"
	
	/*--------------------------------------------//
	Constructors
	//--------------------------------------------*/
		game::game(){
			//set default view angles
			viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
			viewerAltitude = INITIAL_VIEWER_ALTITUDE;
			//initialize world and interface
			worldspace = new world(TIMESTEP, TIMEOUT, VERTEXRAD, GRAVOBJMASS, GRAVITYCONSTANT, FRICTIONDIST, FRICTIONCONSTANT, DEFORMCONSTANT);
			display = new interface();

			//setup frame delay display
			FrameDelay* frame;
			frame = new FrameDelay();
			display->add(frame);

			//add model to world
			mesh* obj = new mesh();
			vertex* a = new vertex(0,0,0);
			vertex* b = new vertex(0,0,1);
			vertex* c = new vertex(0,1,0);
			vertex* d = new vertex(0,1,1);
			obj->addTri(a,b,c);
			obj->addTri(d,b,c);
			obj->addMat("textures/test.png",0);
			worldspace->addMesh(obj);


			ourShader = new Shader("Shader.vs", "Shader.fs", NULL);

			unsigned int VBO[4];
			//vertex array
			float vert[3][4] = {
				{-0.5, 0.5, -1.0, 1.0},
				{-1.0, -0.5, -1.0, 1.0},
				{0.5, -0.5, -1.0, 1.0}
			};
			//normal array
			float norm[3][3] = {
				{1.0, 1.0, 1.0},
				{1.0, 1.0, 1.0},
				{1.0, 1.0, 1.0}
			};
			//color array
			float col[3][4]  = {
				{1.0, 0.0, 0.0, 1.0},
				{0.0, 1.0, 0.0, 1.0},
				{0.0, 0.0, 1.0, 1.0}
			};
			//texture coordinate array
			float st[3][2]  = {
				{1.0, 0.0},
				{0.0, 1.0},
				{0.0, 0.0}
			};

		    glGenVertexArrays(1, &VAO);
		    glBindVertexArray(VAO);
		    glGenBuffers(4, VBO);

		    //position
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			glBufferData(GL_ARRAY_BUFFER, 3*4*sizeof(GLfloat), vert, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, (GLuint)4, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)0);

		    //normal
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
			glBufferData(GL_ARRAY_BUFFER, 3*3*sizeof(GLfloat), norm, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)1, (GLuint)3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)1);

		    //color
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
			glBufferData(GL_ARRAY_BUFFER, 3*4*sizeof(GLfloat), col, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)3, (GLuint)4, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)3);

		    //texture coordinate
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
			glBufferData(GL_ARRAY_BUFFER, 3*2*sizeof(GLfloat), st, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)4, (GLuint)2, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)4);

		    glBindVertexArray(0);

		    char* ImagePath = "textures/test.png";
			glGenTextures(1, &index);
		    glBindTexture(GL_TEXTURE_2D, index); 
		    //set the texture wrapping parameters
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		    //set texture filtering parameters
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    //load image, create texture and generate mipmaps
		    int width, height, nrChannels;
		    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		    unsigned char *data = stbi_load((ImagePath), &width, &height, &nrChannels, 0);
		    if (data){
		    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		    }else{
		        printf("Failed to load texture %s\n", ImagePath);
		    }
		    stbi_image_free(data);
		}

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		game::~game(){
			delete worldspace;
			delete display;
		}
		
	/*--------------------------------------------//
	Predraw
	Passes the function call down the stack for 
	drawing elements before the lighting has been 
	added.
	//--------------------------------------------*/
		void game::predraw(){
			//Draw frame delay text
			glPushMatrix();
				glDisable( GL_DEPTH_TEST );
				display->draw();
				glEnable( GL_DEPTH_TEST );
			glPopMatrix();
		}

	/*--------------------------------------------//
	Postdraw
	Performs player camera related operations and 
	passes down the stack for drawing objects after
	lighting has been done.
	//--------------------------------------------*/
		void game::postdraw(float aspect){
			//Position and orient camera.
			float position[] = { 0.0f, 0.0f, 0.0f };
			float camera[] = { position[0] + VIEWER_DISTANCE * sin(viewerAltitude) * sin(viewerAzimuth), 
				position[1] + VIEWER_DISTANCE * cos(viewerAltitude), 
				position[2] + VIEWER_DISTANCE * sin(viewerAltitude) * cos(viewerAzimuth) 
			};
			gluLookAt(camera[0], camera[1], camera[2], position[0], position[1], position[2], 0.0, 1.0, 0.0);

			//Draw the objects
			glActiveTexture(GL_TEXTURE0);
			worldspace->draw();

			//Display a square
			glPushMatrix();
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, index);
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
				glBindTexture(GL_TEXTURE_2D, 0);
			glPopMatrix();

			glLoadIdentity();

			//Bind the shader that we want to use
			ourShader->use();

			//Apply Transformations
			float i[16] = {
			   1, 0, 0, 0,
			   0, 1, 0, 0,
			   0, 0, 1, 0,
			   0, 0, 0, 1
			};
			glm::mat4 view;
	        glm::mat4 model;
	        glm::mat4 projection;
	        memcpy(glm::value_ptr(view), i, sizeof(i));
	        memcpy(glm::value_ptr(model), i, sizeof(i));
	        memcpy(glm::value_ptr(projection), i, sizeof(i));
	        float angle = 00.0f;
	        projection 	= glm::perspective(glm::radians(FRUSTUM_FIELD_OF_VIEW), aspect, FRUSTUM_NEAR_PLANE, FRUSTUM_FAR_PLANE);
	        view       	= glm::lookAt(
			    glm::vec3(camera[0], camera[1], camera[2]), // Camera position
			    glm::vec3(position[0], position[1], position[2]), // Looking at position
			    glm::vec3(0,1,0)  // Orientation
		    );
	        model 		= glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	        // pass transformation matrices to the shader
	        ourShader->setMat4("gl_ModelViewProjectionMatrix", projection);
	        ourShader->setMat4("gl_ModelViewMatrix", model);
	        ourShader->setMat4("ViewMatrix", view);
	        ourShader->setVec3("light_position", vec3(2.0f, 5.0f, 2.0f));
	        ourShader->setInt("texture1set", 1);
	        ourShader->setInt("texture1", index);
	        ourShader->setInt("texture2set", 1);
	        ourShader->setInt("texture2", index);

			//Display a square
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, index);
			glEnable(GL_TEXTURE_2D);
       		glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
	        glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);

			//Disable Shader
	        glUseProgram(0);
		}

	/*--------------------------------------------//
	Update
	Perform any changes or updates to the game 
	caused by a passage of time.
	//--------------------------------------------*/
		int game::update(int value){
			//Update value and check if we are on a update cycle for the physics simulation
			if (value % worldspace->getTimeStep() == 0){
				//worldspace->update();
				value = 0;
			}
			return value++;
		}

	/*--------------------------------------------//
	Keyboard Press Event Handler
	Handles any keyboard key inputs from user
	//--------------------------------------------*/
		void game::keypressASCII(unsigned char pressedKey, int mouseXPosition, int mouseYPosition){
			switch(pressedKey){
				//switch based upon keys pressed to perform actions desired
				//none yet - placeholder
			}
		}

	/*--------------------------------------------//
	Non ASCII Keyboard Press Event Handler
	Handles any Non ASCII keyboard key inputs from user
	This will catch certain events unable to be caught
	normally
	//--------------------------------------------*/
		void game::keypressNonASCII(int pressedKey, int mouseXPosition, int mouseYPosition){
			switch (pressedKey){
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
				case GLUT_KEY_UP:{
					viewerAltitude += VIEWER_ANGLE_INCREMENT;
					if (viewerAltitude > PI - VIEWER_ANGLE_INCREMENT)
						viewerAltitude = PI - VIEWER_ANGLE_INCREMENT;
					break;
				}
				case GLUT_KEY_DOWN:{
					viewerAltitude -= VIEWER_ANGLE_INCREMENT;
					if (viewerAltitude < VIEWER_ANGLE_INCREMENT)
						viewerAltitude = VIEWER_ANGLE_INCREMENT;
					break;
				}
			}
		}
#endif