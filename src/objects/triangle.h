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
	#include "../../deps/gl/glut.h"
	
	#include "vertex.h"
	#include "mesh.h"
	#include "../common/vector.h"
	#include "../common/plane.h"
	#include "../common/line.h"

class triangle{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			int* indices;//stores the array index to the vertex
			mesh* obj;//stores the object the triangle belongs to
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			triangle();
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			triangle(int a, int b, int c, mesh* o);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~triangle();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			int getIndex() const;
			bool operator==(const triangle &other) const;
			bool operator!=(const triangle &other) const;
			vertex* getVertex(int i) const;
			vec3 getNormal();
			vec3 getPosition();
			bool intersects(vec3 vec);
			void draw();
};
#endif