/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#ifndef COLLISIONMODEL_H
#define COLLISIONMODEL_H

#include "collisionmesh.h"

#include <vector>

// forward declaration
class Model;

class CollisionModel {
public:
	Model* model;

	std::vector<CollisionMesh> meshes;

	CollisionModel(Model* model);
};

#endif