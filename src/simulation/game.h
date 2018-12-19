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
	#include "../../deps/glm/glm.hpp"
	#include "../../deps/gl/glew.h"
	#include "../../deps/gl/freeglut.h"

	#include "../globals.h"
	#include "../shader/shader.h"
	#include "../objects/world.h"
	#include "../interface/interface.h"
	#include "../interface/text/frameDelay.h"

	#include <cstring>
	#include <string>

class game{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			world* worldspace;//Stores the physical world, handles all interactions between discrete objects
			interface* display;//Interacts directly with the player through 2D elements
			float viewerAzimuth;//Player view azimuth
			float viewerAltitude;//Player view altitude
			Shader* ourShader;//Our graphical shader
			unsigned int VAO;
			unsigned int index;

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
			void predraw();
			void postdraw(float aspect);
			
			int update(int value);
			void keypressASCII(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
			void keypressNonASCII(int pressedKey, int mouseXPosition, int mouseYPosition);
};
#endif