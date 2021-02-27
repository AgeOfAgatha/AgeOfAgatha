/*--------------------------------------------//
Interface header
This is the root object holding any user
interface.  This is like the world for physics.
//--------------------------------------------*/
#ifndef INTERFACE_H
#define INTERFACE_H
class uinterface;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "../globals.h"

	#include "element.h"

	#include <stdlib.h>
	#include <stdio.h>

class uinterface{
	private:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			element** ui;
			int uiNum;

	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			uinterface();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void add(element* e);
			void remove(element* e);
			void draw();
};
#endif
