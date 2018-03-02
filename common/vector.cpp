/*--------------------------------------------//
Vector definition
This is used to simplify definition of points
//--------------------------------------------*/
#ifndef VECTOR
#define VECTOR
#include <stdlib.h>
class vector{
	public:
		double x;
		double y;
		double z; 
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		vector(){
			x = 0;
			y = 0;
			z = 0;
		};

		/*--------------------------------------------//
		Constuctor with positions specified
		//--------------------------------------------*/
		vector(double xi, double yi, double zi):vector(){
			x = xi;
			y = yi;
			z = zi;
		};

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~vector(){};

		/*--------------------------------------------//
		Normalize the vector
		makes the sum of each component equal to one
		//--------------------------------------------*/
		void normalize(){
			int a = abs(x)+abs(y)+abs(z);
			x = x/a;
			y = y/a;
			z = z/a;
		}

		/*--------------------------------------------//
		Length of a vector
		//--------------------------------------------*/
		double length(){
			return (sqrt( pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) ));
		}

		/*--------------------------------------------//
		Distance between two points
		//--------------------------------------------*/
		double distance(vector vec2){
			return (sqrt( pow(this->x - vec2.x, 2) + pow(this->y - vec2.y, 2) + pow(this->z - vec2.z, 2) ));
		}

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
		//Addition
			vector operator+(const int &other) {
				this->x += other;
				this->y += other;
				this->z += other;
				return (*this);
			};
			vector operator+(const float &other) {
				this->x += other;
				this->y += other;
				this->z += other;
				return (*this);
			};
			vector operator+(const double &other) {
				this->x += other;
				this->y += other;
				this->z += other;
				return (*this);
			};
			vector operator+(const vector &other) {
				this->x += other.x;
				this->y += other.y;
				this->z += other.z;
				return (*this);
			};
		//Subtraction
			vector operator-(const int &other) {
				this->x -= other;
				this->y -= other;
				this->z -= other;
				return (*this);
			};
			vector operator-(const float &other) {
				this->x -= other;
				this->y -= other;
				this->z -= other;
				return (*this);
			};
			vector operator-(const double &other) {
				this->x -= other;
				this->y -= other;
				this->z -= other;
				return (*this);
			};
			vector operator-(const vector &other) {
				this->x -= other.x;
				this->y -= other.y;
				this->z -= other.z;
				return (*this);
			};
		//Divison
			vector operator/(const int &other) {
				this->x /= other;
				this->y /= other;
				this->z /= other;
				return (*this);
			};
			vector operator/(const float &other) {
				this->x /= other;
				this->y /= other;
				this->z /= other;
				return (*this);
			};
			vector operator/(const double &other) {
				this->x /= other;
				this->y /= other;
				this->z /= other;
				return (*this);
			};
			vector operator/(const vector &other) {
				this->x /= other.x;
				this->y /= other.y;
				this->z /= other.z;
				return (*this);
			};
		//Multiplication
			vector operator*(const int &other) {
				this->x *= other;
				this->y *= other;
				this->z *= other;
				return (*this);
			};
			vector operator*(const float &other) {
				this->x *= other;
				this->y *= other;
				this->z *= other;
				return (*this);
			};
			vector operator*(const double &other) {
				this->x *= other;
				this->y *= other;
				this->z *= other;
				return (*this);
			};
			vector operator*(const vector &other) {
				this->x *= other.x;
				this->y *= other.y;
				this->z *= other.z;
				return (*this);
			};		
		//Compairison
			bool operator==(const vector &other) const {
				return (this->x == other.x && this->y == other.y && this->z == other.z);
			};
			bool operator==(const int &other) const {
				return (this->x == other && this->y == other && this->z == other);
			};
			bool operator==(const float &other) const {
				return (this->x == other && this->y == other && this->z == other);
			};
			bool operator==(const double &other) const {
				return (this->x == other && this->y == other && this->z == other);
			};
			bool operator!=(const vector &other) const {
				return *this!=other;
			};
};
#endif