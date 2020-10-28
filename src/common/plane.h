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
			Vec3 n;//normal vector, (a,b,c)
			double d;//basically offset, d = -(a*x0 + b*y0 + c*z0)

	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
			Plane();

		/*--------------------------------------------//
		Overloaded constructors
		//--------------------------------------------*/
			Plane(Vec3 a, Vec3 b);
			Plane(Vec3 a, double b);

		/*--------------------------------------------//
		Check if point is behind us
		//--------------------------------------------*/
			bool Facing(Vec3 a);
};
#endif