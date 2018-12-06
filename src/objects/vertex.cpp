/*--------------------------------------------//
Vertex definition
This is used to simplify definition of points
on a triangular surface of a mesh
//--------------------------------------------*/
#ifndef VERTEX
#define VERTEX
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "vertex.h"

	/*--------------------------------------------//
	Constructors
	//--------------------------------------------*/
		vertex::vertex():vec3(){
		}
		vertex::vertex(double a, double b, double c):vec3(a,b,c){
		}

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		vertex::~vertex(){};


	/*--------------------------------------------//
	Overridden operators
	//--------------------------------------------*/
		//Arithmetic
			//Addition
				vertex vertex::operator+(const int &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					return (*this);
				};
				vertex vertex::operator+(const float &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					return (*this);
				};
				vertex vertex::operator+(const double &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					return (*this);
				};
				vertex vertex::operator+(const vec3 &other) {
					this->x(x()+other.x());
					this->y(y()+other.y());
					this->z(z()+other.z());
					return (*this);
				};
			//Subtraction
				vertex vertex::operator-(const int &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					return (*this);
				};
				vertex vertex::operator-(const float &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					return (*this);
				};
				vertex vertex::operator-(const double &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					return (*this);
				};
				vertex vertex::operator-(const vec3 &other) {
					this->x(x()-other.x());
					this->y(y()-other.y());
					this->z(z()-other.z());
					return (*this);
				};
			//Divison
				vertex vertex::operator/(const int &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					return (*this);
				};
				vertex vertex::operator/(const float &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					return (*this);
				};
				vertex vertex::operator/(const double &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					return (*this);
				};
				vertex vertex::operator/(const vec3 &other) {
					this->x(x()/other.x());
					this->y(y()/other.y());
					this->z(z()/other.z());
					return (*this);
				};
			//Multiplication
				vertex vertex::operator*(const int &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					return (*this);
				};
				vertex vertex::operator*(const float &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					return (*this);
				};
				vertex vertex::operator*(const double &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					return (*this);
				};
				vertex vertex::operator*(const vec3 &other) {
					this->x(x()*other.x());
					this->y(y()*other.y());
					this->z(z()*other.z());
					return (*this);
				};
		//Compairison
			//less than
				bool vertex::operator<(const vec3 &other) const {
					return (this->length() < other.length());
				};
				bool vertex::operator<(const int &other) const {
					return (this->x() < other && this->y() < other && this->z() < other);
				};
				bool vertex::operator<(const float &other) const {
					return (this->x() < other && this->y() < other && this->z() < other);
				};
				bool vertex::operator<(const double &other) const {
					return (this->x() < other && this->y() < other && this->z() < other);
				};
				bool vertex::operator<=(const vec3 &other) const {
					return (this->length() <= other.length());
				};
				bool vertex::operator<=(const int &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other);
				};
				bool vertex::operator<=(const float &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other);
				};
				bool vertex::operator<=(const double &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other);
				};
			//greater than
				bool vertex::operator>(const vec3 &other) const {
					return (this->length() > other.length());
				};
				bool vertex::operator>(const int &other) const {
					return (this->x() > other && this->y() > other && this->z() > other);
				};
				bool vertex::operator>(const float &other) const {
					return (this->x() > other && this->y() > other && this->z() > other);
				};
				bool vertex::operator>(const double &other) const {
					return (this->x() > other && this->y() > other && this->z() > other);
				};
				bool vertex::operator>=(const vec3 &other) const {
					return (this->length() >= other.length());
				};
				bool vertex::operator>=(const int &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other);
				};
				bool vertex::operator>=(const float &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other);
				};
				bool vertex::operator>=(const double &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other);
				};
			//equals
				bool vertex::operator==(const vec3 &other) const {
					return (this->x() == other.x() && this->y() == other.y() && this->z() == other.z());
				};
				bool vertex::operator==(const int &other) const {
					return (this->x() == other && this->y() == other && this->z() == other);
				};
				bool vertex::operator==(const float &other) const {
					return (this->x() == other && this->y() == other && this->z() == other);
				};
				bool vertex::operator==(const double &other) const {
					return (this->x() == other && this->y() == other && this->z() == other);
				};
				bool vertex::operator!=(const vec3 &other) const {
					return *this!=other;
				};
				bool vertex::operator!=(const int &other) const {
					return *this!=other;
				};
				bool vertex::operator!=(const float &other) const {
					return *this!=other;
				};
				bool vertex::operator!=(const double &other) const {
					return *this!=other;
				};
		//Assignment
			///=
				vertex vertex::operator/=(const vertex &other){
					this->x(x() / other.x());
					this->y(y() / other.y());
					this->z(z() / other.z());
					return *this;
				}
				vertex vertex::operator/=(const vec3 &other){
					this->x(x() / other.x());
					this->y(y() / other.y());
					this->z(z() / other.z());
					return *this;
				}
			//*=
				vertex vertex::operator*=(const vertex &other){
					this->x(x() * other.x());
					this->y(y() * other.y());
					this->z(z() * other.z());
					return *this;
				}
				vertex vertex::operator*=(const vec3 &other){
					this->x(x() * other.x());
					this->y(y() * other.y());
					this->z(z() * other.z());
					return *this;
				}
			//-=
				vertex vertex::operator-=(const vertex &other){
					this->x(x() - other.x());
					this->y(y() - other.y());
					this->z(z() - other.z());
					return *this;
				}
				vertex vertex::operator-=(const vec3 &other){
					this->x(x() - other.x());
					this->y(y() - other.y());
					this->z(z() - other.z());
					return *this;
				}
			//+=
				vertex vertex::operator+=(const vertex &other){
					this->x(x() + other.x());
					this->y(y() + other.y());
					this->z(z() + other.z());
					return *this;
				}
				vertex vertex::operator+=(const vec3 &other){
					this->x(x() + other.x());
					this->y(y() + other.y());
					this->z(z() + other.z());
					return *this;
				}
			//==
				vertex vertex::operator=(const vertex &other){
					this->x(other.x());
					this->y(other.y());
					this->z(other.z());
					return *this;
				}
				vertex vertex::operator=(const vec3 &other){
					this->x(other.x());
					this->y(other.y());
					this->z(other.z());
					return *this;
				}
#endif