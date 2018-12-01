/*--------------------------------------------//
Element header
This is the parent class of any user interface
element.  Its children should expand on the
functionality here.  This guarantees functions
for the interface class.
//--------------------------------------------*/
#ifndef ELEMENT_H
#define ELEMENT_H
class element;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "interface.h"

class element{
	private:
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			interface* ui;//the containing interface
			element* parent;//the elements parent if any

	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			element();

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
			~element();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void setInterface(interface* u);
			interface* getInterface();
			void setParent(element* p);
			element* getParent();
			virtual void draw(){}
};
#endif