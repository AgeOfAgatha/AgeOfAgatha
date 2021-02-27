/*--------------------------------------------//
Skeleton definition
defines how a mesh moves and interacts for a
actor.  Uses bones and joints.
//--------------------------------------------*/
#ifndef SKELETON
#define SKELETON
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "skeleton.h"

	/*--------------------------------------------//
	Default Constructor
	//--------------------------------------------*/
		skeleton::skeleton():mesh(){
			root = NULL;
			parity = false;
		}

	/*--------------------------------------------//
	Drawing function
	this will call each vertex's drawing function
	in groupings of three (their owning triangle)
	each triangle then will apply translations
	according to its parent bone.
	//--------------------------------------------*/
		void skeleton::draw(Shader* shader){
			glPushMatrix();
				//Apply Transformations
				if(deuler == true){
					quat = glm::quat(glm::vec3(euler.p, euler.y, euler.r));
					deuler = false;
				}
				glm::mat4 model = glm::toMat4(quat);
				model = glm::translate(model, glm::vec3(this->position.x, this->position.y, this->position.z));
		    	shader->setMat4("ModelMatrix", model);
		        shader->setVec3("light_position", vec3(2.0f, 5.0f, 2.0f));
				//draw geometry
				for (int i = 0; i < this->getTriangleCount(); i++){
					triangle* k = this->getTriangle(i);
					k->draw(shader);
				}
			glPopMatrix();
			parity = !parity;//flip our parity flag
		}

	/*--------------------------------------------//
	Update functions
	this advances the object's current motion/animation
	//--------------------------------------------*/
		void skeleton::updateAcc(){
			this->setAcceleration(force/mass);
			this->setAngAcc(angFrc);
			root->updateAcc();//Only difference from mesh
		};
		void skeleton::updateVel(){
			this->setVelocity(velocity + acceleration);
			this->setAngVel(angVel + angAcc);
			root->updateVel();//Only difference from mesh
		};
		void skeleton::updatePos(){
			this->setPosition(position + velocity);
			this->setAngles(euler + angVel);
			root->updatePos();//Only difference from mesh

			if(deuler == true){
				quat = glm::quat(glm::vec3(euler.p, euler.y, euler.r));
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