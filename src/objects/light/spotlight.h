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
            Class Variables
            //--------------------------------------------*/
                glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, FRUSTUM_NEAR_PLANE, FRUSTUM_FAR_PLANE);
                std::vector<glm::mat4> shadowTransforms;
            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
                void initTex(){
                    shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
                    shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
                    shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
                    shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
                    shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
                    shadowTransforms.push_back(shadowProj * glm::lookAt((glm::vec3)position, (glm::vec3)position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
                
                    //Create the shadow map texture
                    glGenTextures(1, &depthMap);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);
				    for (unsigned int i = 0; i < 6; ++i)
	                    glTexImage2D(   GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
	                                    GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
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
				
            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                spotlight(){
                    direclight();

                    position = vec3(0.0f, 0.0f, 0.0f);
                    fov = 360.0f;
                    constant = 1.0f;
                    linear = 1.0f;
                    exponential = 1.0f;

                    initTex();
                }
            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
            	void drawTex(Shader* shad){
                    glBindFramebuffer(GL_FRAMEBUFFER,FBO);
					shad->setVec3("LightPos", position);
					shad->setFloat("Far_Plane", FRUSTUM_FAR_PLANE);

					for (unsigned int i = 0; i < 6; ++i){
						char c = i+'0';
						shad->setMat4((string("ShadowMatrices[") + c + string("]")).c_str(), shadowTransforms[i]);
					}
                    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,0,0);
                    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthMap,0);
            	}
            	void bindTex(Shader* shad){
                    shad->setInt("DepthMap", depthMap);
                    shad->setVec3("SpotLight.position", (glm::vec3)position);
                    shad->setFloat("SpotLight.constant", constant);
                    shad->setFloat("SpotLight.linear", linear);
                    shad->setFloat("SpotLight.exponential", exponential);
                    shad->setVec3("SpotLight.direc.direction", (glm::vec3)direction);
                    shad->setVec3("SpotLight.direc.base.color", (glm::vec3)base.color);
 	
 					//Bind & enable shadow map texture
 					glActiveTexture(GL_TEXTURE0 + depthMap);
            		glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);
            	};
    };
#endif