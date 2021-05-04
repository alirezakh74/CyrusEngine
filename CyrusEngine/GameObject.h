#pragma once

#include "LoaderParams.h"

class GameObject
{
public:

	virtual void load(const LoaderParams* pParams) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;

protected:

	GameObject();
	virtual ~GameObject();

	/*GameObject(const LoaderParams* pParams);
	virtual ~GameObject();*/
};

