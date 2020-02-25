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
	Constructors
	//--------------------------------------------*/
		vec2::vec2(const vec3 &a){this->x = a.x; this->y = a.y;}
		vec2::vec2(const vec4 &a){this->x = a.x; this->y = a.y;}
		vec3::vec3(const vec4 &a){this->x = a.x; this->y = a.y; this->z = a.z;}
	/*--------------------------------------------//
	Normalize the vector
	makes the sum of each component equal to one
	//--------------------------------------------*/
		void vec2::normalize(){
			int a = abs(this->x)+abs(this->y);
			this->x = this->x/a;
			this->y = this->x/y;
		}
		void vec3::normalize(){
			int a = abs(this->x)+abs(this->y)+abs(this->z);
			this->x = this->x/a;
			this->y = this->y/a;
			this->z = this->z/a;
		}
		void vec4::normalize(){
			int a = abs(this->x)+abs(this->y)+abs(this->z)+abs(this->w);
			this->x = this->x/a;
			this->y = this->y/a;
			this->z = this->z/a;
			this->w = this->w/a;
		}

	/*--------------------------------------------//
	Length of a vector
	//--------------------------------------------*/
		double vec2::length() const{
			return (sqrt( pow(this->x, 2) + pow(this->y, 2) ));
		}
		double vec3::length() const{
			return (sqrt( pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) ));
		}
		double vec4::length() const{
			return (sqrt( pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2) ));
		}

	/*--------------------------------------------//
	Distance between two points
	//--------------------------------------------*/
		double vec2::distance(vec2 other) const{
			return (sqrt( pow(this->x - other.x, 2) + pow(this->y - other.y, 2) ));
		}
		double vec3::distance(vec3 other) const{
			return (sqrt( pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2) ));
		}
		double vec4::distance(vec4 other) const{
			return (sqrt( pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2) + pow(this->w - other.w, 2) ));
		}

	/*--------------------------------------------//
	dot product of two vectors
	//--------------------------------------------*/
		double vec2::dot(vec2 other) const{
			return (this->x*other.x + this->y*other.y);
		}
		double vec3::dot(vec3 other) const{
			return (this->x*other.x + this->y*other.y + this->z*other.z);
		}
		double vec4::dot(vec4 other) const{
			return (this->x*other.x + this->y*other.y + this->z*other.z + this->w*other.w);
		}
#endif