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
	#include "../globals.h"

	#include "texture.h"
	#include "vertex.h"
	#include "mesh.h"
	#include "../globals.h"
	#include "../shaders/shader.h"
	#include "../common/plane.h"
	#include "../common/line.h"

class triangle{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			Vec2** textcoord;//texture coordinates
			double** textblend;//texture blend
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
			triangle(vertex* a, vertex* b, vertex* c, Vec2 st1, double b1, Vec2 st2, double b2, Vec2 st3, double b3);
			triangle(vertex* a, vertex* b, vertex* c, Vec2* st1, double b1, Vec2* st2, double b2, Vec2* st3, double b3);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~triangle();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void setMat(texture* t, int n);
			void setMat(char* path, int flags, int n);
			bool operator==(const triangle &other) const;
			bool operator!=(const triangle &other) const;
			vertex* getVertex(int i) const;
			Vec3 getNormal();
			Vec3 getPosition();
			bool intersects(Vec3 vec);
			void draw(Shader* shader);
};
#endif
