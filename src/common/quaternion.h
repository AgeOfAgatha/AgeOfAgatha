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
	class Quat:public glm::quat{
		private:
		protected:
		public:
			/*--------------------------------------------//
			Constructors
			//--------------------------------------------*/
				Quat():glm::quat(){}
				Quat(glm::vec3 vec):glm::quat(vec){}
				Quat(Vec3 vec):glm::quat(glm::vec3(vec[0], vec[1], vec[2])){}
				Quat(Angles ang):glm::quat(glm::vec3(ang.p, ang.y, ang.r)){}
				Quat(double w, double x, double y, double z):glm::quat(w,x,y,z){}
			/*--------------------------------------------//
			Functions
			//--------------------------------------------*/
				Quat Hamilton(Quat other);
	};
#endif