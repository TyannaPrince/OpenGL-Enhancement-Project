/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

#include "bounds.h"
#include "../physics/collisionmesh.h"
#include "../physics/rigidbody.h"

class Ray {
public:
	glm::vec3 origin;
	glm::vec3 dir;
	glm::vec3 invdir;

	Ray(glm::vec3 origin, glm::vec3 dir);

	bool intersectsBoundingRegion(BoundingRegion br, float &tmin, float &tmax);
	bool intersectsMesh(CollisionMesh* mesh, RigidBody* rb, float &t);
};

#endif