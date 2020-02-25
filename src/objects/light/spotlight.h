#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../globals.h"
    #include "light.h"
    #include "direclight.h"

    #include <stdlib.h>
    #include <stdio.h>

/*--------------------------------------------//
Spot Light Class
//--------------------------------------------*/
    class spotlight{
        private:
        protected:
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                direclight direc;
                vec3 position;
                float fov;
                float constant;
                float linear;
                float exponential;

            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                spotlight(){
                    direc = direclight();
                    position = vec3(0.0f, 0.0f, 0.0f);
                    fov = 360.0f;
                    constant = 1.0f;
                    linear = 1.0f;
                    exponential = 1.0f;
                }
    };
#endif