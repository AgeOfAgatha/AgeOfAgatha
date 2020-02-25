/*--------------------------------------------//
Texture definition
//--------------------------------------------*/
#ifndef TEXTURE_H
#define TEXTURE_H
/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <glew.h>
	#include <freeglut.h>
	#include "../../deps/glm/glm.hpp"
	#include "../../deps/stb/stb_image.h"

class texture{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			unsigned int index;
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			texture(char* ImagePath, int flags);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~texture();
		/*--------------------------------------------//
		Use and display the texture
		//--------------------------------------------*/
			void use();
};
#endif