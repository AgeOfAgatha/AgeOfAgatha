#ifndef DIRECLIGHT_H
#define DIRECLIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../globals.h"
    #include "light.h"

    #include <stdlib.h>
    #include <stdio.h>

/*--------------------------------------------//
Spot Light Class
//--------------------------------------------*/
    class direclight{
        private:
        protected:
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                light base;
                vec3 direction;

            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                direclight(){
                    base = light();
                    direction = vec3(0.0f, 0.0f, -1.0f);
                }
    };
#endif