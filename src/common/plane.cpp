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
			n = Vec3(0,0,0);
			d = 0.0;
		}
	/*--------------------------------------------//
	Overloaded constructors
	//--------------------------------------------*/
		Plane::Plane(Vec3 a, Vec3 b){
			n = a;
			d = -(a.x*b.x + a.y*b.y + a.z*b.z);
		}
		Plane::Plane(Vec3 a, double b){
			n = a;
			d = b;
		}
	/*--------------------------------------------//
	Check if point is behind us
	//--------------------------------------------*/
		bool Plane::Facing(Vec3 a){
			return ((n.x*a.x + n.y*a.y + n.z*a.y - d) / a.Length()) > 0;
		}
#endif