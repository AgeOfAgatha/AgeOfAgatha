/*--------------------------------------------//
Angles definition
This is used to simplify definition of angles
//--------------------------------------------*/
#ifndef ANGLES_H
#define ANGLES_H
class angles;

class angles{
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
			angles();

		/*--------------------------------------------//
		Constuctor with angles specified
		//--------------------------------------------*/
			angles(double pi, double yi, double ri);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~angles();

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
			//arithmetic
				//addition
					angles operator+(const angles &other);
					angles operator+=(const angles &other);
				//subtraction
					angles operator-(const angles &other);
					angles operator-=(const angles &other);
				//multiplication
					angles operator*(const angles &other);
					angles operator*=(const angles &other);
					angles operator*(const int &other);
					angles operator*=(const int &other);
				//division
					angles operator/(const angles &other);
					angles operator/=(const angles &other);
					angles operator/(const int &other);
					angles operator/=(const int &other);
			//compairisons
				//less than
					bool operator<(const int &other) const;
					bool operator<=(const int &other) const;
					bool operator<(const float &other) const;
					bool operator<=(const float &other) const;
					bool operator<(const double &other) const;
					bool operator<=(const double &other) const;
					bool operator<(const angles &other) const;
					bool operator<=(const angles &other) const;
				//greater than
					bool operator>(const int &other) const;
					bool operator>=(const int &other) const;
					bool operator>(const float &other) const;
					bool operator>=(const float &other) const;
					bool operator>(const double &other) const;
					bool operator>=(const double &other) const;
					bool operator>(const angles &other) const;
					bool operator>=(const angles &other) const;
				//equals
					bool operator==(const angles &other) const;
					bool operator==(const int &other) const;
					bool operator==(const float &other) const;
					bool operator==(const double &other) const;
					bool operator!=(const angles &other) const;
					bool operator!=(const int &other) const;
					bool operator!=(const float &other) const;
					bool operator!=(const double &other) const;
};
#endif