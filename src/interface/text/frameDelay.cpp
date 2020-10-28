/*--------------------------------------------//
Frame Delay Definition
This displays the frames delay at the top
left hand corner of the window
//--------------------------------------------*/
#ifndef FRAMEDELAY
#define FRAMEDELAY
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "frameDelay.h"

	/*--------------------------------------------//
	Constructors
	//--------------------------------------------*/
		FrameDelay::FrameDelay():element(){
			//default color
			color[0] = DEFAULT_TEXT_COLOR_R;
			color[1] = DEFAULT_TEXT_COLOR_G;
			color[2] = DEFAULT_TEXT_COLOR_B;
			//default position
			pos[0] = DEFAULT_TEXT_POS_X;
			pos[1] = DEFAULT_TEXT_POS_Y;
			pos[2] = DEFAULT_TEXT_POS_Z;
			//initialize time
			oldtime = 0;
		}

	/*--------------------------------------------//
	Set Position
	//--------------------------------------------*/
		void FrameDelay::setPos(Vec3 p){
			pos[0] = p.x;
			pos[1] = p.y;
			pos[2] = p.z;
		}
		void FrameDelay::setPos(float p[]){
			pos[0] = p[0];
			pos[1] = p[1];
			pos[2] = p[2];
		}
		void FrameDelay::setPos(float x, float y, float z){
			pos[0] = x;
			pos[1] = y;
			pos[2] = z;
		}

	/*--------------------------------------------//
	Get Position
	//--------------------------------------------*/
		Vec3 FrameDelay::getPos(){
			return Vec3((double)pos[0], (double)pos[1], (double)pos[2]);
		}

	/*--------------------------------------------//
	Set Color
	//--------------------------------------------*/
		void FrameDelay::setColor(Vec3 p){
			color[0] = p.x;
			color[1] = p.y;
			color[2] = p.z;
		}
		void FrameDelay::setColor(float p[]){
			color[0] = p[0];
			color[1] = p[1];
			color[2] = p[2];
		}
		void FrameDelay::setColor(float x, float y, float z){
			color[0] = x;
			color[1] = y;
			color[2] = z;
		}

	/*--------------------------------------------//
	Get Color
	//--------------------------------------------*/
		Vec3 FrameDelay::getColor(){
			return Vec3((double)color[0], (double)color[1], (double)color[2]);
		}

	/*--------------------------------------------//
	Draw function
	//--------------------------------------------*/
		void FrameDelay::draw(){
			//measure speed
			time_t curtime;
			char buf[255];
			static double latency = 0;
			static time_t lastime = 0;
			static int fps = 0;

			// Update frames-per-second
			curtime = clock();
			latency = ((double)(curtime - lastime)/CLOCKS_PER_SEC);
			if (latency > 0)
				fps = 1 / latency;
			lastime = curtime;

			//Print fps
			static char fpsString[32];
			memset(fpsString, '\0', sizeof(fpsString));
			sprintf(fpsString, "%.2lfms\n%d FPS", latency,fps);

			//Set matrices for ortho
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			//Print text
			glRasterPos2f(-1.0f, 0.9f);
			for(unsigned int i=0; i<strlen(fpsString); ++i)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fpsString[i]);

			//reset matrices
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();

			glFinish();
			glutSwapBuffers();
			glutPostRedisplay();
		}
#endif
