/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#include "collisionmodel.h"

#include "../graphics/objects/model.h"

CollisionModel::CollisionModel(Model* model)
	: model(model) {}