/*--------------------------------------------//
Vertex definition
This is used to simplify definition of points
on a triangular surface of a mesh
//--------------------------------------------*/
#ifndef VERTEX
#define VERTEX

#ifndef VECTOR
#include "../common/vector.cpp"
#endif

class vertex: public vector{
	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		vertex():vector(){};

		/*--------------------------------------------//
		Constuctor with positions specified
		//--------------------------------------------*/
		vertex(double xi, double yi, double zi):vector(xi, yi, zi){};

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~vertex(){};

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
		bool operator==(const vertex &other) const {
			return (this->x == other.x && this->y == other.y && this->z == other.z);
		};
		bool operator!=(const vertex &other) const {
			return *this!=other;
		};
};
#endif