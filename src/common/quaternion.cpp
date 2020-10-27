/*--------------------------------------------//
quaternion definition
This is used to simplify definition of quaternions
//--------------------------------------------*/
#ifndef QUATERNION
#define QUATERNION
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "quaternion.h"

	/*--------------------------------------------//
	Constructors
	//--------------------------------------------*/
		Quat::Quat(Angles ang){}
		Quat::Quat(Vec3 u, Vec3 v){
			float norm_u_norm_v = sqrt(u.Dot(u) * v.Dot(v));
			float real_part = norm_u_norm_v + u.Dot(v);
			Vec3 t;

			// If u and v are exactly opposite, rotate 180 degrees
			// around an arbitrary orthogonal axis. Axis normalisation
			// can happen later, when we normalise the quaternion.
			if(real_part < float(1.e-6f) * norm_u_norm_v){
				real_part = 0;
				t = abs(u.x) > abs(u.z) ? Vec3(-u.y, u.x, 0.0f) : Vec3(0.0f, -u.z, u.y);
			}else{
			// Otherwise, build quaternion the standard way.
				t = u.Cross(v);
			}

			*this = Quat(real_part, t.x, t.y, t.z).Normalize();
		}
		Quat::Quat(const Vec3& q){
			Vec3 c = cos(q * 0.5);
			Vec3 s = sin(q * 0.5);

			this->w = c.x * c.y * c.z + s.x * s.y * s.z;
			this->x = s.x * c.y * c.z - c.x * s.y * s.z;
			this->y = c.x * s.y * c.z + s.x * c.y * s.z;
			this->z = c.x * c.y * s.z - s.x * s.y * c.z;
		}

	/*--------------------------------------------//
	Cross of two quaternions
	//--------------------------------------------*/
		Quat Quat::Cross(Quat q2){
			Quat q1 = *this;
			return Quat(
				q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
				q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
				q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
				q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x);
		}

	/*--------------------------------------------//
	Dot of two quaternions
	//--------------------------------------------*/
		float Quat::Dot(Quat q){
		}

	/*--------------------------------------------//
	Length of the quaternion
	//--------------------------------------------*/
		float Quat::Length(){
			return sqrt(this->Dot(*this));
		}

	/*--------------------------------------------//
	Normalize the quaternion
	//--------------------------------------------*/
		Quat Quat::Normalize(){
			float len = Length();
			if(len <= 0) // Problem
				return Quat(1, 0, 0, 0);
			float oneOverLen = 1 / len;
			return Quat(w * oneOverLen, x * oneOverLen, y * oneOverLen, z * oneOverLen);
		}

	/*--------------------------------------------//
	Hamilton Product
	By my limited knowledge of quaternions, this is similar to the concept of multiplying two real numbers
	courtesy of: wikipedia.org/wiki/Quaternion#Hamilton_product
	//--------------------------------------------*/
		Quat Quat::Hamilton(Quat other){
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
			Quat res = Quat(b3, c3, d3, a3);//result quaternion
			return res;
		}
#endif
