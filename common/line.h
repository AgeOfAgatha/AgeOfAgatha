/*--------------------------------------------//
Line header
follows plane definition as: a direction and a
point along that line in 3d space
//--------------------------------------------*/
#ifndef LINE_H
#define LINE_H
class line;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <math.h>
	#include "vector.h"
	#include "../objects/vertex.h"

class line{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			vector n;//directional vector
			vector p;//basically offset, a point along the line from which the line extends along n and -n
			
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			line();
			line(vector a, vector b);
			line(vertex a, vector b):line((vector) a, b){}
			line(vector a, vertex b):line(a, (vector) b){}
			line(vertex a, vertex b):line((vector) a, (vector) b){}

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			double distance(vector v, vector& i, double U);
};
#endif