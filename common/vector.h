/*--------------------------------------------//
Vector definition
This is used to simplify definition of points
//--------------------------------------------*/
#ifndef VECTOR_H
#define VECTOR_H
class vector;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <stdlib.h>
	#include <math.h>

class vector{
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double pos[3];
			
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			vector();
			vector(double xi, double yi, double zi);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~vector();

		/*--------------------------------------------//
		Getters
		//--------------------------------------------*/
			double x();
			double y();
			double z();

		/*--------------------------------------------//
		Setters
		//--------------------------------------------*/
			void x(double xi);
			void y(double yi);
			void z(double zi);

		/*--------------------------------------------//
		Normalize the vector
		makes the sum of each component equal to one
		//--------------------------------------------*/
			void normalize();

		/*--------------------------------------------//
		Length of a vector
		//--------------------------------------------*/
			double length();

		/*--------------------------------------------//
		Distance between two points
		//--------------------------------------------*/
			double distance(vector vec2);

		/*--------------------------------------------//
		dot product of two vectors
		//--------------------------------------------*/
			double dot(vector vec2);

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
			//Arithmetic
				//Addition
					vector operator+(const int &other);
					vector operator+(const float &other);
					vector operator+(const double &other);
					vector operator+(const vector &other);
				//Subtraction
					vector operator-(const int &other);
					vector operator-(const float &other);
					vector operator-(const double &other);
					vector operator-(const vector &other);
				//Divison
					vector operator/(const int &other);
					vector operator/(const float &other);
					vector operator/(const double &other);
					vector operator/(const vector &other);
				//Multiplication
					vector operator*(const int &other);
					vector operator*(const float &other);
					vector operator*(const double &other);
					vector operator*(const vector &other);
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
};
#endif