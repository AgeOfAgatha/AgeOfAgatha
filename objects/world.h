/*--------------------------------------------//
World definition
This is where the simulation is controlled
//--------------------------------------------*/
#ifndef WORLD_H
#define WORLD_H
class world;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "mesh.h"
	#include "../common/sorting.h"

class world{
	private:
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			//set by external at time of creation
			int timestep;//how often is this world updated
			int timeout;//how many iterations can an object not move before it is considered asleep
			double vertexrad;//used for implicit function tests, determines how large of a collision sphere the vertex is considered as
			double gravObjMass;//the mass value above which will be simulated as an object applying gravity to everyone else
			double gravConst;//multiplier for gravity within this 'world'.  works just like the real life gravity constant
			double frictionDist;//used to 'feather' objects during broad phase collision detection
			double frictionConst;//multiplier for friciton within this 'world'
			double deformConst;//multiplier for all deformation within this 'world'
			//used to keep track of simulation specifics
			int objCnt;
			mesh** objects;
			int gravObjCnt;
			mesh** gravObj;

		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			world();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void addGravObj(mesh* &obj);
			void remGravObj(mesh* &obj);
			bool implicitTest(vector pos1, vector pos2, double rad1, double rad2, vector vel1, vector vel2);
			bool isAwake(mesh* &obj);
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			world(int ts, int to, double vr, double gom, double gc, double fd, double fc, double dc);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~world();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void addMesh(mesh* &obj);
			void remMesh(mesh* &obj);
			int getTimeStep();
			int getObjectCount();
			mesh* getObject(int i);
			void draw();
			void applyGravity(mesh* &obj);
			void applyFriction(mesh* &obj);
			void update();
			void testBpCollision(mesh* &obj, int i);
			void testNpCollision(mesh* &obj, mesh** &filter, int &filterCnt);
};
#endif