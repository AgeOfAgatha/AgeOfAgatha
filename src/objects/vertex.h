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

class vertex:public vec4{
	private:
	protected:
		/*--------------------------------------------//
		Class variables
		//--------------------------------------------*/
			vec3* normal;//normal for the vertex
			vec4* color;//vertex color
			vec2* textcoord;//texture coordinates
			double* textblend;//blend between textures
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vertex();
			vertex(double a, double b, double c);
			vertex(vec3 p);
			vertex(vec3 p, vec3 n, vec4 c, vec2 t, double bl);
			vertex(vec3 p, vec3* n, vec4* c, vec2* t, double* bl);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~vertex();

		/*--------------------------------------------//
		Getters
		//--------------------------------------------*/
			vec3 xyz();
			//normals
				vec3* atn();
				double nx();
				double ny();
				double nz();
			//colors
				vec4* atcol();
				double r();
				double g();
				double b();
			//texture
				vec2* atst();
				double* atbl();
				double s();
				double t();
				double blend();

		/*--------------------------------------------//
		Setters
		//--------------------------------------------*/
			//normals
				void nx(double);
				void ny(double);
				void nz(double);
			//colors
				void r(double);
				void g(double);
				void b(double);
			//texture
				void s(double);
				void t(double);
				void blend(double);

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