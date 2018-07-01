/*--------------------------------------------//
Joint header
This is used in conjunction with bones to 
create a skeleton for actors
//--------------------------------------------*/
#ifndef JOINT_H
#define JOINT_H
class joint;

/*--------------------------------------------//
Pre Includes
//--------------------------------------------*/
	#include "bone.h"

class joint{
	private:
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			int childCnt;//how many children
			vector offset;//what is our vector offset from our parent bone
			vector wPos;//our stored world position
			bool wPosParity;//the bool parity property used by getPos
			
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			joint();

	public:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			bone* parent;//what bone are we parented to
			boneChild** children;//what bones are our children

		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			joint(bone* p, vector o);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~joint();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void addBone();
			void remBone(boneChild* &b);
			vector getPos(bool parity);
			void updateAcc();
			void updateVel();
			void updatePos();
};
#endif