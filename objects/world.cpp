/*--------------------------------------------//
World definition
This is where the simulation is controlled
//--------------------------------------------*/
#ifndef WORLD
#define WORLD
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "world.h"
	
	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		world::world(){
			timestep = 1;
			timeout = 1;
			vertexrad = 1.0;
			objCnt = 0;
			objects = NULL;
			gravObjCnt = 0;
			gravObj = NULL;
		};

	/*--------------------------------------------//
	Overloaded constructor
	//--------------------------------------------*/
		world::world(int ts, int to, double vr, double gom, double gc, double fd, double fc, double dc):world(){
			timestep = ts;
			timeout = to;
			vertexrad = vr;
			gravObjMass = gom;
			gravConst = gc;
			frictionDist = fd;
			frictionConst = fc;
			deformConst = dc;
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		world::~world(){
			for (int i = 0; i < this->getObjectCount(); i++){
				free ((mesh*)(this->getObject(i)));
			}
		};

	/*--------------------------------------------//
	Adds a object to the world space
	takes a mesh as a parameter
	//--------------------------------------------*/
		void world::addMesh(mesh* &obj){
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
		void world::remMesh(mesh* &obj){
			for (int i = 0; i < objCnt; i++){
				//find object to remove
				if (obj == objects[i]){
					//move last object to here
					objects[i] = objects[objCnt-1];
					//trim last object
					mesh** newobjs = (mesh**) realloc(objects, sizeof(mesh*)*(objCnt-1));
					//check if memory was allocated
					if (newobjs!=NULL) {
						remGravObj(obj);
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
		int world::getTimeStep(){
			return timestep;
		};
		int world::getObjectCount(){
			return objCnt;
		};
		mesh* world::getObject(int i){
			return objects[i];
		};

	/*--------------------------------------------//
	Drawing function
	defers drawing to individual object
	implementation
	//--------------------------------------------*/
		void world::draw(){
			for (int i = 0; i < this->getObjectCount(); i++){
				this->getObject(i)->draw();
			}
		};

	/*--------------------------------------------//
	Gravity function
	calculates gravity for inputted object
	//--------------------------------------------*/
		void world::applyGravity(mesh* &obj){
			//only simulate gravity for objects listed as gravity objects
			for (int i = 0; i < gravObjCnt; i++){
				mesh* obj2 = gravObj[i];
				vector pos1 = obj->getPosition();
				vector pos2 = obj2->getPosition();
				double mass1 = obj->getMass();
				double mass2 = obj2->getMass();

				vector dir = pos1 - pos2;
				double distance = (dir).length();
				dir.normalize();

				obj->applyForce( dir * gravConst * mass1 * mass2 / pow(distance, 2) );
			}
		};

	/*--------------------------------------------//
	Friction function
	calculates friction for inputted object
	//--------------------------------------------*/
		void world::applyFriction(mesh* &obj){
			for (int i = 0; i < obj->getNearbyCnt(); i++){
				//setup variables
				mesh* obj2 = obj->getNearby(i);
				vector pos1 = obj->getPosition();
				vector pos2 = obj2->getPosition();
				vector vel1 = obj->getVelocity();
				vector vel2 = obj2->getVelocity();
				int mass1 = obj->getMass();
				int mass2 = obj2->getMass();
				double rad1 = obj->getRadius();
				double rad2 = obj2->getRadius();

				//find net velocity
				vector velNet = vel1 - vel2;
				//find force being applied, p = mv
				vector force = velNet / timestep * (mass1 + mass2);
				//define a projected line from obj1 along velocity
				line projection = line(pos1, velNet);
				vector intercept = vector(0,0,0);
				double u = 0.0;
				//find how close obj1 and obj2 get
				double distance = projection.distance(pos2, intercept, u);
				//now apply an estimate for the friction force
				obj->applyForce(force * frictionConst * (rad1 + rad2 - distance));
				obj2->applyForce(force * frictionConst * (rad1 + rad2 - distance));
			}
		};

	/*--------------------------------------------//
	Update function
	proceeds all objects forward by one timestep
	//--------------------------------------------*/
		void world::update(){
			for (int i = 0; i < objCnt; ++i){
				applyGravity(objects[i]);
				testBpCollision(objects[i], i);
				objects[i]->updateAcc();
				objects[i]->updateVel();
				objects[i]->updatePos();
				if (objects[i]->getMass() > gravObjMass){
					addGravObj(objects[i]);
				}else{
					remGravObj(objects[i]);
				}
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
		void world::testBpCollision(mesh* &obj, int i){
			//store objects that could be colliding
			mesh** filter = (mesh**) malloc(sizeof(mesh*)*objCnt-1-i);
			int filterCnt = 0;
			//loop over all objects starting after 'i'th item.  the 'i'th item should be the current item
			for (i++; i < objCnt-i; i++){
				mesh* obj2 = objects[i];
				//no self collision or collision between two 'sleeping' objects (objects not in motion)
				if(obj2 != obj && (isAwake(obj) || isAwake(obj2))){
					vector vel1 = obj->getVelocity() + obj->getForce()/obj->getMass();
					vector vel2 = obj2->getVelocity() + obj2->getForce()/obj2->getMass();

					//implicit function testing
					if(implicitTest(obj->getPosition(), obj2->getPosition(), obj->getRadius()+frictionDist, obj2->getRadius()+frictionDist, vel1, vel2)){
						//bounding sphere and bounding cube collide.  collision is possible
						filter[filterCnt] = obj2;
						filterCnt++;
						//add each other to the nearby lists
						obj->addNearby(obj2);
						obj2->addNearby(obj);
					}else{
						//remove each other as nearby objects
						obj->remNearby(obj2);
						obj2->remNearby(obj);
					}
				}else{
					//remove each other as nearby objects
					obj->remNearby(obj2);
					obj2->remNearby(obj);
				}
			}
			//-- From this point forward we start to affect more than one object, be careful with multithreading --//
			//apply friction to this object before any collision resolution occurs
			applyFriction(obj);

			//proceed to narrow phase collision detection with filter objects
			if(filterCnt > 0){
				testNpCollision(obj, filter, filterCnt);
			}
			free (filter);
			return;
		};

	/*--------------------------------------------//
	Narrowphase Collision detection
	Sorts the objects by an estimated collision time
	Then resolves collisions vertex by vertex
	//--------------------------------------------*/
		void world::testNpCollision(mesh* &obj, mesh** &filter, int &filterCnt){
			//We first need to sort by order of collision
			HeapSort heap;
			double times[filterCnt];
			for (int i = 0; i < filterCnt; i++){
				//setup variables
				mesh* obj2 = filter[i];
				vector vel1 = obj->getVelocity() + obj->getForce()/obj->getMass();
				vector vel2 = obj2->getVelocity() + obj2->getForce()/obj2->getMass();
				vector pos1 = obj->getPosition();
				vector pos2 = obj2->getPosition();

				//estimate time
				vector velNet = vel1 - vel2;
				vector intercept = vector(0,0,0);
				line projection = line(pos1, velNet);
				double u = 0.0;
				projection.distance(pos2, intercept, u);
				times[i] = u;
			}
			//finally use our time estimates to sort our filter
			heap = HeapSort((void**)filter, (double**)&times, filterCnt);

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

				//decide how much force goes into deformation and movement
				//p = mv, m1v1 + m2v2 = (m1+m2)v3
				vector resultVel = (vel1 * obj->getMass() + vel2 * obj2->getMass()) / (obj->getMass() + obj2->getMass());
				vector moveFrc1 = (resultVel - vel1) / timestep * obj->getMass();//units might match but probably not 100% formula accurate
				vector moveFrc2 = (resultVel - vel2) / timestep * obj2->getMass();//should give a good approximation though
				vector deformFrc1 = obj->getMaxDisplacement(moveFrc1);
				vector deformFrc2 = obj2->getMaxDisplacement(moveFrc2);
				moveFrc1 = moveFrc1 - deformFrc1;
				moveFrc2 = moveFrc2 - deformFrc2;

				//apply move forces
				obj->applyForce(moveFrc1);
				obj2->applyForce(moveFrc2);

				//we are going to adjust vertex positions now (apply deformation)
				//tad inefficent... loops over the vertices on both objects, hopefully narrows down quicker by implicit tests
				//loop over all vertices on object 1
				int vert1cnt = obj->getVertexCount();
				for (int j = 0; j < vert1cnt; j++){
					vertex* vert1 = obj->getVertex(j);
					vector vert1pos = vector(vert1->x(), vert1->y(), vert1->z()) + pos1;
					//implicit function test on vert1 to obj2
					if(implicitTest(vert1pos, pos2, vertexrad, rad2, vel1, vel2)){
						int vert2cnt = obj2->getVertexCount();
						//loop over all vertices on object 2
						for (int k = 0; k < vert2cnt; k++){
							vertex* vert2 = obj2->getVertex(k);
							vector vert2pos = vector(vert2->x(), vert2->y(), vert2->z()) + pos2;
							//implicit function on vert2 to obj1
							if(implicitTest(pos1, vert2pos, rad1, vertexrad, vel1, vel2)){
								//both vert1 and vert2 might collide with something on the other object
								//now we check if vert1 and vert2 collide with each other
								//define a line from vert1 extending along the net velocity
								vector velNet = vel1 - vel2;
								line projection = line(*vert1, velNet);
								vector intercept = vector(0,0,0);
								double u = 0.0;
								//find distance, time, and intercept point
								double distance = projection.distance(*vert2, intercept, u);

								if(distance > vertexrad){
									//vert1 and vert2 come within vertexrad distance at intercept point
									double time = (u - floor(u)) * timestep;//a value between 0->1 * timestep gives the amount of time into this timestep
									*vert1 -= deformFrc1 * deformConst / (distance * time * vert1cnt);//units might match but probably not 100% formula accurate
									*vert2 -= deformFrc2 * deformConst / (distance * time * vert2cnt);//should give a good approximation though
								}
							}
						}
					}
				}

				/*
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
					continue;
				}

				//now test each triangle collision and assign weight for magnitudes of impact
				for (int j = 0; j < tris1Cnt; j++){
					triangle* tri1 = tris1[j];
					for (int k = 0; k < tris2Cnt; k++){
						triangle* tri2 = tris2[k];
						//check if avg point of tri2 intersects with tri1
						if(tri1->intersects(tri2->getPosition())){
							vector tri1pos = pos1 + tri1->getPosition();
							vector tri2pos = pos2 + tri2->getPosition();
							//find the dot product of the normals (how much 'deflection' occurs)
							double attack = tri1->getNormal().dot(tri2->getNormal());
							//find the proximity to the primary collision
							vector colVec = pos1 - pos2;
							vector triColVec = tri1pos - tri2pos;
							double triColDiff = (colVec - triColVec).length();
							double proximity1 = rad1 / triColDiff;
							double proximity2 = rad2 / triColDiff;

							//apply to each vertex of both triangles
							for (int l = 0; l < 3; l++){
								tris1[j*tris1Cnt + k]->getVertex(l)->x -= deformFrc1.x * proximity1 * attack;
								tris1[j*tris1Cnt + k]->getVertex(l)->y -= deformFrc1.y * proximity1 * attack;
								tris1[j*tris1Cnt + k]->getVertex(l)->z -= deformFrc1.z * proximity1 * attack;

								tris2[j*tris1Cnt + k]->getVertex(l)->x -= deformFrc2.x * proximity2 * attack;
								tris2[j*tris1Cnt + k]->getVertex(l)->y -= deformFrc2.y * proximity2 * attack;
								tris2[j*tris1Cnt + k]->getVertex(l)->z -= deformFrc2.z * proximity2 * attack;
							}
						}else{
							//no collision
						}
					}
				}
				//done with this check... clean up
				free (tris1);
				free (tris2);
				//*/
			}
		};

	/*--------------------------------------------//
	Adds a object to the gravity object list
	takes a mesh as a parameter
	//--------------------------------------------*/
		void world::addGravObj(mesh* &obj){
			mesh** newobjs = (mesh**) realloc(gravObj, sizeof(mesh*)*(gravObjCnt+1));

			if (newobjs!=NULL) {
				gravObj = newobjs;

				gravObj[gravObjCnt] = obj;
				gravObjCnt++;
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		};

	/*--------------------------------------------//
	Removes the specified mesh as a gravity object
	does nothing if it is not found
	//--------------------------------------------*/
		void world::remGravObj(mesh* &obj){
			for (int i = 0; i < gravObjCnt; i++){
				//find object to remove
				if (obj == gravObj[i]){
					//move last object to here
					gravObj[i] = gravObj[gravObjCnt-1];
					//trim last object
					mesh** newobjs = (mesh**) realloc(gravObj, sizeof(mesh*)*(gravObjCnt-1));
					//check if memory was allocated
					if (newobjs!=NULL) {
						gravObj = newobjs;
						gravObjCnt--;
					}else{
						puts ("Error (re)allocating memory");
						exit (1);
					}
					return;
				}
			}
		};

	/*--------------------------------------------//
	Implicit test function
	checks if two implicit function defined spheres
	intersect
	//--------------------------------------------*/
		bool world::implicitTest(vector pos1, vector pos2, double rad1, double rad2, vector vel1, vector vel2){
			//calculate x portion
			(pos2.x() > pos1.x()) ? /*Decide which direction to go*/
				(pos1.x() + rad1 + vel1.x() > pos2.x() - vel2.x()) ? pos1.x(pos2.x()) : pos1.x(pos1.x() + rad1 + vel1.x() - vel2.x()):
				(pos1.x() - rad1 - vel1.x() > pos2.x() + vel2.x()) ? pos1.x(pos2.x()) : pos1.x(pos1.x() - rad1 + vel1.x() - vel2.x());

			//calculate y portion
			(pos2.y() > pos1.y()) ? /*Decide which direction to go*/
				(pos1.y() + rad1 + vel1.y() > pos2.y() - vel2.y()) ? pos1.y(pos2.y()) : pos1.y(pos1.y() + rad1 + vel1.y() - vel2.y()):
				(pos1.y() - rad1 - vel1.y() > pos2.y() + vel2.y()) ? pos1.y(pos2.y()) : pos1.y(pos1.y() - rad1 + vel1.y() - vel2.y());

			//calculate z portion
			(pos2.z() > pos1.z()) ? /*Decide which direction to go*/
				(pos1.z() + rad1 + vel1.z() > pos2.z() - vel2.z()) ? pos1.z(pos2.z()) : pos1.z(pos1.z() + rad1 + vel1.z() - vel2.z()):
				(pos1.z() - rad1 - vel1.z() > pos2.z() + vel2.z()) ? pos1.z(pos2.z()) : pos1.z(pos1.z() - rad1 + vel1.z() - vel2.z());

			return (pos2.x()*pos2.x() + pos2.y()*pos2.y() + pos2.z()*pos2.z() - rad1*rad1 <= 0);
		};

	/*--------------------------------------------//
	Checks if an object is awake or not
	does this by compairing to our timeout value
	//--------------------------------------------*/
		bool world::isAwake(mesh* &obj){
			return obj->getTimer() > timeout;
		};
#endif