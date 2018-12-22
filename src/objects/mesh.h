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
	#include "../../deps/gl/glew.h"
	#include "../../deps/gl/freeglut.h"
	#include "../../deps/glm/glm.hpp"

	#include "triangle.h"
	#include "../shader/shader.h"
	#include "../common/angles.h"
	#include "../common/sorting.h"
	#include "../common/vector.h"
	#include "../common/quaternion.h"
	#include "../globals.h"

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
			angles euler;//stores the meshes euler angles in relation to the world
			bool deuler = true;//stores a true or false for if the angles have been changed since last update
			glm::quat quat;//stores our euler angles in a quaternion to avoid gimbal lock.  This is what is actually used for calculations
			angles angVel;//stores the angular velocity
			angles angAcc;//stores the angular acceleration
			angles angFrc;//stores the angular force (scale it by distance when you change this)
			vec3 position;//stores the position within the world of this mesh
			vec3 velocity;//store the positional velocity
			vec3 acceleration;//store the positional acceleration
			vec3 force;//store the positional force
			vec3 COM;//center of mass (technically center of detail because it uses vertices)
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
				void addTri(vertex* &a, vertex* &b, vertex* &c, vec2 st1, double b1, vec2 st2, double b2, vec2 st3, double b3);
				void remTri(triangle* &tri);
				int getTriangleCount();
				triangle* getTriangle(int i);
			//Nearby meshes
				void addNearby(mesh* &o);
				void remNearby(mesh* &o);
				mesh* getNearby(int i);
				int getNearbyCnt();
			//Force
				vec3 getMaxDisplacement(vec3 force);
				vec3 getForce();
				void setForce(vec3 frc);
				void setForce(double xfrc, double yfrc, double zfrc);
				void applyForce(vec3 frc);
				void applyForce(double xfrc, double yfrc, double zfrc);
				angles getAngFrc();
				void setAngfrc(angles ang);
				void setAngfrc(double pitch, double yaw, double roll);
			//Acceleration
				vec3 getAcceleration();
				void setAcceleration(vec3 acc);
				void setAcceleration(double xacc, double yacc, double zacc);
				angles getAngAcc();
				void setAngAcc(angles ang);
				void setAngAcc(double pitch, double yaw, double roll);
				void updateAcc();
			//Velocity
				vec3 getVelocity();
				void setVelocity(vec3 vel);
				void setVelocity(double xvel, double yvel, double zvel);
				angles getAngVel();
				void setAngVel(angles ang);
				void setAngVel(double pitch, double yaw, double roll);
				void updateVel();
			//Position
				vec3 getPosition();
				void setPosition(vec3 pos);
				void setPosition(double xpos, double ypos, double zpos);
				void updatePos();
			//Angles
				angles getAngles();
				void setAngles(angles ang);
				void setAngles(double pitch, double yaw, double roll);
};
#endif