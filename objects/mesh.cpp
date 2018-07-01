/*--------------------------------------------//
Mesh definition
This is our basic object
//--------------------------------------------*/
#ifndef MESH
#define MESH
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "mesh.h"

	/*--------------------------------------------//
	Attempts to add a vertex to our vertex list
	//--------------------------------------------*/
		void mesh::addVertex(vertex* &v){
			//check if vertex is already in vertex list
			for (int i = 0; i < vertsCnt; i++){
				if (verts[i] == v){
					return;
				}
			}
			//if not add to list and update Center of mass
			vertex** newverts = (vertex**) realloc(verts, sizeof(vertex*)*(vertsCnt+1));
			//check if memory allocated
			if (newverts!=NULL) {
				//add vertex
				verts = newverts;

				verts[vertsCnt] = v;
				vertsCnt++;
				//update center of mass
				COM.x(COM.x() + v->x()/vertsCnt);
				COM.y(COM.y() + v->y()/vertsCnt);
				COM.z(COM.z() + v->z()/vertsCnt);

				//find largest radius
				for (int i = 0; i < vertsCnt; ++i){
					double dx = COM.x() - verts[i]->x();
					double dy = COM.y() - verts[i]->y();
					double dz = COM.z() - verts[i]->z();
					double dr = sqrt(dx*dx + dy*dy + dz*dz);
					if (dr > radius){
						radius = dr;
					}
				}
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		};

	/*--------------------------------------------//
	Attempts to remove a vertex from our vertex list
	//--------------------------------------------*/
		void mesh::remVertex(vertex* &v){
			for (int i = 0; i < vertsCnt; i++){
				if (*v == *(verts[i])){
					//found vertex... verify if vertex is used by other triangles in current mesh
					int matches = 0;
					for (int j = 0; j < triCnt; j++){
						for (int k = 0; k < 3; k++){
							//check if vertex matches
							if (*v == *(tris[j]->getVertex(k))){
								matches++;
								if (matches > 1){
									return;//too many matches to remove vertex from list
								}
							}
						}
					}
					//move last object to here
					verts[i] = verts[vertsCnt-1];
					//trim last object
					vertex** newverts = (vertex**) realloc(verts, sizeof(vertex*)*(vertsCnt-1));
					//check if memory was allocated
					if (newverts!=NULL) {
						verts = newverts;
						//update center of mass
						COM.x(COM.x() - v->x()/vertsCnt);
						COM.y(COM.y() - v->y()/vertsCnt);
						COM.z(COM.z() - v->z()/vertsCnt);
						vertsCnt--;
					}else{
						puts ("Error (re)allocating memory");
						exit (1);
					}
					return;
				}
			}
		};

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		mesh::mesh(){
			triCnt = 0;
			tris = NULL;
			vertsCnt = 0;
			verts = NULL;
			nearbyCnt = 0;
			nearby = NULL;

			COM = vertex(0,0,0);
			
			position = vertex(0,0,0);
			velocity = vertex(0,0,0);
			acceleration = vertex(0,0,0);
			force = vertex(0,0,0);

			euler = angles(0.0, 0.0, 0.0);
			angVel = angles(0.0, 0.0, 0.0);
			angAcc = angles(0.0, 0.0, 0.0);
			angFrc = angles(0.0, 0.0, 0.0);
			quat = quaternion(euler);

			timer = 0;

			mass = 1;
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		mesh::~mesh(){
			for (int i = 0; i < this->getTriangleCount(); i++){
				free ((triangle*)(this->getTriangle(i)));
			}
		};

	/*--------------------------------------------//
	Add a triangle to the mesh by specifying points
	//--------------------------------------------*/
		void mesh::addTri(vertex* &a, vertex* &b, vertex* &c){
			triangle** newtris = (triangle**) realloc(tris, sizeof(triangle*)*(triCnt+1));

			if (newtris!=NULL) {
				tris = newtris;

				addVertex(a);
				addVertex(b);
				addVertex(c);
				tris[triCnt] = new triangle(a, b, c);
				triCnt++;
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		};

	/*--------------------------------------------//
	Removes the passed triangle object if found
	//--------------------------------------------*/
		void mesh::remTri(triangle &tri){
			for (int i = 0; i < triCnt; i++){
				if (tri == *(tris[i])){
					//move last object to here
					tris[i] = tris[triCnt-1];
					//trim last object
					triangle** newtris = (triangle**) realloc(tris, sizeof(triangle*)*(triCnt-1));
					//check if memory was allocated
					if (newtris!=NULL) {
						vertex* a = tri.getVertex(0);
						vertex* b = tri.getVertex(1);
						vertex* c = tri.getVertex(2);
						remVertex(a);
						remVertex(b);
						remVertex(c);
						tris = newtris;
						triCnt--;
					}else{
						puts ("Error (re)allocating memory");
						exit (1);
					}
					return;
				}
			}
		};

	/*--------------------------------------------//
	Attempts to add a vertex to our vertex list
	//--------------------------------------------*/
		void mesh::addNearby(mesh* &o){
			//check if vertex is already in vertex list
			for (int i = 0; i < nearbyCnt; i++){
				if (nearby[i] == o){
					return;
				}
			}
			//if not add to list and update Center of mass
			mesh** newnearby = (mesh**) realloc(nearby, sizeof(mesh*)*(nearbyCnt+1));
			//check if memory allocated
			if (newnearby!=NULL) {
				nearby = newnearby;

				nearby[nearbyCnt] = o;
				nearbyCnt++;
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		};

	/*--------------------------------------------//
	Attempts to remove a vertex from our vertex list
	//--------------------------------------------*/
		void mesh::remNearby(mesh* &o){
			for (int i = 0; i < nearbyCnt; i++){
				if (o == (nearby[i])){
					//move last object to here
					nearby[i] = nearby[nearbyCnt-1];
					//trim last object
					mesh** newnearby = (mesh**) realloc(nearby, sizeof(mesh*)*(nearbyCnt-1));
					//check if memory was allocated
					if (newnearby!=NULL) {
						nearby = newnearby;
						nearbyCnt--;
					}else{
						puts ("Error (re)allocating memory");
						exit (1);
					}
					return;
				}
			}
		};

	/*--------------------------------------------//
	Returns the nearby object at the index
	//--------------------------------------------*/
		mesh* mesh::getNearby(int i){
			return nearby[i];
		};

	/*--------------------------------------------//
	Returns the number of nearby objects
	//--------------------------------------------*/
		int mesh::getNearbyCnt(){
			return nearbyCnt;
		};

	/*--------------------------------------------//
	Returns the objects last movement timer
	//--------------------------------------------*/
		int mesh::getTimer(){
			return timer;
		};

	/*--------------------------------------------//
	Decide how much force this object can handle
	before deformation takes place
	//--------------------------------------------*/
		vector mesh::getMaxDisplacement(vector force){
			return (force * 0.1);
		};

	/*--------------------------------------------//
	Returns the number of vertices in the mesh
	//--------------------------------------------*/
		int mesh::getVertexCount(){
			return vertsCnt;
		};

	/*--------------------------------------------//
	Returns the vertex in our array of vertices
	at the specified index
	//--------------------------------------------*/
		vertex* mesh::getVertex(int i){
			return verts[i];
		};

	/*--------------------------------------------//
	Returns the number of triangles in the mesh
	//--------------------------------------------*/
		int mesh::getTriangleCount(){
			return triCnt;
		};

	/*--------------------------------------------//
	Returns the triangle in our array of triangles
	at the specified index
	//--------------------------------------------*/
		triangle* mesh::getTriangle(int i){
			return tris[i];
		};

	/*--------------------------------------------//
	Returns the meshes radius for its bounding 
	geometry
	//--------------------------------------------*/
		double mesh::getRadius(){
			return radius;
		};

	/*--------------------------------------------//
	Returns the meshes angles in relation to the
	world space
	//--------------------------------------------*/
		angles mesh::getAngles(){
			return euler;
		};

	/*--------------------------------------------//
	Sets the meshes angles in relation to the world
	space
	//--------------------------------------------*/
		void mesh::setAngles(angles ang){
			this->setAngles(ang.p, ang.y, ang.r);
			return;
		};
		void mesh::setAngles(double pitch, double yaw, double roll){
			if(pitch != euler.p){
				euler.p = pitch;
				deuler = true;
			}
			if(yaw != euler.y){
				euler.y = yaw;
				deuler = true;
			}
			if(roll != euler.r){
				euler.r = roll;
				deuler = true;
			}
			return;
		};

	/*--------------------------------------------//
	Returns the meshes angular velocity in relation
	to the world space
	//--------------------------------------------*/
		angles mesh::getAngVel(){
			return angVel;
		};

	/*--------------------------------------------//
	Sets the meshes anglular velocity in relation to
	the world space
	//--------------------------------------------*/
		void mesh::setAngVel(angles ang){
			angVel = ang;
			return;
		};
		void mesh::setAngVel(double pitch, double yaw, double roll){
			this->setAngVel(angles(pitch,yaw,roll));
			return;
		};

	/*--------------------------------------------//
	Returns the meshes angular acceleration in 
	relation to the world space
	//--------------------------------------------*/
		angles mesh::getAngAcc(){
			return angAcc;
		};

	/*--------------------------------------------//
	Sets the meshes anglular acceleration in 
	relation to the world space
	//--------------------------------------------*/
		void mesh::setAngAcc(angles ang){
			angAcc = ang;
			return;
		};
		void mesh::setAngAcc(double pitch, double yaw, double roll){
			this->setAngAcc(angles(pitch,yaw,roll));
			return;
		};

	/*--------------------------------------------//
	Returns the meshes angular force in relation to
	the world space
	//--------------------------------------------*/
		angles mesh::getAngFrc(){
			return angFrc;
		};

	/*--------------------------------------------//
	Sets the meshes anglular force in relation to 
	the world space
	//--------------------------------------------*/
		void mesh::setAngfrc(angles ang){
			angFrc = ang;
			return;
		};
		void mesh::setAngfrc(double pitch, double yaw, double roll){
			this->setAngfrc(angles(pitch,yaw,roll));
			return;
		};

	/*--------------------------------------------//
	Returns the meshes position in relation to the
	world space
	//--------------------------------------------*/
		vector mesh::getPosition(){
			return position;
		};

	/*--------------------------------------------//
	Sets the meshes position in relation to the
	world space
	//--------------------------------------------*/
		void mesh::setPosition(vector pos){
			position = pos;
			return;
		};
		void mesh::setPosition(double xpos, double ypos, double zpos){
			this->setPosition(vector(xpos, ypos, zpos));
			return;
		};

	/*--------------------------------------------//
	Returns the meshes velocity in relation to the
	world space
	//--------------------------------------------*/
		vector mesh::getVelocity(){
			return velocity;
		};

	/*--------------------------------------------//
	Sets the meshes velocity in relation to the
	world space
	//--------------------------------------------*/
		void mesh::setVelocity(vector vel){
			velocity = vel;
			return;
		};
		void mesh::setVelocity(double xvel, double yvel, double zvel){
			this->setVelocity(vector(xvel, yvel, zvel));
			return;
		};

	/*--------------------------------------------//
	Returns the meshes acceleration in relation to 
	the world space
	//--------------------------------------------*/
		vector mesh::getAcceleration(){
			return acceleration;
		};

	/*--------------------------------------------//
	Sets the meshes acceleration in relation to the
	world space
	//--------------------------------------------*/
		void mesh::setAcceleration(vector acc){
			acceleration = acc;
			return;
		};
		void mesh::setAcceleration(double xacc, double yacc, double zacc){
			this->setAcceleration(vector(xacc, yacc, zacc));
			return;
		};

	/*--------------------------------------------//
	Returns the meshes force in relation to the 
	world space
	//--------------------------------------------*/
		vector mesh::getForce(){
			return force;
		};

	/*--------------------------------------------//
	Sets the meshes force in relation to the
	world space
	//--------------------------------------------*/
		void mesh::setForce(vector frc){
			force = frc;
			return;
		};
		void mesh::setForce(double xfrc, double yfrc, double zfrc){
			this->setForce(vector(xfrc, yfrc, zfrc));
			return;
		};
		void mesh::applyForce(vector frc){
			force = force + frc;
			return;
		};
		void mesh::applyForce(double xfrc, double yfrc, double zfrc){
			this->applyForce(vector(xfrc, yfrc, zfrc));
			return;
		};

	/*--------------------------------------------//
	Returns the meshes mass
	//--------------------------------------------*/
		double mesh::getMass(){
			return mass;
		};

	/*--------------------------------------------//
	Sets the meshes mass
	//--------------------------------------------*/
		void mesh::setMass(double ma){
			mass = ma;
		};

	/*--------------------------------------------//
	Drawing functions
	this gets deferred to each triangles to draw
	//--------------------------------------------*/
		void mesh::draw(){
			glPushMatrix();
				glMultMatrixd(this->quat.toMatrix());
				glTranslated(this->position.x(), this->position.y(), this->position.z());
				for (int i = 0; i < this->getTriangleCount(); i++){
					triangle* k = this->getTriangle(i);
					k->draw();
				}
			glPopMatrix();
		};

	/*--------------------------------------------//
	Update functions
	this advances the object's current motion/animation
	//--------------------------------------------*/
		void mesh::updateAcc(){
			this->setAcceleration(force/mass);
			this->setAngAcc(angFrc);//normally torque = force * distance but that would require keeping track of the distance on each force
		};
		void mesh::updateVel(){
			this->setVelocity(velocity + acceleration);
			this->setAngVel(angVel + angAcc);
		};
		void mesh::updatePos(){
			this->setPosition(position + velocity);
			this->setAngles(euler + angVel);

			if(deuler == true){
				quat.setAngles(euler.p, euler.y, euler.r);
				deuler = false;
			}

			//check if we moved
			if(velocity > 0 && angVel > 0){
				timer = 0;
			}else{
				timer++;
			}
		};
#endif