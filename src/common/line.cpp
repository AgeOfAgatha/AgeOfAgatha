/*--------------------------------------------//
Line definition
follows plane definition as: a direction and a
point along that line in 3d space
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
		line::line(){
			n = vec3(0,0,0);
			p = vec3(0,0,0);
		}

	/*--------------------------------------------//
	Overloaded constructor
	//--------------------------------------------*/
		line::line(vec3 a, vec3 b){
			n = a;
			p = b;
		}
		
	/*--------------------------------------------//
	Finds the shortest distance between this line 
	and a given point
	equations used:
	P = p + U*n, (v-P) dot (n) = 0
	//--------------------------------------------*/
		double line::distance(vec3 v, vec3& i, double U){
		    U = ((v.x - p.x)*(n.x) + (v.y - p.y)*(n.y) + (v.z - p.z)*(n.z)) / pow(n.length(), 2);
		    i = v + n*U;
		    double distance = (v - i).length();
		 	return distance;
		}
#endif