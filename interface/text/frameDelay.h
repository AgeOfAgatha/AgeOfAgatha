/*--------------------------------------------//
Frame Delay Header
This displays the frames delay at the top
left hand corner of the window
//--------------------------------------------*/
#ifndef FRAMEDELEY_H
#define FRAMEDELAY_H
class FrameDelay;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../../globals.h"
	#include "../element.h"
	#include "../../common/vector.h"

class FrameDelay:public element{
	private:
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			double oldtime;//For Performance Tracking
			char text[MAX_CHARACTERS_TEXT];
			float color[3];//color of text
			float pos[3];//position of text
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			FrameDelay();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void setPos(vector p);
			void setPos(float p[]);
			void setPos(float x, float y, float z);
			vector getPos();
			void setColor(vector p);
			void setColor(float p[]);
			void setColor(float x, float y, float z);
			vector getColor();
			void draw();
};
#endif