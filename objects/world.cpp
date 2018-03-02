/*--------------------------------------------//
World definition
This is where the simulation is controlled
//--------------------------------------------*/
#ifndef WORLD
#define WORLD

#ifndef MESH
#include "mesh.cpp"
#endif

class world{
	private:
		int timestep;//how often is this world updated
		int timeout;//how many iterations can an object not move before it is considered asleep
		int objCnt;
		mesh** objects;
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		world(){
			timestep = 1;
			timeout = 1;
			objCnt = 0;
			objects = NULL;
		};
	public:
		/*--------------------------------------------//
		Overloaded constructor
		//--------------------------------------------*/
		world(int t, int y):world(){
			timestep = t;
			timeout = y;
		}

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~world(){
			for (int i = 0; i < this->getObjectCount(); i++){
				free ((mesh*)(this->getObject(i)));
			}
		};

		/*--------------------------------------------//
		Adds a object to the world space
		takes a mesh as a parameter
		//--------------------------------------------*/
		void addMesh(mesh* &obj){
			mesh** newobjs = (mesh**) realloc(objects, sizeof(mesh*)*(objCnt+1));

			if (newobjs!=NULL) {
				objects = newobjs;

				objects[objCnt] = obj;
				objCnt++;
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		};

		/*--------------------------------------------//
		Removes the specified mesh from the world
		does nothing if it is not found
		//--------------------------------------------*/
		void remMesh(mesh* &obj){
			for (int i = 0; i < objCnt; i++){
				//find object to remove
				if (obj == objects[i]){
					//move last object to here
					objects[i] = objects[objCnt-1];
					//trim last object
					mesh** newobjs = (mesh**) realloc(objects, sizeof(mesh*)*(objCnt-1));
					//check if memory was allocated
					if (newobjs!=NULL) {
						objects = newobjs;
						objCnt--;
					}else{
						puts ("Error (re)allocating memory");
						exit (1);
					}
					return;
				}
			}
		};

		/*--------------------------------------------//
		Getters
		//--------------------------------------------*/
		int getTimeStep(){
			return timestep;
		};
		int getObjectCount(){
			return objCnt;
		};
		mesh* getObject(int i){
			return objects[i];
		};

		/*--------------------------------------------//
		Drawing function
		defers drawing to individual object
		implementation
		//--------------------------------------------*/
		void draw(){
			for (int i = 0; i < this->getObjectCount(); i++){
				this->getObject(i)->draw();
			}
		};

		/*--------------------------------------------//
		Gravity function
		calculates gravity for inputted object
		//--------------------------------------------*/
		void applyGravity(mesh* &obj){
		};

		/*--------------------------------------------//
		Friction function
		calculates friction for inputted object
		//--------------------------------------------*/
		void applyFriction(mesh* &obj){
		};

		/*--------------------------------------------//
		Update function
		proceeds all objects forward by one timestep
		//--------------------------------------------*/
		void update(){
			for (int i = 0; i < objCnt; ++i){
				applyGravity(objects[i]);
				testBpCollision(objects[i], i);
				applyFriction(objects[i]);
				objects[i]->updateAcc();
				objects[i]->updateVel();
				objects[i]->updatePos();
			}
			return;
		};
		/*--------------------------------------------//
		Implicit test function
		checks if two implicit function defined spheres
		intersect
		//--------------------------------------------*/
		bool implicitTest(vector pos1, vector pos2, double rad1, double rad2, vector vel1, vector vel2){
			//calculate x portion
			(pos2.x > pos1.x) ? /*Decide which direction to go*/
				(pos1.x + rad1 + vel1.x > pos2.x - vel2.x) ? pos1.x = pos2.x : pos1.x += rad1 + vel1.x - vel2.x:
				(pos1.x - rad1 - vel1.x > pos2.x + vel2.x) ? pos1.x = pos2.x : pos1.x -= rad1 + vel1.x - vel2.x;

			//calculate y portion
			(pos2.y > pos1.y) ? /*Decide which direction to go*/
				(pos1.y + rad1 + vel1.y > pos2.y - vel2.y) ? pos1.y = pos2.y : pos1.y += rad1 + vel1.y - vel2.y:
				(pos1.y - rad1 - vel1.y > pos2.y + vel2.y) ? pos1.y = pos2.y : pos1.y -= rad1 + vel1.y - vel2.y;

			//calculate z portion
			(pos2.z > pos1.z) ? /*Decide which direction to go*/
				(pos1.z + rad1 + vel1.z > pos2.z - vel2.z) ? pos1.z = pos2.z : pos1.z += rad1 + vel1.z - vel2.z:
				(pos1.z - rad1 - vel1.z > pos2.z + vel2.z) ? pos1.z = pos2.z : pos1.z -= rad1 + vel1.z - vel2.z;

			return (pos2.x*pos2.x + pos2.y*pos2.y + pos2.z*pos2.z - rad1*rad1 <= 0);
		};
		/*--------------------------------------------//
		Broadphase Collision detection
		narrows down the possible objects that a given
		object could be colliding with.
		This is done using the 'meshes' 'radius'
		attribute and treating it as a implicit bounding 
		sphere and explicit bounding cube.
		This allows for implicit object simplification.
		//--------------------------------------------*/
		void testBpCollision(mesh* &obj, int i){
			//store objects that could be colliding
			mesh** filter = (mesh**) malloc(sizeof(mesh*)*objCnt-1-i);
			int filterCnt = 0;
			//loop over all objects starting after 'i'th item.  the 'i'th item should be the current item
			for (i++; i < objCnt-i; i++){
				mesh* obj2 = objects[i];
				//no self collision or collision between two 'sleeping' objects (objects not in motion)
				if(obj2 != obj && (obj->isAwake() || obj2->isAwake())){
					vector vel1 = obj->getVelocity() + obj->getForce()/obj->getMass();
					vector vel2 = obj2->getVelocity() + obj2->getForce()/obj2->getMass();

					//implicit function testing
					if(implicitTest(obj->getPosition(), obj2->getPosition(), obj->getRadius(), obj2->getRadius(), vel1, vel2)){
						//bounding sphere and bounding cube collide.  collision is possible
						filter[filterCnt] = obj2;
						filterCnt++;
					}
				}
			}
			//proceed to narrow phase collision detection with filter objects
			if(filterCnt > 0){
				testNpCollision(obj, filter, filterCnt);
			}
			free (filter);
			return;
		};
		/*--------------------------------------------//
		Narrowphase Collision detection
		//--------------------------------------------*/
		void testNpCollision(mesh* &obj, mesh** &filter, int &filterCnt){
			//loop over all objects that could still collide
			for (int i = 0; i < filterCnt; i++){
				//setup variables
				mesh* obj2 = filter[i];
				vector vel1 = obj->getVelocity() + obj->getForce()/obj->getMass();
				vector vel2 = obj2->getVelocity() + obj2->getForce()/obj2->getMass();
				vector pos1 = obj->getPosition();
				vector pos2 = obj2->getPosition();
				double rad1 = obj->getRadius();
				double rad2 = obj2->getRadius();

				//create triangle filters
				triangle** tris1 = (triangle**)malloc(sizeof(triangle*)*obj->getTriangleCount());//overestimate malloc
				int tris1Cnt = 0;

				triangle** tris2 = (triangle**)malloc(sizeof(triangle*)*obj2->getTriangleCount());//overestimate malloc
				int tris2Cnt = 0;

				//loop over all of object1's triangles
				for (int j = 0; j < obj->getTriangleCount(); j++){
					//implicit function testing
					if(implicitTest(obj->getTriangle(j)->getPosition(), pos2, 1, rad2, vel1, vel2)){
						//passed test, add to triangle filter
						tris1[tris1Cnt] = obj->getTriangle(j);
						tris1Cnt++;
					}
				}

				//loop over all of object2's triangles
				for (int j = 0; j < obj2->getTriangleCount(); j++){
					//implicit function testing
					if(implicitTest(pos1, obj2->getTriangle(j)->getPosition(), rad1, 1, vel1, vel2)){
						//passed test, add to triangle filter
						tris2[tris2Cnt] = obj2->getTriangle(j);
						tris2Cnt++;
					}
				}

				//check if collision is still possible
				if(tris1Cnt + tris2Cnt == 0){
					free (tris1);
					free (tris2);
					break;
				}

				//collision weight matrix
				double* colMat = (double*)malloc(sizeof(double)*tris1Cnt*tris2Cnt);

				//now test each triangle collision and assign weight for magnitudes of impact
				for (int j = 0; j < tris1Cnt; j++){
					triangle* tri1 = tris1[j];
					for (int k = 0; k < tris2Cnt; k++){
						triangle* tri2 = tris2[k];
						//check if avg point of tri2 intersects with tri1
						if(tri1->intersects(tri2->getPosition())){
							//placeholder
							colMat[j*tris1Cnt +k] = 1.0;//assign a value for degree of collision force
						}
					}
				}
			}
		};
};
#endif