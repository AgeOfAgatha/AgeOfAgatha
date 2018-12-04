/*--------------------------------------------//
Vector definition
This is used to simplify definition of points
//--------------------------------------------*/
#ifndef VECTOR
#define VECTOR
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "vector.h"

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		vec1::vec1(){
			pos[0] = 0;
		};
		vec2::vec2(){
			pos[0] = 0;
			pos[1] = 0;
		};
		vec3::vec3(){
			pos[0] = 0;
			pos[1] = 0;
			pos[2] = 0;
		};
		vec4::vec4(){
			pos[0] = 0;
			pos[1] = 0;
			pos[2] = 0;
			pos[3] = 0;
		};

	/*--------------------------------------------//
	Constuctor with positions specified
	//--------------------------------------------*/
		vec1::vec1(double xi):vec1(){
			pos[0] = xi;
		};
		vec2::vec2(double xi, double yi):vec2(){
			pos[0] = xi;
			pos[1] = yi;
		};
		vec3::vec3(double xi, double yi, double zi):vec3(){
			pos[0] = xi;
			pos[1] = yi;
			pos[2] = zi;
		};
		vec4::vec4(double xi, double yi, double zi, double wi):vec4(){
			pos[0] = xi;
			pos[1] = yi;
			pos[2] = zi;
			pos[3] = wi;
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		vec1::~vec1(){};
		vec2::~vec2(){};
		vec3::~vec3(){};
		vec4::~vec4(){};

	/*--------------------------------------------//
	Getters
	//--------------------------------------------*/
		double vec1::x() const{
			return pos[0];
		}
		double vec2::x() const{
			return pos[0];
		}
		double vec2::y() const{
			return pos[1];
		}
		double vec3::x() const{
			return pos[0];
		}
		double vec3::y() const{
			return pos[1];
		}
		double vec3::z() const{
			return pos[2];
		}
		double vec4::x() const{
			return pos[0];
		}
		double vec4::y() const{
			return pos[1];
		}
		double vec4::z() const{
			return pos[2];
		}
		double vec4::w() const{
			return pos[3];
		}

	/*--------------------------------------------//
	Setters
	//--------------------------------------------*/
		void vec1::x(double xi){
			pos[0] = xi;
		}
		void vec2::x(double xi){
			pos[0] = xi;
		}
		void vec2::y(double yi){
			pos[1] = yi;
		}
		void vec3::x(double xi){
			pos[0] = xi;
		}
		void vec3::y(double yi){
			pos[1] = yi;
		}
		void vec3::z(double zi){
			pos[2] = zi;
		}
		void vec4::x(double xi){
			pos[0] = xi;
		}
		void vec4::y(double yi){
			pos[1] = yi;
		}
		void vec4::z(double zi){
			pos[2] = zi;
		}
		void vec4::w(double wi){
			pos[3] = wi;
		}

	/*--------------------------------------------//
	Normalize the vector
	makes the sum of each component equal to one
	//--------------------------------------------*/
		void vec1::normalize(){
			int a = abs(x());
			x(pos[0]/a);
		}
		void vec2::normalize(){
			int a = abs(x())+abs(y());
			x(x()/a);
			y(y()/a);
		}
		void vec3::normalize(){
			int a = abs(x())+abs(y())+abs(z());
			x(x()/a);
			y(y()/a);
			z(z()/a);
		}
		void vec4::normalize(){
			int a = abs(x())+abs(y())+abs(z())+abs(w());
			x(x()/a);
			y(y()/a);
			z(z()/a);
			w(w()/a);
		}

	/*--------------------------------------------//
	Length of a vector
	//--------------------------------------------*/
		double vec1::length() const{
			return (sqrt( pow(this->x(), 2) ));
		}
		double vec2::length() const{
			return (sqrt( pow(this->x(), 2) + pow(this->y(), 2) ));
		}
		double vec3::length() const{
			return (sqrt( pow(this->x(), 2) + pow(this->y(), 2) + pow(this->z(), 2) ));
		}
		double vec4::length() const{
			return (sqrt( pow(this->x(), 2) + pow(this->y(), 2) + pow(this->z(), 2) + pow(this->w(), 2) ));
		}

	/*--------------------------------------------//
	Distance between two points
	//--------------------------------------------*/
		double vec1::distance(vec1 other) const{
			return (sqrt( pow(this->x() - other.x(), 2) ));
		}
		double vec2::distance(vec2 other) const{
			return (sqrt( pow(this->x() - other.x(), 2) + pow(this->y() - other.y(), 2) ));
		}
		double vec3::distance(vec3 other) const{
			return (sqrt( pow(this->x() - other.x(), 2) + pow(this->y() - other.y(), 2) + pow(this->z() - other.z(), 2) ));
		}
		double vec4::distance(vec4 other) const{
			return (sqrt( pow(this->x() - other.x(), 2) + pow(this->y() - other.y(), 2) + pow(this->z() - other.z(), 2) + pow(this->w() - other.w(), 2) ));
		}

	/*--------------------------------------------//
	dot product of two vectors
	//--------------------------------------------*/
		double vec1::dot(vec1 other) const{
			return (this->x()*other.x());
		}
		double vec2::dot(vec2 other) const{
			return (this->x()*other.x() + this->y()*other.y());
		}
		double vec3::dot(vec3 other) const{
			return (this->x()*other.x() + this->y()*other.y() + this->z()*other.z());
		}
		double vec4::dot(vec4 other) const{
			return (this->x()*other.x() + this->y()*other.y() + this->z()*other.z() + this->w()*other.w());
		}

	/*--------------------------------------------//
	get pointer to data
	//--------------------------------------------*/
		double* vec1::at(){
			return pos;
		}
		double* vec2::at(){
			return pos;
		}
		double* vec3::at(){
			return pos;
		}
		double* vec4::at(){
			return pos;
		}

	/*--------------------------------------------//
	Overridden operators
	//--------------------------------------------*/
		double vec1::operator[](const int &index) const{
			assert(index >= 0 && index < 1);
			return pos[index];
		}
		double vec2::operator[](const int &index) const{
			assert(index >= 0 && index < 2);
			return pos[index];
		}
		double vec3::operator[](const int &index) const{
			assert(index >= 0 && index < 3);
			return pos[index];
		}
		double vec4::operator[](const int &index) const{
			assert(index >= 0 && index < 4);
			return pos[index];
		}
		//Arithmetic
			//Addition
				vec1 vec1::operator+(const int &other) {
					this->x(x()+other);
					return (*this);
				};
				vec1 vec1::operator+(const float &other) {
					this->x(x()+other);
					return (*this);
				};
				vec1 vec1::operator+(const double &other) {
					this->x(x()+other);
					return (*this);
				};
				vec1 vec1::operator+(const vec1 &other) {
					this->x(x()+other.x());
					return (*this);
				};
				vec2 vec2::operator+(const int &other) {
					this->x(x()+other);
					this->y(y()+other);
					return (*this);
				};
				vec2 vec2::operator+(const float &other) {
					this->x(x()+other);
					this->y(y()+other);
					return (*this);
				};
				vec2 vec2::operator+(const double &other) {
					this->x(x()+other);
					this->y(y()+other);
					return (*this);
				};
				vec2 vec2::operator+(const vec2 &other) {
					this->x(x()+other.x());
					this->y(y()+other.y());
					return (*this);
				};
				vec3 vec3::operator+(const int &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					return (*this);
				};
				vec3 vec3::operator+(const float &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					return (*this);
				};
				vec3 vec3::operator+(const double &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					return (*this);
				};
				vec3 vec3::operator+(const vec3 &other) {
					this->x(x()+other.x());
					this->y(y()+other.y());
					this->z(z()+other.z());
					return (*this);
				};
				vec4 vec4::operator+(const int &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					this->w(w()+other);
					return (*this);
				};
				vec4 vec4::operator+(const float &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					this->w(w()+other);
					return (*this);
				};
				vec4 vec4::operator+(const double &other) {
					this->x(x()+other);
					this->y(y()+other);
					this->z(z()+other);
					this->w(w()+other);
					return (*this);
				};
				vec4 vec4::operator+(const vec4 &other) {
					this->x(x()+other.x());
					this->y(y()+other.y());
					this->z(z()+other.z());
					this->w(w()+other.w());
					return (*this);
				};
			//Subtraction
				vec1 vec1::operator-(const int &other) {
					this->x(x()-other);
					return (*this);
				};
				vec1 vec1::operator-(const float &other) {
					this->x(x()-other);
					return (*this);
				};
				vec1 vec1::operator-(const double &other) {
					this->x(x()-other);
					return (*this);
				};
				vec1 vec1::operator-(const vec1 &other) {
					this->x(x()-other.x());
					return (*this);
				};
				vec2 vec2::operator-(const int &other) {
					this->x(x()-other);
					this->y(y()-other);
					return (*this);
				};
				vec2 vec2::operator-(const float &other) {
					this->x(x()-other);
					this->y(y()-other);
					return (*this);
				};
				vec2 vec2::operator-(const double &other) {
					this->x(x()-other);
					this->y(y()-other);
					return (*this);
				};
				vec2 vec2::operator-(const vec2 &other) {
					this->x(x()-other.x());
					this->y(y()-other.y());
					return (*this);
				};
				vec3 vec3::operator-(const int &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					return (*this);
				};
				vec3 vec3::operator-(const float &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					return (*this);
				};
				vec3 vec3::operator-(const double &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					return (*this);
				};
				vec3 vec3::operator-(const vec3 &other) {
					this->x(x()-other.x());
					this->y(y()-other.y());
					this->z(z()-other.z());
					return (*this);
				};
				vec4 vec4::operator-(const int &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					this->w(w()-other);
					return (*this);
				};
				vec4 vec4::operator-(const float &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					this->w(w()-other);
					return (*this);
				};
				vec4 vec4::operator-(const double &other) {
					this->x(x()-other);
					this->y(y()-other);
					this->z(z()-other);
					this->w(w()-other);
					return (*this);
				};
				vec4 vec4::operator-(const vec4 &other) {
					this->x(x()-other.x());
					this->y(y()-other.y());
					this->z(z()-other.z());
					this->w(w()-other.w());
					return (*this);
				};
			//Divison
				vec1 vec1::operator/(const int &other) {
					this->x(x()/other);
					return (*this);
				};
				vec1 vec1::operator/(const float &other) {
					this->x(x()/other);
					return (*this);
				};
				vec1 vec1::operator/(const double &other) {
					this->x(x()/other);
					return (*this);
				};
				vec1 vec1::operator/(const vec1 &other) {
					this->x(x()/other.x());
					return (*this);
				};
				vec2 vec2::operator/(const int &other) {
					this->x(x()/other);
					this->y(y()/other);
					return (*this);
				};
				vec2 vec2::operator/(const float &other) {
					this->x(x()/other);
					this->y(y()/other);
					return (*this);
				};
				vec2 vec2::operator/(const double &other) {
					this->x(x()/other);
					this->y(y()/other);
					return (*this);
				};
				vec2 vec2::operator/(const vec2 &other) {
					this->x(x()/other.x());
					this->y(y()/other.y());
					return (*this);
				};
				vec3 vec3::operator/(const int &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					return (*this);
				};
				vec3 vec3::operator/(const float &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					return (*this);
				};
				vec3 vec3::operator/(const double &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					return (*this);
				};
				vec3 vec3::operator/(const vec3 &other) {
					this->x(x()/other.x());
					this->y(y()/other.y());
					this->z(z()/other.z());
					return (*this);
				};
				vec4 vec4::operator/(const int &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					this->w(w()/other);
					return (*this);
				};
				vec4 vec4::operator/(const float &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					this->w(w()/other);
					return (*this);
				};
				vec4 vec4::operator/(const double &other) {
					this->x(x()/other);
					this->y(y()/other);
					this->z(z()/other);
					this->w(w()/other);
					return (*this);
				};
				vec4 vec4::operator/(const vec4 &other) {
					this->x(x()/other.x());
					this->y(y()/other.y());
					this->z(z()/other.z());
					this->w(w()/other.w());
					return (*this);
				};
			//Multiplication
				vec1 vec1::operator*(const int &other) {
					this->x(x()*other);
					return (*this);
				};
				vec1 vec1::operator*(const float &other) {
					this->x(x()*other);
					return (*this);
				};
				vec1 vec1::operator*(const double &other) {
					this->x(x()*other);
					return (*this);
				};
				vec1 vec1::operator*(const vec1 &other) {
					this->x(x()*other.x());
					return (*this);
				};
				vec2 vec2::operator*(const int &other) {
					this->x(x()*other);
					this->y(y()*other);
					return (*this);
				};
				vec2 vec2::operator*(const float &other) {
					this->x(x()*other);
					this->y(y()*other);
					return (*this);
				};
				vec2 vec2::operator*(const double &other) {
					this->x(x()*other);
					this->y(y()*other);
					return (*this);
				};
				vec2 vec2::operator*(const vec2 &other) {
					this->x(x()*other.x());
					this->y(y()*other.y());
					return (*this);
				};
				vec3 vec3::operator*(const int &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					return (*this);
				};
				vec3 vec3::operator*(const float &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					return (*this);
				};
				vec3 vec3::operator*(const double &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					return (*this);
				};
				vec3 vec3::operator*(const vec3 &other) {
					this->x(x()*other.x());
					this->y(y()*other.y());
					this->z(z()*other.z());
					return (*this);
				};
				vec4 vec4::operator*(const int &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					this->w(w()*other);
					return (*this);
				};
				vec4 vec4::operator*(const float &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					this->w(w()*other);
					return (*this);
				};
				vec4 vec4::operator*(const double &other) {
					this->x(x()*other);
					this->y(y()*other);
					this->z(z()*other);
					this->w(w()*other);
					return (*this);
				};
				vec4 vec4::operator*(const vec4 &other) {
					this->x(x()*other.x());
					this->y(y()*other.y());
					this->z(z()*other.z());
					this->w(w()*other.w());
					return (*this);
				};
		//Compairison
			//less than
				bool vec1::operator<(const vec1 &other) const {
					return (this->length() < other.length());
				};
				bool vec1::operator<(const int &other) const {
					return (this->x() < other);
				};
				bool vec1::operator<(const float &other) const {
					return (this->x() < other);
				};
				bool vec1::operator<(const double &other) const {
					return (this->x() < other);
				};
				bool vec1::operator<=(const vec1 &other) const {
					return (this->length() <= other.length());
				};
				bool vec1::operator<=(const int &other) const {
					return (this->x() <= other);
				};
				bool vec1::operator<=(const float &other) const {
					return (this->x() <= other);
				};
				bool vec1::operator<=(const double &other) const {
					return (this->x() <= other);
				};
				bool vec2::operator<(const vec2 &other) const {
					return (this->length() < other.length());
				};
				bool vec2::operator<(const int &other) const {
					return (this->x() < other && this->y() < other);
				};
				bool vec2::operator<(const float &other) const {
					return (this->x() < other && this->y() < other);
				};
				bool vec2::operator<(const double &other) const {
					return (this->x() < other && this->y() < other);
				};
				bool vec2::operator<=(const vec2 &other) const {
					return (this->length() <= other.length());
				};
				bool vec2::operator<=(const int &other) const {
					return (this->x() <= other && this->y() <= other);
				};
				bool vec2::operator<=(const float &other) const {
					return (this->x() <= other && this->y() <= other);
				};
				bool vec2::operator<=(const double &other) const {
					return (this->x() <= other && this->y() <= other);
				};
				bool vec3::operator<(const vec3 &other) const {
					return (this->length() < other.length());
				};
				bool vec3::operator<(const int &other) const {
					return (this->x() < other && this->y() < other && this->z() < other);
				};
				bool vec3::operator<(const float &other) const {
					return (this->x() < other && this->y() < other && this->z() < other);
				};
				bool vec3::operator<(const double &other) const {
					return (this->x() < other && this->y() < other && this->z() < other);
				};
				bool vec3::operator<=(const vec3 &other) const {
					return (this->length() <= other.length());
				};
				bool vec3::operator<=(const int &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other);
				};
				bool vec3::operator<=(const float &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other);
				};
				bool vec3::operator<=(const double &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other);
				};
				bool vec4::operator<(const vec4 &other) const {
					return (this->length() < other.length());
				};
				bool vec4::operator<(const int &other) const {
					return (this->x() < other && this->y() < other && this->z() < other && this->w() < other);
				};
				bool vec4::operator<(const float &other) const {
					return (this->x() < other && this->y() < other && this->z() < other && this->w() < other);
				};
				bool vec4::operator<(const double &other) const {
					return (this->x() < other && this->y() < other && this->z() < other && this->w() < other);
				};
				bool vec4::operator<=(const vec4 &other) const {
					return (this->length() <= other.length());
				};
				bool vec4::operator<=(const int &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other && this->w() <= other);
				};
				bool vec4::operator<=(const float &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other && this->w() <= other);
				};
				bool vec4::operator<=(const double &other) const {
					return (this->x() <= other && this->y() <= other && this->z() <= other && this->w() <= other);
				};
			//greater than
				bool vec1::operator>(const vec1 &other) const {
					return (this->length() > other.length());
				};
				bool vec1::operator>(const int &other) const {
					return (this->x() > other);
				};
				bool vec1::operator>(const float &other) const {
					return (this->x() > other);
				};
				bool vec1::operator>(const double &other) const {
					return (this->x() > other);
				};
				bool vec1::operator>=(const vec1 &other) const {
					return (this->length() >= other.length());
				};
				bool vec1::operator>=(const int &other) const {
					return (this->x() >= other);
				};
				bool vec1::operator>=(const float &other) const {
					return (this->x() >= other);
				};
				bool vec1::operator>=(const double &other) const {
					return (this->x() >= other);
				};
				bool vec2::operator>(const vec2 &other) const {
					return (this->length() > other.length());
				};
				bool vec2::operator>(const int &other) const {
					return (this->x() > other && this->y() > other);
				};
				bool vec2::operator>(const float &other) const {
					return (this->x() > other && this->y() > other);
				};
				bool vec2::operator>(const double &other) const {
					return (this->x() > other && this->y() > other);
				};
				bool vec2::operator>=(const vec2 &other) const {
					return (this->length() >= other.length());
				};
				bool vec2::operator>=(const int &other) const {
					return (this->x() >= other && this->y() >= other);
				};
				bool vec2::operator>=(const float &other) const {
					return (this->x() >= other && this->y() >= other);
				};
				bool vec2::operator>=(const double &other) const {
					return (this->x() >= other && this->y() >= other);
				};
				bool vec3::operator>(const vec3 &other) const {
					return (this->length() > other.length());
				};
				bool vec3::operator>(const int &other) const {
					return (this->x() > other && this->y() > other && this->z() > other);
				};
				bool vec3::operator>(const float &other) const {
					return (this->x() > other && this->y() > other && this->z() > other);
				};
				bool vec3::operator>(const double &other) const {
					return (this->x() > other && this->y() > other && this->z() > other);
				};
				bool vec3::operator>=(const vec3 &other) const {
					return (this->length() >= other.length());
				};
				bool vec3::operator>=(const int &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other);
				};
				bool vec3::operator>=(const float &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other);
				};
				bool vec3::operator>=(const double &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other);
				};
				bool vec4::operator>(const vec4 &other) const {
					return (this->length() > other.length());
				};
				bool vec4::operator>(const int &other) const {
					return (this->x() > other && this->y() > other && this->z() > other && this->w() > other);
				};
				bool vec4::operator>(const float &other) const {
					return (this->x() > other && this->y() > other && this->z() > other && this->w() > other);
				};
				bool vec4::operator>(const double &other) const {
					return (this->x() > other && this->y() > other && this->z() > other && this->w() > other);
				};
				bool vec4::operator>=(const vec4 &other) const {
					return (this->length() >= other.length());
				};
				bool vec4::operator>=(const int &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other && this->w() >= other);
				};
				bool vec4::operator>=(const float &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other && this->w() >= other);
				};
				bool vec4::operator>=(const double &other) const {
					return (this->x() >= other && this->y() >= other && this->z() >= other && this->w() >= other);
				};
			//equals
				bool vec1::operator==(const vec1 &other) const {
					return (this->x() == other.x());
				};
				bool vec1::operator==(const int &other) const {
					return (this->x() == other);
				};
				bool vec1::operator==(const float &other) const {
					return (this->x() == other);
				};
				bool vec1::operator==(const double &other) const {
					return (this->x() == other);
				};
				bool vec1::operator!=(const vec1 &other) const {
					return *this!=other;
				};
				bool vec1::operator!=(const int &other) const {
					return *this!=other;
				};
				bool vec1::operator!=(const float &other) const {
					return *this!=other;
				};
				bool vec1::operator!=(const double &other) const {
					return *this!=other;
				};
				bool vec2::operator==(const vec2 &other) const {
					return (this->x() == other.x() && this->y() == other.y());
				};
				bool vec2::operator==(const int &other) const {
					return (this->x() == other && this->y() == other);
				};
				bool vec2::operator==(const float &other) const {
					return (this->x() == other && this->y() == other);
				};
				bool vec2::operator==(const double &other) const {
					return (this->x() == other && this->y() == other);
				};
				bool vec2::operator!=(const vec2 &other) const {
					return *this!=other;
				};
				bool vec2::operator!=(const int &other) const {
					return *this!=other;
				};
				bool vec2::operator!=(const float &other) const {
					return *this!=other;
				};
				bool vec2::operator!=(const double &other) const {
					return *this!=other;
				};
				bool vec3::operator==(const vec3 &other) const {
					return (this->x() == other.x() && this->y() == other.y() && this->z() == other.z());
				};
				bool vec3::operator==(const int &other) const {
					return (this->x() == other && this->y() == other && this->z() == other);
				};
				bool vec3::operator==(const float &other) const {
					return (this->x() == other && this->y() == other && this->z() == other);
				};
				bool vec3::operator==(const double &other) const {
					return (this->x() == other && this->y() == other && this->z() == other);
				};
				bool vec3::operator!=(const vec3 &other) const {
					return *this!=other;
				};
				bool vec3::operator!=(const int &other) const {
					return *this!=other;
				};
				bool vec3::operator!=(const float &other) const {
					return *this!=other;
				};
				bool vec3::operator!=(const double &other) const {
					return *this!=other;
				};
				bool vec4::operator==(const vec4 &other) const {
					return (this->x() == other.x() && this->y() == other.y() && this->z() == other.z() && this->w() == other.w());
				};
				bool vec4::operator==(const int &other) const {
					return (this->x() == other && this->y() == other && this->z() == other && this->w() == other);
				};
				bool vec4::operator==(const float &other) const {
					return (this->x() == other && this->y() == other && this->z() == other && this->w() == other);
				};
				bool vec4::operator==(const double &other) const {
					return (this->x() == other && this->y() == other && this->z() == other && this->w() == other);
				};
				bool vec4::operator!=(const vec4 &other) const {
					return *this!=other;
				};
				bool vec4::operator!=(const int &other) const {
					return *this!=other;
				};
				bool vec4::operator!=(const float &other) const {
					return *this!=other;
				};
				bool vec4::operator!=(const double &other) const {
					return *this!=other;
				};
#endif