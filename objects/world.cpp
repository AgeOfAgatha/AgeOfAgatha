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
		int timestep;
		int objCnt;
		mesh** objects;
	public:
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		world(){
			timestep = 2;
			objCnt = 0;
			objects = NULL;
		};

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
		Update function
		proceeds all objects forward by one timestep
		//--------------------------------------------*/
		void update(){
			for (int i = 0; i < objCnt; ++i){
				//tell each object to advance a timestep
				objects[i]->update();
			}
			//have each object test collisions with objects past it in the list.  this avoids doing repeat tests
			for (int i = 0; i < objCnt; ++i){
				//verify each item is in a valid state before continuing
				testBpCollision(objects[i], i);
			}
			return;
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
				//no self collision
				if(obj2 != obj){
					vector pos1 = obj->getPosition();
					double rad1 = obj->getRadius();
					vector pos2 = obj2->getPosition();
					double rad2 = obj2->getRadius();

					//find bounding cube position
					vector pos3 = pos2;
					if(pos2.x < pos1.x){
						pos3.x += rad2;
					}else{
						pos3.x -= rad2;
					}
					if(pos2.y < pos1.y){
						pos3.y += rad2;
					}else{
						pos3.y -= rad2;
					}
					if(pos2.z < pos1.z){
						pos3.z += rad2;
					}else{
						pos3.z -= rad2;
					}

					//implicit function testing
					if(pos3.x*pos3.x + pos3.y*pos3.y + pos3.z*pos3.z - rad1*rad1 <= 0){
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
			return;
		};
		/*--------------------------------------------//
		Narrowphase Collision detection
		//--------------------------------------------*/
		void testNpCollision(mesh* &obj, mesh** &filter, int &filterCnt){
		};
};
#endif