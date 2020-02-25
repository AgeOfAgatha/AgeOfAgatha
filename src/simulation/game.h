/*--------------------------------------------//
Game Header
This is the scene controller for the physics world
and the ui interface.
//--------------------------------------------*/
#ifndef GAME_H
#define GAME_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <glew.h>
	#include <freeglut.h>

	#include "../../deps/stb/stb_image.h"
	#include "../../deps/glm/glm.hpp"

    #include "../globals.h"
	#include "../common/vector.h"
	#include "../common/quaternion.h"
	#include "../objects/world.h"
	#include "../objects/light/light.h"
	#include "../objects/light/direclight.h"
	#include "../objects/light/spotlight.h"
	#include "../interface/interface.h"
	#include "../interface/text/frameDelay.h"

	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <limits.h>
	#include <float.h>
	#include <string.h>
	#include <time.h>

/*--------------------------------------------//
Class Blueprint
//--------------------------------------------*/
class game{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			world* worldspace;//Stores the physical world, handles all interactions between discrete objects
			uinterface* display;//Interacts directly with the player through 2D elements
			double viewerAltitude = 1; 
			double viewerAzimuth = 1;
			double viewerDistance = VIEWER_DISTANCE;
			GLint currWindowSize[2];//Size of the window
			GLint currViewportSize[2];//Size of the viewport
			int Window;

			//input specifics
			bool lbutton = false;
			bool wireframe = false;

	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			game();
		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~game();
		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void PreDraw();
			void Draw();
			void PostDraw();
			int Update(int value);
			void KeypressASCII(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
			void KeypressNonASCII(int pressedKey, int mouseXPosition, int mouseYPosition);
			void Visible(int v);
			void Reshape(int w, int h);
			void MenuUse(int v);
			void HandleButton(int button, int state, int x, int y);
			void HandleMotion(int x, int y);
			void HandleScroll(int wheel, int direc, int x, int y);
};
#endif