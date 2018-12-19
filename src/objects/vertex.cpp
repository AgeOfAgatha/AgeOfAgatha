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
			normal = new vec3(1.0, 1.0, 1.0);
			color = new vec3(1.0, 1.0, 1.0);
			textcoord = new vec2(1.0, 1.0);
			textblend = new double(0.5);
		}
		vertex::vertex(double a, double b, double c):vec3(a,b,c){
			normal = new vec3(1.0, 1.0, 1.0);
			color = new vec3(1.0, 1.0, 1.0);
			textcoord = new vec2(1.0, 1.0);
			textblend = new double(0.5);
		}

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		vertex::~vertex(){};

	/*--------------------------------------------//
	Getters
	//--------------------------------------------*/
		//normals
			double vertex::nx(){return normal->x();}
			double vertex::ny(){return normal->y();}
			double vertex::nz(){return normal->z();}
		//colors
			double vertex::r(){return color->x();}
			double vertex::g(){return color->y();}
			double vertex::b(){return color->z();}
		//texture
			double vertex::s(){return textcoord->x();}
			double vertex::t(){return textcoord->y();}
			double vertex::blend(){return *textblend;}

	/*--------------------------------------------//
	Setters
	//--------------------------------------------*/
		//normals
			void vertex::nx(double a){
				normal->x(a);
			}
			void vertex::ny(double a){
				normal->y(a);
			}
			void vertex::nz(double a){
				normal->z(a);
			}
		//colors
			void vertex::r(double a){
				color->x(a);
			}
			void vertex::g(double a){
				color->y(a);
			}
			void vertex::b(double a){
				color->z(a);
			}
		//texture
			void vertex::s(double a){
				textcoord->x(a);
			}
			void vertex::t(double a){
				textcoord->y(a);
			}
			void vertex::blend(double a){
				*textblend = a;
			}

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