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
    class direclight:public light{
        private:
        protected:
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                vec3 direction;

            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                direclight():light(){
                    direction = vec3(0.0f, 0.0f, 0.0f);
                }
    };
#endif