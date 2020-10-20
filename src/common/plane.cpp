/*--------------------------------------------//
Plane definition
follows Plane definition as: ax + by + cz + d = 0
//--------------------------------------------*/
#ifndef PLANE
#define PLANE
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "Plane.h"

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		Plane::Plane(){
			n = vec3(0,0,0);
			d = 0.0;
		}
	/*--------------------------------------------//
	Overloaded constructors
	//--------------------------------------------*/
		Plane::Plane(vec3 a, vec3 b){
			n = a;
			d = -(a.x*b.x + a.y*b.y + a.z*b.z);
		}
		Plane::Plane(vec3 a, double b){
			n = a;
			d = b;
		}
	/*--------------------------------------------//
	Check if point is behind us
	//--------------------------------------------*/
		bool Plane::Facing(vec3 a){
			return ((n.x*a.x + n.y*a.y + n.z*a.y - d) / a.length()) > 0;
		}
#endif