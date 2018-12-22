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

			//load object
			mesh* parent;
			worldspace->loadObj("models/cube.obj", "models/cube.mtl", &parent);
			parent->setPosition(vec3(0,0,1));

			//mesh* parent2;
			//worldspace->loadObj("models/cube.obj", "models/cube.mtl", &parent2);
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
		}

	/*--------------------------------------------//
	Draw
	Performs player camera related operations and 
	passes down the stack for drawing objects after
	lighting has been done.
	//--------------------------------------------*/
		void game::draw(float aspect){
			//Position and orient camera.
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f );
			glm::quat quat = glm::quat(glm::vec3(viewerAltitude, viewerAzimuth, 0));
			glm::mat4 looking = glm::toMat4(quat);
			glm::vec4 camera = looking * glm::vec4(position.x + 0.0f, position.y + 0.0f, position.z + 1.0f*VIEWER_DISTANCE, 1.0f);;

			//Create project matrix
	        glm::mat4 projection;
		    projection = glm::perspective(glm::radians(FRUSTUM_FIELD_OF_VIEW), aspect, FRUSTUM_NEAR_PLANE, FRUSTUM_FAR_PLANE);
		    
		    //Find up vector
		    glm::vec4 up = looking * glm::vec4(0,1,0,1);
		    //Create view matrix
	        glm::mat4 view;
		    view = glm::lookAt(
			    glm::vec3(camera[0], camera[1], camera[2]), 		// Camera is at (4,3,3), in World Space
			    position, 											// and looks at the origin
			   	glm::vec3(up[0], up[1], up[2]) 						// Head is up
		    );
		 
			//Draw the world
			worldspace->draw(projection, view);
		}

	/*--------------------------------------------//
	Postdraw
	Passes the function call down the stack for 
	drawing elements after all 3D elements have been
	drawn
	//--------------------------------------------*/
		void game::postdraw(){
			//Draw interface overlay
			glPushMatrix();
				glDisable( GL_DEPTH_TEST );
				display->draw();
				glEnable( GL_DEPTH_TEST );
			glPopMatrix();
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
#endif