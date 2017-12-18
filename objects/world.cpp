////////////////////////////////////////////////////////////////////
/*
//World Definition file - sets up the physics world space and classes
*/
////////////////////////////////////////////////////////////////////
/*--------------------------------------------//
Vertex definition
This is used to simplify definition of points
//--------------------------------------------*/
class vertex{
	public:
		float x;
		float y;
		float z; 
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		vertex(){
			x = 0;
			y = 0;
			z = 0;
		};

		/*--------------------------------------------//
		Constuctor with positions specified
		//--------------------------------------------*/
		vertex(float xi, float yi, float zi):vertex(){
			x = xi;
			y = yi;
			z = zi;
		};

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~vertex(){};

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
		bool operator==(const vertex &other) const {
			return (this->x == other.x && this->y == other.y && this->z == other.z);
		};
		bool operator!=(const vertex &other) const {
			return *this!=other;
		};
};

/*--------------------------------------------//
Triangle definition
Smallest object that can be drawn
//--------------------------------------------*/
class triangle{
	private:
		vertex normal;
		float texpos;
	public:
		vertex** verts;
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		triangle(){
			verts = (vertex**)malloc(sizeof(vertex*)*3);
			for (int i = 0; i < 3; i++){
				verts[i] = (vertex*)malloc(sizeof(vertex));
			}
		};

		/*--------------------------------------------//
		Constructor with the positions specified
		//--------------------------------------------*/
		triangle(vertex* &a, vertex* &b, vertex* &c):triangle(){
			(verts[0]) = a;
			(verts[1]) = b;
			(verts[2]) = c;
		};

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~triangle(){
			for (int i = 0; i < 3; i++){
				delete (verts[i]);
			}
			delete verts;
		};

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
		bool operator==(const triangle &other) const {
			return (this->verts[0] == other.verts[0] && this->verts[1] == other.verts[1] && this->verts[2] == other.verts[2]);
		};
		bool operator!=(const triangle &other) const {
			return *this!=other;
		};

		/*--------------------------------------------//
		Getters - returns private variable information
		//--------------------------------------------*/
		vertex* getVertex(int i){
			return (verts[i]);
		};
		vertex getNormal(){
			return normal;
		};
		float getTexPos(){
			return texpos;
		};

		/*--------------------------------------------//
		Draws the triangle
		//--------------------------------------------*/
		void draw(){
			glBegin(GL_TRIANGLES);
				glColor3f(1.0, 1.0, 1.0);
				for (int i = 0; i < 3; i++){
					vertex* j = this->getVertex(i);
		            glVertex3f(j->x, j->y, j->z);
				}
		    glEnd();
		};
};

/*--------------------------------------------//
Mesh definition
This is our basic object
//--------------------------------------------*/
class mesh{
	private:
		int triCnt;
		triangle** tris;
		int vertsCnt;
		vertex** verts;
		vertex velocity;
		vertex COM;//center of mass

		/*--------------------------------------------//
		Attempts to add a vertex to our vertex list
		//--------------------------------------------*/
		void addVertex(vertex* &v){
			for (int i = 0; i < vertsCnt; i++){
				if (verts[i] == v){
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
			velocity = vertex(0,0,0);
			COM = vertex(0,0,0);
		};

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~mesh(){
			for (int i = 0; i < this->getTriangleCount(); i++){
				//delete (triangle*)(this->getTriangle(i));
			}
		};

		/*--------------------------------------------//
		Add a triangle to the mesh by specifying points
		//--------------------------------------------*/
		void addTri(vertex* &a, vertex* &b, vertex* &c){
			int i;
			triangle** newtris = (triangle**)malloc(sizeof(triangle*)*(triCnt+1));
			for (i = 0; i < triCnt; i++){
				newtris[i] = tris[i];
			}
			newtris[i] = (triangle*)malloc(sizeof(triangle));
			*(newtris[i]) = triangle();
			newtris[i]->verts[0] = a;
			newtris[i]->verts[1] = b;
			newtris[i]->verts[2] = c;

			triangle** temp = tris;
			tris = newtris;
			//delete temp;
			triCnt++;
		};

		/*--------------------------------------------//
		Removes the passed triangle object if found
		//--------------------------------------------*/
		void remove(triangle &tri){
			int i;
			for (i = 0; i < triCnt; i++){
				if (tri == *(tris[i])){
					triangle** newtris = (triangle**)malloc(sizeof(triangle*)*triCnt);
					for (int j = 0; i < triCnt; i++){
						if (j < i){
							newtris[j] = tris[j];
						}else{
							newtris[j] = tris[j+1];
						}
					}
					triangle** temp = tris;
					tris = newtris;
					delete temp;
					triCnt--;
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
		Drawing functions
		this gets deferred to each triangles to draw
		//--------------------------------------------*/
		void draw(){
			for (int i = 0; i < this->getTriangleCount(); i++){
				triangle* k = this->getTriangle(i);
				k->draw();
			}
		};
};

/*--------------------------------------------//
World definition
This is where the simulation is controlled
//--------------------------------------------*/
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
			timestep = 20;
			objCnt = 0;
			objects = NULL;
		};

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~world(){
			for (int i = 0; i < this->getObjectCount(); i++){
				delete (mesh*)(this->getObject(i));
			}
		};

		/*--------------------------------------------//
		Adds a object to the world space
		takes a mesh as a parameter
		//--------------------------------------------*/
		void add(mesh* &obj){
			int i;
			mesh** newobjs = (mesh**)malloc(sizeof(mesh*)*(objCnt+1));
			for (i = 0; i < objCnt; i++){
				newobjs[i] = objects[i];
			}
			newobjs[i] = obj;
			mesh** temp = objects;
			objects = newobjs;
			delete temp;
			objCnt++;
		};

		/*--------------------------------------------//
		Removes the specified object from the world
		does nothing if it is not found
		//--------------------------------------------*/
		void remove(mesh* &obj){
			int i;
			for (i = 0; i < objCnt; i++){
				if (obj == objects[i]){
					mesh** newobjs = (mesh**)malloc(sizeof(mesh*)*objCnt);
					for (int j = 0; i < objCnt; i++){
						if (j < i){
							newobjs[j] = objects[j];
						}else{
							newobjs[j] = objects[j+1];
						}
					}
					objects = newobjs;
					objCnt--;
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
			return;
		};
};