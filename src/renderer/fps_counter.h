//////////////////////////////////////////////////////////////////////////////////////////
//	FPS_COUNTER.h
//	Frames per sceond counter class
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

class FPS_COUNTER
{
public:
	FPS_COUNTER()	:	fps(0.0f), lastTime(0.0f), frames(0), time(0.0f)
	{}
	~FPS_COUNTER()	{}

	void Update(void);
	float GetFps(void)	{	return fps;	}

protected:
	float fps;

	float lastTime;
	int frames;
	float time;
};

#endif	//FPS_COUNTER_H