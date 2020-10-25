/*--------------------------------------------//
Angles definition
This is used to simplify definition of Angles
//--------------------------------------------*/
#ifndef ANGLES
#define ANGLES
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "angles.h"

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		Angles::Angles(){
			p = 0;
			y = 0;
			r = 0;
		};

	/*--------------------------------------------//
	Constuctor with Angles specified
	//--------------------------------------------*/
		Angles::Angles(double pi, double yi, double ri):Angles(){
			p = pi;
			y = yi;
			r = ri;
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		Angles::~Angles(){};

	/*--------------------------------------------//
	Overridden operators
	//--------------------------------------------*/
		//Arithmetic
			//addition
				Angles Angles::operator+(const Angles &other) {
					return Angles(this->p + other.p, this->y + other.y, this->r + other.r);
				};
				Angles Angles::operator+=(const Angles &other) {
					this->p += other.p;
					this->y += other.y;
					this->r += other.r;
					return (*this);
				};
			//subtraction
				Angles Angles::operator-(const Angles &other) {
					return Angles(this->p - other.p, this->y - other.y, this->r - other.r);
				};
				Angles Angles::operator-=(const Angles &other) {
					this->p -= other.p;
					this->y -= other.y;
					this->r -= other.r;
					return (*this);
				};
			//multiplication
				Angles Angles::operator*(const Angles &other) {
					return Angles(this->p * other.p, this->y * other.y, this->r * other.r);
				};
				Angles Angles::operator*=(const Angles &other) {
					this->p *= other.p;
					this->y *= other.y;
					this->r *= other.r;
					return (*this);
				};
				Angles Angles::operator*(const int &other) {
					return Angles(this->p * other, this->y * other, this->r * other);
				};
				Angles Angles::operator*=(const int &other) {
					this->p *= other;
					this->y *= other;
					this->r *= other;
					return (*this);
				};
			//division
				Angles Angles::operator/(const Angles &other) {
					return Angles(this->p / other.p, this->y / other.y, this->r / other.r);
				};
				Angles Angles::operator/=(const Angles &other) {
					this->p /= other.p;
					this->y /= other.y;
					this->r /= other.r;
					return (*this);
				};
				Angles Angles::operator/(const int &other) {
					return Angles(this->p / other, this->y / other, this->r / other);
				};
				Angles Angles::operator/=(const int &other) {
					this->p /= other;
					this->y /= other;
					this->r /= other;
					return (*this);
				};
		//compairisons
			//less than
				bool Angles::operator<(const int &other) const {
					return (this->p < other && this->y < other && this->r < other);
				};
				bool Angles::operator<=(const int &other) const {
					return (this->p <= other && this->y <= other && this->r <= other);
				};
				bool Angles::operator<(const float &other) const {
					return (this->p < other && this->y < other && this->r < other);
				};
				bool Angles::operator<=(const float &other) const {
					return (this->p <= other && this->y <= other && this->r <= other);
				};
				bool Angles::operator<(const double &other) const {
					return (this->p < other && this->y < other && this->r < other);
				};
				bool Angles::operator<=(const double &other) const {
					return (this->p <= other && this->y <= other && this->r <= other);
				};
				bool Angles::operator<(const Angles &other) const {
					return (this->p < other.p && this->y < other.y && this->r < other.r);
				};
				bool Angles::operator<=(const Angles &other) const {
					return (this->p <= other.p && this->y <= other.y && this->r <= other.r);
				};
			//greater than
				bool Angles::operator>(const int &other) const {
					return (this->p > other && this->y > other && this->r > other);
				};
				bool Angles::operator>=(const int &other) const {
					return (this->p >= other && this->y >= other && this->r >= other);
				};
				bool Angles::operator>(const float &other) const {
					return (this->p > other && this->y > other && this->r > other);
				};
				bool Angles::operator>=(const float &other) const {
					return (this->p >= other && this->y >= other && this->r >= other);
				};
				bool Angles::operator>(const double &other) const {
					return (this->p > other && this->y > other && this->r > other);
				};
				bool Angles::operator>=(const double &other) const {
					return (this->p >= other && this->y >= other && this->r >= other);
				};
				bool Angles::operator>(const Angles &other) const {
					return (this->p > other.p && this->y > other.y && this->r > other.r);
				};
				bool Angles::operator>=(const Angles &other) const {
					return (this->p >= other.p && this->y >= other.y && this->r >= other.r);
				};
			//equals
				bool Angles::operator==(const Angles &other) const {
					return (this->p == other.p && this->y == other.y && this->r == other.r);
				};
				bool Angles::operator==(const int &other) const {
					return (this->p == other && this->y == other && this->r == other);
				};
				bool Angles::operator==(const float &other) const {
					return (this->p == other && this->y == other && this->r == other);
				};
				bool Angles::operator==(const double &other) const {
					return (this->p == other && this->y == other && this->r == other);
				};
				bool Angles::operator!=(const Angles &other) const {
					return *this!=other;
				};
				bool Angles::operator!=(const int &other) const {
					return *this!=other;
				};
				bool Angles::operator!=(const float &other) const {
					return *this!=other;
				};
				bool Angles::operator!=(const double &other) const {
					return *this!=other;
				};
#endif
