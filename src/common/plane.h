/*--------------------------------------------//
Plane definition
follows Plane definition as: ax + by + cz + d = 0
//--------------------------------------------*/
#ifndef PLANE_H
#define PLANE_H
class Plane;

/*--------------------------------------------//
Include
//--------------------------------------------*/
	#include "vector.h"

class Plane{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			vec3 n;//normal vector, (a,b,c)
			double d;//basically offset, d = -(a*x0 + b*y0 + c*z0)

	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
			Plane();

		/*--------------------------------------------//
		Overloaded constructors
		//--------------------------------------------*/
			Plane(vec3 a, vec3 b);
			Plane(vec3 a, double b);

		/*--------------------------------------------//
		Check if point is behind us
		//--------------------------------------------*/
			bool Facing(vec3 a);
};
#endif