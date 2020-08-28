//////////////////////////////////////////////////////////////////////////////////////////
//	TIMER.h
//	Timer class
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef TIMER_H
#define TIMER_H

class TIMER
{
public:
	TIMER()	:	isPaused(false)
	{	Reset();	}
	~TIMER()	{}

	void Reset();
	double GetTime();

	void Pause();
	void Unpause();

protected:
	double startTime;

	bool isPaused;
	double pauseTime;
};

#endif	//TIMER_H