/*--------------------------------------------//
Skeleton header
defines how a mesh moves and interacts for a
actor.  Uses bones and joints.
//--------------------------------------------*/
#ifndef SKELETON_H
#define SKELETON_H
class skeleton;

/*--------------------------------------------//
Pre Includes
//--------------------------------------------*/
	#include "../../../deps/gl/glut.h"

	#include "../mesh.h"
	#include "bone.h"
	#include "joint.h"
	#include "boneVertex.h"

class skeleton:public mesh{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			bone* root;//stores the root bone
			bool parity;//stores the current parity flag passed during position calculations

		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			skeleton();

		/*--------------------------------------------//
		Functions.
		//--------------------------------------------*/
			void draw();
			void updateAcc();
			void updateVel();
			void updatePos();
};
#endif