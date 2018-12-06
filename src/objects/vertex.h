/*--------------------------------------------//
Vertex definition
This is used to simplify definition of points
on a triangular surface of a mesh
//--------------------------------------------*/
#ifndef VERTEX_H
#define VERTEX_H
class vertex;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../common/vector.h"
	#include "mesh.h"

class vertex:public vec3{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vertex();
			vertex(double a, double b, double c);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~vertex();

		/*--------------------------------------------//
		Overriden Functions
		//--------------------------------------------*/
			//Arithmetic
				//Addition
					vertex operator+(const int &other);
					vertex operator+(const float &other);
					vertex operator+(const double &other);
					vertex operator+(const vec3 &other);
				//Subtraction
					vertex operator-(const int &other);
					vertex operator-(const float &other);
					vertex operator-(const double &other);
					vertex operator-(const vec3 &other);
				//Divison
					vertex operator/(const int &other);
					vertex operator/(const float &other);
					vertex operator/(const double &other);
					vertex operator/(const vec3 &other);
				//Multiplication
					vertex operator*(const int &other);
					vertex operator*(const float &other);
					vertex operator*(const double &other);
					vertex operator*(const vec3 &other);
			//Compairison
				//less than
					bool operator<(const vec3 &other) const;
					bool operator<(const int &other) const;
					bool operator<(const float &other) const;
					bool operator<(const double &other) const;
					bool operator<=(const vec3 &other) const;
					bool operator<=(const int &other) const;
					bool operator<=(const float &other) const;
					bool operator<=(const double &other) const;
				//greater than
					bool operator>(const vec3 &other) const;
					bool operator>(const int &other) const;
					bool operator>(const float &other) const;
					bool operator>(const double &other) const;
					bool operator>=(const vec3 &other) const;
					bool operator>=(const int &other) const;
					bool operator>=(const float &other) const;
					bool operator>=(const double &other) const;
				//equals
					bool operator==(const vec3 &other) const;
					bool operator==(const int &other) const;
					bool operator==(const float &other) const;
					bool operator==(const double &other) const;
					bool operator!=(const vec3 &other) const;
					bool operator!=(const int &other) const;
					bool operator!=(const float &other) const;
					bool operator!=(const double &other) const;
			//Assignment
				///=
					vertex operator/=(const vertex &other);
					vertex operator/=(const vec3 &other);
				//*=
					vertex operator*=(const vertex &other);
					vertex operator*=(const vec3 &other);
				//-=
					vertex operator-=(const vertex &other);
					vertex operator-=(const vec3 &other);
				//+=
					vertex operator+=(const vertex &other);
					vertex operator+=(const vec3 &other);
				//==
					vertex operator=(const vertex &other);
					vertex operator=(const vec3 &other);
};
#endif