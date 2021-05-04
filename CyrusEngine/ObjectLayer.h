#pragma once

#include "Layer.h"
#include <vector>
#include "GameObject.h"

class ObjectLayer : public Layer
{
public:

	virtual void update() override;
	virtual void render() override;

	std::vector<GameObject*>* getGameObjects()
	{
		return &m_gameObjects;
	}

private:

	std::vector<GameObject*> m_gameObjects;
};

