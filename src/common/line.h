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

class line{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			vec3 n;//directional vector
			vec3 p;//basically offset, a point along the line from which the line extends along n and -n
			
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			line();
			line(vec3 a, vec3 b);

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			double distance(vec3 v, vec3& i, double U);
};
#endif