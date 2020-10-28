/*--------------------------------------------//
Mesh Header
This is our basic object
//--------------------------------------------*/
#ifndef MESH_H
#define MESH_H
class mesh;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../globals.h"

	#include "triangle.h"
	#include "../shaders/shader.h"
	#include "../common/Angles.h"
	#include "../common/sorting.h"
	#include "../common/vector.h"
	#include "../common/quaternion.h"

	#include <assert.h>
	#include <stdio.h>

class mesh{
	private:
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			mesh* parent;//our parent mesh
			mesh** childs;//mesh we are a parent to
			int childCnt;//how many children do we have
			int triCnt;//stores how many triangles are in this mesh
			triangle** tris;//stores the triangles that make up this mesh
			int nearbyCnt;//how many nearby objects do we have in the array
			mesh** nearby;//nearby objects from last collision test
			Angles euler;//stores the meshes euler Angles in relation to the world
			bool deuler = true;//stores a true or false for if the Angles have been changed since last update
			Quat quat;//stores our euler Angles in a quaternion to avoid gimbal lock.  This is what is actually used for calculations
			Angles angVel;//stores the angular velocity
			Angles angAcc;//stores the angular acceleration
			Angles angFrc;//stores the angular force (scale it by distance when you change this)
			Vec3 position;//stores the position within the world of this mesh
			Vec3 velocity;//store the positional velocity
			Vec3 acceleration;//store the positional acceleration
			Vec3 force;//store the positional force
			Vec3 COM;//center of mass (technically center of detail because it uses vertices)
			double radius;//maximum distance away from COM for the purposes of faster collision detection
			double mass;//amount of mass this object has
			int timer;//time since last movement, used for deciding if awake
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			mesh();

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~mesh();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void draw(Shader* shader);
			//Misc Attributes
				int getTimer();
				double getRadius();
				void setGlobalMat(char* path, int flags, int n);
			//Parent/Child
				mesh* getParent();
				void setParent(mesh* p);
				void addChild(mesh* c);
				void removeChild(mesh* c);
				mesh* getChild(int i);
				int getChildCnt();
			//Mass
				void setMass(double ma);
				double getMass();
			//Vertices
				void getVertices(vertex*** mesh, int* count);
			//Triangles
				void addTri(triangle* t);
				void addTri(vertex* &a, vertex* &b, vertex* &c, Vec2 st1, double b1, Vec2 st2, double b2, Vec2 st3, double b3);
				void remTri(triangle* &tri);
				int getTriangleCount();
				triangle* getTriangle(int i);
			//Nearby meshes
				void addNearby(mesh* &o);
				void remNearby(mesh* &o);
				mesh* getNearby(int i);
				int getNearbyCnt();
			//Force
				Vec3 getMaxDisplacement(Vec3 force);
				Vec3 getForce();
				void setForce(Vec3 frc);
				void setForce(double xfrc, double yfrc, double zfrc);
				void applyForce(Vec3 frc);
				void applyForce(double xfrc, double yfrc, double zfrc);
				Angles getAngFrc();
				void setAngfrc(Angles ang);
				void setAngfrc(double pitch, double yaw, double roll);
			//Acceleration
				Vec3 getAcceleration();
				void setAcceleration(Vec3 acc);
				void setAcceleration(double xacc, double yacc, double zacc);
				Angles getAngAcc();
				void setAngAcc(Angles ang);
				void setAngAcc(double pitch, double yaw, double roll);
				void updateAcc();
			//Velocity
				Vec3 getVelocity();
				void setVelocity(Vec3 vel);
				void setVelocity(double xvel, double yvel, double zvel);
				Angles getAngVel();
				void setAngVel(Angles ang);
				void setAngVel(double pitch, double yaw, double roll);
				void updateVel();
			//Position
				Vec3 getPosition();
				void setPosition(Vec3 pos);
				void setPosition(double xpos, double ypos, double zpos);
				void updatePos();
			//Angles
				Angles getAngles();
				void setAngles(Angles ang);
				void setAngles(double pitch, double yaw, double roll);
};
#endif
