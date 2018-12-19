/*--------------------------------------------//
Triangle definition
Smallest object that can be drawn
//--------------------------------------------*/
#ifndef TRIANGLE
#define TRIANGLE
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "triangle.h"

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		triangle::triangle(){
			points = (vertex**)malloc(sizeof(vertex*)*3);
			VAO = 0;
			materials[0] = NULL;
			materials[1] = NULL;
		};
		
	/*--------------------------------------------//
	Constructor with the positions specified
	//--------------------------------------------*/
		triangle::triangle(vertex* a, vertex* b, vertex* c):triangle(){
			points[0] = a;
			points[1] = b;
			points[2] = c;
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		triangle::~triangle(){
			free (points);
		};

	/*--------------------------------------------//
	Set Material
	sets the material for the specified index
	will load in a texture at the path with given 
	flags into the new material
	//--------------------------------------------*/
		void triangle::setMat(char* path, int flags, int n){
			materials[n] = new texture(path, flags);
		}

	/*--------------------------------------------//
	Overridden operators
	//--------------------------------------------*/
		bool triangle::operator==(const triangle &other) const {
			return (*getVertex(0) == *other.getVertex(0) && 
				*getVertex(1) == *other.getVertex(1) && 
				*getVertex(2) == *other.getVertex(2));
		};
		bool triangle::operator!=(const triangle &other) const {
			return *this!=other;
		};

	/*--------------------------------------------//
	Getters - returns private variable information
	//--------------------------------------------*/
		vertex* triangle::getVertex(int i) const{
			return (points[i]);
		};
		vec3 triangle::getNormal(){
			vertex* a = getVertex(0);
			vertex* b = getVertex(1);
			vertex* c = getVertex(2);

			vec3* v = new vec3(b->x() - a->x(), b->y() - a->y(), b->z() - a->z());
			vec3* w = new vec3(c->x() - a->x(), c->y() - a->y(), c->z() - a->z());

			//define some planes
			vec3 normal =  vec3(v->y()*w->x() - v->z()*w->y(), v->z()*w->x() - v->x()*w->z(), v->x()*w->y() - v->y()*w->x());
			normal.normalize();
			return normal;
		};

	/*--------------------------------------------//
	Get position - returns avg of vertices
	//--------------------------------------------*/
		vec3 triangle::getPosition(){
			vertex* a = getVertex(0);
			vertex* b = getVertex(1);
			vertex* c = getVertex(2);

			double x = (a->x() + b->x() + c->x())/3;
			double y = (a->y() + b->y() + c->y())/3;
			double z = (a->z() + b->z() + c->z())/3;

			return vec3(x, y, z);
		}

	/*--------------------------------------------//
	Checks if a point is behind the triangle and
	within the bounds of the triangle
	//--------------------------------------------*/
		bool triangle::intersects(vec3 vec){
			vertex a = *(getVertex(0));
			vertex b = *(getVertex(1));
			vertex c = *(getVertex(2));

			//plane aligned with triangle
			plane plane1 = plane(getNormal(), getPosition());

			//define 'bumper' planes
			vec3 pos2 = vec3((a.x()+b.x())/2, (a.y()+b.y())/2, (a.z()+b.z())/2);
			vec3 pos3 = vec3((c.x()+b.x())/2, (c.y()+b.y())/2, (c.z()+b.z())/2);
			vec3 pos4 = vec3((a.x()+c.x())/2, (a.y()+c.y())/2, (a.z()+c.z())/2);

			vec3 norm2 = c - pos2;
			vec3 norm3 = a - pos3;
			vec3 norm4 = b - pos4;

			norm2.normalize();
			norm3.normalize();
			norm4.normalize();

			plane plane2 = plane(norm2, pos2);
			plane plane3 = plane(norm3, pos4);
			plane plane4 = plane(norm3, pos4);

			return ( plane1.facing(vec) && !(plane2.facing(vec) || plane3.facing(vec) || plane4.facing(vec)) );
		}

	/*--------------------------------------------//
	Draws the triangle
	//--------------------------------------------*/
		void triangle::draw(Shader* shader){
			unsigned int VBO[5];
					
			vertex* u = this->getVertex(0);
			vertex* v = this->getVertex(1);
			vertex* w = this->getVertex(2);
			float vert[3][4] = {
				{u->x(), u->y(), u->z(), 1.0},
				{v->x(), v->y(), v->z(), 1.0},
				{w->x(), w->y(), w->z(), 1.0}
			};
			//normal array
			float norm[3][3] = {
				{u->nx(), u->ny(), u->nx()},
				{v->nx(), v->ny(), v->nz()},
				{w->nx(), w->ny(), w->nz()}
			};
			//color array
			float col[3][4]  = {
				{u->r(), u->g(), u->b(), 1.0},
				{v->r(), v->g(), v->b(), 1.0},
				{w->r(), w->g(), w->b(), 1.0}
			};
			//texture coordinate array
			float st[3][2]  = {
				{u->s(), u->t()},
				{v->s(), v->t()},
				{w->s(), w->t()}
			};
			//texture blending array
			float blend[3][1]  = {
				{u->blend()},
				{v->blend()},
				{w->blend()}
			};

		    glGenVertexArrays(1, &VAO);
		    glBindVertexArray(VAO);
		    glGenBuffers(5, VBO);

		    //position
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			glBufferData(GL_ARRAY_BUFFER, 3*4*sizeof(GLfloat), vert, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, (GLuint)4, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)0);

		    //normal
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
			glBufferData(GL_ARRAY_BUFFER, 3*3*sizeof(GLfloat), norm, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)1, (GLuint)3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)1);

		    //color
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
			glBufferData(GL_ARRAY_BUFFER, 3*4*sizeof(GLfloat), col, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)3, (GLuint)4, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)3);

		    //texture coordinate
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
			glBufferData(GL_ARRAY_BUFFER, 3*2*sizeof(GLfloat), st, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)4, (GLuint)2, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)4);

		    //texture blend
		    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
			glBufferData(GL_ARRAY_BUFFER, 3*1*sizeof(GLfloat), blend, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)5, (GLuint)1, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		    glEnableVertexAttribArray((GLuint)5);

			//Bind Textures
			if (materials[0] != NULL){
				shader->setInt("texture1set", 1);
	        	shader->setInt("texture1", materials[0]->index);
				glActiveTexture(GL_TEXTURE1);
				materials[0]->use();
			}else{
				shader->setInt("texture1set", 0);
			}
			if (materials[1] != NULL){
				shader->setInt("texture2set", 1);
	        	shader->setInt("texture2", materials[1]->index);
				glActiveTexture(GL_TEXTURE2);
				materials[1]->use();
			}else{
				shader->setInt("texture2set", 0);
			}
			glEnable(GL_TEXTURE_2D);

			//Draw geometry
       		glColor3f(1.0f, 1.0f, 1.0f);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			//Unbind Textures
			if (materials[0] != NULL){
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (materials[0] != NULL){
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			//Unbind ourself
	        glBindVertexArray(0);
		};
#endif