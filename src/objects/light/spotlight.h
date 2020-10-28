#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

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
	class spotlight{
		private:
		protected:
			/*--------------------------------------------//
			Class Variables
			//--------------------------------------------*/
				Mat4 LightProjectionMatrix;
				unsigned int ShadowMapFBO, ShadowMapTexture;
		public: 
			/*--------------------------------------------//
			Class Variables
			//--------------------------------------------*/
				Vec3 position;
				float fov;
				float constant;
				float linear;
				float exponential;
				Vec3 color;
				
			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				spotlight(){
					color = Vec3(0.0f, 0.0f, 0.0f);
					position = Vec3(0.0f, 0.0f, 0.0f);
					fov = 360.0f;
					constant = 0.0f;
					linear = 0.0f;
					exponential = 0.0f;

					
					LightProjectionMatrix.Perspective(TORAD(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, (float)FRUSTUM_NEAR_PLANE, (float)FRUSTUM_FAR_PLANE);
					
					//Create the shadow map frame buffer for directional lights
					glGenFramebuffers(1, &ShadowMapFBO);
					glGenTextures(1, &ShadowMapTexture);
					glBindTexture(GL_TEXTURE_CUBE_MAP, ShadowMapTexture);
					for (unsigned int i = 0; i < 6; ++i)
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
					glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
					glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ShadowMapTexture, 0);
					glDrawBuffer(GL_NONE);
					glReadBuffer(GL_NONE);
					glBindFramebuffer(GL_FRAMEBUFFER, 0);
				}
			/*--------------------------------------------//
			Functions
			//--------------------------------------------*/
				void drawTex(Shader* shad){
					Mat4 LightViewMatrix;
					std::vector<Mat4> shadowTransforms;
					shadowTransforms.push_back(LightProjectionMatrix * LightViewMatrix.LookAt(position, position + Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f)));
					shadowTransforms.push_back(LightProjectionMatrix * LightViewMatrix.LookAt(position, position + Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f)));
					shadowTransforms.push_back(LightProjectionMatrix * LightViewMatrix.LookAt(position, position + Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f)));
					shadowTransforms.push_back(LightProjectionMatrix * LightViewMatrix.LookAt(position, position + Vec3(0.0f, -1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f)));
					shadowTransforms.push_back(LightProjectionMatrix * LightViewMatrix.LookAt(position, position + Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, -1.0f, 0.0f)));
					shadowTransforms.push_back(LightProjectionMatrix * LightViewMatrix.LookAt(position, position + Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, -1.0f, 0.0f)));
					
					glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
					glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					glActiveTexture(GL_TEXTURE0 + ShadowMapTexture);
					glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);

					shad->setVec3("lightPos", position);
					shad->setFloat("far_plane", FRUSTUM_FAR_PLANE);
					for (int i = 0; i < 6; ++i)
						shad->setMat4("shadowMatrices[" + patch::to_string(i) + "]", shadowTransforms[i]);

				}
				void bindTex(Shader* shad){
					glActiveTexture(GL_TEXTURE0 + ShadowMapTexture);
					glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);

					shad->setVec3("SpotLight.position", position);
					shad->setFloat("SpotLight.fov", fov);
					shad->setFloat("SpotLight.constant", constant);
					shad->setFloat("SpotLight.linear", linear);
					shad->setFloat("SpotLight.exponential", exponential);
					shad->setVec3("SpotLight.color", color);
					shad->setFloat("far_plane", FRUSTUM_FAR_PLANE);
					shad->setInt("DepthMap", ShadowMapTexture);
					shad->setInt("ALIAS", SPOTLIGHT_ALIAS);
				};
	};
#endif