/*--------------------------------------------//
Vector definition
This is used to simplify definition of points
//--------------------------------------------*/
#ifndef VECTOR_H
#define VECTOR_H
class vec1;
class vec2;
class vec3;
class vec4;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <stdlib.h>
	#include <assert.h>
	#include <math.h>

class vec1{
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double pos[1];
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vec1();
			vec1(double xi);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~vec1();

		/*--------------------------------------------//
		Getters
		//--------------------------------------------*/
			double x() const;

		/*--------------------------------------------//
		Setters
		//--------------------------------------------*/
			void x(double xi);

		/*--------------------------------------------//
		Normalize the vec1
		makes the sum of each component equal to one
		//--------------------------------------------*/
			void normalize();

		/*--------------------------------------------//
		Length of a vector
		//--------------------------------------------*/
			double length() const;

		/*--------------------------------------------//
		Distance between two points
		//--------------------------------------------*/
			double distance(vec1 other) const;

		/*--------------------------------------------//
		dot product of two vectors
		//--------------------------------------------*/
			double dot(vec1 other) const;

		/*--------------------------------------------//
		get pointer to data
		//--------------------------------------------*/
			double* at();

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
			double operator[](const int &index) const;
			//Arithmetic
				//Addition
					vec1 operator+(const int &other);
					vec1 operator+(const float &other);
					vec1 operator+(const double &other);
					vec1 operator+(const vec1 &other);
				//Subtraction
					vec1 operator-(const int &other);
					vec1 operator-(const float &other);
					vec1 operator-(const double &other);
					vec1 operator-(const vec1 &other);
				//Divison
					vec1 operator/(const int &other);
					vec1 operator/(const float &other);
					vec1 operator/(const double &other);
					vec1 operator/(const vec1 &other);
				//Multiplication
					vec1 operator*(const int &other);
					vec1 operator*(const float &other);
					vec1 operator*(const double &other);
					vec1 operator*(const vec1 &other);
			//Compairison
				//less than
					bool operator<(const vec1 &other) const;
					bool operator<(const int &other) const;
					bool operator<(const float &other) const;
					bool operator<(const double &other) const;
					bool operator<=(const vec1 &other) const;
					bool operator<=(const int &other) const;
					bool operator<=(const float &other) const;
					bool operator<=(const double &other) const;
				//greater than
					bool operator>(const vec1 &other) const;
					bool operator>(const int &other) const;
					bool operator>(const float &other) const;
					bool operator>(const double &other) const;
					bool operator>=(const vec1 &other) const;
					bool operator>=(const int &other) const;
					bool operator>=(const float &other) const;
					bool operator>=(const double &other) const;
				//equals
					bool operator==(const vec1 &other) const;
					bool operator==(const int &other) const;
					bool operator==(const float &other) const;
					bool operator==(const double &other) const;
					bool operator!=(const vec1 &other) const;
					bool operator!=(const int &other) const;
					bool operator!=(const float &other) const;
					bool operator!=(const double &other) const;
};
class vec2{
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double pos[2];
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vec2();
			vec2(double xi, double yi);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~vec2();

		/*--------------------------------------------//
		Getters
		//--------------------------------------------*/
			double x() const;
			double y() const;

		/*--------------------------------------------//
		Setters
		//--------------------------------------------*/
			void x(double xi);
			void y(double yi);

		/*--------------------------------------------//
		Normalize the vec2
		makes the sum of each component equal to one
		//--------------------------------------------*/
			void normalize();

		/*--------------------------------------------//
		Length of a vector
		//--------------------------------------------*/
			double length() const;

		/*--------------------------------------------//
		Distance between two points
		//--------------------------------------------*/
			double distance(vec2 other) const;

		/*--------------------------------------------//
		dot product of two vectors
		//--------------------------------------------*/
			double dot(vec2 other) const;

		/*--------------------------------------------//
		get pointer to data
		//--------------------------------------------*/
			double* at();

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
			double operator[](const int &index) const;
			//Arithmetic
				//Addition
					vec2 operator+(const int &other);
					vec2 operator+(const float &other);
					vec2 operator+(const double &other);
					vec2 operator+(const vec2 &other);
				//Subtraction
					vec2 operator-(const int &other);
					vec2 operator-(const float &other);
					vec2 operator-(const double &other);
					vec2 operator-(const vec2 &other);
				//Divison
					vec2 operator/(const int &other);
					vec2 operator/(const float &other);
					vec2 operator/(const double &other);
					vec2 operator/(const vec2 &other);
				//Multiplication
					vec2 operator*(const int &other);
					vec2 operator*(const float &other);
					vec2 operator*(const double &other);
					vec2 operator*(const vec2 &other);
			//Compairison
				//less than
					bool operator<(const vec2 &other) const;
					bool operator<(const int &other) const;
					bool operator<(const float &other) const;
					bool operator<(const double &other) const;
					bool operator<=(const vec2 &other) const;
					bool operator<=(const int &other) const;
					bool operator<=(const float &other) const;
					bool operator<=(const double &other) const;
				//greater than
					bool operator>(const vec2 &other) const;
					bool operator>(const int &other) const;
					bool operator>(const float &other) const;
					bool operator>(const double &other) const;
					bool operator>=(const vec2 &other) const;
					bool operator>=(const int &other) const;
					bool operator>=(const float &other) const;
					bool operator>=(const double &other) const;
				//equals
					bool operator==(const vec2 &other) const;
					bool operator==(const int &other) const;
					bool operator==(const float &other) const;
					bool operator==(const double &other) const;
					bool operator!=(const vec2 &other) const;
					bool operator!=(const int &other) const;
					bool operator!=(const float &other) const;
					bool operator!=(const double &other) const;
};
class vec3{
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double pos[3];
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vec3();
			vec3(double xi, double yi, double zi);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~vec3();

		/*--------------------------------------------//
		Getters
		//--------------------------------------------*/
			double x() const;
			double y() const;
			double z() const;

		/*--------------------------------------------//
		Setters
		//--------------------------------------------*/
			void x(double xi);
			void y(double yi);
			void z(double zi);

		/*--------------------------------------------//
		Normalize the vec3
		makes the sum of each component equal to one
		//--------------------------------------------*/
			void normalize();

		/*--------------------------------------------//
		Length of a vector
		//--------------------------------------------*/
			double length() const;

		/*--------------------------------------------//
		Distance between two points
		//--------------------------------------------*/
			double distance(vec3 other) const;

		/*--------------------------------------------//
		dot product of two vectors
		//--------------------------------------------*/
			double dot(vec3 other) const;

		/*--------------------------------------------//
		get pointer to data
		//--------------------------------------------*/
			double* at();

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
			double operator[](const int &index) const;
			//Arithmetic
				//Addition
					vec3 operator+(const int &other);
					vec3 operator+(const float &other);
					vec3 operator+(const double &other);
					vec3 operator+(const vec3 &other);
				//Subtraction
					vec3 operator-(const int &other);
					vec3 operator-(const float &other);
					vec3 operator-(const double &other);
					vec3 operator-(const vec3 &other);
				//Divison
					vec3 operator/(const int &other);
					vec3 operator/(const float &other);
					vec3 operator/(const double &other);
					vec3 operator/(const vec3 &other);
				//Multiplication
					vec3 operator*(const int &other);
					vec3 operator*(const float &other);
					vec3 operator*(const double &other);
					vec3 operator*(const vec3 &other);
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
class vec4{
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double pos[4];
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vec4();
			vec4(double xi, double yi, double zi, double wi);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~vec4();

		/*--------------------------------------------//
		Getters
		//--------------------------------------------*/
			double x() const;
			double y() const;
			double z() const;
			double w() const;

		/*--------------------------------------------//
		Setters
		//--------------------------------------------*/
			void x(double xi);
			void y(double yi);
			void z(double zi);
			void w(double wi);

		/*--------------------------------------------//
		Normalize the vec4
		makes the sum of each component equal to one
		//--------------------------------------------*/
			void normalize();

		/*--------------------------------------------//
		Length of a vector
		//--------------------------------------------*/
			double length() const;

		/*--------------------------------------------//
		Distance between two points
		//--------------------------------------------*/
			double distance(vec4 other) const;

		/*--------------------------------------------//
		dot product of two vectors
		//--------------------------------------------*/
			double dot(vec4 other) const;

		/*--------------------------------------------//
		get pointer to data
		//--------------------------------------------*/
			double* at();

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
			double operator[](const int &index) const;
			//Arithmetic
				//Addition
					vec4 operator+(const int &other);
					vec4 operator+(const float &other);
					vec4 operator+(const double &other);
					vec4 operator+(const vec4 &other);
				//Subtraction
					vec4 operator-(const int &other);
					vec4 operator-(const float &other);
					vec4 operator-(const double &other);
					vec4 operator-(const vec4 &other);
				//Divison
					vec4 operator/(const int &other);
					vec4 operator/(const float &other);
					vec4 operator/(const double &other);
					vec4 operator/(const vec4 &other);
				//Multiplication
					vec4 operator*(const int &other);
					vec4 operator*(const float &other);
					vec4 operator*(const double &other);
					vec4 operator*(const vec4 &other);
			//Compairison
				//less than
					bool operator<(const vec4 &other) const;
					bool operator<(const int &other) const;
					bool operator<(const float &other) const;
					bool operator<(const double &other) const;
					bool operator<=(const vec4 &other) const;
					bool operator<=(const int &other) const;
					bool operator<=(const float &other) const;
					bool operator<=(const double &other) const;
				//greater than
					bool operator>(const vec4 &other) const;
					bool operator>(const int &other) const;
					bool operator>(const float &other) const;
					bool operator>(const double &other) const;
					bool operator>=(const vec4 &other) const;
					bool operator>=(const int &other) const;
					bool operator>=(const float &other) const;
					bool operator>=(const double &other) const;
				//equals
					bool operator==(const vec4 &other) const;
					bool operator==(const int &other) const;
					bool operator==(const float &other) const;
					bool operator==(const double &other) const;
					bool operator!=(const vec4 &other) const;
					bool operator!=(const int &other) const;
					bool operator!=(const float &other) const;
					bool operator!=(const double &other) const;
};
#endif