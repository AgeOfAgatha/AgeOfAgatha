#ifndef GLOBALS_H
#define GLOBALS_H
using namespace std;
#define GLUT_DISABLE_ATEXIT_HACK
#define GLX_GLXEXT_LEGACY
#include <GL/GLee.h>
#include <GL/glut.h>
#include <string>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
//Mathematical
#if defined(_WIN32)
#  define drand48() (((float) rand())/((float) RAND_MAX))
#  define srand48(x) (srand((x)))
#elif defined __APPLE__
#  define drand48() (((float) rand())/((float) RAND_MAX))
#  define srand48(x) (srand((x)))
#endif
#define	 		PI  						3.1415926535f						//
#define 		STR(x) 						#x 									//
#define 		MAX(x,y) 					(((x) > (y)) ? (x) : (y))			//
#define 		TORAD(x) 					((PI/180.0)*(x))					//
#define 		TODEG(x) 					((180.0/PI)*(x))					//

//window settings
#define 		MAX_FRAMES_IN_FLIGHT  	 	2									//
#define 		INIT_WINDOW_POSITION_X 		0									//
#define 		INIT_WINDOW_POSITION_Y 		0									//
#define 		INIT_WINDOW_SIZE_X    		512									//
#define 		INIT_WINDOW_SIZE_Y    		512									//
#define 		ASPECT_RATIO            	(double)INIT_WINDOW_SIZE_X/INIT_WINDOW_SIZE_Y
#define 		FRUSTUM_FIELD_OF_VIEW   	45.0f								//
#define 		FRUSTUM_NEAR_PLANE      	0.1f 								//
#define 		FRUSTUM_FAR_PLANE       	100.0f								//
#define 		BACKGROUND_COLOR_R	     	0.0f								//
#define 		BACKGROUND_COLOR_G	     	0.0f								//
#define 		BACKGROUND_COLOR_B	     	0.0f								//
#define			WINDOW_TITLE 				"Root"								//
#define			ENGINE_TITLE 				"Root Engine"						//

// UI Property Constants
#define			MAX_CHARACTERS_TEXT 		1024 								//Max amount of characters in one text element.
#define			DEFAULT_TEXT_COLOR_R 		1.0f 								//Default color for text
#define			DEFAULT_TEXT_COLOR_G 		0.0f								//Default color for text
#define			DEFAULT_TEXT_COLOR_B 		0.0f 								//Default color for text
#define			DEFAULT_TEXT_POS_X 			-1.0f 								//Default position for text
#define			DEFAULT_TEXT_POS_Y 			1.0f 								//Default position for text
#define			DEFAULT_TEXT_POS_Z 			-1.0f 								//Default position for text

//Driver Constants
#define			TIMESTEP 					3									//how often do we calculate physics?
#define			TIMEOUT 					3									//how many iterations before an object is considered 'asleep'
#define			FRICTIONDIST 				3.0									//how much to increase object size while testing for nearby objects to apply friction to
#define			VERTEXRAD 					1.0									//how big of a sphere should a vertex be considered as for collisions
#define			GRAVOBJMASS 				100									//how much mass does an object need before it is considered to be applying gravity to other objects
#define			GRAVITYCONSTANT 			100									//multiplier for all gravity applied in the simulation
#define			FRICTIONCONSTANT 			100									//multiplier for all friction applied in the simulation
#define			DEFORMCONSTANT 				0.1									//multiplier for all deformation applied in the simulation
#define			UPDATE_TIMER				20									//how often do we run the timer function which updates the world
#define 		BUFFER_RES_X				512									//what resolution to render for our buffer (width)
#define 		BUFFER_RES_Y				512									//what resolution to render for our buffer (height)

// Material Properties Constants
#define			MAX_TRIANGLE_MATERIALS   	2									// Maximum supported textures per triangle
#define			AMBIENT_COEFF				1.0f								// Minimal ambient reflectance.
#define			DIFFUSE_COEFF    			1.0f								// Maximal diffuse reflectance.
#define			SPECULAR_COEFF   			1.0f								// Maximal specular reflectance.
#define			SPECULAR_EXPON   			20.0f								// Low level of shininess (scale: 0-128).

//Lighting Constants
#define			SHADOW_WIDTH				512 								//
#define			SHADOW_HEIGHT 				512 								//
#define			LIGHT_AMBIENT_R 			0.8f 								//
#define			LIGHT_AMBIENT_G 			0.8f								//
#define			LIGHT_AMBIENT_B 			0.8f								//
#define			LIGHT_DIFFUSE_R 			0.9f								//
#define			LIGHT_DIFFUSE_G 			0.9f								//
#define			LIGHT_DIFFUSE_B 			0.9f								//
#define			LIGHT_SPECULAR_R 			1.0f								//
#define			LIGHT_SPECULAR_G 			1.0f								//
#define			LIGHT_SPECULAR_B 			1.0f								//
#define			LIGHT_MODEL_AMBIENT_R 		0.7f								//
#define			LIGHT_MODEL_AMBIENT_G 		0.7f								//
#define			LIGHT_MODEL_AMBIENT_B 		0.7f								//

// Viewer Positioning Constants
#define			VIEWER_DISTANCE				10.0f 								//
#define			INITIAL_VIEWER_AZIMUTH		0									//
#define			INITIAL_VIEWER_ALTITUDE 	0									//
#define			VIEWER_ANGLE_INCREMENT 		PI / 60.0f							//
#endif
