/*--------------------------------------------//
Vector header
simplifies vector use
//--------------------------------------------*/
#ifndef VECTOR_H
#define VECTOR_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../../deps/glm/glm.hpp"

/*--------------------------------------------//
Classes
//--------------------------------------------*/
	class vec2;
	class vec3;
	class vec4;
	class vec2:public glm::dvec2{
		private:
		protected:
		public:
			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				vec2():glm::dvec2(){}
				vec2(int a, int b):vec2(){this->x = a; this->y = b;}
				vec2(double a, double b):vec2(){this->x = a; this->y = b;}
				vec2(const vec3 &a);
				vec2(const vec4 &a);
			/*--------------------------------------------//
			Operations
			//--------------------------------------------*/
				void normalize();
				double length() const;
				double distance(vec2 other) const;
				double dot(vec2 other) const;
			/*--------------------------------------------//
			Overridden operators
			//--------------------------------------------*/
				//Arithmetic
					//Addition
						vec2 operator+(const int &other){return vec2(this->x + other, this->y + other);}
						vec2 operator+(const float &other){return vec2(this->x + other, this->y + other);}
						vec2 operator+(const double &other){return vec2(this->x + other, this->y + other);}
						vec2 operator+(const vec2 &other){return vec2(this->x + other[0], this->y + other[1]);}
						vec2 operator+=(const int &other){this->x += other; this->y += other; return *this;}
						vec2 operator+=(const float &other){this->x += other; this->y += other; return *this;}
						vec2 operator+=(const double &other){this->x += other; this->y += other; return *this;}
						vec2 operator+=(const vec2 &other){this->x += other[0]; this->y += other[1]; return *this;}
					//Subtraction
						vec2 operator-(const int &other){return vec2(this->x - other, this->y - other);}
						vec2 operator-(const float &other){return vec2(this->x - other, this->y - other);}
						vec2 operator-(const double &other){return vec2(this->x - other, this->y - other);}
						vec2 operator-(const vec2 &other){return vec2(this->x - other[0], this->y - other[1]);}
						vec2 operator-=(const int &other){this->x -= other; this->y -= other; return *this;}
						vec2 operator-=(const float &other){this->x -= other; this->y -= other; return *this;}
						vec2 operator-=(const double &other){this->x -= other; this->y -= other; return *this;}
						vec2 operator-=(const vec2 &other){this->x -= other[0]; this->y -= other[1]; return *this;}
					//Divison
						vec2 operator/(const int &other){return vec2(this->x / other, this->y / other);}
						vec2 operator/(const float &other){return vec2(this->x / other, this->y / other);}
						vec2 operator/(const double &other){return vec2(this->x / other, this->y / other);}
						vec2 operator/(const vec2 &other){return vec2(this->x / other[0], this->y / other[1]);}
						vec2 operator/=(const int &other){this->x /= other; this->y /= other; return *this;}
						vec2 operator/=(const float &other){this->x /= other; this->y /= other; return *this;}
						vec2 operator/=(const double &other){this->x /= other; this->y /= other; return *this;}
						vec2 operator/=(const vec2 &other){this->x /= other[0]; this->y /= other[1]; return *this;}
					//Multiplication
						vec2 operator*(const int &other){return vec2(this->x * other, this->y * other);}
						vec2 operator*(const float &other){return vec2(this->x * other, this->y * other);}
						vec2 operator*(const double &other){return vec2(this->x * other, this->y * other);}
						vec2 operator*(const vec2 &other){return vec2(this->x * other[0], this->y * other[1]);}
						vec2 operator*=(const int &other){this->x *= other; this->y *= other; return *this;}
						vec2 operator*=(const float &other){this->x *= other; this->y *= other; return *this;}
						vec2 operator*=(const double &other){this->x *= other; this->y *= other; return *this;}
						vec2 operator*=(const vec2 &other){this->x *= other[0]; this->y *= other[1]; return *this;}
				//Compairison
					//less than
						bool operator<(const vec2 &other) const{return this->x < other[0] && this->y < other[1];}
						bool operator<(const int &other) const{return this->x < other && this->y < other;}
						bool operator<(const float &other) const{return this->x < other && this->y < other;}
						bool operator<(const double &other) const{return this->x < other && this->y < other;}
						bool operator<=(const vec2 &other) const{return this->x <= other[0] && this->y <= other[1];}
						bool operator<=(const int &other) const{return this->x <= other && this->y <= other;}
						bool operator<=(const float &other) const{return this->x <= other && this->y <= other;}
						bool operator<=(const double &other) const{return this->x <= other && this->y <= other;}
					//greater than
						bool operator>(const vec2 &other) const{return this->x > other[0] && this->y > other[1];}
						bool operator>(const int &other) const{return this->x > other && this->y > other;}
						bool operator>(const float &other) const{return this->x > other && this->y > other;}
						bool operator>(const double &other) const{return this->x > other && this->y > other;}
						bool operator>=(const vec2 &other) const{return this->x >= other[0] && this->y >= other[1];}
						bool operator>=(const int &other) const{return this->x >= other && this->y >= other;}
						bool operator>=(const float &other) const{return this->x >= other && this->y >= other;}
						bool operator>=(const double &other) const{return this->x >= other && this->y >= other;}
					//equals
						bool operator==(const vec2 &other) const{return this->x == other[0] && this->y == other[1];}
						bool operator==(const int &other) const{return this->x == other && this->y == other;}
						bool operator==(const float &other) const{return this->x == other && this->y == other;}
						bool operator==(const double &other) const{return this->x == other && this->y == other;}
						bool operator!=(const vec2 &other) const{return this->x != other[0] && this->y != other[1];}
						bool operator!=(const int &other) const{return this->x != other && this->y != other;}
						bool operator!=(const float &other) const{return this->x != other && this->y != other;}
						bool operator!=(const double &other) const{return this->x != other && this->y != other;}
	};
	class vec3:public glm::dvec3{
		private:
		protected:
		public:
			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				vec3():glm::dvec3(){};
				vec3(int a, int b, int c):vec3(){this->x = a; this->y = b; this->z = c;}
				vec3(double a, double b, double c):vec3(){this->x = a; this->y = b; this->z = c;}
				vec3(const vec4 &a);
			/*--------------------------------------------//
			Operations
			//--------------------------------------------*/
				void normalize();
				double length() const;
				double distance(vec3 other) const;
				double dot(vec3 other) const;
			/*--------------------------------------------//
			Overridden operators
			//--------------------------------------------*/
				//Arithmetic
					//Addition
						vec3 operator+(const int &other){return vec3(this->x + other, this->y + other, this->z + other);}
						vec3 operator+(const float &other){return vec3(this->x + other, this->y + other, this->z + other);}
						vec3 operator+(const double &other){return vec3(this->x + other, this->y + other, this->z + other);}
						vec3 operator+(const vec3 &other){return vec3(this->x + other[0], this->y + other[1], this->z + other[2]);}
						vec3 operator+=(const int &other){this->x += other; this->y += other; this->z += other; return *this;}
						vec3 operator+=(const float &other){this->x += other; this->y += other; this->z += other; return *this;}
						vec3 operator+=(const double &other){this->x += other; this->y += other; this->z += other; return *this;}
						vec3 operator+=(const vec3 &other){this->x += other[0]; this->y += other[1]; this->z += other[2]; return *this;}
					//Subtraction
						vec3 operator-(const int &other){return vec3(this->x - other, this->y - other, this->z - other);}
						vec3 operator-(const float &other){return vec3(this->x - other, this->y - other, this->z - other);}
						vec3 operator-(const double &other){return vec3(this->x - other, this->y - other, this->z - other);}
						vec3 operator-(const vec3 &other){return vec3(this->x - other[0], this->y - other[1], this->z - other[2]);}
						vec3 operator-=(const int &other){this->x -= other; this->y -= other; this->z -= other; return *this;}
						vec3 operator-=(const float &other){this->x -= other; this->y -= other; this->z -= other; return *this;}
						vec3 operator-=(const double &other){this->x -= other; this->y -= other; this->z -= other; return *this;}
						vec3 operator-=(const vec3 &other){this->x -= other[0]; this->y -= other[1]; this->z -= other[2]; return *this;}
					//Divison
						vec3 operator/(const int &other){return vec3(this->x / other, this->y / other, this->z / other);}
						vec3 operator/(const float &other){return vec3(this->x / other, this->y / other, this->z / other);}
						vec3 operator/(const double &other){return vec3(this->x / other, this->y / other, this->z / other);}
						vec3 operator/(const vec3 &other){return vec3(this->x / other[0], this->y / other[1], this->z / other[2]);}
						vec3 operator/=(const int &other){this->x /= other; this->y /= other; this->z /= other; return *this;}
						vec3 operator/=(const float &other){this->x /= other; this->y /= other; this->z /= other; return *this;}
						vec3 operator/=(const double &other){this->x /= other; this->y /= other; this->z /= other; return *this;}
						vec3 operator/=(const vec3 &other){this->x /= other[0]; this->y /= other[1]; this->z /= other[2]; return *this;}
					//Multiplication
						vec3 operator*(const int &other){return vec3(this->x * other, this->y * other, this->z * other);}
						vec3 operator*(const float &other){return vec3(this->x * other, this->y * other, this->z * other);}
						vec3 operator*(const double &other){return vec3(this->x * other, this->y * other, this->z * other);}
						vec3 operator*(const vec3 &other){return vec3(this->x * other[0], this->y * other[1], this->z * other[2]);}
						vec3 operator*=(const int &other){this->x *= other; this->y *= other; this->z *= other; return *this;}
						vec3 operator*=(const float &other){this->x *= other; this->y *= other; this->z *= other; return *this;}
						vec3 operator*=(const double &other){this->x *= other; this->y *= other; this->z *= other; return *this;}
						vec3 operator*=(const vec3 &other){this->x *= other[0]; this->y *= other[1]; this->z *= other[2]; return *this;}
				//Compairison
					//less than
						bool operator<(const vec3 &other) const{return this->x < other[0] && this->y < other[1] && this->z < other[2];}
						bool operator<(const int &other) const{return this->x < other && this->y < other && this->z < other;}
						bool operator<(const float &other) const{return this->x < other && this->y < other && this->z < other;}
						bool operator<(const double &other) const{return this->x < other && this->y < other && this->z < other;}
						bool operator<=(const vec3 &other) const{return this->x <= other[0] && this->y <= other[1] && this->z <= other[2];}
						bool operator<=(const int &other) const{return this->x <= other && this->y <= other && this->z <= other;}
						bool operator<=(const float &other) const{return this->x <= other && this->y <= other && this->z <= other;}
						bool operator<=(const double &other) const{return this->x <= other && this->y <= other && this->z <= other;}
					//greater than
						bool operator>(const vec3 &other) const{return this->x > other[0] && this->y > other[1] && this->z > other[2];}
						bool operator>(const int &other) const{return this->x > other && this->y > other && this->z > other;}
						bool operator>(const float &other) const{return this->x > other && this->y > other && this->z > other;}
						bool operator>(const double &other) const{return this->x > other && this->y > other && this->z > other;}
						bool operator>=(const vec3 &other) const{return this->x >= other[0] && this->y >= other[1] && this->z >= other[2];}
						bool operator>=(const int &other) const{return this->x >= other && this->y >= other && this->z >= other;}
						bool operator>=(const float &other) const{return this->x >= other && this->y >= other && this->z >= other;}
						bool operator>=(const double &other) const{return this->x >= other && this->y >= other && this->z >= other;}
					//equals
						bool operator==(const vec3 &other) const{return this->x == other[0] && this->y == other[1] && this->z == other[2];}
						bool operator==(const int &other) const{return this->x == other && this->y == other && this->z == other;}
						bool operator==(const float &other) const{return this->x == other && this->y == other && this->z == other;}
						bool operator==(const double &other) const{return this->x == other && this->y == other && this->z == other;}
						bool operator!=(const vec3 &other) const{return this->x != other[0] && this->y != other[1] && this->z != other[2];}
						bool operator!=(const int &other) const{return this->x != other && this->y != other && this->z != other;}
						bool operator!=(const float &other) const{return this->x != other && this->y != other && this->z != other;}
						bool operator!=(const double &other) const{return this->x != other && this->y != other && this->z != other;}
	};
	class vec4:public glm::dvec4{
		private:
		protected:
		public:
			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				vec4():glm::dvec4(){};
				vec4(int a, int b, int c, int d):vec4(){this->x = a; this->y = b; this->z = c; this->w = d;}
				vec4(double a, double b, double c, double d):vec4(){this->x = a; this->y = b; this->z = c; this->w = d;}
			/*--------------------------------------------//
			Operations
			//--------------------------------------------*/
				void normalize();
				double length() const;
				double distance(vec4 other) const;
				double dot(vec4 other) const;
			/*--------------------------------------------//
			Overridden operators
			//--------------------------------------------*/
				//Arithmetic
					//Addition
						vec4 operator+(const int &other){return vec4(this->x + other, this->y + other, this->z + other, this->w + other);}
						vec4 operator+(const float &other){return vec4(this->x + other, this->y + other, this->z + other, this->w + other);}
						vec4 operator+(const double &other){return vec4(this->x + other, this->y + other, this->z + other, this->w + other);}
						vec4 operator+(const vec3 &other){return vec4(this->x + other[0], this->y + other[1], this->z + other[2], this->w);}
						vec4 operator+(const vec4 &other){return vec4(this->x + other[0], this->y + other[1], this->z + other[2], this->w + other[3]);}
						vec4 operator+=(const int &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						vec4 operator+=(const float &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						vec4 operator+=(const double &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						vec4 operator+=(const vec3 &other){this->x += other[0]; this->y += other[1]; this->z += other[2]; return *this;}
						vec4 operator+=(const vec4 &other){this->x += other[0]; this->y += other[1]; this->z += other[2]; this->w += other[2]; return *this;}
					//Subtraction
						vec4 operator-(const int &other){return vec4(this->x - other, this->y - other, this->z - other, this->w - other);}
						vec4 operator-(const float &other){return vec4(this->x - other, this->y - other, this->z - other, this->w - other);}
						vec4 operator-(const double &other){return vec4(this->x - other, this->y - other, this->z - other, this->w - other);}
						vec4 operator-(const vec3 &other){return vec4(this->x - other[0], this->y - other[1], this->z - other[2], this->w);}
						vec4 operator-(const vec4 &other){return vec4(this->x - other[0], this->y - other[1], this->z - other[2], this->w - other[3]);}
						vec4 operator-=(const int &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						vec4 operator-=(const float &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						vec4 operator-=(const double &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						vec4 operator-=(const vec3 &other){this->x -= other[0]; this->y -= other[1]; this->z -= other[2]; return *this;}
						vec4 operator-=(const vec4 &other){this->x -= other[0]; this->y -= other[1]; this->z -= other[2]; this->w -= other[3]; return *this;}
					//Divison
						vec4 operator/(const int &other){return vec4(this->x / other, this->y / other, this->z / other, this->w / other);}
						vec4 operator/(const float &other){return vec4(this->x / other, this->y / other, this->z / other, this->w / other);}
						vec4 operator/(const double &other){return vec4(this->x / other, this->y / other, this->z / other, this->w / other);}
						vec4 operator/(const vec3 &other){return vec4(this->x / other[0], this->y / other[1], this->z / other[2], this->w);}
						vec4 operator/(const vec4 &other){return vec4(this->x / other[0], this->y / other[1], this->z / other[2], this->w / other[3]);}
						vec4 operator/=(const int &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						vec4 operator/=(const float &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						vec4 operator/=(const double &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						vec4 operator/=(const vec3 &other){this->x /= other[0]; this->y /= other[1]; this->z /= other[2]; return *this;}
						vec4 operator/=(const vec4 &other){this->x /= other[0]; this->y /= other[1]; this->z /= other[2]; this->w /= other[3]; return *this;}
					//Multiplication
						vec4 operator*(const int &other){return vec4(this->x * other, this->y * other, this->z * other, this->w * other);}
						vec4 operator*(const float &other){return vec4(this->x * other, this->y * other, this->z * other, this->w * other);}
						vec4 operator*(const double &other){return vec4(this->x * other, this->y * other, this->z * other, this->w * other);}
						vec4 operator*(const vec3 &other){return vec4(this->x * other[0], this->y * other[1], this->z * other[2], this->w);}
						vec4 operator*(const vec4 &other){return vec4(this->x * other[0], this->y * other[1], this->z * other[2], this->w * other[3]);}
						vec4 operator*=(const int &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						vec4 operator*=(const float &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						vec4 operator*=(const double &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						vec4 operator*=(const vec3 &other){this->x *= other[0]; this->y *= other[1]; this->z *= other[2]; return *this;}
						vec4 operator*=(const vec4 &other){this->x *= other[0]; this->y *= other[1]; this->z *= other[2]; this->w *= other[3]; return *this;}
				//Compairison
					//less than
						bool operator<(const vec4 &other) const{return this->x < other[0] && this->y < other[1] && this->z < other[2] && this->w < other[3];}
						bool operator<(const int &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<(const float &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<(const double &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<=(const vec4 &other) const{return this->x <= other[0] && this->y <= other[1] && this->z <= other[2] && this->w <= other[3];}
						bool operator<=(const int &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
						bool operator<=(const float &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
						bool operator<=(const double &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
					//greater than
						bool operator>(const vec4 &other) const{return this->x > other[0] && this->y > other[1] && this->z > other[2] && this->w > other[3];}
						bool operator>(const int &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>(const float &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>(const double &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>=(const vec4 &other) const{return this->x >= other[0] && this->y >= other[1] && this->z >= other[2] && this->w >= other[3];}
						bool operator>=(const int &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
						bool operator>=(const float &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
						bool operator>=(const double &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
					//equals
						bool operator==(const vec4 &other) const{return this->x == other[0] && this->y == other[1] && this->z == other[2] && this->w == other[3];}
						bool operator==(const int &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator==(const float &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator==(const double &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator!=(const vec4 &other) const{return this->x != other[0] && this->y != other[1] && this->z != other[2] && this->w != other[3];}
						bool operator!=(const int &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
						bool operator!=(const float &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
						bool operator!=(const double &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
	};
#endif