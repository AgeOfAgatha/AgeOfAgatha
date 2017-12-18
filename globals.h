#ifndef GLOBALS_H

const float PI = 3.1415926535f;

// Window Position/Resizing Constants
const int   INIT_WINDOW_POSITION[2] = { 50, 50 };
const float ASPECT_RATIO            = 1.0f;
const int   INIT_WINDOW_SIZE[2]     = { 900, int(900/ASPECT_RATIO) };
const float FRUSTUM_FIELD_OF_VIEW   = 35.0f;
const float FRUSTUM_NEAR_PLANE      = 0.1f;
const float FRUSTUM_FAR_PLANE       = 100.0f;
const float BACKGROUND_COLOR[3]     = {0.9f, 0.7f, 0.3f};

// Lighting Constants
const float LIGHT_0_POSITION[]    = { 0.0f, 3.0f, 0.0f, 0.0f};
const float LIGHT_1_POSITION[]    = { 0.0f, -50.0f, 50.0f, 0.0f};
const float LIGHT_AMBIENT[]       = { 0.8f, 0.8f, 0.8f, 1.0f};
const float LIGHT_DIFFUSE[]       = { 0.9f, 0.9f, 0.9f, 1.0f};
const float LIGHT_SPECULAR[]      = { 1.0f, 1.0f, 1.0f, 1.0f};
const float LIGHT_MODEL_AMBIENT[] = { 0.7f, 0.7f, 0.7f, 1.0f};

// Viewer Positioning Constants
const float VIEWER_DISTANCE         = 30.0f;
const float INITIAL_VIEWER_AZIMUTH = PI / 2.0f;
const float INITIAL_VIEWER_ALTITUDE = PI / 2.5f;
const float VIEWER_ANGLE_INCREMENT  = PI / 60.0f;

// Material Properties Constants
const float AMBIENT_COEFF  = -1.0f;    // Minimal ambient reflectance.
const float DIFFUSE_COEFF  =  1.0f;    // Maximal diffuse reflectance.
const float SPECULAR_COEFF =  1.0f;    // Maximal specular reflectance.
const float SPECULAR_EXPON =  20.0f;    // Low level of shininess (scale: 0-128).

#define GLOBALS_H
#endif