#ifndef DIRECLIGHT_H
#define DIRECLIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../globals.h"
    #include "../../shaders/shader.h"
    #include "light.h"

    #include <stdlib.h>
    #include <stdio.h>

/*--------------------------------------------//
Spot Light Class
//--------------------------------------------*/
    class direclight{
        private:
        protected:
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                unsigned int depthMap;

            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
                void initTex(){
                    //Create the shadow map texture
                    glGenTextures(1, &depthMap);
                    glBindTexture(GL_TEXTURE_2D, depthMap);
                    glTexImage2D(   GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
                                    GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                };
                
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                light base;
                vec3 direction;
				glm::mat4 lightProjectionMatrix, lightViewMatrix;
				
            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                direclight(){
                    base = light();
                    direction = vec3(0.0f, 0.0f, -1.0f);

                    initTex();

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
                }
            /*--------------------------------------------//
            Functions
            //--------------------------------------------*/
            	void drawTex(Shader* shad){
					glm::mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;
					shad->setMat4("LightSpaceMatrix", lightSpaceMatrix);
            	}
            	void copyTex(){
					//Read the depth buffer into the shadow map texture
					glBindTexture(GL_TEXTURE_2D, depthMap);
					glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SHADOW_HEIGHT, SHADOW_WIDTH);
            	}
            	void bindTex(Shader* shad){
            		shad->setInt("DepthMap", depthMap);
 					shad->setVec3("DirecLight.direction", (glm::vec3)direction);
 					shad->setVec3("DirecLight.base.color", (glm::vec3)base.color);

 					//Bind & enable shadow map texture
 					glActiveTexture(GL_TEXTURE0 + depthMap);
 					glBindTexture(GL_TEXTURE_2D, depthMap);
            	};
    };
#endif