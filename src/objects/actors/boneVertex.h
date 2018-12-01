/*--------------------------------------------//
BoneVertex Header
This is a special kind of vertex which ties a
vertex to a bone.
//--------------------------------------------*/
#ifndef BONEVERTEX_H
#define BONEVERTEX_H
class boneVertex;

/*--------------------------------------------//
Pre Includes
//--------------------------------------------*/
	#include "../../common/vector.h"
	#include "../vertex.h"
	#include "bone.h"

class boneVertex:public vertex{
	private:
	protected:	
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			bone* parent;//the bone we are parented to
			vertex offset;//our offset from bones position at parenting
			vec3 wPos;//our stored world position
			bool wPosParity;//parity flag for world position used in get position function

		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			boneVertex();
			boneVertex(double xi, double yi, double zi);

	public:	
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			boneVertex(bone* p, double xi, double yi, double zi);

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			bone* getParent();
			void setParent(bone* p);
			vec3 getPos(bool parity);
			double x();
			double y();
			double z();
			void x(double xi);
			void y(double yi);
			void z(double zi);
			void draw(bool parity);
};
#endif