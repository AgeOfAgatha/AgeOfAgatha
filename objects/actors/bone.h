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
	#include "skeleton.h"
	#include "joint.h"

class bone{
	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			joint** children;//the joints that are childs of the bone
			int childCnt;//how many joints are on this bone
			vector wPos;//the stored world position
			bool wPosParity;//the stored parity property to decide if to recalculate the wPos
			vector dir;//the stored direction of the bone
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
			void addJoint(vector origin);
			void remJoint(joint* &b);
			void updateAcc();
			void updateVel();
			void updatePos();
			virtual vector getPos(bool parity){return vector();}
			virtual vector getDirection(bool parity){return vector();}
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
			vector getPos(bool parity);
			vector getDirection(bool parity);
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
			vector offset;//our offset from the parent joint
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
			vector getPos(bool parity);
			vector getDirection(bool parity);
			angles getAng();
			void setAng(angles a);
};
#endif