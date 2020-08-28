//////////////////////////////////////////////////////////////////////////////////////////
//	Shadow Mapping Tutorial
//	Accompanies a tutorial found on my site
//	Downloaded from: www.paulsprojects.net
//	Created:	16th September 2003
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef MAIN_H
#define MAIN_H

//Called for initiation
bool Init(void);

//Called to draw scene
void Draw(void);

//Called on window resize
void Reshape(int w, int h);

//Called when a key is pressed
void Keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv);

#endif	//MAIN_H
