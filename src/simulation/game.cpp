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
			//setup default window size
			currWindowSize[0] = INIT_WINDOW_SIZE_X;
			currWindowSize[1] = INIT_WINDOW_SIZE_Y;
			Window = glutGetWindow();
			//set default view angles
			viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
			viewerAltitude = INITIAL_VIEWER_ALTITUDE;
			//initialize world and interface
			worldspace = new world(TIMESTEP, TIMEOUT, VERTEXRAD, GRAVOBJMASS, GRAVITYCONSTANT, FRICTIONDIST, FRICTIONCONSTANT, DEFORMCONSTANT);
			display = new uinterface();

			//setup frame delay display
			FrameDelay* frame;
			frame = new FrameDelay();
			display->add(frame);

			//load object
			for (int i = -1; i < 2; i++){
				for (int j = -1; j < 2; j++){
					for (int k = -1; k < 2; k++){
						mesh* parent;
						worldspace->loadObj("models/cube.obj", "models/cube.mtl", &parent);
						parent->setPosition(vec3(3*(i),3*(j),3*(k)));
					}
				}
			}

			//intialize lighting
				spotlight* spot = new spotlight();
				direclight* direc = new direclight();

				spot->position = vec3(0.0f, -5.0f, 0.0f);
				spot->direc.base.color = vec3(0.0f, 1.0f, 0.0f);
				spot->constant = 2.0f;
				spot->linear = 0.5f;
				spot->exponential = 0.25f;
			//load lighting into world
			worldspace->addSLight(spot);
		}

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		game::~game(){
			delete worldspace;
			delete display;
		}

	/*--------------------------------------------//
	PreDraw
	Passes the function call down the stack for
	drawing elements before the lighting has been
	added.
	//--------------------------------------------*/
		void game::PreDraw(){
		}

	/*--------------------------------------------//
	Draw
	Performs player camera related operations and
	passes down the stack for drawing objects after
	lighting has been done.
	//--------------------------------------------*/
		void game::Draw(){
			//Position and orient camera.
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f );
			glm::quat quat = glm::quat(vec3(viewerAltitude, viewerAzimuth, 0.0));
			glm::mat4 looking = toMat4(quat);
			glm::vec4 camera = looking * glm::vec4(position.x + 0.0f, position.y + 0.0f, position.z + 1.0f*viewerDistance, 1.0f);;

			//Create project matrix
			glm::mat4 projection;
			projection = glm::perspective(glm::radians(FRUSTUM_FIELD_OF_VIEW), (float)currWindowSize[0]/currWindowSize[1], (float)FRUSTUM_NEAR_PLANE, (float)FRUSTUM_FAR_PLANE);
			//Find up vector
			glm::vec4 up = looking * glm::vec4(0,1,0,1);
			//Create view matrix
			glm::mat4 view;
			view = glm::lookAt(
				glm::vec3(camera[0], camera[1], camera[2]),
				position,
				glm::vec3(up[0], up[1], up[2])
			);

			//Draw the world
			worldspace->draw(projection, view, camera, currWindowSize);
		}

	/*--------------------------------------------//
	PostDraw
	Passes the function call down the stack for 
	drawing elements after all 3D elements have been
	drawn
	//--------------------------------------------*/
		void game::PostDraw(){
			//Draw interface overlay
			glDisable( GL_DEPTH_TEST );
			display->draw();
			glEnable( GL_DEPTH_TEST );
		}

	/*--------------------------------------------//
	Update
	This serves as our clock for the game
	All updates due to passage of time to animation 
	or changes in the game's state should start here
	//--------------------------------------------*/
		int game::Update(int value){
			glutPostRedisplay();//Update
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
		void game::KeypressASCII(unsigned char pressedKey, int mouseXPosition, int mouseYPosition){
			switch (pressedKey){
			}
		}

	/*--------------------------------------------//
	Non ASCII Keyboard Press Event Handler
	Handles any Non ASCII keyboard key inputs from user
	This will catch certain events unable to be caught
	normally
	//--------------------------------------------*/
		void game::KeypressNonASCII(int pressedKey, int mouseXPosition, int mouseYPosition){
			switch (pressedKey){
				case GLUT_KEY_F1:{
					glutDestroyWindow(Window);
	        		exit(EXIT_SUCCESS);
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

	/*--------------------------------------------//
	Visible - glut visibility function
	//--------------------------------------------*/
		void game::Visible(int v){
			glutIdleFunc(NULL);
		}

	/*--------------------------------------------//
	Reshape - handle window resizing
	//--------------------------------------------*/
		void game::Reshape(int w, int h){
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
	MenuUse - handle glut menu in use
	//--------------------------------------------*/
		void game::MenuUse(int v){
		}

	/*--------------------------------------------//
	HandleButton - handle mouse button events
	//--------------------------------------------*/
		void game::HandleButton(int button, int state, int x, int y){
			glutPostRedisplay();

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

	/*--------------------------------------------//
	HandleMotion - handle mouse motion events
	//--------------------------------------------*/
		void game::HandleMotion(int x, int y){
			glutPostRedisplay();

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

#endif
