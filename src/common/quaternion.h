/*--------------------------------------------//
Quaternion header
This is used for storing orientation without
gimbal lock
//--------------------------------------------*/
#ifndef QUATERNION_H
#define QUATERNION_H
class quaternion;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <stdlib.h>
	#include <math.h>
	#include "angles.h"

class quaternion{
	private:
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double x;
			double y;
			double z;
			double w;
			
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			quaternion();
			quaternion(angles ang);
			quaternion(double xi, double yi, double zi, double wi);

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void setAngles(double Pitch, double Yaw, double Roll);
			angles getAngles();
			double* toMatrix();
			quaternion Hamilton(quaternion other);
};
#endif