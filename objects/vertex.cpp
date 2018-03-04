/*--------------------------------------------//
Vertex definition
This is used to simplify definition of points
on a triangular surface of a mesh
//--------------------------------------------*/
#ifndef VERTEX
#define VERTEX

#ifndef VECTOR
#include "../common/vector.cpp"
#endif

class vertex: public vector{
	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		vertex():vector(){};

		/*--------------------------------------------//
		Constuctor with positions specified
		//--------------------------------------------*/
		vertex(double xi, double yi, double zi):vector(xi, yi, zi){};

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~vertex(){};

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
		//Addition
			vertex operator+(const int &other) {
				this->x += other;
				this->y += other;
				this->z += other;
				return (*this);
			};
			vertex operator+(const float &other) {
				this->x += other;
				this->y += other;
				this->z += other;
				return (*this);
			};
			vertex operator+(const double &other) {
				this->x += other;
				this->y += other;
				this->z += other;
				return (*this);
			};
			vertex operator+(const vector &other) {
				this->x += other.x;
				this->y += other.y;
				this->z += other.z;
				return (*this);
			};
		//Subtraction
			vertex operator-(const int &other) {
				this->x -= other;
				this->y -= other;
				this->z -= other;
				return (*this);
			};
			vertex operator-(const float &other) {
				this->x -= other;
				this->y -= other;
				this->z -= other;
				return (*this);
			};
			vertex operator-(const double &other) {
				this->x -= other;
				this->y -= other;
				this->z -= other;
				return (*this);
			};
			vertex operator-(const vector &other) {
				this->x -= other.x;
				this->y -= other.y;
				this->z -= other.z;
				return (*this);
			};
		//Divison
			vertex operator/(const int &other) {
				this->x /= other;
				this->y /= other;
				this->z /= other;
				return (*this);
			};
			vertex operator/(const float &other) {
				this->x /= other;
				this->y /= other;
				this->z /= other;
				return (*this);
			};
			vertex operator/(const double &other) {
				this->x /= other;
				this->y /= other;
				this->z /= other;
				return (*this);
			};
			vertex operator/(const vector &other) {
				this->x /= other.x;
				this->y /= other.y;
				this->z /= other.z;
				return (*this);
			};
		//Multiplication
			vertex operator*(const int &other) {
				this->x *= other;
				this->y *= other;
				this->z *= other;
				return (*this);
			};
			vertex operator*(const float &other) {
				this->x *= other;
				this->y *= other;
				this->z *= other;
				return (*this);
			};
			vertex operator*(const double &other) {
				this->x *= other;
				this->y *= other;
				this->z *= other;
				return (*this);
			};
			vertex operator*(const vector &other) {
				this->x *= other.x;
				this->y *= other.y;
				this->z *= other.z;
				return (*this);
			};		
		//Compairison
			//less than
				bool operator<(const vector &other) const {
					return (this->x < other.x && this->y < other.y && this->z < other.z);
				};
				bool operator<(const int &other) const {
					return (this->x < other && this->y < other && this->z < other);
				};
				bool operator<(const float &other) const {
					return (this->x < other && this->y < other && this->z < other);
				};
				bool operator<(const double &other) const {
					return (this->x < other && this->y < other && this->z < other);
				};
				bool operator<=(const vector &other) const {
					return (this->x <= other.x && this->y <= other.y && this->z <= other.z);
				};
				bool operator<=(const int &other) const {
					return (this->x <= other && this->y <= other && this->z <= other);
				};
				bool operator<=(const float &other) const {
					return (this->x <= other && this->y <= other && this->z <= other);
				};
				bool operator<=(const double &other) const {
					return (this->x <= other && this->y <= other && this->z <= other);
				};
			//greater than
				bool operator>(const vector &other) const {
					return (this->x > other.x && this->y > other.y && this->z > other.z);
				};
				bool operator>(const int &other) const {
					return (this->x > other && this->y > other && this->z > other);
				};
				bool operator>(const float &other) const {
					return (this->x > other && this->y > other && this->z > other);
				};
				bool operator>(const double &other) const {
					return (this->x > other && this->y > other && this->z > other);
				};
				bool operator>=(const vector &other) const {
					return (this->x >= other.x && this->y >= other.y && this->z >= other.z);
				};
				bool operator>=(const int &other) const {
					return (this->x >= other && this->y >= other && this->z >= other);
				};
				bool operator>=(const float &other) const {
					return (this->x >= other && this->y >= other && this->z >= other);
				};
				bool operator>=(const double &other) const {
					return (this->x >= other && this->y >= other && this->z >= other);
				};
			//equals
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
				bool operator!=(const int &other) const {
					return *this!=other;
				};
				bool operator!=(const float &other) const {
					return *this!=other;
				};
				bool operator!=(const double &other) const {
					return *this!=other;
				};
		//Assignment
			///=
				vertex operator/=(const vertex &other){
					this->x /= other.x;
					this->y /= other.y;
					this->z /= other.z;
					return *this;
				}
				vertex operator/=(const vector &other){
					this->x /= other.x;
					this->y /= other.y;
					this->z /= other.z;
					return *this;
				}
			//*=
				vertex operator*=(const vertex &other){
					this->x *= other.x;
					this->y *= other.y;
					this->z *= other.z;
					return *this;
				}
				vertex operator*=(const vector &other){
					this->x *= other.x;
					this->y *= other.y;
					this->z *= other.z;
					return *this;
				}
			//-=
				vertex operator-=(const vertex &other){
					this->x -= other.x;
					this->y -= other.y;
					this->z -= other.z;
					return *this;
				}
				vertex operator-=(const vector &other){
					this->x -= other.x;
					this->y -= other.y;
					this->z -= other.z;
					return *this;
				}
			//+=
				vertex operator+=(const vertex &other){
					this->x += other.x;
					this->y += other.y;
					this->z += other.z;
					return *this;
				}
				vertex operator+=(const vector &other){
					this->x += other.x;
					this->y += other.y;
					this->z += other.z;
					return *this;
				}
			//==
				vertex operator=(const vertex &other){
					this->x = other.x;
					this->y = other.y;
					this->z = other.z;
					return *this;
				}
				vertex operator=(const vector &other){
					this->x = other.x;
					this->y = other.y;
					this->z = other.z;
					return *this;
				}
};
#endif