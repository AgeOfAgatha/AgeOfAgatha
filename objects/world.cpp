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
				objects[i]->update();
			}
			return;
		};
};
#endif