/*--------------------------------------------//
Element definition
This is the parent class of any user interface
element.  Its children should expand on the
functionality here.  This guarantees functions
for the interface class.
//--------------------------------------------*/
#ifndef ELEMENTS
#define ELEMENTS
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "element.h"

	/*--------------------------------------------//
	Constructor
	//--------------------------------------------*/
		element::element(){
			ui = NULL;
			parent = NULL;
		}

	/*--------------------------------------------//
	Destructor
	//--------------------------------------------*/
		element::~element(){
			//nothing here yet
		}

	/*--------------------------------------------//
	Set Interface
	//--------------------------------------------*/
		void element::setInterface(interface* u){
			ui = u;
		}

	/*--------------------------------------------//
	Get Interface
	//--------------------------------------------*/
		interface* element::getInterface(){
			return ui;
		}

	/*--------------------------------------------//
	Set Parent Element
	//--------------------------------------------*/
		void element::setParent(element* p){
			parent = p;
		}

	/*--------------------------------------------//
	Get Parent Element
	//--------------------------------------------*/
		element* element::getParent(){
			return parent;
		}
#endif