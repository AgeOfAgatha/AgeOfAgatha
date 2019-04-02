#ifndef LIGHT_H
#define LIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../globals.h"

    #include <stdlib.h>
    #include <stdio.h>

/*--------------------------------------------//
Light Class
//--------------------------------------------*/
    class light{
        private:
        protected:
        public:
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                vec3 color;
                float ambientIntensity;
                float diffuseIntensity;

            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                light(){
                    color = vec3(0.0f, 0.0f, 0.0f);
                    ambientIntensity = 0.0f;
                    diffuseIntensity = 0.0f;
                }
    };
#endif