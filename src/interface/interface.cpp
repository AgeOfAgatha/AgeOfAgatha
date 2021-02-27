/*--------------------------------------------//
Interface Definition
This is the root object holding any user
interface.  This is like the world for physics.
//--------------------------------------------*/
#ifndef UI
#define UI
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "interface.h"

	/*--------------------------------------------//
	Constructors
	//--------------------------------------------*/
		uinterface::uinterface(){
			ui = NULL;
			uiNum = 0;
		}

	/*--------------------------------------------//
	Add element
	//--------------------------------------------*/
		void uinterface::add(element* e){
			element** newui = (element**) realloc(ui, sizeof(element*)*(uiNum+1));

			if (newui!=NULL) {
				ui = newui;
				ui[uiNum] = e;
				ui[uiNum]->setInterface(this);
				uiNum++;
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		}

	/*--------------------------------------------//
	Remove element
	//--------------------------------------------*/
		void uinterface::remove(element* e){
			for (int i = 0; i < uiNum; i++){
				if (e == ui[i]){
					//move last object to here
					ui[i] = ui[uiNum-1];
					//trim last object
					element** newui = (element**) realloc(ui, sizeof(element*)*(uiNum-1));
					//check if memory was allocated
					if (newui!=NULL) {
						ui = newui;
						uiNum--;
					}else{
						puts ("Error (re)allocating memory");
						exit (1);
					}
					return;
				}
			}
		}

	/*--------------------------------------------//
	Draw
	//--------------------------------------------*/
		void uinterface::draw(){
			for (int i = 0; i < uiNum; i++){
				ui[i]->draw();
			}
		}
#endif
