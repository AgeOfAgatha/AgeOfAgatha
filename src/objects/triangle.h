/*--------------------------------------------//
Triangle header
Smallest object that can be drawn
//--------------------------------------------*/
#ifndef TRIANGLE_H
#define TRIANGLE_H
class triangle;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../../deps/glm/glm.hpp"
	#include "../../deps/gl/glew.h"
	#include "../../deps/gl/freeglut.h"
	
	#include "texture.h"
	#include "vertex.h"
	#include "mesh.h"
	#include "../globals.h"
	#include "../shader/shader.h"
	#include "../common/vector.h"
	#include "../common/plane.h"
	#include "../common/line.h"

class triangle{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			vertex** points;//stores the vertices that make up this object
			unsigned int VAO;//stores the objects opengl vertex array object
			unsigned int VBO[5];//stores the vertex buffer objects for vertex properties
			texture* materials[MAX_TRIANGLE_MATERIALS];//stores the class object for our texture
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			triangle();
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			triangle(vertex* a, vertex* b, vertex* c);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~triangle();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void setMat(char* path, int flags, int n);
			bool operator==(const triangle &other) const;
			bool operator!=(const triangle &other) const;
			vertex* getVertex(int i) const;
			vec3 getNormal();
			vec3 getPosition();
			bool intersects(vec3 vec);
			void draw(Shader* shader);
};
#endif