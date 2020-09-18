#ifndef DIRECLIGHT_H
#define DIRECLIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../../deps/glm/glm.hpp"
    #include "../../shaders/shader.h"
    #include "../../common/vector.h"
    #include "../../common/quaternion.h"
    #include "../../globals.h"
    #include "light.h"

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h> 

/*--------------------------------------------//
Spot Light Class
//--------------------------------------------*/
    class direclight{
        private:
        protected:
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                unsigned int depthMap, FBO, buffer;

            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
                void initTex(){
                    // Create shadow texture
                    glBindTexture(GL_TEXTURE_2D, depthMap);
                    // Create empty texture
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, SHADOW_HEIGHT, SHADOW_WIDTH, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
                    // Bilinear filtering
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    // Color needs to be 0 outside of texture coordinates
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
                };
                
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                light base;
                vec3 direction;
				
            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                direclight(){
                    base = light();
                    direction = vec3(0.0f, 0.0f, -1.0f);

                    glGenFramebuffers(1, &FBO);
                    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
                    glGenRenderbuffers(1, &buffer);
                    glBindRenderbuffer(GL_RENDERBUFFER, buffer);
                    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, SHADOW_HEIGHT, SHADOW_WIDTH);
                    // Attach the renderbuffer
                    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, buffer);

                    initTex();

                    glBindFramebuffer(GL_FRAMEBUFFER, 0);
                }
            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
            	void drawTex(Shader* shad){
                    //Position and orient camera.
                    int viewerAltitude = -asin(-direction[2]);
                    int viewerAzimuth = atan2(-direction[1], -direction[0]);
                    int viewerDistance = 20;
                    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f );
                    glm::quat quat = glm::quat(glm::vec3(viewerAltitude, viewerAzimuth, 0.0));
                    glm::mat4 looking = toMat4(quat);
                    glm::vec4 camera = looking * glm::vec4(position.x + 0.0f, position.y + 0.0f, position.z + 1.0f*viewerDistance, 1.0f);

                    //Create project matrix
                    glm::mat4 projection;
                    projection = glm::perspective(glm::radians(FRUSTUM_FIELD_OF_VIEW), (float)SHADOW_WIDTH/SHADOW_HEIGHT, (float)FRUSTUM_NEAR_PLANE, (float)FRUSTUM_FAR_PLANE);
                    //Find up vector
                    glm::vec4 up = looking * glm::vec4(0,1,0,1);
                    //Create view matrix
                    glm::mat4 view;
                    view = glm::lookAt(
                        glm::vec3(camera[0], camera[1], camera[2]),
                        position,
                        glm::vec3(up[0], up[1], up[2])
                    );
                    glm::mat4 lightSpaceMatrix = projection * view;
                    glBindFramebuffer(GL_FRAMEBUFFER,FBO);
                    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,0,0);
                    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthMap,0);
                    shad->setMat4("ViewMatrix", view);
                    shad->setMat4("ProjectionMatrix", projection);
            	}
            	void bindTex(Shader* shad){
                    //Position and orient camera.
                    int viewerAltitude = -asin(-direction[2]);
                    int viewerAzimuth = atan2(-direction[1], -direction[0]);
                    int viewerDistance = 20;
                    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f );
                    glm::quat quat = glm::quat(glm::vec3(viewerAltitude, viewerAzimuth, 0.0));
                    glm::mat4 looking = toMat4(quat);
                    glm::vec4 camera = looking * glm::vec4(position.x + 0.0f, position.y + 0.0f, position.z + 1.0f*viewerDistance, 1.0f);

                    //Create project matrix
                    glm::mat4 projection;
                    projection = glm::perspective(glm::radians(FRUSTUM_FIELD_OF_VIEW), (float)SHADOW_WIDTH/SHADOW_HEIGHT, (float)FRUSTUM_NEAR_PLANE, (float)FRUSTUM_FAR_PLANE);
                    //Find up vector
                    glm::vec4 up = looking * glm::vec4(0,1,0,1);
                    //Create view matrix
                    glm::mat4 view;
                    view = glm::lookAt(
                        glm::vec3(camera[0], camera[1], camera[2]),
                        position,
                        glm::vec3(up[0], up[1], up[2])
                    );
                    glm::mat4 lightSpaceMatrix = projection * view;
                    shad->setMat4("LightSpaceMatrix", lightSpaceMatrix);
                    shad->setInt("DepthMap", depthMap);
                    shad->setVec3("DirecLight.direction", (glm::vec3)direction);
                    shad->setVec3("DirecLight.base.color", (glm::vec3)base.color);

 					//Bind & enable shadow map texture
 					glActiveTexture(GL_TEXTURE0 + depthMap);
 					glBindTexture(GL_TEXTURE_2D, depthMap);
            	};
    };
#endif