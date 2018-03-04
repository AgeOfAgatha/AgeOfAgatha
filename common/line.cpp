/*--------------------------------------------//
Line definition
follows plane definition as: a direction and a
point along that line in 3d space
//--------------------------------------------*/
#ifndef LINE
#define LINE

#ifndef VERTEX
#include "vertex.cpp"
#endif

class line{
	private:
		vector n;//directional vector
		vector p;//basically offset, a point along the line from which the line extends along n and -n
	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		line(){
			n = vector(0,0,0);
			p = vector(0,0,0);
		}

		/*--------------------------------------------//
		Overloaded constructor
		//--------------------------------------------*/
		line(vector a, vector b){
			n = a;
			p = b;
		}
		line(vertex a, vector b):line((vector)a, b){}
		line(vector a, vertex b):line(a, (vector)b){}
		line(vertex a, vertex b):line((vector)a, (vector)b){}

		/*--------------------------------------------//
		Finds the shortest distance between this line 
		and a given point
		equations used:
		P = p + U*n, (v-P) dot (n) = 0
		//--------------------------------------------*/
		double distance(vector v, vector& i, double U){
		    U = ((v.x - p.x)*(n.x) + (v.y - p.y)*(n.y) + (v.z - p.z)*(n.z)) / pow(n.length(), 2);
		    i = v + n*U;
		    double distance = (v - i).length();
		 	return distance;
		}
};
#endif