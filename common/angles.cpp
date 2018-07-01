/*--------------------------------------------//
Angles definition
This is used to simplify definition of angles
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
		angles::angles(){
			p = 0;
			y = 0;
			r = 0;
		};

	/*--------------------------------------------//
	Constuctor with angles specified
	//--------------------------------------------*/
		angles::angles(double pi, double yi, double ri):angles(){
			p = pi;
			y = yi;
			r = ri;
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		angles::~angles(){};

	/*--------------------------------------------//
	Overridden operators
	//--------------------------------------------*/
		//Arithmetic
			//addition
				angles angles::operator+(const angles &other) {
					return angles(this->p + other.p, this->y + other.y, this->r + other.r);
				};
				angles angles::operator+=(const angles &other) {
					this->p += other.p;
					this->y += other.y;
					this->r += other.r;
					return (*this);
				};
			//subtraction
				angles angles::operator-(const angles &other) {
					return angles(this->p - other.p, this->y - other.y, this->r - other.r);
				};
				angles angles::operator-=(const angles &other) {
					this->p -= other.p;
					this->y -= other.y;
					this->r -= other.r;
					return (*this);
				};
			//multiplication
				angles angles::operator*(const angles &other) {
					return angles(this->p * other.p, this->y * other.y, this->r * other.r);
				};
				angles angles::operator*=(const angles &other) {
					this->p *= other.p;
					this->y *= other.y;
					this->r *= other.r;
					return (*this);
				};
				angles angles::operator*(const int &other) {
					return angles(this->p * other, this->y * other, this->r * other);
				};
				angles angles::operator*=(const int &other) {
					this->p *= other;
					this->y *= other;
					this->r *= other;
					return (*this);
				};
			//division
				angles angles::operator/(const angles &other) {
					return angles(this->p / other.p, this->y / other.y, this->r / other.r);
				};
				angles angles::operator/=(const angles &other) {
					this->p /= other.p;
					this->y /= other.y;
					this->r /= other.r;
					return (*this);
				};
				angles angles::operator/(const int &other) {
					return angles(this->p / other, this->y / other, this->r / other);
				};
				angles angles::operator/=(const int &other) {
					this->p /= other;
					this->y /= other;
					this->r /= other;
					return (*this);
				};
		//compairisons
			//less than
				bool angles::operator<(const int &other) const {
					return (this->p < other && this->y < other && this->r < other);
				};
				bool angles::operator<=(const int &other) const {
					return (this->p <= other && this->y <= other && this->r <= other);
				};
				bool angles::operator<(const float &other) const {
					return (this->p < other && this->y < other && this->r < other);
				};
				bool angles::operator<=(const float &other) const {
					return (this->p <= other && this->y <= other && this->r <= other);
				};
				bool angles::operator<(const double &other) const {
					return (this->p < other && this->y < other && this->r < other);
				};
				bool angles::operator<=(const double &other) const {
					return (this->p <= other && this->y <= other && this->r <= other);
				};
				bool angles::operator<(const angles &other) const {
					return (this->p < other.p && this->y < other.y && this->r < other.r);
				};
				bool angles::operator<=(const angles &other) const {
					return (this->p <= other.p && this->y <= other.y && this->r <= other.r);
				};
			//greater than
				bool angles::operator>(const int &other) const {
					return (this->p > other && this->y > other && this->r > other);
				};
				bool angles::operator>=(const int &other) const {
					return (this->p >= other && this->y >= other && this->r >= other);
				};
				bool angles::operator>(const float &other) const {
					return (this->p > other && this->y > other && this->r > other);
				};
				bool angles::operator>=(const float &other) const {
					return (this->p >= other && this->y >= other && this->r >= other);
				};
				bool angles::operator>(const double &other) const {
					return (this->p > other && this->y > other && this->r > other);
				};
				bool angles::operator>=(const double &other) const {
					return (this->p >= other && this->y >= other && this->r >= other);
				};
				bool angles::operator>(const angles &other) const {
					return (this->p > other.p && this->y > other.y && this->r > other.r);
				};
				bool angles::operator>=(const angles &other) const {
					return (this->p >= other.p && this->y >= other.y && this->r >= other.r);
				};
			//equals
				bool angles::operator==(const angles &other) const {
					return (this->p == other.p && this->y == other.y && this->r == other.r);
				};
				bool angles::operator==(const int &other) const {
					return (this->p == other && this->y == other && this->r == other);
				};
				bool angles::operator==(const float &other) const {
					return (this->p == other && this->y == other && this->r == other);
				};
				bool angles::operator==(const double &other) const {
					return (this->p == other && this->y == other && this->r == other);
				};
				bool angles::operator!=(const angles &other) const {
					return *this!=other;
				};
				bool angles::operator!=(const int &other) const {
					return *this!=other;
				};
				bool angles::operator!=(const float &other) const {
					return *this!=other;
				};
				bool angles::operator!=(const double &other) const {
					return *this!=other;
				};
#endif