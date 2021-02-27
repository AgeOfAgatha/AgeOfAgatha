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
	#include "../globals.h"
	#include "../common/vector.h"
	#include "../common/sorting.h"
	#include "../shaders/shader.h"
	#include "light/spotlight.h"
	#include "light/direclight.h"
	#include "texture.h"
	#include "mesh.h"

	#include <stdlib.h>
	#include <string.h>
	#include <vector>

class world{
	private:
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
			int objCnt;//standard mesh objects
			mesh** objects;
			int transCnt;//transparent meshes
			mesh** transparents;
			int dlightCnt;//directional lights
			direclight** dlights;
			int slightCnt;//spot lights
			spotlight** slights;
			int gravObjCnt;//objects applying gravity
			mesh** gravObj;

			//init shaders and buffers
			Shader *DepthDirecShader, *DepthSpotShader, *ShadowNullMapping, *ShadowDirecMapping, *ShadowSpotMapping;
		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			//initialization
				void ShaderInit();
			//misc
				bool implicitTest(Vec3 pos1, Vec3 pos2, double radi1, double radi2, Vec3 vel1, Vec3 vel2);
				bool isAwake(mesh* &obj);

	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			world();
			world(int ts, int to, double vr, double gom, double gc, double fd, double fc, double dc);

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~world();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			//regular objects
				bool loadObj(char* objPath, char* mtlPath, mesh** parent);
				void addMesh(mesh* &obj);
				void remMesh(mesh* &obj);
				mesh* getObject(int i);
				int getObjectCount();
				void objectSort(Vec4 camera);
			//gravity objects
				void addGravObj(mesh* &obj);
				void remGravObj(mesh* &obj);
			//transparents
				void addTrans(mesh* &obj);
				void remTrans(mesh* &obj);
				mesh* getTrans(int i);
				int getTransCount();
			//lights
				//directional lights
					void addDLight(direclight* &l);
					void remDLight(direclight* &l);
					direclight* getDLight(int i);
					int getDLightCount();
				//spot lights
					void addSLight(spotlight* &l);
					void remSLight(spotlight* &l);
					spotlight* getSLight(int i);
					int getSLightCount();
			//misc
				int getTimeStep();
			//rendering
				void draw(Mat4 projection, Mat4 view, Vec4 camera, GLint currWindowSize[2]);
			//Physics
				void update();
				void applyGravity(mesh* &obj);
				void applyFriction(mesh* &obj);
				void testBpCollision(mesh* &obj, int i);
				void testNpCollision(mesh* &obj, mesh** &filter, int &filterCnt);
};
#endif
