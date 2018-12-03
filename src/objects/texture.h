/*--------------------------------------------//
Texture definition
//--------------------------------------------*/
#ifndef TEXTURE_H
#define TEXTURE_H
/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#ifndef GLEW_STATIC
    #define GLEW_STATIC
    #include "../../deps/gl/glew.h"
    #include "../../deps/gl/glut.h"
	#endif

class texture{
	private:
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			unsigned int index;
	public:
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