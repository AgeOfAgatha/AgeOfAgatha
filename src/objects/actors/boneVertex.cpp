/*--------------------------------------------//
BoneVertex definition
This is a special kind of vertex which ties a
vertex to a bone.
//--------------------------------------------*/
#ifndef BONEVERTEX
#define BONEVERTEX
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "boneVertex.h"

	/*--------------------------------------------//
	Constructors
	//--------------------------------------------*/
		boneVertex::boneVertex():vertex(){
			parent = NULL;
			offset = vec3();
		}
		boneVertex::boneVertex(double a, double b, double c):vertex(a,b,c){
			parent = NULL;
			offset = vec3();
		}
		boneVertex::boneVertex(bone* p, double a, double b, double c):boneVertex(a, b, c){
			setParent(p);	
		}

	/*--------------------------------------------//
	Get Parent Bone
	//--------------------------------------------*/
		bone* boneVertex::getParent(){
			return parent;
		}

	/*--------------------------------------------//
	Set Parent Bone
	//--------------------------------------------*/
		void boneVertex::setParent(bone* par){
			parent = par;
			vec3 pos1 = parent->getPos(wPosParity);
			angles ang1 = parent->getAng() * -1;//use negative angle to get offset from bones position as if it had no rotation

			//create quaternions
			quaternion p = quaternion(0, x(), y(), z());
			quaternion r = quaternion(ang1);//rotation quaternion
			quaternion t = quaternion(-r.x, -r.y, -r.z, r.w);//basically r'

			//now we have enough to get a new quaternion q which will be p rotated using hamilton product
			quaternion q = t.Hamilton(r.Hamilton(p));

			//at this point q is our vertex's position rotated by the negative angle of the bone
			//therefore our offset would be the difference between our position and the bones position
			offset = vec3(q.x, q.y, q.z) - pos1;
		}

	/*--------------------------------------------//
	Get World Positions
	takes a based bool for parity
	this parity should be flipped each subsequent 
	call or the returned position will not be 
	recalculated
	//--------------------------------------------*/
		vec3 boneVertex::getPos(bool parity){
			if (parity != wPosParity){
				vec3 pos1 = parent->getPos(parity);//find parents position
				vec3 dir1 = parent->getDirection(parity);//find what direction bone is pointing
				angles ang1 = parent->getAng();//find angles of bone

				//now rotate our position to align with bone without accounting for how close to base of bone we are
				//create quaternions
				quaternion p = quaternion(0, offset.x(), offset.y(), offset.z());
				quaternion r = quaternion(ang1);//rotation quaternion
				quaternion t = quaternion(-r.x, -r.y, -r.z, r.w);//basically r'

				//now we have enough to get a new quaternion q which will be p rotated using hamilton product
				quaternion q = t.Hamilton(r.Hamilton(p));

				//now find the world position by adding the world position of the bone
				vec3 pos2 = vec3(q.x, q.y, q.z) + pos1;

				//now find out how in line we are with the bone.  IE something along the beginning of the bone does not move as much
				double mul = 1 - dir1.dot(pos2 - pos1)/2;

				angles ang2 = ang1 * mul;

				//recalculate position adjusted by quaternions
				r = quaternion(ang2);
				t = quaternion(-r.x, -r.y, -r.z, r.w);
				q = t.Hamilton(r.Hamilton(p));

				wPos = vec3(q.x, q.y, q.z) + pos1;
				wPosParity = parity;
			}
			return wPos;
		}
		double boneVertex::x(){
			return getPos(!wPosParity).x();
		}
		double boneVertex::y(){
			return getPos(!wPosParity).y();
		}
		double boneVertex::z(){
			return getPos(!wPosParity).z();
		}

	/*--------------------------------------------//
	Set World Position
	//--------------------------------------------*/
		void boneVertex::x(double a){
			pos[0] = a;
			setParent(parent);//will recalculate offset for us
		}
		void boneVertex::y(double b){
			pos[1] = b;
			setParent(parent);//will recalculate offset for us
		}
		void boneVertex::z(double c){
			pos[2] = c;
			setParent(parent);//will recalculate offset for us
		}

	/*--------------------------------------------//
	Draw
	//--------------------------------------------*/
		void boneVertex::draw(bool parity){
			getPos(parity);//update stored wPos if parity changed
		    glVertex3d(wPos.x(), wPos.y(), wPos.z());
		}
#endif