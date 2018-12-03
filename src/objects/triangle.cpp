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
			verts = (vertex**)malloc(sizeof(vertex*)*3);
		};
		
	/*--------------------------------------------//
	Constructor with the positions specified
	//--------------------------------------------*/
		triangle::triangle(vertex* &a, vertex* &b, vertex* &c):triangle(){
			(verts[0]) = a;
			(verts[1]) = b;
			(verts[2]) = c;
		};

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		triangle::~triangle(){
			for (int i = 0; i < 3; i++){
				free (verts[i]);
			}
			free (verts);
		};

	/*--------------------------------------------//
	Overridden operators
	//--------------------------------------------*/
		bool triangle::operator==(const triangle &other) const {
			return (this->verts[0] == other.verts[0] && this->verts[1] == other.verts[1] && this->verts[2] == other.verts[2]);
		};
		bool triangle::operator!=(const triangle &other) const {
			return *this!=other;
		};

	/*--------------------------------------------//
	Getters - returns private variable information
	//--------------------------------------------*/
		vertex* triangle::getVertex(int i){
			return (verts[i]);
		};
		vec3 triangle::getNormal(){
			vertex* a = verts[0];
			vertex* b = verts[1];
			vertex* c = verts[2];

			vec3* v = new vec3(b->x() - a->x(), b->y() - a->y(), b->z() - a->z());
			vec3* w = new vec3(c->x() - a->x(), c->y() - a->y(), c->z() - a->z());

			//define some planes
			vec3 normal =  vec3(v->y()*w->x() - v->z()*w->y(), v->z()*w->x() - v->x()*w->z(), v->x()*w->y() - v->y()*w->x());
			normal.normalize();
			return normal;
		};
		double triangle::getTexPos(){
			return texpos;
		};

	/*--------------------------------------------//
	Get position - returns avg of vertices
	//--------------------------------------------*/
		vec3 triangle::getPosition(){
			vertex* a = verts[0];
			vertex* b = verts[1];
			vertex* c = verts[2];

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
			vertex a = *(verts[0]);
			vertex b = *(verts[1]);
			vertex c = *(verts[2]);

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
		void triangle::draw(){
			glBegin(GL_TRIANGLES);
				for (int i = 0; i < 3; i++){
					vertex* j = this->getVertex(i);
		            glVertex3d(j->x(), j->y(), j->z());
				}
		    glEnd();
		};
#endif