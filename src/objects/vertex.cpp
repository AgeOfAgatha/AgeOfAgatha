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
		/*--------------------------------------------//
		Constructor with default normal and color
		//--------------------------------------------*/
			vertex::vertex(){
				pos = new Vec4(0.0, 0.0, 0., 1.0);
				normal = new Vec3(1.0, 1.0, 1.0);
				color = new Vec4(1.0, 1.0, 1.0, 1.0);
			}
			vertex::vertex(Vec3 p):vertex(){
				pos->x = p.x;
				pos->y = p.y;
				pos->z = p.z;
			}
			vertex::vertex(double a, double b, double c):vertex(){
				pos->x = a;
				pos->y = b;
				pos->z = c;
			}
		/*--------------------------------------------//
		Constructor with specified normal and color
		//--------------------------------------------*/
			vertex::vertex(Vec3 p, Vec3 n, Vec4 c){
				pos = new Vec4(p[0], p[1], p[2], 1.0);
				normal = new Vec3(n[0], n[1], n[2]);
				color = new Vec4(c[0], c[1], c[2], c[3]);
			}
			vertex::vertex(Vec4* p, Vec3* n, Vec4* c){
				pos = p;
				normal = n;
				color = c;
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
					vertex v = vertex(*pos+other, *normal, *color);
					return v;
				};
				vertex vertex::operator+(const float &other) {
					vertex v = vertex(*pos+other, *normal, *color);
					return v;
				};
				vertex vertex::operator+(const double &other) {
					vertex v = vertex(*pos+other, *normal, *color);
					return v;
				};
				vertex vertex::operator+(const Vec3 &other) {
					vertex v = vertex(*pos+other, *normal, *color);
					return v;
				};
				vertex vertex::operator+=(const int &other) {
					*this = *this + other;
					return (*this);
				};
				vertex vertex::operator+=(const float &other) {
					*this = *this + other;
					return (*this);
				};
				vertex vertex::operator+=(const double &other) {
					*this = *this + other;
					return (*this);
				};
				vertex vertex::operator+=(const Vec3 &other) {
					*this = *this + other;
					return (*this);
				};
			//Subtraction
				vertex vertex::operator-(const int &other) {
					vertex v = vertex(*pos-other, *normal, *color);
					return v;
				};
				vertex vertex::operator-(const float &other) {
					vertex v = vertex(*pos-other, *normal, *color);
					return v;
				};
				vertex vertex::operator-(const double &other) {
					vertex v = vertex(*pos-other, *normal, *color);
					return v;
				};
				vertex vertex::operator-(const Vec3 &other) {
					vertex v = vertex(*pos-other, *normal, *color);
					return v;
				};
				vertex vertex::operator-=(const int &other) {
					*this = *this - other;
					return (*this);
				};
				vertex vertex::operator-=(const float &other) {
					*this = *this - other;
					return (*this);
				};
				vertex vertex::operator-=(const double &other) {
					*this = *this - other;
					return (*this);
				};
				vertex vertex::operator-=(const Vec3 &other) {
					*this = *this - other;
					return (*this);
				};
			//Divison
				vertex vertex::operator/(const int &other) {
					vertex v = vertex(*pos/other, *normal, *color);
					return v;
				};
				vertex vertex::operator/(const float &other) {
					vertex v = vertex(*pos/other, *normal, *color);
					return v;
				};
				vertex vertex::operator/(const double &other) {
					vertex v = vertex(*pos/other, *normal, *color);
					return v;
				};
				vertex vertex::operator/(const Vec3 &other) {
					vertex v = vertex(*pos/other, *normal, *color);
					return v;
				};
				vertex vertex::operator/=(const int &other) {
					*this = *this / other;
					return (*this);
				};
				vertex vertex::operator/=(const float &other) {
					*this = *this / other;
					return (*this);
				};
				vertex vertex::operator/=(const double &other) {
					*this = *this / other;
					return (*this);
				};
				vertex vertex::operator/=(const Vec3 &other) {
					*this = *this / other;
					return (*this);
				};
			//Multiplication
				vertex vertex::operator*(const int &other) {
					vertex v = vertex(*pos*other, *normal, *color);
					return v;
				};
				vertex vertex::operator*(const float &other) {
					vertex v = vertex(*pos*other, *normal, *color);
					return v;
				};
				vertex vertex::operator*(const double &other) {
					vertex v = vertex(*pos*other, *normal, *color);
					return v;
				};
				vertex vertex::operator*(const Vec3 &other) {
					vertex v = vertex(*pos*other, *normal, *color);
					return v;
				};
				vertex vertex::operator*=(const int &other) {
					*this = *this * other;
					return (*this);
				};
				vertex vertex::operator*=(const float &other) {
					*this = *this * other;
					return (*this);
				};
				vertex vertex::operator*=(const double &other) {
					*this = *this * other;
					return (*this);
				};
				vertex vertex::operator*=(const Vec3 &other) {
					*this = *this * other;
					return (*this);
				};
		//Compairison
			//less than
				bool vertex::operator<(const Vec3 &other) const {
					return ((Vec3)*pos < other);
				};
				bool vertex::operator<(const int &other) const {
					return (pos->x < other && pos->y < other && pos->z < other);
				};
				bool vertex::operator<(const float &other) const {
					return (pos->x < other && pos->y < other && pos->z < other);
				};
				bool vertex::operator<(const double &other) const {
					return (pos->x < other && pos->y < other && pos->z < other);
				};
				bool vertex::operator<=(const Vec3 &other) const {
					return ((Vec3)*pos <= other);
				};
				bool vertex::operator<=(const int &other) const {
					return (pos->x <= other && pos->y <= other && pos->z <= other);
				};
				bool vertex::operator<=(const float &other) const {
					return (pos->x <= other && pos->y <= other && pos->z <= other);
				};
				bool vertex::operator<=(const double &other) const {
					return (pos->x <= other && pos->y <= other && pos->z <= other);
				};
			//greater than
				bool vertex::operator>(const Vec3 &other) const {
					return ((Vec3)*pos > other);
				};
				bool vertex::operator>(const int &other) const {
					return (pos->x > other && pos->y > other && pos->z > other);
				};
				bool vertex::operator>(const float &other) const {
					return (pos->x > other && pos->y > other && pos->z > other);
				};
				bool vertex::operator>(const double &other) const {
					return (pos->x > other && pos->y > other && pos->z > other);
				};
				bool vertex::operator>=(const Vec3 &other) const {
					return ((Vec3)*pos >= other);
				};
				bool vertex::operator>=(const int &other) const {
					return (pos->x >= other && pos->y >= other && pos->z >= other);
				};
				bool vertex::operator>=(const float &other) const {
					return (pos->x >= other && pos->y >= other && pos->z >= other);
				};
				bool vertex::operator>=(const double &other) const {
					return (pos->x >= other && pos->y >= other && pos->z >= other);
				};
			//equals
				bool vertex::operator==(const Vec3 &other) const {
					return (pos->x == other.x && pos->y == other.y && pos->z == other.z);
				};
				bool vertex::operator==(const int &other) const {
					return (pos->x == other && pos->y == other && pos->z == other);
				};
				bool vertex::operator==(const float &other) const {
					return (pos->x == other && pos->y == other && pos->z == other);
				};
				bool vertex::operator==(const double &other) const {
					return (pos->x == other && pos->y == other && pos->z == other);
				};
				bool vertex::operator!=(const Vec3 &other) const {
					return (Vec3)*pos!=other;
				};
				bool vertex::operator!=(const int &other) const {
					return *pos!=other;
				};
				bool vertex::operator!=(const float &other) const {
					return *pos!=other;
				};
				bool vertex::operator!=(const double &other) const {
					return *pos!=other;
				};
#endif