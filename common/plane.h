/*--------------------------------------------//
Plane definition
follows plane definition as: ax + by + cz + d = 0
//--------------------------------------------*/
#ifndef PLANE_H
#define PLANE_H
class plane;

/*--------------------------------------------//
Include
//--------------------------------------------*/
	#include "vector.h"

class plane{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			vector n;//normal vector, (a,b,c)
			double d;//basically offset, d = -(a*x0 + b*y0 + c*z0)

	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
			plane();

		/*--------------------------------------------//
		Overloaded constructors
		//--------------------------------------------*/
			plane(vector a, vector b);
			plane(vector a, double b);

		/*--------------------------------------------//
		Check if point is behind us
		//--------------------------------------------*/
			bool facing(vector a);
};
#endif