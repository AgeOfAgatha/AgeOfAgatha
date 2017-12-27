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
		angles euler;//stores the meshes euler angles in relation to the world
		bool deuler = true;//stores a true or false for if the angles have been changed since last update
		quaternion quat;//stores our euler angles in a quaternion to avoid gimbal lock.  This is what is actually used for calculations
		angles angVel;//stores the angular velocity
		vector position;//stores the position within the world of this mesh
		vector velocity;//store the positional velocity
		vector COM;//center of mass (technically center of detail because it uses vertices)
		double radius;//maximum distance away from COM for the purposes of faster collision detection

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

			COM = vertex(0,0,0);
			
			position = vertex(0,0,0);
			velocity = vertex(0,0,0);

			euler = angles(0.0, 0.0, 0.0);
			angVel = angles(0.0, 0.0, 0.0);
			quat = quaternion(euler);
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
		Returns the meshes angular velocity in relation
		to the world space
		//--------------------------------------------*/
		angles getAngVelocity(){
			return angVel;
		};

		/*--------------------------------------------//
		Sets the meshes angular velocity in relation
		to the world space
		//--------------------------------------------*/
		void setAngVelocity(angles ang){
			if(ang != angVel){
				angVel = ang;
				deuler = true;
			}
			return;
		};
		void setAngVelocity(double pitch, double yaw, double roll){
			this->setAngVelocity(angles(pitch, yaw, roll));
			return;
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
		void update(){
			position.x += velocity.x;
			position.y += velocity.y;
			position.z += velocity.z;

			this->setAngles(angles(euler.p + angVel.p, euler.y + angVel.y, euler.r + angVel.r));

			if(deuler == true){
				quat.setAngles(euler.p, euler.y, euler.r);
				deuler = false;
			}
		};
};
#endif