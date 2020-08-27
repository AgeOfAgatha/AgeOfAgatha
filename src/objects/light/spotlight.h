#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../globals.h"
    #include "../../shaders/shader.h"
    #include "light.h"
    #include "direclight.h"

    #include <stdlib.h>
    #include <stdio.h>

/*--------------------------------------------//
Spot Light Class
//--------------------------------------------*/
    class spotlight: public direclight{
        private:
        protected:
            /*--------------------------------------------//
            FunctionslightProjectionMatrixlightProjectionMatrixlightProjeclightProjectionMatrix
            //--------------------------------------------*/
                void initTex(){
                    //Create the shadow map texture
                    glGenTextures(1, &depthMap);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);
				    for (unsigned int i = 0; i < 6; ++i)
	                    glTexImage2D(   GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
	                                    GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
				    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                };
                
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                vec3 position;
                float fov;
                float constant;
                float linear;
                float exponential;
				glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, FRUSTUM_NEAR_PLANE, FRUSTUM_FAR_PLANE);
				std::vector<glm::mat4> shadowTransforms;
				
            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                spotlight(){
                    position = vec3(0.0f, 0.0f, 0.0f);
                    fov = 360.0f;
                    constant = 1.0f;
                    linear = 1.0f;
                    exponential = 1.0f;

                    initTex();

                    //glm::mat4 lightProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, FRUSTUM_NEAR_PLANE, FRUSTUM_FAR_PLANE);
					//glm::mat4 lightViewMatrix = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3( 0.0f, 0.0f,  0.0f), glm::vec3( 0.0f, 1.0f,  0.0f)); 
					glPushMatrix();

					glLoadIdentity();
					gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
					glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&lightProjectionMatrix[0][0]);
					
					glLoadIdentity();
					gluLookAt(	direction[0], direction[1], direction[2],
								0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f);
					glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&lightViewMatrix[0][0]);
					
					glPopMatrix();


					shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
					shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
					shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
					shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
					shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
					shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
                }
            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
            	void drawTex(Shader* shad){
					shad->use();
					shad->setVec3("LightPos", position);
					shad->setFloat("Far_Plane", FRUSTUM_FAR_PLANE);
					
					glm::mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;
					shad->setMat4("LightSpaceMatrix", lightSpaceMatrix);
					//glMatrixMode(GL_PROJECTION);
					//glLoadMatrixf((GLfloat*)&lightProjectionMatrix[0][0]);
					//glMatrixMode(GL_MODELVIEW);
					//glLoadMatrixf((GLfloat*)&lightViewMatrix[0][0]);
					
					for (unsigned int i = 0; i < 6; ++i){
						char c = i+'0';
						shad->setMat4((string("ShadowMatrices[") + c + string("]")).c_str(), shadowTransforms[i]);
					}
            	}
            	void copyTex(){
					//Read the depth buffer into the shadow map texture
 					glActiveTexture(GL_TEXTURE0 + depthMap);
					glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);
					glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SHADOW_HEIGHT, SHADOW_WIDTH);
            	}
            	void bindTex(Shader* shad){
            		shad->use();
            		shad->setInt("DepthMap", depthMap);
 					shad->setVec3("SpotLight.position", (glm::vec3)position);
 					shad->setFloat("SpotLight.constant", constant);
 					shad->setFloat("SpotLight.linear", linear);
 					shad->setFloat("SpotLight.exponential", exponential);
 					shad->setVec3("SpotLight.direc.direction", (glm::vec3)direction);
 					shad->setVec3("SpotLight.direc.base.color", (glm::vec3)base.color);
					glm::mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;
					shad->setMat4("LightSpaceMatrix", lightSpaceMatrix);
 	
 					//Bind & enable shadow map texture
 					glActiveTexture(GL_TEXTURE0 + depthMap);
            		glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);
            	};
    };
#endif