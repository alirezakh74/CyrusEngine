#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{

public:

	virtual void load(const LoaderParams* pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();

private:

	const int m_speed = 5;

};

class EnemyCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const override
	{
		return new Enemy();
	}
};

