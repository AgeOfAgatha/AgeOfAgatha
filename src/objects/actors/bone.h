/*--------------------------------------------//
Bone header
This is used in conjunction with joints to 
create a skeleton for actors
//--------------------------------------------*/
#ifndef BONE_H
#define BONE_H
class bone;
class boneParent;
class boneChild;

/*--------------------------------------------//
Pre Includes
//--------------------------------------------*/
	#include <glew.h>
	#include <freeglut.h>
	#include "../../../deps/glm/glm.hpp"

	#include "../../common/quaternion.h"
	#include "../../common/vector.h"
	#include "skeleton.h"
	#include "joint.h"

class bone{
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			joint** children;//the joints that are childs of the bone
			int childCnt;//how many joints are on this bone
			vec3 wPos;//the stored world position
			bool wPosParity;//the stored parity property to decide if to recalculate the wPos
			vec3 dir;//the stored direction of the bone
			bool dirParity;//the stored parity property to decide if to recalculate the direction

		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			bone();

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			virtual ~bone(){}

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void addJoint(vec3 origin);
			void remJoint(joint* &b);
			void updateAcc();
			void updateVel();
			void updatePos();
			virtual vec3 getPos(bool parity){return vec3();}
			virtual vec3 getDirection(bool parity){return vec3();}
			virtual angles getAng(){return angles();}
			virtual void setAng(angles a){}
};

class boneParent:public bone{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			skeleton* parent;//what mesh does this skeleton belong to

		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			boneParent();

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~boneParent();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			vec3 getPos(bool parity);
			vec3 getDirection(bool parity);
			angles getAng();
			void setAng(angles a);
};

class boneChild:public bone{
	private:
	protected:
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			joint* parent;//the parent joint which connects to another bone and defines where we are in relation to that bone
			vec3 offset;//our offset from the parent joint
			angles ang;//our orientation angle from the parent joint
			angles angVel;//the velocity our angles are changing at
			angles angAcc;//the rate our angular velocity is changing at
			angles angFrc;//what angular forces are being applied (prescaled by distance)

		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			boneChild();

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~boneChild();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void updateAcc();
			void updateVel();
			void updatePos();
			vec3 getPos(bool parity);
			vec3 getDirection(bool parity);
			angles getAng();
			void setAng(angles a);
};
#endif