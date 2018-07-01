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
		vector::vector(){
			pos[0] = 0;
			pos[1] = 0;
			pos[2] = 0;
		};

	/*--------------------------------------------//
	Constuctor with positions specified
	//--------------------------------------------*/
		vector::vector(double xi, double yi, double zi):vector(){
			pos[0] = xi;
			pos[1] = yi;
			pos[2] = zi;
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		vector::~vector(){

		};

	/*--------------------------------------------//
	Getters
	//--------------------------------------------*/
		double vector::x(){
			return pos[0];
		}
		double vector::y(){
			return pos[1];
		}
		double vector::z(){
			return pos[2];
		}

	/*--------------------------------------------//
	Setters
	//--------------------------------------------*/
		void vector::x(double xi){
			pos[0] = xi;
		}
		void vector::y(double yi){
			pos[1] = yi;
		}
		void vector::z(double zi){
			pos[2] = zi;
		}

	/*--------------------------------------------//
	Normalize the vector
	makes the sum of each component equal to one
	//--------------------------------------------*/
		void vector::normalize(){
			int a = abs(pos[0])+abs(pos[1])+abs(pos[2]);
			pos[0] = pos[0]/a;
			pos[1] = pos[1]/a;
			pos[2] = pos[2]/a;
		}

	/*--------------------------------------------//
	Length of a vector
	//--------------------------------------------*/
		double vector::length(){
			return (sqrt( pow(this->x(), 2) + pow(this->y(), 2) + pow(this->z(), 2) ));
		}

	/*--------------------------------------------//
	Distance between two points
	//--------------------------------------------*/
		double vector::distance(vector vec2){
			return (sqrt( pow(this->pos[0] - vec2.x(), 2) + pow(this->pos[1] - vec2.y(), 2) + pow(this->pos[2] - vec2.z(), 2) ));
		}

	/*--------------------------------------------//
	dot product of two vectors
	//--------------------------------------------*/
		double vector::dot(vector vec2){
			return (this->x()*vec2.x() + this->y()*vec2.y() + this->z()*vec2.z());
		}

	/*--------------------------------------------//
	Overridden operators
	//--------------------------------------------*/
		//Arithmetic
			//Addition
				vector vector::operator+(const int &other) {
					this->pos[0] += other;
					this->pos[1] += other;
					this->pos[2] += other;
					return (*this);
				};
				vector vector::operator+(const float &other) {
					this->pos[0] += other;
					this->pos[1] += other;
					this->pos[2] += other;
					return (*this);
				};
				vector vector::operator+(const double &other) {
					this->pos[0] += other;
					this->pos[1] += other;
					this->pos[2] += other;
					return (*this);
				};
				vector vector::operator+(const vector &other) {
					this->pos[0] += other.pos[0];  
					this->pos[1] += other.pos[1]; 
					this->pos[2] += other.pos[2];  
					return (*this);
				};
			//Subtraction
				vector vector::operator-(const int &other) {
					this->pos[0] -= other;
					this->pos[1] -= other;
					this->pos[2] -= other;
					return (*this);
				};
				vector vector::operator-(const float &other) {
					this->pos[0] -= other;
					this->pos[1] -= other;
					this->pos[2] -= other;
					return (*this);
				};
				vector vector::operator-(const double &other) {
					this->pos[0] -= other;
					this->pos[1] -= other;
					this->pos[2] -= other;
					return (*this);
				};
				vector vector::operator-(const vector &other) {
					this->pos[0] -= other.pos[0];  
					this->pos[1] -= other.pos[1];  
					this->pos[2] -= other.pos[2];  
					return (*this);
				};
			//Divison
				vector vector::operator/(const int &other) {
					this->pos[0] /= other;
					this->pos[1] /= other;
					this->pos[2] /= other;
					return (*this);
				};
				vector vector::operator/(const float &other) {
					this->pos[0] /= other;
					this->pos[1] /= other;
					this->pos[2] /= other;
					return (*this);
				};
				vector vector::operator/(const double &other) {
					this->pos[0] /= other;
					this->pos[1] /= other;
					this->pos[2] /= other;
					return (*this);
				};
				vector vector::operator/(const vector &other) {
					this->pos[0] /= other.pos[0];  
					this->pos[1] /= other.pos[1];  
					this->pos[2] /= other.pos[2];  
					return (*this);
				};
			//Multiplication
				vector vector::operator*(const int &other) {
					this->pos[0] *= other;
					this->pos[1] *= other;
					this->pos[2] *= other;
					return (*this);
				};
				vector vector::operator*(const float &other) {
					this->pos[0] *= other;
					this->pos[1] *= other;
					this->pos[2] *= other;
					return (*this);
				};
				vector vector::operator*(const double &other) {
					this->pos[0] *= other;
					this->pos[1] *= other;
					this->pos[2] *= other;
					return (*this);
				};
				vector vector::operator*(const vector &other) {
					this->pos[0] *= other.pos[0];  
					this->pos[1] *= other.pos[1];  
					this->pos[2] *= other.pos[2];  
					return (*this);
				};		
		//Compairison
			//less than
				bool vector::operator<(const vector &other) const {
					return (this->pos[0] < other.pos[0]  && this->pos[1] < other.pos[1]  && this->pos[2] < other.pos[2] );
				};
				bool vector::operator<(const int &other) const {
					return (this->pos[0] < other && this->pos[1] < other && this->pos[2] < other);
				};
				bool vector::operator<(const float &other) const {
					return (this->pos[0] < other && this->pos[1] < other && this->pos[2] < other);
				};
				bool vector::operator<(const double &other) const {
					return (this->pos[0] < other && this->pos[1] < other && this->pos[2] < other);
				};
				bool vector::operator<=(const vector &other) const {
					return (this->pos[0] <= other.pos[0]  && this->pos[1] <= other.pos[1]  && this->pos[2] <= other.pos[2] );
				};
				bool vector::operator<=(const int &other) const {
					return (this->pos[0] <= other && this->pos[1] <= other && this->pos[2] <= other);
				};
				bool vector::operator<=(const float &other) const {
					return (this->pos[0] <= other && this->pos[1] <= other && this->pos[2] <= other);
				};
				bool vector::operator<=(const double &other) const {
					return (this->pos[0] <= other && this->pos[1] <= other && this->pos[2] <= other);
				};
			//greater than
				bool vector::operator>(const vector &other) const {
					return (this->pos[0] > other.pos[0]  && this->pos[1] > other.pos[1]  && this->pos[2] > other.pos[2] );
				};
				bool vector::operator>(const int &other) const {
					return (this->pos[0] > other && this->pos[1] > other && this->pos[2] > other);
				};
				bool vector::operator>(const float &other) const {
					return (this->pos[0] > other && this->pos[1] > other && this->pos[2] > other);
				};
				bool vector::operator>(const double &other) const {
					return (this->pos[0] > other && this->pos[1] > other && this->pos[2] > other);
				};
				bool vector::operator>=(const vector &other) const {
					return (this->pos[0] >= other.pos[0]  && this->pos[1] >= other.pos[1]  && this->pos[2] >= other.pos[2] );
				};
				bool vector::operator>=(const int &other) const {
					return (this->pos[0] >= other && this->pos[1] >= other && this->pos[2] >= other);
				};
				bool vector::operator>=(const float &other) const {
					return (this->pos[0] >= other && this->pos[1] >= other && this->pos[2] >= other);
				};
				bool vector::operator>=(const double &other) const {
					return (this->pos[0] >= other && this->pos[1] >= other && this->pos[2] >= other);
				};
			//equals
				bool vector::operator==(const vector &other) const {
					return (this->pos[0] == other.pos[0]  && this->pos[1] == other.pos[1]  && this->pos[2] == other.pos[2] );
				};
				bool vector::operator==(const int &other) const {
					return (this->pos[0] == other && this->pos[1] == other && this->pos[2] == other);
				};
				bool vector::operator==(const float &other) const {
					return (this->pos[0] == other && this->pos[1] == other && this->pos[2] == other);
				};
				bool vector::operator==(const double &other) const {
					return (this->pos[0] == other && this->pos[1] == other && this->pos[2] == other);
				};
				bool vector::operator!=(const vector &other) const {
					return *this!=other;
				};
				bool vector::operator!=(const int &other) const {
					return *this!=other;
				};
				bool vector::operator!=(const float &other) const {
					return *this!=other;
				};
				bool vector::operator!=(const double &other) const {
					return *this!=other;
				};
#endif