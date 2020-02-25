#ifndef LIGHT_H
#define LIGHT_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
    #include "../../../deps/glm/glm.hpp"

    #include "../../globals.h"
    #include "../../common/vector.h"

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


            /*--------------------------------------------//
            Constructor
            //--------------------------------------------*/
                light(){
                    color = vec3(1.0f, 1.0f, 1.0f);
                }
    };
#endif