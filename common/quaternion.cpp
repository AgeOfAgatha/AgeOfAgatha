/*--------------------------------------------//
Quaternion definition
This is used for storing orientation without
gimbal lock
//--------------------------------------------*/
#ifndef QUATERNION
#define QUATERNION

#ifndef ANGLES
#include "angles.cpp"
#endif

class quaternion{
	private:
	public:
		double x;
		double y;
		double z;
		double w;
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		quaternion(){
			this->setAngles(0,0,0);
		};

		/*--------------------------------------------//
		Overloaded constructor
		//--------------------------------------------*/
		quaternion(angles ang){
			this->setAngles(ang.p, ang.y, ang.r);
		};

		/*--------------------------------------------//
		Sets all euler angles and updates the quaternion
		//--------------------------------------------*/
		void setAngles(double Pitch, double Yaw, double Roll){
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
		Converts the quaternion into a matrix for
		applying a transformation
		//--------------------------------------------*/
		double* toMatrix(){
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
};
#endif