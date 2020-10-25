/*--------------------------------------------//
Vector header
simplifies vector use
//--------------------------------------------*/
#ifndef VECTOR_H
#define VECTOR_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <math.h>
	#include "../globals.h"

/*--------------------------------------------//
Classes
//--------------------------------------------*/
	class Vec2;
	class Vec3;
	class Vec4;
	class Vec2{
		private:
		protected:
		public:
			/*--------------------------------------------//
			Variables
			//--------------------------------------------*/
				float x;
				float y;

			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				Vec2(void): x(0.0f), y(0.0f){}
				Vec2(double newi): x(newi), y(newi){}
				Vec2(float newi): x(newi), y(newi){}
				Vec2(int newi): x(newi), y(newi){}
				Vec2(double newX, double newY): x(newX), y(newY){}
				Vec2(float newX, float newY): x(newX), y(newY){}
				Vec2(int newX, int newY): x(newX), y(newY){}
				Vec2(const float * rhs): x(*rhs), y(*(rhs+1)){}
				Vec2(const Vec2 & rhs): x(rhs.x), y(rhs.y){}
				~Vec2(){}//destructor

			/*--------------------------------------------//
			Accessors
			//--------------------------------------------*/
				void Set(float newX, float newY){ x=newX; y=newY; }
				void SetX(float newX) {x = newX;}
				void SetY(float newY) {y = newY;}
				float GetX() const {return x;}
				float GetY() const {return y;}
				void LoadZero(void){ x=y=0.0f; }
				void LoadOne(void){	x=y=1.0f; }
				double operator[](int i) const {switch(i){case 0: return x; break; case 1: return y; break;}}

			/*--------------------------------------------//
			Operations
			//--------------------------------------------*/
				void Normalize();
				Vec2 GetNormalized() const;
				double Length() const { return (float)sqrt((x*x)+(y*y)); }
				double GetSquaredLength() const { return (x*x)+(y*y); }
				double Distance(Vec2 other) const;
				double Dot(Vec2 other) const;

				//pack to [0,1] for color
				void PackTo01();
				Vec2 GetPackedTo01() const;

				//vector algebra
				Vec2 CrossProduct(const Vec2 & rhs) const { return Vec2(rhs.y*y - x*rhs.y, y*rhs.x - rhs.x*x); }
				Vec2 Lerp(const Vec2 & v2, float factor) const { return (*this)*(1.0f-factor) + v2*factor; }
				Vec2 QuadraticInterpolate(const Vec2 & v2, const Vec2 & v3, float factor) const { return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor; }

			/*--------------------------------------------//
			Overridden operators
			//--------------------------------------------*/
				operator float* () const {return (float*) this;}
				operator const float* () const {return (const float*) this;}
				Vec2 operator=(const Vec2 &other){this->x = other.x; this->y = other.y; return *this;}
				//Arithmetic
					//Addition
						Vec2 operator+(void) const {return (*this);}
						Vec2 operator+(const int &other) const {return Vec2(this->x + other, this->y + other);}
						Vec2 operator+(const float &other) const {return Vec2(this->x + other, this->y + other);}
						Vec2 operator+(const double &other) const {return Vec2(this->x + other, this->y + other);}
						Vec2 operator+(const Vec2 &other) const {return Vec2(this->x + other[0], this->y + other[1]);}
						Vec2 operator+=(const int &other){this->x += other; this->y += other; return *this;}
						Vec2 operator+=(const float &other){this->x += other; this->y += other; return *this;}
						Vec2 operator+=(const double &other){this->x += other; this->y += other; return *this;}
						Vec2 operator+=(const Vec2 &other){this->x += other[0]; this->y += other[1]; return *this;}
					//Subtraction
						Vec2 operator-(void) const {return Vec2(-x, -y);}
						Vec2 operator-(const int &other) const {return Vec2(this->x - other, this->y - other);}
						Vec2 operator-(const float &other) const {return Vec2(this->x - other, this->y - other);}
						Vec2 operator-(const double &other) const {return Vec2(this->x - other, this->y - other);}
						Vec2 operator-(const Vec2 &other) const {return Vec2(this->x - other[0], this->y - other[1]);}
						Vec2 operator-=(const int &other){this->x -= other; this->y -= other; return *this;}
						Vec2 operator-=(const float &other){this->x -= other; this->y -= other; return *this;}
						Vec2 operator-=(const double &other){this->x -= other; this->y -= other; return *this;}
						Vec2 operator-=(const Vec2 &other){this->x -= other[0]; this->y -= other[1]; return *this;}
					//Divison
						Vec2 operator/(const int &other) const {return Vec2(this->x / other, this->y / other);}
						Vec2 operator/(const float &other) const {return Vec2(this->x / other, this->y / other);}
						Vec2 operator/(const double &other) const {return Vec2(this->x / other, this->y / other);}
						Vec2 operator/(const Vec2 &other) const {return Vec2(this->x / other[0], this->y / other[1]);}
						Vec2 operator/=(const int &other){this->x /= other; this->y /= other; return *this;}
						Vec2 operator/=(const float &other){this->x /= other; this->y /= other; return *this;}
						Vec2 operator/=(const double &other){this->x /= other; this->y /= other; return *this;}
						Vec2 operator/=(const Vec2 &other){this->x /= other[0]; this->y /= other[1]; return *this;}
					//Multiplication
						friend Vec2 operator*(float scaleFactor, const Vec2 & rhs);
						Vec2 operator*(const int &other) const {return Vec2(this->x * other, this->y * other);}
						Vec2 operator*(const float &other) const {return Vec2(this->x * other, this->y * other);}
						Vec2 operator*(const double &other) const {return Vec2(this->x * other, this->y * other);}
						Vec2 operator*(const Vec2 &other) const {return Vec2(this->x * other[0], this->y * other[1]);}
						Vec2 operator*=(const int &other){this->x *= other; this->y *= other; return *this;}
						Vec2 operator*=(const float &other){this->x *= other; this->y *= other; return *this;}
						Vec2 operator*=(const double &other){this->x *= other; this->y *= other; return *this;}
						Vec2 operator*=(const Vec2 &other){this->x *= other[0]; this->y *= other[1]; return *this;}
				//Compairison
					//less than
						bool operator<(const Vec2 &other) const{return this->x < other[0] && this->y < other[1];}
						bool operator<(const int &other) const{return this->x < other && this->y < other;}
						bool operator<(const float &other) const{return this->x < other && this->y < other;}
						bool operator<(const double &other) const{return this->x < other && this->y < other;}
						bool operator<=(const Vec2 &other) const{return this->x <= other[0] && this->y <= other[1];}
						bool operator<=(const int &other) const{return this->x <= other && this->y <= other;}
						bool operator<=(const float &other) const{return this->x <= other && this->y <= other;}
						bool operator<=(const double &other) const{return this->x <= other && this->y <= other;}
					//greater than
						bool operator>(const Vec2 &other) const{return this->x > other[0] && this->y > other[1];}
						bool operator>(const int &other) const{return this->x > other && this->y > other;}
						bool operator>(const float &other) const{return this->x > other && this->y > other;}
						bool operator>(const double &other) const{return this->x > other && this->y > other;}
						bool operator>=(const Vec2 &other) const{return this->x >= other[0] && this->y >= other[1];}
						bool operator>=(const int &other) const{return this->x >= other && this->y >= other;}
						bool operator>=(const float &other) const{return this->x >= other && this->y >= other;}
						bool operator>=(const double &other) const{return this->x >= other && this->y >= other;}
					//equals
						bool operator==(const Vec2 &other) const{return this->x == other[0] && this->y == other[1];}
						bool operator==(const int &other) const{return this->x == other && this->y == other;}
						bool operator==(const float &other) const{return this->x == other && this->y == other;}
						bool operator==(const double &other) const{return this->x == other && this->y == other;}
						bool operator!=(const Vec2 &other) const{return this->x != other[0] && this->y != other[1];}
						bool operator!=(const int &other) const{return this->x != other && this->y != other;}
						bool operator!=(const float &other) const{return this->x != other && this->y != other;}
						bool operator!=(const double &other) const{return this->x != other && this->y != other;}
	};
	class Vec3{
		private:
		protected:
		public:
			/*--------------------------------------------//
			Variables
			//--------------------------------------------*/
				float x;
				float y;
				float z;

			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				Vec3(void): x(0.0f), y(0.0f), z(0.0f){}
				Vec3(double newi): x(newi), y(newi), z(newi){}
				Vec3(float newi): x(newi), y(newi), z(newi){}
				Vec3(int newi): x(newi), y(newi), z(newi){}
				Vec3(double newX, double newY, double newZ): x(newX), y(newY), z(newZ){}
				Vec3(float newX, float newY, float newZ): x(newX), y(newY), z(newZ){}
				Vec3(int newX, int newY, int newZ): x(newX), y(newY), z(newZ){}
				Vec3(const float * rhs): x(*rhs), y(*(rhs+1)), z(*(rhs+2)){}
				Vec3(const Vec4 & rhs);
				Vec3(const Vec3 & rhs): x(rhs.x), y(rhs.y), z(rhs.z){}
				Vec3(const Vec2 & rhs):	x(rhs.x), y(rhs.y), z(0.0f){}
				~Vec3(){}//destructor

			/*--------------------------------------------//
			Accessors
			//--------------------------------------------*/
				void Set(float newX, float newY, float newZ){ x=newX; y=newY; z=newZ; }
				void SetX(float newX) {x = newX;}
				void SetY(float newY) {y = newY;}
				void SetZ(float newZ) {z = newZ;}
				float GetX() const {return x;}
				float GetY() const {return y;}
				float GetZ() const {return z;}
				void LoadZero(void){ x=y=z=0.0f; }
				void LoadOne(void){	x=y=z=1.0f; }
				double operator[](int i) const {switch(i){case 0: return x; break; case 1: return y; break; case 2: return z; break;}}

			/*--------------------------------------------//
			Operations
			//--------------------------------------------*/
				void Normalize();
				Vec3 GetNormalized() const;
				double Length() const { return (float)sqrt((x*x)+(y*y)+(z*z)); }
				double GetSquaredLength() const { return (x*x)+(y*y)+(z*z); }
				double Distance(Vec3 other) const;
				double Dot(Vec3 other) const;

				//pack to [0,1] for color
				void PackTo01();
				Vec3 GetPackedTo01() const;

				//vector algebra
				Vec3 CrossProduct(const Vec3 & rhs) const { return Vec3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x); }
				Vec3 Cross(const Vec3 & rhs) const { return this->CrossProduct(rhs); }
				Vec3 Lerp(const Vec3 & v2, float factor) const { return (*this)*(1.0f-factor) + v2*factor; }
				Vec3 QuadraticInterpolate(const Vec3 & v2, const Vec3 & v3, float factor) const { return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor; }

				//rotations
				void RotateX(double angle);
				Vec3 GetRotatedX(double angle) const;
				void RotateY(double angle);
				Vec3 GetRotatedY(double angle) const;
				void RotateZ(double angle);
				Vec3 GetRotatedZ(double angle) const;
				void RotateAxis(double angle, const Vec3 & axis);
				Vec3 GetRotatedAxis(double angle, const Vec3 & axis) const;

			/*--------------------------------------------//
			Overridden operators
			//--------------------------------------------*/
				operator float* () const {return (float*) this;}
				operator const float* () const {return (const float*) this;}
				Vec3 operator=(const Vec3 &other){this->x = other.x; this->y = other.y; this->z = other.z; return *this;}
				//Arithmetic
					//Addition
						friend Vec3 operator+(int scaleFactor, const Vec3 & rhs){return rhs + scaleFactor;}
						friend Vec3 operator+(double scaleFactor, const Vec3 & rhs){return rhs + scaleFactor;}
						friend Vec3 operator+(float scaleFactor, const Vec3 & rhs){return rhs + scaleFactor;}
						Vec3 operator+(void) const {return (*this);}
						Vec3 operator+(const int &other) const {return Vec3(this->x + other, this->y + other, this->z + other);}
						Vec3 operator+(const float &other) const {return Vec3(this->x + other, this->y + other, this->z + other);}
						Vec3 operator+(const double &other) const {return Vec3(this->x + other, this->y + other, this->z + other);}
						Vec3 operator+(const Vec3 &other) const {return Vec3(this->x + other[0], this->y + other[1], this->z + other[2]);}
						Vec3 operator+=(const int &other){this->x += other; this->y += other; this->z += other; return *this;}
						Vec3 operator+=(const float &other){this->x += other; this->y += other; this->z += other; return *this;}
						Vec3 operator+=(const double &other){this->x += other; this->y += other; this->z += other; return *this;}
						Vec3 operator+=(const Vec3 &other){this->x += other[0]; this->y += other[1]; this->z += other[2]; return *this;}
					//Subtraction
						friend Vec3 operator-(int scaleFactor, const Vec3 & rhs){return rhs - scaleFactor;}
						friend Vec3 operator-(double scaleFactor, const Vec3 & rhs){return rhs - scaleFactor;}
						friend Vec3 operator-(float scaleFactor, const Vec3 & rhs){return rhs - scaleFactor;}
						Vec3 operator-(void) const {return Vec3(-x, -y, -z);}
						Vec3 operator-(const int &other) const {return Vec3(this->x - other, this->y - other, this->z - other);}
						Vec3 operator-(const float &other) const {return Vec3(this->x - other, this->y - other, this->z - other);}
						Vec3 operator-(const double &other) const {return Vec3(this->x - other, this->y - other, this->z - other);}
						Vec3 operator-(const Vec3 &other) const {return Vec3(this->x - other[0], this->y - other[1], this->z - other[2]);}
						Vec3 operator-=(const int &other){this->x -= other; this->y -= other; this->z -= other; return *this;}
						Vec3 operator-=(const float &other){this->x -= other; this->y -= other; this->z -= other; return *this;}
						Vec3 operator-=(const double &other){this->x -= other; this->y -= other; this->z -= other; return *this;}
						Vec3 operator-=(const Vec3 &other){this->x -= other[0]; this->y -= other[1]; this->z -= other[2]; return *this;}
					//Divison
						friend Vec3 operator/(int scaleFactor, const Vec3 & rhs){return rhs / scaleFactor;}
						friend Vec3 operator/(double scaleFactor, const Vec3 & rhs){return rhs / scaleFactor;}
						friend Vec3 operator/(float scaleFactor, const Vec3 & rhs){return rhs / scaleFactor;}
						Vec3 operator/(const int &other) const {return Vec3(this->x / other, this->y / other, this->z / other);}
						Vec3 operator/(const float &other) const {return Vec3(this->x / other, this->y / other, this->z / other);}
						Vec3 operator/(const double &other) const {return Vec3(this->x / other, this->y / other, this->z / other);}
						Vec3 operator/(const Vec3 &other) const {return Vec3(this->x / other[0], this->y / other[1], this->z / other[2]);}
						Vec3 operator/=(const int &other){this->x /= other; this->y /= other; this->z /= other; return *this;}
						Vec3 operator/=(const float &other){this->x /= other; this->y /= other; this->z /= other; return *this;}
						Vec3 operator/=(const double &other){this->x /= other; this->y /= other; this->z /= other; return *this;}
						Vec3 operator/=(const Vec3 &other){this->x /= other[0]; this->y /= other[1]; this->z /= other[2]; return *this;}
					//Multiplication
						friend Vec3 operator*(int scaleFactor, const Vec3 & rhs){return rhs * scaleFactor;}
						friend Vec3 operator*(double scaleFactor, const Vec3 & rhs){return rhs * scaleFactor;}
						friend Vec3 operator*(float scaleFactor, const Vec3 & rhs){return rhs * scaleFactor;}
						Vec3 operator*(const int &other) const {return Vec3(this->x * other, this->y * other, this->z * other);}
						Vec3 operator*(const float &other) const {return Vec3(this->x * other, this->y * other, this->z * other);}
						Vec3 operator*(const double &other) const {return Vec3(this->x * other, this->y * other, this->z * other);}
						Vec3 operator*(const Vec3 &other) const {return Vec3(this->x * other[0], this->y * other[1], this->z * other[2]);}
						Vec3 operator*=(const int &other){this->x *= other; this->y *= other; this->z *= other; return *this;}
						Vec3 operator*=(const float &other){this->x *= other; this->y *= other; this->z *= other; return *this;}
						Vec3 operator*=(const double &other){this->x *= other; this->y *= other; this->z *= other; return *this;}
						Vec3 operator*=(const Vec3 &other){this->x *= other[0]; this->y *= other[1]; this->z *= other[2]; return *this;}
				//Compairison
					//less than
						bool operator<(const Vec3 &other) const{return this->x < other[0] && this->y < other[1] && this->z < other[2];}
						bool operator<(const int &other) const{return this->x < other && this->y < other && this->z < other;}
						bool operator<(const float &other) const{return this->x < other && this->y < other && this->z < other;}
						bool operator<(const double &other) const{return this->x < other && this->y < other && this->z < other;}
						bool operator<=(const Vec3 &other) const{return this->x <= other[0] && this->y <= other[1] && this->z <= other[2];}
						bool operator<=(const int &other) const{return this->x <= other && this->y <= other && this->z <= other;}
						bool operator<=(const float &other) const{return this->x <= other && this->y <= other && this->z <= other;}
						bool operator<=(const double &other) const{return this->x <= other && this->y <= other && this->z <= other;}
					//greater than
						bool operator>(const Vec3 &other) const{return this->x > other[0] && this->y > other[1] && this->z > other[2];}
						bool operator>(const int &other) const{return this->x > other && this->y > other && this->z > other;}
						bool operator>(const float &other) const{return this->x > other && this->y > other && this->z > other;}
						bool operator>(const double &other) const{return this->x > other && this->y > other && this->z > other;}
						bool operator>=(const Vec3 &other) const{return this->x >= other[0] && this->y >= other[1] && this->z >= other[2];}
						bool operator>=(const int &other) const{return this->x >= other && this->y >= other && this->z >= other;}
						bool operator>=(const float &other) const{return this->x >= other && this->y >= other && this->z >= other;}
						bool operator>=(const double &other) const{return this->x >= other && this->y >= other && this->z >= other;}
					//equals
						bool operator==(const Vec3 &other) const{return this->x == other[0] && this->y == other[1] && this->z == other[2];}
						bool operator==(const int &other) const{return this->x == other && this->y == other && this->z == other;}
						bool operator==(const float &other) const{return this->x == other && this->y == other && this->z == other;}
						bool operator==(const double &other) const{return this->x == other && this->y == other && this->z == other;}
						bool operator!=(const Vec3 &other) const{return this->x != other[0] && this->y != other[1] && this->z != other[2];}
						bool operator!=(const int &other) const{return this->x != other && this->y != other && this->z != other;}
						bool operator!=(const float &other) const{return this->x != other && this->y != other && this->z != other;}
						bool operator!=(const double &other) const{return this->x != other && this->y != other && this->z != other;}
	};
	class Vec4{
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
			Constructor
			//--------------------------------------------*/
				Vec4(void): x(0.0f), y(0.0f), z(0.0f), w(0.0f){}
				Vec4(double newi): x(newi), y(newi), z(newi), w(newi){}
				Vec4(float newi): x(newi), y(newi), z(newi), w(newi){}
				Vec4(int newi): x(newi), y(newi), z(newi), w(newi){}
				Vec4(double newX, double newY, double newZ, double newW): x(newX), y(newY), z(newZ), w(newW){}
				Vec4(float newX, float newY, float newZ, float newW): x(newX), y(newY), z(newZ), w(newW){}
				Vec4(int newX, int newY, int newZ, int newW): x(newX), y(newY), z(newZ), w(newW){}
				Vec4(const float * rhs): x(*rhs), y(*(rhs+1)), z(*(rhs+2)), w(*(rhs+3)){}
				Vec4(const Vec4 & rhs): x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){}
				Vec4(const Vec3 & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f){}
				Vec4(const Vec3 & rhs, int newW): x(rhs.x), y(rhs.y), z(rhs.z), w(newW){}
				Vec4(const Vec3 & rhs, float newW): x(rhs.x), y(rhs.y), z(rhs.z), w(newW){}
				Vec4(const Vec3 & rhs, double newW): x(rhs.x), y(rhs.y), z(rhs.z), w(newW){}
				~Vec4(){}//destructor

			/*--------------------------------------------//
			Accessors
			//--------------------------------------------*/
				void Set(float newX, float newY, float newZ, float newW){ x=newX; y=newY; z=newZ; w=newW; }
				void SetX(float newX) {x = newX;}
				void SetY(float newY) {y = newY;}
				void SetZ(float newZ) {z = newZ;}
				void SetW(float newW) {w = newW;}
				float GetX() const {return x;}
				float GetY() const {return y;}
				float GetZ() const {return z;}
				float GetW() const {return w;}
				void LoadZero(void){ x=y=z=w=0.0f; }
				void LoadOne(void){	x=y=z=w=1.0f; }
				double operator[](int i) const {switch(i){case 0: return x; break; case 1: return y; break; case 2: return z; break; case 3: return w; break;}}

			/*--------------------------------------------//
			Operations
			//--------------------------------------------*/
				void Normalize();
				Vec4 GetNormalized() const;
				double Length() const { return (float)sqrt((x*x)+(y*y)+(z*z)+(w*w)); }
				double GetSquaredLength() const { return (x*x)+(y*y)+(z*z)+(w*w); }
				double Distance(Vec4 other) const;
				double Dot(Vec4 other) const;

				//pack to [0,1] for color
				void PackTo01();
				Vec4 GetPackedTo01() const;

				//vector algebra
				Vec4 CrossProduct(const Vec4 & rhs) const { return Vec4(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x, 1.0); }
				Vec4 CrossProduct(const Vec3 & rhs) const { return Vec4(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x, 1.0); }
				Vec4 Cross(const Vec4 & rhs) const { return this->CrossProduct(rhs); }
				Vec4 Cross(const Vec3 & rhs) const { return this->CrossProduct(rhs); }
				Vec4 Lerp(const Vec4 & v2, float factor) const { return (*this)*(1.0f-factor)+v2*factor; }
				Vec4 QuadraticInterpolate(const Vec4 & v2, const Vec4 & v3, float factor) const { return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor; }

				//rotations
				void RotateX(double angle);
				Vec4 GetRotatedX(double angle) const;
				void RotateY(double angle);
				Vec4 GetRotatedY(double angle) const;
				void RotateZ(double angle);
				Vec4 GetRotatedZ(double angle) const;
				void RotateAxis(double angle, const Vec3 & axis);
				Vec4 GetRotatedAxis(double angle, const Vec3 & axis) const;

			/*--------------------------------------------//
			Overridden operators
			//--------------------------------------------*/
				operator Vec3();
				operator float* () const {return (float*) this;}
				operator const float* () const {return (const float*) this;}
				Vec4 operator=(const Vec4 &other){this->x = other.x; this->y = other.y; this->z = other.z; this->w = other.w; return *this;}
				//Arithmetic
					//Addition
						Vec4 operator+(void) const {return (*this);}
						Vec4 operator+(const int &other) const {return Vec4(this->x + other, this->y + other, this->z + other, this->w + other);}
						Vec4 operator+(const float &other) const {return Vec4(this->x + other, this->y + other, this->z + other, this->w + other);}
						Vec4 operator+(const double &other) const {return Vec4(this->x + other, this->y + other, this->z + other, this->w + other);}
						Vec4 operator+(const Vec3 &other) const {return Vec4(this->x + other[0], this->y + other[1], this->z + other[2], this->w);}
						Vec4 operator+(const Vec4 &other) const {return Vec4(this->x + other[0], this->y + other[1], this->z + other[2], this->w + other[3]);}
						Vec4 operator+=(const int &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						Vec4 operator+=(const float &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						Vec4 operator+=(const double &other){this->x += other; this->y += other; this->z += other; this->w += other; return *this;}
						Vec4 operator+=(const Vec3 &other){this->x += other[0]; this->y += other[1]; this->z += other[2]; return *this;}
						Vec4 operator+=(const Vec4 &other){this->x += other[0]; this->y += other[1]; this->z += other[2]; this->w += other[2]; return *this;}
					//Subtraction
						Vec4 operator-(void) const {return Vec4(-x, -y, -z, -w);}
						Vec4 operator-(const int &other) const {return Vec4(this->x - other, this->y - other, this->z - other, this->w - other);}
						Vec4 operator-(const float &other) const {return Vec4(this->x - other, this->y - other, this->z - other, this->w - other);}
						Vec4 operator-(const double &other) const {return Vec4(this->x - other, this->y - other, this->z - other, this->w - other);}
						Vec4 operator-(const Vec3 &other) const {return Vec4(this->x - other[0], this->y - other[1], this->z - other[2], this->w);}
						Vec4 operator-(const Vec4 &other) const {return Vec4(this->x - other[0], this->y - other[1], this->z - other[2], this->w - other[3]);}
						Vec4 operator-=(const int &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						Vec4 operator-=(const float &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						Vec4 operator-=(const double &other){this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this;}
						Vec4 operator-=(const Vec3 &other){this->x -= other[0]; this->y -= other[1]; this->z -= other[2]; return *this;}
						Vec4 operator-=(const Vec4 &other){this->x -= other[0]; this->y -= other[1]; this->z -= other[2]; this->w -= other[3]; return *this;}
					//Divison
						Vec4 operator/(const int &other) const {return Vec4(this->x / other, this->y / other, this->z / other, this->w / other);}
						Vec4 operator/(const float &other) const {return Vec4(this->x / other, this->y / other, this->z / other, this->w / other);}
						Vec4 operator/(const double &other) const {return Vec4(this->x / other, this->y / other, this->z / other, this->w / other);}
						Vec4 operator/(const Vec3 &other) const {return Vec4(this->x / other[0], this->y / other[1], this->z / other[2], this->w);}
						Vec4 operator/(const Vec4 &other) const {return Vec4(this->x / other[0], this->y / other[1], this->z / other[2], this->w / other[3]);}
						Vec4 operator/=(const int &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						Vec4 operator/=(const float &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						Vec4 operator/=(const double &other){this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this;}
						Vec4 operator/=(const Vec3 &other){this->x /= other[0]; this->y /= other[1]; this->z /= other[2]; return *this;}
						Vec4 operator/=(const Vec4 &other){this->x /= other[0]; this->y /= other[1]; this->z /= other[2]; this->w /= other[3]; return *this;}
					//Multiplication
						friend Vec4 operator*(float scaleFactor, const Vec4 & rhs);
						Vec4 operator*(const int &other) const {return Vec4(this->x * other, this->y * other, this->z * other, this->w * other);}
						Vec4 operator*(const float &other) const {return Vec4(this->x * other, this->y * other, this->z * other, this->w * other);}
						Vec4 operator*(const double &other) const {return Vec4(this->x * other, this->y * other, this->z * other, this->w * other);}
						Vec4 operator*(const Vec3 &other) const {return Vec4(this->x * other[0], this->y * other[1], this->z * other[2], this->w);}
						Vec4 operator*(const Vec4 &other) const {return Vec4(this->x * other[0], this->y * other[1], this->z * other[2], this->w * other[3]);}
						Vec4 operator*=(const int &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						Vec4 operator*=(const float &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						Vec4 operator*=(const double &other){this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this;}
						Vec4 operator*=(const Vec3 &other){this->x *= other[0]; this->y *= other[1]; this->z *= other[2]; return *this;}
						Vec4 operator*=(const Vec4 &other){this->x *= other[0]; this->y *= other[1]; this->z *= other[2]; this->w *= other[3]; return *this;}
				//Compairison
					//less than
						bool operator<(const Vec4 &other) const{return this->x < other[0] && this->y < other[1] && this->z < other[2] && this->w < other[3];}
						bool operator<(const int &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<(const float &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<(const double &other) const{return this->x < other && this->y < other && this->z < other && this->w < other;}
						bool operator<=(const Vec4 &other) const{return this->x <= other[0] && this->y <= other[1] && this->z <= other[2] && this->w <= other[3];}
						bool operator<=(const int &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
						bool operator<=(const float &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
						bool operator<=(const double &other) const{return this->x <= other && this->y <= other && this->z <= other && this->w <= other;}
					//greater than
						bool operator>(const Vec4 &other) const{return this->x > other[0] && this->y > other[1] && this->z > other[2] && this->w > other[3];}
						bool operator>(const int &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>(const float &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>(const double &other) const{return this->x > other && this->y > other && this->z > other && this->w > other;}
						bool operator>=(const Vec4 &other) const{return this->x >= other[0] && this->y >= other[1] && this->z >= other[2] && this->w >= other[3];}
						bool operator>=(const int &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
						bool operator>=(const float &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
						bool operator>=(const double &other) const{return this->x >= other && this->y >= other && this->z >= other && this->w >= other;}
					//equals
						bool operator==(const Vec4 &other) const{return this->x == other[0] && this->y == other[1] && this->z == other[2] && this->w == other[3];}
						bool operator==(const int &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator==(const float &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator==(const double &other) const{return this->x == other && this->y == other && this->z == other && this->w == other;}
						bool operator!=(const Vec4 &other) const{return this->x != other[0] && this->y != other[1] && this->z != other[2] && this->w != other[3];}
						bool operator!=(const int &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
						bool operator!=(const float &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
						bool operator!=(const double &other) const{return this->x != other && this->y != other && this->z != other && this->w != other;}
	};
#endif
