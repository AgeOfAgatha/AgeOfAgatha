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
	#if defined(__APPLE__)
		#include <GLUT/glut.h>
	#else
		#include <GL/glut.h>
	#endif
	#include "vertex.h"
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
			vector getNormal();
			double getTexPos();
			vector getPosition();
			bool intersects(vector vec);
			void draw();
};
#endif