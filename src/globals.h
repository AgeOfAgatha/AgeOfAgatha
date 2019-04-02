#ifndef GLOBALS_H

const float 	PI = 3.1415926535f;

// Driver Constants
const int 		TIMESTEP = 3;//how often do we calculate physics?
const int 		TIMEOUT = 3;//how many iterations before an object is considered 'asleep'
const double	FRICTIONDIST = 3.0;//how much to increase object size while testing for nearby objects to apply friction to
const double 	VERTEXRAD = 1.0;//how big of a sphere should a vertex be considered as for collisions
const double	GRAVOBJMASS = 100;//how much mass does an object need before it is considered to be applying gravity to other objects
const double 	GRAVITYCONSTANT = 100;//multiplier for all gravity applied in the simulation
const double 	FRICTIONCONSTANT = 100;//multiplier for all friction applied in the simulation
const double 	DEFORMCONSTANT = 0.1;//multiplier for all deformation applied in the simulation
const int 		TIMER = 20;//how often do we run the timer function which updates the world

// Window Position/Resizing Constants
const float 	ASPECT_RATIO            = 1.33f;
const int   	INIT_WINDOW_POSITION[2] = { 0, 0 };
const int   	INIT_WINDOW_SIZE[2]     = { 800, int(900/ASPECT_RATIO) };
const float 	FRUSTUM_FIELD_OF_VIEW   = 45.0f;
const float 	FRUSTUM_NEAR_PLANE      = 0.1f;
const float 	FRUSTUM_FAR_PLANE       = 100.0f;
const float 	BACKGROUND_COLOR[3]     = {0.0f, 0.0f, 0.0f};

// Lighting Constants
const unsigned int SHADOW_WIDTH 	  = 1024;
const unsigned int SHADOW_HEIGHT 	  = 1024;
const float 	LIGHT_0_POSITION[]    = { 5.5f, 5.5f, 5.5f, 0.0f};
const float 	LIGHT_AMBIENT[]       = { 0.8f, 0.8f, 0.8f, 1.0f};
const float 	LIGHT_DIFFUSE[]       = { 0.9f, 0.9f, 0.9f, 1.0f};
const float 	LIGHT_SPECULAR[]      = { 1.0f, 1.0f, 1.0f, 1.0f};
const float 	LIGHT_MODEL_AMBIENT[] = { 0.7f, 0.7f, 0.7f, 1.0f};

// Viewer Positioning Constants
const float 	VIEWER_DISTANCE         = 10.0f;
const float 	INITIAL_VIEWER_AZIMUTH = 0;
const float 	INITIAL_VIEWER_ALTITUDE = 0;
const float 	VIEWER_ANGLE_INCREMENT  = PI / 60.0f;

// Material Properties Constants
const int 		MAX_TRIANGLE_MATERIALS  = 2;// Maximum supported textures per triangle
const float 	AMBIENT_COEFF  = -1.0f;    // Minimal ambient reflectance.
const float 	DIFFUSE_COEFF  =  1.0f;    // Maximal diffuse reflectance.
const float 	SPECULAR_COEFF =  1.0f;    // Maximal specular reflectance.
const float 	SPECULAR_EXPON =  20.0f;    // Low level of shininess (scale: 0-128).

// UI Property Constants
const int 		MAX_CHARACTERS_TEXT = 1024; 					//Max amount of characters in one text element.
const float 	DEFAULT_TEXT_COLOR[] = {1.0f, 0.0f, 0.0f}; 		//Default color for text
const float 	DEFAULT_TEXT_POS[] = {-1.0f, 1.0f, -1.0f}; 	//Default position for text

#define GLOBALS_H
#endif