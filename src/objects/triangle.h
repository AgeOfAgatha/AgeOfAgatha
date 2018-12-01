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
	#ifndef GLEW_STATIC
    #define GLEW_STATIC
	#include "../../deps/gl/glew.h"
	#include "../../deps/gl/glut.h"
	#endif
	
	#include "vertex.h"
	#include "../common/vector.h"
	#include "../common/plane.h"
	#include "../common/line.h"

class triangle{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double texpos;
			vertex** verts;
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			triangle();
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			triangle(vertex* &a, vertex* &b, vertex* &c);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~triangle();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			bool operator==(const triangle &other) const;
			bool operator!=(const triangle &other) const;
			vertex* getVertex(int i);
			vec3 getNormal();
			double getTexPos();
			vec3 getPosition();
			bool intersects(vec3 vec);
			void draw();
};
#endif