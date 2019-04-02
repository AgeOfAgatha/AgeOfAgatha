#ifndef POINTLIGHT_H
#define POINTLIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../globals.h"
    #include "light.h"

    #include <stdlib.h>
    #include <stdio.h>

/*--------------------------------------------//
Point Light Class
//--------------------------------------------*/
    class fallofflight{
        private:
        protected:
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                float constant;
                float linear;
                float exponential;

            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                fallofflight(){
                    constant = 1.0f;
                    linear = 0.0f;
                    exponential = 0.0f;
                }
    };
    class pointlight:public light{
        private:
        protected:
        public: 
            /*--------------------------------------------//
            Class Variables
            //--------------------------------------------*/
                vec3 position;
                fallofflight falloff;

            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                pointlight(){
                    position = vec3(0.0f, 0.0f, 0.0f);
                }
    };
#endif