#ifndef MODELINSTANCE_H
#define MODELINSTANCE_H

#include "ModelInstance.h"

class ModelInstance
{
public:
	ModelAsset* asset;
	glm::mat4 transform;

	ModelInstance() :
	asset(NULL),
		transform()
	{}
};

#endif