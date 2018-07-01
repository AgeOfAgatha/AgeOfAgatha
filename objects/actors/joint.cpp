/*--------------------------------------------//
Joint definition
This is used in conjunction with bones to 
create a skeleton for actors
//--------------------------------------------*/
#ifndef JOINT
#define JOINT
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "joint.h"

	/*--------------------------------------------//
	Default Constructor
	//--------------------------------------------*/
		joint::joint(){
			parent = NULL;
			offset = vector();
		}

	/*--------------------------------------------//
	Overloaded Constructor
	//--------------------------------------------*/
		joint::joint(bone* p, vector o){
			parent = p;
			offset = o;
		}

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		joint::~joint(){
			for (int i = 0; i < childCnt; i++){
				delete children[i];
			}
		}

	/*--------------------------------------------//
	Add a bone as a child
	//--------------------------------------------*/
		void joint::addBone(){
			boneChild** newChildren = (boneChild**) realloc(children, sizeof(boneChild*)*(childCnt+1));

			if (newChildren!=NULL) {
				children = newChildren;

				children[childCnt] = new boneChild();
				childCnt++;
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		};

	/*--------------------------------------------//
	Remove a bone as a child
	//--------------------------------------------*/
		void joint::remBone(boneChild* &b){
			for (int i = 0; i < childCnt; i++){
				if (b == children[i]){
					//move last object to here
					children[i] = children[childCnt-1];
					//trim last object
					boneChild** newChildren = (boneChild**) realloc(children, sizeof(boneChild*)*(childCnt-1));
					//check if memory was allocated
					if (newChildren!=NULL){
						delete b;
						children = newChildren;
						childCnt--;
					}else{
						puts ("Error (re)allocating memory");
						exit (1);
					}
					return;
				}
			}
		};

	/*--------------------------------------------//
	Get World Position
	takes a bool for parity
	this decides whether to recalculate the wPos
	//--------------------------------------------*/
		vector joint::getPos(bool parity){
			if (wPosParity != parity){
				vector wPos = offset + parent->getPos(parity);
				wPosParity = parity;
			}
			return  wPos;
		}

	/*--------------------------------------------//
	Update function
	//--------------------------------------------*/
		void joint::updateAcc(){
			for (int i = 0; i < childCnt; i++){
				children[i]->updateAcc();
			}
		}
		void joint::updateVel(){
			for (int i = 0; i < childCnt; i++){
				children[i]->updateVel();
			}
		}
		void joint::updatePos(){
			for (int i = 0; i < childCnt; i++){
				children[i]->updatePos();
			}
		}
#endif