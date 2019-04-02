#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../globals.h"
    #include "light.h"
    #include "pointlight.h"

    #include <stdlib.h>
    #include <stdio.h>

/*--------------------------------------------//
Spot Light Class
//--------------------------------------------*/
    class spotlight:public pointlight{
        private:
        protected:
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                vec3 direction;
                float cutoff;

            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                spotlight(){
                    direction = vec3(0.0f, 0.0f, 0.0f);
                    cutoff = 0.0f;
                }
    };
#endif