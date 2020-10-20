/*--------------------------------------------//
Angles definition
This is used to simplify definition of Angles
//--------------------------------------------*/
#ifndef ANGLES_H
#define ANGLES_H
class Angles;

class Angles{
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double p;
			double y;
			double r;
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
			Angles();

		/*--------------------------------------------//
		Constuctor with Angles specified
		//--------------------------------------------*/
			Angles(double pi, double yi, double ri);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~Angles();

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
			//arithmetic
				//addition
					Angles operator+(const Angles &other);
					Angles operator+=(const Angles &other);
				//subtraction
					Angles operator-(const Angles &other);
					Angles operator-=(const Angles &other);
				//multiplication
					Angles operator*(const Angles &other);
					Angles operator*=(const Angles &other);
					Angles operator*(const int &other);
					Angles operator*=(const int &other);
				//division
					Angles operator/(const Angles &other);
					Angles operator/=(const Angles &other);
					Angles operator/(const int &other);
					Angles operator/=(const int &other);
			//compairisons
				//less than
					bool operator<(const int &other) const;
					bool operator<=(const int &other) const;
					bool operator<(const float &other) const;
					bool operator<=(const float &other) const;
					bool operator<(const double &other) const;
					bool operator<=(const double &other) const;
					bool operator<(const Angles &other) const;
					bool operator<=(const Angles &other) const;
				//greater than
					bool operator>(const int &other) const;
					bool operator>=(const int &other) const;
					bool operator>(const float &other) const;
					bool operator>=(const float &other) const;
					bool operator>(const double &other) const;
					bool operator>=(const double &other) const;
					bool operator>(const Angles &other) const;
					bool operator>=(const Angles &other) const;
				//equals
					bool operator==(const Angles &other) const;
					bool operator==(const int &other) const;
					bool operator==(const float &other) const;
					bool operator==(const double &other) const;
					bool operator!=(const Angles &other) const;
					bool operator!=(const int &other) const;
					bool operator!=(const float &other) const;
					bool operator!=(const double &other) const;
};
#endif