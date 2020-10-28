#ifndef DIRECLIGHT_H
#define DIRECLIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../../globals.h"
	#include "../../shaders/shader.h"
	#include "../../common/vector.h"
	#include "../../common/quaternion.h"

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
				unsigned int depthMap, FBO, buffer;
				unsigned int ShadowMapFBO, ShadowMapTexture;
				Mat4 LightProjectionMatrix;
				Mat4 LightViewMatrix;
		public: 
			/*--------------------------------------------//
			Class Variables
			//--------------------------------------------*/
				Vec3 color;
				Vec3 direction;
				
			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				direclight(){
					color = Vec3(1.0f, 1.0f, 1.0f);
					direction = Vec3(0.0f, 0.0f, -1.0f);

					LightProjectionMatrix.Perspective(TORAD(45.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, (float)FRUSTUM_NEAR_PLANE, (float)FRUSTUM_FAR_PLANE);
				
					//Create the shadow map frame buffer for directional lights
					glGenFramebuffers(1, &ShadowMapFBO);
					glGenTextures(1, &ShadowMapTexture);
					glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);
					glTexImage2D(	GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
									GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
					float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
					glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
					glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMapTexture, 0);
					glDrawBuffer(GL_NONE);
					glReadBuffer(GL_NONE);
					glBindFramebuffer(GL_FRAMEBUFFER, 0);
				}
			/*--------------------------------------------//
			Functions
			//--------------------------------------------*/
				void drawTex(Shader* shad){
					LightViewMatrix.LookAt(direction, Vec3(0,0,0), Vec3(0,1,0));
					
					glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
					glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					glActiveTexture(GL_TEXTURE0 + ShadowMapTexture);
					glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);

					shad->setMat4("CameraProjectionMatrix", LightProjectionMatrix);
					shad->setMat4("LightProjectionMatrix", LightProjectionMatrix);
					shad->setMat4("CameraViewMatrix", LightViewMatrix);
					shad->setMat4("LightViewMatrix", LightViewMatrix);
				}
				void bindTex(Shader* shad){
					glActiveTexture(GL_TEXTURE0 + ShadowMapTexture);
					glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);

					shad->setMat4("LightProjectionMatrix", LightProjectionMatrix);
					shad->setMat4("LightViewMatrix", LightViewMatrix);
					shad->setVec3("DirecLight.color", color);
					shad->setVec3("DirecLight.direction", direction);
					shad->setInt("DepthMap", ShadowMapTexture);
					shad->setInt("ALIAS", DIRECTIONAL_ALIAS);
				};
	};
#endif