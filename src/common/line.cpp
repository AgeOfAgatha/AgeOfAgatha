/*--------------------------------------------//
Line definition
follows plane definition as: a direction and a
point along that Line in 3d space
//--------------------------------------------*/
#ifndef LINE
#define LINE
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "line.h"
	
	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		Line::Line(){
			n = Vec3(0,0,0);
			p = Vec3(0,0,0);
		}

	/*--------------------------------------------//
	Overloaded constructor
	//--------------------------------------------*/
		Line::Line(Vec3 a, Vec3 b){
			n = a;
			p = b;
		}
		
	/*--------------------------------------------//
	Finds the shortest distance between this Line 
	and a given point
	equations used:
	P = p + U*n, (v-P) dot (n) = 0
	//--------------------------------------------*/
		double Line::Distance(Vec3 v, Vec3& i, double U){
		    U = ((v.x - p.x)*(n.x) + (v.y - p.y)*(n.y) + (v.z - p.z)*(n.z)) / pow(n.Length(), 2);
		    i = v + n*U;
		    double distance = (v - i).Length();
		 	return distance;
		}
#endif
