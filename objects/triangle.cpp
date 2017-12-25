/*--------------------------------------------//
Triangle definition
Smallest object that can be drawn
//--------------------------------------------*/
#ifndef TRIANGLES
#define TRIANGLES

#ifndef VERTEX
#include "vertex.cpp"
#endif

class triangle{
	private:
		vertex normal;
		double texpos;
		vertex** verts;
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		triangle(){
			verts = (vertex**)malloc(sizeof(vertex*)*3);
		};
	public:
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
				free (verts[i]);
			}
			free (verts);
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
		double getTexPos(){
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
		            glVertex3d(j->x, j->y, j->z);
				}
		    glEnd();
		};
};
#endif