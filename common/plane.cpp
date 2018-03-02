/*--------------------------------------------//
Plane definition
follows plane definition as: ax + by + cz + d = 0
//--------------------------------------------*/
#ifndef PLANE
#define PLANE

#ifndef VERTEX
#include "vertex.cpp"
#endif

class plane{
	private:
		vector n;//normal vector, (a,b,c)
		double d;//basically offset, d = -(a*x0 + b*y0 + c*z0)
	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		plane(){
			n = vector(0,0,0);
			d = 0.0;
		}
		/*--------------------------------------------//
		Overloaded constructors
		//--------------------------------------------*/
		plane(vector a, vector b){
			n = a;
			d = -(a.x*b.x + a.y*b.y + a.z*b.z);
		}
		plane(vector a, double b){
			n = a;
			d = b;
		}
		/*--------------------------------------------//
		Check if point is behind us
		//--------------------------------------------*/
		bool facing(vector a){
			return ((n.x*a.x + n.y*a.y + n.z*a.y - d) / a.length()) > 0;
		}
};
#endif