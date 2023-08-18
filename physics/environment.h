/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <glm/glm.hpp>

/*
    Environment class
    - stores values for environment (constants, etc)

    NOTE: 1 cubic unit in OpenGL space is equivalent to 1 meter cubed
*/

class Environment {
public:
    static glm::vec3 worldUp;						// up vector in world
    static glm::vec3 gravitationalAcceleration;		// acceleration due to gravity
};

#endif