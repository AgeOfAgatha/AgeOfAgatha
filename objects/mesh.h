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
	#include <stdio.h>
	#if defined(__APPLE__)
		#include <GLUT/glut.h>
	#else
		#include <GL/glut.h>
	#endif
	#include "triangle.h"
	#include "../common/quaternion.h"

class mesh{
	private:
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			int triCnt;//stores how many triangles are in this mesh
			triangle** tris;//stores the triangles that make up this mesh
			int vertsCnt;//stores how many vertices are being used by the mesh
			vertex** verts;//stores a list of vertices being used by this mesh
			int nearbyCnt;//how many nearby objects do we have in the array
			mesh** nearby;//nearby objects from last collision test
			angles euler;//stores the meshes euler angles in relation to the world
			bool deuler = true;//stores a true or false for if the angles have been changed since last update
			quaternion quat;//stores our euler angles in a quaternion to avoid gimbal lock.  This is what is actually used for calculations
			angles angVel;//stores the angular velocity
			angles angAcc;//stores the angular acceleration
			angles angFrc;//stores the angular force (scale it by distance when you change this)
			vector position;//stores the position within the world of this mesh
			vector velocity;//store the positional velocity
			vector acceleration;//store the positional acceleration
			vector force;//store the positional force
			vector COM;//center of mass (technically center of detail because it uses vertices)
			double radius;//maximum distance away from COM for the purposes of faster collision detection
			double mass;//amount of mass this object has
			int timer;//time since last movement, used for deciding if awake

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void addVertex(vertex* &v);
			void remVertex(vertex* &v);
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
			void addTri(vertex* &a, vertex* &b, vertex* &c);
			void remTri(triangle &tri);
			void addNearby(mesh* &o);
			void remNearby(mesh* &o);
			mesh* getNearby(int i);
			int getNearbyCnt();
			int getTimer();
			vector getMaxDisplacement(vector force);
			int getVertexCount();
			vertex* getVertex(int i);
			int getTriangleCount();
			triangle* getTriangle(int i);
			double getRadius();
			angles getAngles();
			void setAngles(angles ang);
			void setAngles(double pitch, double yaw, double roll);
			angles getAngVel();
			void setAngVel(angles ang);
			void setAngVel(double pitch, double yaw, double roll);
			angles getAngAcc();
			void setAngAcc(angles ang);
			void setAngAcc(double pitch, double yaw, double roll);
			angles getAngFrc();
			void setAngfrc(angles ang);
			void setAngfrc(double pitch, double yaw, double roll);
			vector getPosition();
			void setPosition(vector pos);
			void setPosition(double xpos, double ypos, double zpos);
			vector getVelocity();
			void setVelocity(vector vel);
			void setVelocity(double xvel, double yvel, double zvel);
			vector getAcceleration();
			void setAcceleration(vector acc);
			void setAcceleration(double xacc, double yacc, double zacc);
			vector getForce();
			void setForce(vector frc);
			void setForce(double xfrc, double yfrc, double zfrc);
			void applyForce(vector frc);
			void applyForce(double xfrc, double yfrc, double zfrc);
			double getMass();
			void setMass(double ma);
			void draw();
			void updateAcc();
			void updateVel();
			void updatePos();
};
#endif