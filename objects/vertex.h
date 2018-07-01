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

class vertex:public vector{
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vertex();
			vertex(double xi, double yi, double zi);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~vertex();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			//Arithmetic
				//Addition
					vertex operator+(const int &other);
					vertex operator+(const float &other);
					vertex operator+(const double &other);
					vertex operator+(const vector &other);
				//Subtraction
					vertex operator-(const int &other);
					vertex operator-(const float &other);
					vertex operator-(const double &other);
					vertex operator-(const vector &other);
				//Divison
					vertex operator/(const int &other);
					vertex operator/(const float &other);
					vertex operator/(const double &other);
					vertex operator/(const vector &other);
				//Multiplication
					vertex operator*(const int &other);
					vertex operator*(const float &other);
					vertex operator*(const double &other);
					vertex operator*(const vector &other);
			//Compairison
				//less than
					bool operator<(const vector &other) const;
					bool operator<(const int &other) const;
					bool operator<(const float &other) const;
					bool operator<(const double &other) const;
					bool operator<=(const vector &other) const;
					bool operator<=(const int &other) const;
					bool operator<=(const float &other) const;
					bool operator<=(const double &other) const;
				//greater than
					bool operator>(const vector &other) const;
					bool operator>(const int &other) const;
					bool operator>(const float &other) const;
					bool operator>(const double &other) const;
					bool operator>=(const vector &other) const;
					bool operator>=(const int &other) const;
					bool operator>=(const float &other) const;
					bool operator>=(const double &other) const;
				//equals
					bool operator==(const vector &other) const;
					bool operator==(const int &other) const;
					bool operator==(const float &other) const;
					bool operator==(const double &other) const;
					bool operator!=(const vector &other) const;
					bool operator!=(const int &other) const;
					bool operator!=(const float &other) const;
					bool operator!=(const double &other) const;
			//Assignment
				///=
					vertex operator/=(const vertex &other);
					vertex operator/=(const vector &other);
				//*=
					vertex operator*=(const vertex &other);
					vertex operator*=(const vector &other);
				//-=
					vertex operator-=(const vertex &other);
					vertex operator-=(const vector &other);
				//+=
					vertex operator+=(const vertex &other);
					vertex operator+=(const vector &other);
				//==
					vertex operator=(const vertex &other);
					vertex operator=(const vector &other);
};
#endif