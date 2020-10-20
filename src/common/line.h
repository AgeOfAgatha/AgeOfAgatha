/*--------------------------------------------//
Line header
follows plane definition as: a direction and a
point along that Line in 3d space
//--------------------------------------------*/
#ifndef LINE_H
#define LINE_H
class Line;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <math.h>

	#include "vector.h"

class Line{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			vec3 n;//directional vector
			vec3 p;//basically offset, a point along the Line from which the Line extends along n and -n
			
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			Line();
			Line(vec3 a, vec3 b);

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			double Distance(vec3 v, vec3& i, double U);
};
#endif