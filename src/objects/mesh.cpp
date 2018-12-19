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
	Default constructor
	//--------------------------------------------*/
		mesh::mesh(){
			parent = NULL;
			childs = NULL;
			childCnt = 0;

			triCnt = 0;
			tris = NULL;
			nearbyCnt = 0;
			nearby = NULL;

			COM = vec3(0,0,0);
			
			position = vec3(0,0,0);
			velocity = vec3(0,0,0);
			acceleration = vec3(0,0,0);
			force = vec3(0,0,0);

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
	Drawing functions
	this gets deferred to each triangle to draw
	//--------------------------------------------*/
		void mesh::draw(float* position, float* camera, float aspect, Shader* shader){
			glPushMatrix();
				//Apply Transformations
				float i[16] = {
				   1, 0, 0, 0,
				   0, 1, 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1
				};
				glm::mat4 view;
		        glm::mat4 model;
		        glm::mat4 projection;
		        //fill with identity
		        memcpy(glm::value_ptr(view), i, sizeof(i));
		        memcpy(glm::value_ptr(model), i, sizeof(i));
		        memcpy(glm::value_ptr(projection), i, sizeof(i));


		        projection 	= glm::perspective(glm::radians(FRUSTUM_FIELD_OF_VIEW), aspect, FRUSTUM_NEAR_PLANE, FRUSTUM_FAR_PLANE);
		        view       	= glm::lookAt(
				    glm::vec3(camera[0], camera[1], camera[2]), // Camera position
				    glm::vec3(position[0], position[1], position[2]), // Looking at position
				    glm::vec3(0,1,0)  // Orientation
			    );
				//apply rotation
			    memcpy(glm::value_ptr(model), this->quat.toMatrix(), sizeof(i));
				//apply translation
				model = glm::translate(model, glm::vec3(this->position.x(), this->position.y(), this->position.z()));
			    //pass to shader
		        shader->setMat4("gl_ModelViewProjectionMatrix", projection);
		        shader->setMat4("gl_ModelViewMatrix", model);
		        shader->setMat4("ViewMatrix", view);
		        shader->setVec3("light_position", vec3(2.0f, 5.0f, 2.0f));
				//draw geometry
				for (int i = 0; i < this->getTriangleCount(); i++){
					triangle* k = this->getTriangle(i);
					k->draw(shader);
				}
			glPopMatrix();
		};

	/*--------------------------------------------//
	Misc Attributes
	//--------------------------------------------*/
		/*--------------------------------------------//
		Set Global Material
		Sets the specified material to all triangles on
		the mesh
		//--------------------------------------------*/
			void mesh::setGlobalMat(char* path, int flags, int n){
				assert(n >= 0 && n <= MAX_TRIANGLE_MATERIALS);
				switch(n){
					case 0:{
						glActiveTexture(GL_TEXTURE1);
						break;
					}
					case 1:{
						glActiveTexture(GL_TEXTURE2);
						break;
					}
				}
				for (int i = 0; i < this->getTriangleCount(); i++){
					triangle* k = this->getTriangle(i);
					k->setMat(path, flags, n);
				}
				glBindTexture(GL_TEXTURE_2D, 0);
			}

		/*--------------------------------------------//
		Returns the objects last movement timer
		//--------------------------------------------*/
			int mesh::getTimer(){
				return timer;
			};

		/*--------------------------------------------//
		Returns the meshes radius for its bounding 
		geometry
		//--------------------------------------------*/
			double mesh::getRadius(){
				return radius;
			};

	/*--------------------------------------------//
	Parent/Child
	//--------------------------------------------*/
		/*--------------------------------------------//
		Get Parent
		//--------------------------------------------*/
			mesh* mesh::getParent(){
				return parent;
			}
		/*--------------------------------------------//
		Set Parent
		//--------------------------------------------*/
			void mesh::setParent(mesh* p){
				parent = p;
			}
		/*--------------------------------------------//
		Add Child
		//--------------------------------------------*/
			void mesh::addChild(mesh* c){

			}
		/*--------------------------------------------//
		Remove Child
		//--------------------------------------------*/
			void mesh::removeChild(mesh* c){
				
			}
		/*--------------------------------------------//
		Get Child
		//--------------------------------------------*/
			mesh* mesh::getChild(int i){
				return childs[i];
			}
		/*--------------------------------------------//
		Get number of children
		//--------------------------------------------*/
			int mesh::getChildCnt(){
				return childCnt;
			}

	/*--------------------------------------------//
	Mass
	//--------------------------------------------*/
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
	Vertices
	//--------------------------------------------*/
		/*--------------------------------------------//
		Get Vertices
		Retrieves all vertices in mesh and a count
		//--------------------------------------------*/
			void mesh::getVertices(vertex*** mesh, int* count){
				//maximum possible amount of vertices
				HeapSort heap;
				*mesh = (vertex**)malloc(sizeof(vertex*)*triCnt*3);
				*count = 0;
				for (int i = 0; i < triCnt; i++){
					triangle* t = getTriangle(i);
					for (int j = 0; j < 3; j++){
						vertex* v = t->getVertex(j);

						if (BinarySearch::Search((void**)mesh, *count, (void*)v) == v){
							heap = HeapSort((void**)mesh, (double**)&mesh, *count);
							(*mesh)[*count] = v;
							(*count)++;
						}
					}
				}
			}

	/*--------------------------------------------//
	Triangles
	//--------------------------------------------*/
		/*--------------------------------------------//
		Add a triangle to the mesh by specifying points
		//--------------------------------------------*/
			void mesh::addTri(vertex* &a, vertex* &b, vertex* &c){
				triangle** newtris = (triangle**) realloc(tris, sizeof(triangle*)*(triCnt+1));

				if (newtris!=NULL) {
					tris = newtris;

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
			void mesh::remTri(triangle* &tri){
				for (int i = 0; i < triCnt; i++){
					if (*tri == *(tris[i])){
						//move last object to here
						tris[i] = tris[triCnt-1];
						//trim last object
						triangle** newtris = (triangle**) realloc(tris, sizeof(triangle*)*(triCnt-1));
						//check if memory was allocated
						if (newtris!=NULL) {
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
	Nearby Meshes
	//--------------------------------------------*/
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
		Adds a nearby mesh to our list
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
		Attempts to remove a nearby mesh from our list
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
	Position
	//--------------------------------------------*/
		/*--------------------------------------------//
		Returns the meshes position in relation to the
		world space
		//--------------------------------------------*/
			vec3 mesh::getPosition(){
				return position;
			};

		/*--------------------------------------------//
		Sets the meshes position in relation to the
		world space
		//--------------------------------------------*/
			void mesh::setPosition(vec3 pos){
				position = pos;
				return;
			};
			void mesh::setPosition(double xpos, double ypos, double zpos){
				this->setPosition(vec3(xpos, ypos, zpos));
				return;
			};

	/*--------------------------------------------//
	Angles
	//--------------------------------------------*/
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
	Velocity
	//--------------------------------------------*/
		/*--------------------------------------------//
		Returns the meshes velocity in relation to the
		world space
		//--------------------------------------------*/
			vec3 mesh::getVelocity(){
				return velocity;
			};

		/*--------------------------------------------//
		Sets the meshes velocity in relation to the
		world space
		//--------------------------------------------*/
			void mesh::setVelocity(vec3 vel){
				velocity = vel;
				return;
			};
			void mesh::setVelocity(double xvel, double yvel, double zvel){
				this->setVelocity(vec3(xvel, yvel, zvel));
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
	Acceleration
	//--------------------------------------------*/
		/*--------------------------------------------//
		Returns the meshes acceleration in relation to 
		the world space
		//--------------------------------------------*/
			vec3 mesh::getAcceleration(){
				return acceleration;
			};

		/*--------------------------------------------//
		Sets the meshes acceleration in relation to the
		world space
		//--------------------------------------------*/
			void mesh::setAcceleration(vec3 acc){
				acceleration = acc;
				return;
			};
			void mesh::setAcceleration(double xacc, double yacc, double zacc){
				this->setAcceleration(vec3(xacc, yacc, zacc));
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
	Force
	//--------------------------------------------*/
		/*--------------------------------------------//
		Decide how much force this object can handle
		before deformation takes place
		//--------------------------------------------*/
			vec3 mesh::getMaxDisplacement(vec3 force){
				return (force * 0.1);
			};

		/*--------------------------------------------//
		Returns the meshes force in relation to the 
		world space
		//--------------------------------------------*/
			vec3 mesh::getForce(){
				return force;
			};

		/*--------------------------------------------//
		Sets the meshes force in relation to the
		world space
		//--------------------------------------------*/
			void mesh::setForce(vec3 frc){
				force = frc;
				return;
			};
			void mesh::setForce(double xfrc, double yfrc, double zfrc){
				this->setForce(vec3(xfrc, yfrc, zfrc));
				return;
			};
			void mesh::applyForce(vec3 frc){
				force = force + frc;
				return;
			};
			void mesh::applyForce(double xfrc, double yfrc, double zfrc){
				this->applyForce(vec3(xfrc, yfrc, zfrc));
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