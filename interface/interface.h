/*--------------------------------------------//
Interface header
This is the root object holding any user
interface.  This is like the world for physics.
//--------------------------------------------*/
#ifndef INTERFACE_H
#define INTERFACE_H
class interface;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <stdlib.h>
	#include <stdio.h>
	#include "element.h"
	#if defined(__APPLE__)
		#include <GLUT/glut.h>
	#else
		#include <GL/glut.h>
	#endif

class interface{
	private:
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			element** ui;
			int uiNum;

	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			interface();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void add(element* e);
			void remove(element* e);
			void draw();
};
#endif