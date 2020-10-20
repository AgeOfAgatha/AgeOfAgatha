/*--------------------------------------------//
quaternion definition
This is used to simplify definition of quaternions
//--------------------------------------------*/
#ifndef QUATERNION
#define QUATERNION
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "quaternion.h"

	/*--------------------------------------------//
	Hamilton Product
	By my limited knowledge of quaternions, this is similar to the concept of multiplying two real numbers
	courtesy of: wikipedia.org/wiki/Quaternion#Hamilton_product
	//--------------------------------------------*/
		Quat Quat::Hamilton(Quat other){
			//first translating this into variables that match with hamilton product
			double a1 = this->w;
			double b1 = this->x;
			double c1 = this->y;
			double d1 = this->z;

			double a2 = other.w;
			double b2 = other.x;
			double c2 = other.y;
			double d2 = other.z;

			//now we construct the components for the resulting quaternion
			double a3 = a1*a2 - b1*b2 - c1*c2 - d1*d2;
			double b3 = a1*b2 + b1*a2 + c1*d2 - d1*c2;
			double c3 = a1*c2 - b1*d2 + c1*a2 + d1*b2;
			double d3 = a1*d2 + b1*c2 - c1*b2 + d1*a2;				

			//constructor goes in order of x,y,z,w
			Quat res = Quat(b3, c3, d3, a3);//result quaternion
			return res;
		}
#endif