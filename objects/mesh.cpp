/*--------------------------------------------//
Mesh definition
This is our basic object
//--------------------------------------------*/
#ifndef MESH
#define MESH

#ifndef TRIANGLES
#include "triangle.cpp"
#endif

#ifndef QUATERNION
#include "../common/quaternion.cpp"
#endif

class mesh{
	private:
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
		angles angFrc;//stores the angular force
		vector position;//stores the position within the world of this mesh
		vector velocity;//store the positional velocity
		vector acceleration;//store the positional acceleration
		vector force;//store the positional force
		vector COM;//center of mass (technically center of detail because it uses vertices)
		double radius;//maximum distance away from COM for the purposes of faster collision detection
		double mass;//amount of mass this object has
		int timer;//time since last movement, used for deciding if awake

		/*--------------------------------------------//
		Attempts to add a vertex to our vertex list
		//--------------------------------------------*/
		void addVertex(vertex* &v){
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
				COM.x += v->x/vertsCnt;
				COM.y += v->y/vertsCnt;
				COM.z += v->z/vertsCnt;

				//find largest radius
				for (int i = 0; i < vertsCnt; ++i){
					double dx = COM.x - verts[i]->x;
					double dy = COM.y - verts[i]->y;
					double dz = COM.z - verts[i]->z;
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
		void remVertex(vertex* &v){
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
						COM.x -= v->x/vertsCnt;
						COM.y -= v->y/vertsCnt;
						COM.z -= v->z/vertsCnt;
						vertsCnt--;
					}else{
						puts ("Error (re)allocating memory");
						exit (1);
					}
					return;
				}
			}
		};
	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		mesh(){
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
		~mesh(){
			for (int i = 0; i < this->getTriangleCount(); i++){
				free ((triangle*)(this->getTriangle(i)));
			}
		};

		/*--------------------------------------------//
		Add a triangle to the mesh by specifying points
		//--------------------------------------------*/
		void addTri(vertex* &a, vertex* &b, vertex* &c){
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
		void remTri(triangle &tri){
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
		void addNearby(mesh* &o){
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
		void remNearby(mesh* &o){
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
		mesh* getNearby(int i){
			return nearby[i];
		};

		/*--------------------------------------------//
		Returns the number of nearby objects
		//--------------------------------------------*/
		int getNearbyCnt(){
			return nearbyCnt;
		};

		/*--------------------------------------------//
		Returns the objects last movement timer
		//--------------------------------------------*/
		int getTimer(){
			return timer;
		};

		/*--------------------------------------------//
		Decide how much force this object can handle
		before deformation takes place
		//--------------------------------------------*/
		vector getMaxDisplacement(vector force){
			return (force * 0.1);
		};

		/*--------------------------------------------//
		Returns the number of vertices in the mesh
		//--------------------------------------------*/
		int getVertexCount(){
			return vertsCnt;
		};

		/*--------------------------------------------//
		Returns the vertex in our array of vertices
		at the specified index
		//--------------------------------------------*/
		vertex* getVertex(int i){
			return verts[i];
		};

		/*--------------------------------------------//
		Returns the number of triangles in the mesh
		//--------------------------------------------*/
		int getTriangleCount(){
			return triCnt;
		};

		/*--------------------------------------------//
		Returns the triangle in our array of triangles
		at the specified index
		//--------------------------------------------*/
		triangle* getTriangle(int i){
			return tris[i];
		};

		/*--------------------------------------------//
		Returns the meshes radius for its bounding 
		geometry
		//--------------------------------------------*/
		double getRadius(){
			return radius;
		};

		/*--------------------------------------------//
		Returns the meshes angles in relation to the
		world space
		//--------------------------------------------*/
		angles getAngles(){
			return euler;
		};

		/*--------------------------------------------//
		Sets the meshes angles in relation to the world
		space
		//--------------------------------------------*/
		void setAngles(angles ang){
			this->setAngles(ang.p, ang.y, ang.r);
			return;
		};
		void setAngles(double pitch, double yaw, double roll){
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
		angles getAngVel(){
			return angVel;
		};

		/*--------------------------------------------//
		Sets the meshes anglular velocity in relation to
		the world space
		//--------------------------------------------*/
		void setAngVel(angles ang){
			angVel = ang;
			return;
		};
		void setAngVel(double pitch, double yaw, double roll){
			this->setAngVel(angles(pitch,yaw,roll));
			return;
		};

		/*--------------------------------------------//
		Returns the meshes angular acceleration in 
		relation to the world space
		//--------------------------------------------*/
		angles getAngAcc(){
			return angAcc;
		};

		/*--------------------------------------------//
		Sets the meshes anglular acceleration in 
		relation to the world space
		//--------------------------------------------*/
		void setAngAcc(angles ang){
			angAcc = ang;
			return;
		};
		void setAngAcc(double pitch, double yaw, double roll){
			this->setAngAcc(angles(pitch,yaw,roll));
			return;
		};

		/*--------------------------------------------//
		Returns the meshes angular force in relation to
		the world space
		//--------------------------------------------*/
		angles getAngFrc(){
			return angFrc;
		};

		/*--------------------------------------------//
		Sets the meshes anglular force in relation to 
		the world space
		//--------------------------------------------*/
		void setAngfrc(angles ang){
			angFrc = ang;
			return;
		};
		void setAngfrc(double pitch, double yaw, double roll){
			this->setAngfrc(angles(pitch,yaw,roll));
			return;
		};

		/*--------------------------------------------//
		Returns the meshes position in relation to the
		world space
		//--------------------------------------------*/
		vector getPosition(){
			return position;
		};

		/*--------------------------------------------//
		Sets the meshes position in relation to the
		world space
		//--------------------------------------------*/
		void setPosition(vector pos){
			position = pos;
			return;
		};
		void setPosition(double xpos, double ypos, double zpos){
			this->setPosition(vector(xpos, ypos, zpos));
			return;
		};

		/*--------------------------------------------//
		Returns the meshes velocity in relation to the
		world space
		//--------------------------------------------*/
		vector getVelocity(){
			return velocity;
		};

		/*--------------------------------------------//
		Sets the meshes velocity in relation to the
		world space
		//--------------------------------------------*/
		void setVelocity(vector vel){
			velocity = vel;
			return;
		};
		void setVelocity(double xvel, double yvel, double zvel){
			this->setVelocity(vector(xvel, yvel, zvel));
			return;
		};

		/*--------------------------------------------//
		Returns the meshes acceleration in relation to 
		the world space
		//--------------------------------------------*/
		vector getAcceleration(){
			return acceleration;
		};

		/*--------------------------------------------//
		Sets the meshes acceleration in relation to the
		world space
		//--------------------------------------------*/
		void setAcceleration(vector acc){
			acceleration = acc;
			return;
		};
		void setAcceleration(double xacc, double yacc, double zacc){
			this->setAcceleration(vector(xacc, yacc, zacc));
			return;
		};

		/*--------------------------------------------//
		Returns the meshes force in relation to the 
		world space
		//--------------------------------------------*/
		vector getForce(){
			return force;
		};

		/*--------------------------------------------//
		Sets the meshes force in relation to the
		world space
		//--------------------------------------------*/
		void setForce(vector frc){
			force = frc;
			return;
		};
		void setForce(double xfrc, double yfrc, double zfrc){
			this->setForce(vector(xfrc, yfrc, zfrc));
			return;
		};
		void applyForce(vector frc){
			force = force + frc;
			return;
		};
		void applyForce(double xfrc, double yfrc, double zfrc){
			this->applyForce(vector(xfrc, yfrc, zfrc));
			return;
		};

		/*--------------------------------------------//
		Returns the meshes mass
		//--------------------------------------------*/
		double getMass(){
			return mass;
		};

		/*--------------------------------------------//
		Sets the meshes mass
		//--------------------------------------------*/
		void setMass(double ma){
			mass = ma;
		};

		/*--------------------------------------------//
		Drawing functions
		this gets deferred to each triangles to draw
		//--------------------------------------------*/
		void draw(){
			glPushMatrix();
				glMultMatrixd(this->quat.toMatrix());
				glTranslated(this->position.x, this->position.y, this->position.z);
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
		void updateAcc(){
			this->setAcceleration(force/mass);
			this->setAngAcc(angAcc + angFrc);
		};
		void updateVel(){
			this->setVelocity(velocity + acceleration);
			this->setAngVel(angVel + angAcc);
		};
		void updatePos(){
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
};
#endif