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
	#ifndef GLEW_STATIC
    #define GLEW_STATIC
	#include "../../deps/gl/glew.h"
	#include "../../deps/gl/glut.h"
	#endif
	
	#include "texture.h"
	#include "triangle.h"
	#include "../common/vector.h"
	#include "../common/quaternion.h"

	#include <stdio.h>

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
			vec3 position;//stores the position within the world of this mesh
			vec3 velocity;//store the positional velocity
			vec3 acceleration;//store the positional acceleration
			vec3 force;//store the positional force
			vec3 COM;//center of mass (technically center of detail because it uses vertices)
			double radius;//maximum distance away from COM for the purposes of faster collision detection
			double mass;//amount of mass this object has
			int timer;//time since last movement, used for deciding if awake
			texture* material;//stores the class object for our texture

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
			void addMat(char* path, int flags);
			double* getMeshArray();
			void addTri(vertex* &a, vertex* &b, vertex* &c);
			void remTri(triangle &tri);
			void addNearby(mesh* &o);
			void remNearby(mesh* &o);
			mesh* getNearby(int i);
			int getNearbyCnt();
			int getTimer();
			vec3 getMaxDisplacement(vec3 force);
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
			vec3 getPosition();
			void setPosition(vec3 pos);
			void setPosition(double xpos, double ypos, double zpos);
			vec3 getVelocity();
			void setVelocity(vec3 vel);
			void setVelocity(double xvel, double yvel, double zvel);
			vec3 getAcceleration();
			void setAcceleration(vec3 acc);
			void setAcceleration(double xacc, double yacc, double zacc);
			vec3 getForce();
			void setForce(vec3 frc);
			void setForce(double xfrc, double yfrc, double zfrc);
			void applyForce(vec3 frc);
			void applyForce(double xfrc, double yfrc, double zfrc);
			double getMass();
			void setMass(double ma);
			void draw();
			void updateAcc();
			void updateVel();
			void updatePos();
};
#endif