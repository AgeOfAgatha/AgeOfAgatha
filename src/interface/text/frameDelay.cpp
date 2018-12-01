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
			//set text to blank
			memset(text, 0, MAX_CHARACTERS_TEXT);
			//default color
			color[0] = DEFAULT_TEXT_COLOR[0];
			color[1] = DEFAULT_TEXT_COLOR[1];
			color[2] = DEFAULT_TEXT_COLOR[2];
			//default position
			pos[0] = DEFAULT_TEXT_POS[0];
			pos[1] = DEFAULT_TEXT_POS[1];
			pos[2] = DEFAULT_TEXT_POS[2];
			//initialize time
			oldtime = 0;
		}

	/*--------------------------------------------//
	Set Position
	//--------------------------------------------*/
		void FrameDelay::setPos(vec3 p){
			pos[0] = p.x();
			pos[1] = p.y();
			pos[2] = p.z();
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
		vec3 FrameDelay::getPos(){
			return vec3((double)pos[0], (double)pos[1], (double)pos[2]);
		}

	/*--------------------------------------------//
	Set Color
	//--------------------------------------------*/
		void FrameDelay::setColor(vec3 p){
			color[0] = p.x();
			color[1] = p.y();
			color[2] = p.z();
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
		vec3 FrameDelay::getColor(){
			return vec3((double)color[0], (double)color[1], (double)color[2]);
		}

	/*--------------------------------------------//
	Draw function
	//--------------------------------------------*/
		void FrameDelay::draw(){
			glPushMatrix();
				// Measure speed
				double newtime = glutGet(GLUT_ELAPSED_TIME);
				sprintf (text, "%0.0lfms", newtime - oldtime);
				glTranslatef(pos[0], pos[1], pos[2]);
				glRasterPos3f(0.0, 0.0, 0.0);
				glColor3f(color[0], color[1], color[2]);
				int len = strlen(text);
				for (int i = 0; i < len; i++) {
				    //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
				}
				oldtime = newtime;
			glPopMatrix();
		}
#endif