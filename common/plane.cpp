/*--------------------------------------------//
Plane definition
follows plane definition as: ax + by + cz + d = 0
//--------------------------------------------*/
#ifndef PLANE
#define PLANE
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "plane.h"

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		plane::plane(){
			n = vector(0,0,0);
			d = 0.0;
		}
	/*--------------------------------------------//
	Overloaded constructors
	//--------------------------------------------*/
		plane::plane(vector a, vector b){
			n = a;
			d = -(a.x()*b.x() + a.y()*b.y() + a.z()*b.z());
		}
		plane::plane(vector a, double b){
			n = a;
			d = b;
		}
	/*--------------------------------------------//
	Check if point is behind us
	//--------------------------------------------*/
		bool plane::facing(vector a){
			return ((n.x()*a.x() + n.y()*a.y() + n.z()*a.y() - d) / a.length()) > 0;
		}
#endif