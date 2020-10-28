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
	#include "../globals.h"

	#include "../common/vector.h"
	#include "mesh.h"

class vertex{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Class variables
		//--------------------------------------------*/
			Vec4* pos;//position for the vertex
			Vec3* normal;//normal for the vertex
			Vec4* color;//vertex color
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vertex();
			vertex(double a, double b, double c);
			vertex(Vec3 p);
			vertex(Vec3 p, Vec3 n, Vec4 c);
			vertex(Vec4* p, Vec3* n, Vec4* c);

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
					vertex operator+(const Vec3 &other);
					vertex operator+=(const int &other);
					vertex operator+=(const float &other);
					vertex operator+=(const double &other);
					vertex operator+=(const Vec3 &other);
				//Subtraction
					vertex operator-(const int &other);
					vertex operator-(const float &other);
					vertex operator-(const double &other);
					vertex operator-(const Vec3 &other);
					vertex operator-=(const int &other);
					vertex operator-=(const float &other);
					vertex operator-=(const double &other);
					vertex operator-=(const Vec3 &other);
				//Divison
					vertex operator/(const int &other);
					vertex operator/(const float &other);
					vertex operator/(const double &other);
					vertex operator/(const Vec3 &other);
					vertex operator/=(const int &other);
					vertex operator/=(const float &other);
					vertex operator/=(const double &other);
					vertex operator/=(const Vec3 &other);
				//Multiplication
					vertex operator*(const int &other);
					vertex operator*(const float &other);
					vertex operator*(const double &other);
					vertex operator*(const Vec3 &other);
					vertex operator*=(const int &other);
					vertex operator*=(const float &other);
					vertex operator*=(const double &other);
					vertex operator*=(const Vec3 &other);
			//Compairison
				//less than
					bool operator<(const Vec3 &other) const;
					bool operator<(const int &other) const;
					bool operator<(const float &other) const;
					bool operator<(const double &other) const;
					bool operator<=(const Vec3 &other) const;
					bool operator<=(const int &other) const;
					bool operator<=(const float &other) const;
					bool operator<=(const double &other) const;
				//greater than
					bool operator>(const Vec3 &other) const;
					bool operator>(const int &other) const;
					bool operator>(const float &other) const;
					bool operator>(const double &other) const;
					bool operator>=(const Vec3 &other) const;
					bool operator>=(const int &other) const;
					bool operator>=(const float &other) const;
					bool operator>=(const double &other) const;
				//equals
					bool operator==(const Vec3 &other) const;
					bool operator==(const int &other) const;
					bool operator==(const float &other) const;
					bool operator==(const double &other) const;
					bool operator!=(const Vec3 &other) const;
					bool operator!=(const int &other) const;
					bool operator!=(const float &other) const;
					bool operator!=(const double &other) const;
};
#endif
