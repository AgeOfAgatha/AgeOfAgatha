/*--------------------------------------------//
Quaternion definition
This is used for storing orientation without
gimbal lock
//--------------------------------------------*/
#ifndef QUATERNION
#define QUATERNION
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "quaternion.h"

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		quaternion::quaternion(){
			this->setAngles(0,0,0);
		};

	/*--------------------------------------------//
	Overloaded constructor
	//--------------------------------------------*/
		quaternion::quaternion(angles ang){
			this->setAngles(ang.p, ang.y, ang.r);
		};
		quaternion::quaternion(double xi, double yi, double zi, double wi){
			x = xi;
			y = yi;
			z = zi;
			w = wi;
		};

	/*--------------------------------------------//
	Sets all euler angles and updates the quaternion
	//--------------------------------------------*/
		void quaternion::setAngles(double Pitch, double Yaw, double Roll){
			//Set the values, which came in degrees, to radians for C++ trig functions
			float rYaw = Yaw * PI / 180;
			float rPitch = Pitch * PI / 180;
			float rRoll = Roll * PI / 180;

			//Components
			float C1 = cos(rYaw / 2);
			float C2 = cos(rPitch / 2);
			float C3 = cos(rRoll / 2);
			float S1 = sin(rYaw / 2);
			float S2 = sin(rPitch / 2);
			float S3 = sin(rRoll / 2);

			//Create the final values
			w = ((C1 * C2 * C3) - (S1 * S2 * S3));
			x = (S1 * S2 * C3) + (C1 * C2 * S3);
			y = (S1 * C2 * C3) + (C1 * S2 * S3);
			z = (C1 * S2 * C3) - (S1 * C2 * S3);
		};

	/*--------------------------------------------//
	Converts back into euler angles
	//--------------------------------------------*/
		angles quaternion::getAngles(){
			double pitch, yaw, roll;
			// roll (x-axis rotation)
			double sinr = +2.0 * (w*x + y*z);
			double cosr = +1.0 - 2.0 * (x*x + y*y);
			roll = atan2(sinr, cosr);

			// pitch (y-axis rotation)
			double sinp = +2.0 * (w*y - z*x);
			if (fabs(sinp) >= 1)
				pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
			else
				pitch = asin(sinp);

			// yaw (z-axis rotation)
			double siny = +2.0 * (w*z + x*y);
			double cosy = +1.0 - 2.0 * (y*y + z*z);  
			yaw = atan2(siny, cosy);

			return angles(pitch, yaw, roll);
		};

	/*--------------------------------------------//
	Converts the quaternion into a matrix for
	applying a transformation
	//--------------------------------------------*/
		double* quaternion::toMatrix(){
			double* data = (double*) malloc(sizeof(double)*16);

			//Column 1
		    data[0] = (w*w) + (x*x) - (y*y) - (z*z);
		    data[1] = (2*x*y) + (2*w*z);
		    data[2] = (2*x*z) - (2*w*y);
		    data[3] = 0;
		    //Column 2
		    data[4] = (2*x*y) - (2*w*z);
		    data[5] = (w*w) - (x*x) + (y*y) - (z*z);
		    data[6] = (2*y*z) + (2*w*x);
		    data[7] = 0;
		    //Column 3
		    data[8] = (2*x*z) + (2*w*y);
		    data[9] = (2*y*z) - (2*w*x);
		    data[10] = (w*w) - (x*x) - (y*y) + (z*z);
		    data[11] = 0;
		    //Column 4
		    data[12] = 0;
		    data[13] = 0;
		    data[14] = 0;
		    data[15] = 1;

			return data;
		};

	/*--------------------------------------------//
	Hamilton Product
	By my limited knowledge of quaternions, this is similar to the concept of multiplying two real numbers
	courtesy of: wikipedia.org/wiki/Quaternion#Hamilton_product
	//--------------------------------------------*/
		quaternion quaternion::Hamilton(quaternion other){
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
			quaternion res = quaternion(b3, c3, d3, a3);//result quaternion
			return res;
		}
#endif