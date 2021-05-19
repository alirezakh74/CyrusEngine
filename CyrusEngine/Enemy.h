#pragma once

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject
{

public:

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
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

