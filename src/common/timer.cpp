//////////////////////////////////////////////////////////////////////////////////////////
//	TIMER.cpp
//	Functions for timer class
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////
#include "timer.h"
#include <time.h>
void TIMER::Reset()
{
	startTime=(double)clock();
}

double TIMER::GetTime()
{
	if(isPaused)
		return pauseTime-startTime;
	else
		return ((double)clock())-startTime;
}

void TIMER::Pause()
{
	//Only pause if currently unpaused
	if(isPaused)
		return;

	isPaused=true;
	pauseTime=(double)clock();
}

void TIMER::Unpause()
{
	//Only unpause if currently paused
	if(!isPaused)
		return;

	isPaused=false;

	//Update start time to reflect pause
	startTime+=((double)clock()-pauseTime);
}