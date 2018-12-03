/*--------------------------------------------//
Texture definition
//--------------------------------------------*/
#ifndef TEXTURE
#define TEXTURE
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "texture.h"

		#ifndef STB_IMAGE
		#define STB_IMAGE
		#define STB_IMAGE_IMPLEMENTATION //telling it to use header as definition
	    #include "../../deps/stb/stb_image.h"
		#endif

	/*--------------------------------------------//
	Default constructor
	takes a path to the image
	takes an int value for flags
		0 = GL_RGB
		1 = GL_RGBA
	//--------------------------------------------*/
		texture::texture(char* ImagePath, int flags){
			glGenTextures(1, &index);
	        glBindTexture(GL_TEXTURE_2D, index); 
	         // set the texture wrapping parameters
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	        // set texture filtering parameters
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	        // load image, create texture and generate mipmaps
	        int width, height, nrChannels;
	        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	        unsigned char *data = stbi_load((ImagePath), &width, &height, &nrChannels, 0);
	        if (data){
	        	switch(flags){
	        		case 0:{
	            		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	        			break;
	        		}
	        		case 1:{
	            		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	        			break;
	        		}
	        	}
	        }else{
	            printf("Failed to load texture %s\n", ImagePath);
	        }
	        stbi_image_free(data);
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		texture::~texture(){};

	/*--------------------------------------------//
	Use and display the texture
	//--------------------------------------------*/
		void texture::use(){
			glActiveTexture(index);
    		glBindTexture(GL_TEXTURE_2D, index);
		}

#endif