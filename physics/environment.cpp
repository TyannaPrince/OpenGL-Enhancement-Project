/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#include "environment.h"

/*
    define constants in Environment class
*/

// up vector in world
glm::vec3 Environment::worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

// acceleration due to gravity
glm::vec3 Environment::gravitationalAcceleration = glm::vec3(0.0f, -9.81f, 0.0f);