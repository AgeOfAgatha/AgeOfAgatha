/*--------------------------------------------//
quaternion header
simplifies quaternion use
//--------------------------------------------*/
#ifndef QUATERNION_H
#define QUATERNION_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../../deps/glm/glm.hpp"
	#define GLM_ENABLE_EXPERIMENTAL
	#include "../../deps/glm/gtx/quaternion.hpp"

	#include "vector.h"
	#include "angles.h"

/*--------------------------------------------//
Classes
//--------------------------------------------*/
	class quat:public glm::quat{
		private:
		protected:
		public:
			/*--------------------------------------------//
			Constructors
			//--------------------------------------------*/
				quat():glm::quat(){}
				quat(glm::vec3 vec):glm::quat(vec){}
				quat(vec3 vec):glm::quat(glm::vec3(vec[0], vec[1], vec[2])){}
				quat(angles ang):glm::quat(glm::vec3(ang.p, ang.y, ang.r)){}
				quat(double w, double x, double y, double z):glm::quat(w,x,y,z){}
			/*--------------------------------------------//
			Hamilton Product
			By my limited knowledge of quaternions, this is similar to the concept of multiplying two real numbers
			courtesy of: wikipedia.org/wiki/Quaternion#Hamilton_product
			//--------------------------------------------*/
				quat Hamilton(quat other){
					//first translating this into variables that match with hamilton product
					double a1 = this->w;
					double b1 = this->x;
					double c1 = this->y;
					double d1 = this->z;

					double a2 = other.w;
					double b2 = other.x;
					double c2 = other.y;
					double d2 = other.z;

					//now we construct the components for the resulting quaternion
					double a3 = a1*a2 - b1*b2 - c1*c2 - d1*d2;
					double b3 = a1*b2 + b1*a2 + c1*d2 - d1*c2;
					double c3 = a1*c2 - b1*d2 + c1*a2 + d1*b2;
					double d3 = a1*d2 + b1*c2 - c1*b2 + d1*a2;				

					//constructor goes in order of x,y,z,w
					quat res = quat(b3, c3, d3, a3);//result quaternion
					return res;
				}
	};
#endif