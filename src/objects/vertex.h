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
	#include "../../deps/glm/glm.hpp"
	#include "../../deps/gl/glew.h"
	#include "../../deps/gl/freeglut.h"

	#include "../common/vector.h"
	#include "mesh.h"

class vertex{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Class variables
		//--------------------------------------------*/
			vec4* pos;//position for the vertex
			vec3* normal;//normal for the vertex
			vec4* color;//vertex color
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vertex();
			vertex(double a, double b, double c);
			vertex(vec3 p);
			vertex(vec3 p, vec3 n, vec4 c);
			vertex(vec4* p, vec3* n, vec4* c);

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
					vertex operator+=(const int &other);
					vertex operator+=(const float &other);
					vertex operator+=(const double &other);
					vertex operator+=(const vec3 &other);
				//Subtraction
					vertex operator-(const int &other);
					vertex operator-(const float &other);
					vertex operator-(const double &other);
					vertex operator-(const vec3 &other);
					vertex operator-=(const int &other);
					vertex operator-=(const float &other);
					vertex operator-=(const double &other);
					vertex operator-=(const vec3 &other);
				//Divison
					vertex operator/(const int &other);
					vertex operator/(const float &other);
					vertex operator/(const double &other);
					vertex operator/(const vec3 &other);
					vertex operator/=(const int &other);
					vertex operator/=(const float &other);
					vertex operator/=(const double &other);
					vertex operator/=(const vec3 &other);
				//Multiplication
					vertex operator*(const int &other);
					vertex operator*(const float &other);
					vertex operator*(const double &other);
					vertex operator*(const vec3 &other);
					vertex operator*=(const int &other);
					vertex operator*=(const float &other);
					vertex operator*=(const double &other);
					vertex operator*=(const vec3 &other);
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
};
#endif