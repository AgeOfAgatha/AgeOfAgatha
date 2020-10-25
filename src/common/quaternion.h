/*--------------------------------------------//
quaternion header
simplifies quaternion use
//--------------------------------------------*/
#ifndef QUATERNION_H
#define QUATERNION_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "vector.h"
	#include "angles.h"

/*--------------------------------------------//
Classes
//--------------------------------------------*/
	class Quat{
		private:
		protected:
		public:
			/*--------------------------------------------//
			Variables
			//--------------------------------------------*/
				float x;
				float y;
				float z;
				float w;
			/*--------------------------------------------//
			Constructors
			//--------------------------------------------*/
				Quat(){}
				Quat(Angles ang);
				Quat(Vec3 u, Vec3 v);
				Quat(float s, Vec3 vec):x(vec.x),y(vec.y),z(vec.z),w(s){}
				Quat(const Quat& q):x(q.x),y(q.y),z(q.z),w(q.w){}
				Quat(double wi, double xi, double yi, double zi):x(xi),y(yi),z(zi),w(wi){}
			/*--------------------------------------------//
			Functions
			//--------------------------------------------*/
				Quat Identity(){return Quat(1,0,0,0);}
				Quat Cross(Quat q2);
				float Dot(Quat q);
				float Length();
				Quat Normalize();
				Quat Hamilton(Quat other);

			/*--------------------------------------------//
			Overridden operators
			//--------------------------------------------*/
				operator float* () const {return (float*) this;}
				operator const float* () const {return (const float*) this;}
				Quat operator=(const Quat &other){this->x = other.x; this->y = other.y; this->z = other.z; this->w = other.w; return *this;}
				float operator[](int i) const {switch(i){case 0: return x; break; case 1: return y; break; case 2: return z; break; case 3: return w; break;}}
				//Arithmetic
					//Addition
						Quat operator+(void) const {return (*this);}
						Quat operator+(const int &other) const {return Quat(this->x + other, this->y + other, this->z + other, this->w + other);}
						Quat operator+(const float &other) const {return Quat(this->x + other, this->y + other, this->z + other, this->w + other);}
						Quat operator+(const double &other) const {return Quat(this->x + other, this->y + other, this->z + other, this->w + other);}
						Quat operator+(const Quat &other) const {return Quat(this->x + other[0], this->y + other[1], this->z + other[2], this->w + other[3]);}
						Quat operator+=(const int &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						Quat operator+=(const float &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						Quat operator+=(const double &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						Quat operator+=(const Quat &other){this->x += other[0]; this->y += other[1]; this->z += other[2]; this->w += other[2]; return *this;}
					//Subtraction
						Quat operator-(void) const {return Quat(-x, -y, -z, -w);}
						Quat operator-(const int &other) const {return Quat(this->x - other, this->y - other, this->z - other, this->w - other);}
						Quat operator-(const float &other) const {return Quat(this->x - other, this->y - other, this->z - other, this->w - other);}
						Quat operator-(const double &other) const {return Quat(this->x - other, this->y - other, this->z - other, this->w - other);}
						Quat operator-(const Quat &other) const {return Quat(this->x - other[0], this->y - other[1], this->z - other[2], this->w - other[3]);}
						Quat operator-=(const int &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						Quat operator-=(const float &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						Quat operator-=(const double &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						Quat operator-=(const Quat &other){this->x -= other[0]; this->y -= other[1]; this->z -= other[2]; this->w -= other[3]; return *this;}
					//Divison
						Quat operator/(const int &other) const {return Quat(this->x / other, this->y / other, this->z / other, this->w / other);}
						Quat operator/(const float &other) const {return Quat(this->x / other, this->y / other, this->z / other, this->w / other);}
						Quat operator/(const double &other) const {return Quat(this->x / other, this->y / other, this->z / other, this->w / other);}
						Quat operator/(const Quat &other) const {return Quat(this->x / other[0], this->y / other[1], this->z / other[2], this->w / other[3]);}
						Quat operator/=(const int &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						Quat operator/=(const float &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						Quat operator/=(const double &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						Quat operator/=(const Quat &other){this->x /= other[0]; this->y /= other[1]; this->z /= other[2]; this->w /= other[3]; return *this;}
					//Multiplication
						Quat operator*(const int &other) const {return Quat(this->x * other, this->y * other, this->z * other, this->w * other);}
						Quat operator*(const float &other) const {return Quat(this->x * other, this->y * other, this->z * other, this->w * other);}
						Quat operator*(const double &other) const {return Quat(this->x * other, this->y * other, this->z * other, this->w * other);}
						Quat operator*(const Quat &other) const {return Quat(this->x * other[0], this->y * other[1], this->z * other[2], this->w * other[3]);}
						Quat operator*=(const int &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						Quat operator*=(const float &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						Quat operator*=(const double &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						Quat operator*=(const Quat &other){this->x *= other[0]; this->y *= other[1]; this->z *= other[2]; this->w *= other[3]; return *this;}
				//Compairison
					//less than
						bool operator<(const int &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<(const float &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<(const double &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<(const Quat &other) const{return this->x < other[0] && this->y < other[1] && this->z < other[2] && this->w < other[3];}
						bool operator<=(const int &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
						bool operator<=(const float &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
						bool operator<=(const double &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
						bool operator<=(const Quat &other) const{return this->x <= other[0] && this->y <= other[1] && this->z <= other[2] && this->w <= other[3];}
					//greater than
						bool operator>(const int &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>(const float &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>(const double &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>(const Quat &other) const{return this->x > other[0] && this->y > other[1] && this->z > other[2] && this->w > other[3];}
						bool operator>=(const int &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
						bool operator>=(const float &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
						bool operator>=(const double &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
						bool operator>=(const Quat &other) const{return this->x >= other[0] && this->y >= other[1] && this->z >= other[2] && this->w >= other[3];}
					//equals
						bool operator==(const int &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator==(const float &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator==(const double &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator==(const Quat &other) const{return this->x == other[0] && this->y == other[1] && this->z == other[2] && this->w == other[3];}
						bool operator!=(const int &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
						bool operator!=(const float &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
						bool operator!=(const double &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
						bool operator!=(const Quat &other) const{return this->x != other[0] && this->y != other[1] && this->z != other[2] && this->w != other[3];}
	};
#endif