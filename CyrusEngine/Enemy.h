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

	virtual std::string type() override final { return "Enemy"; }

private:
	const int m_speed = 5;

protected:

	int m_health;

	Enemy() : ShooterObject(), m_health(0) {}
	virtual ~Enemy() {}

	friend class EnemyCreator;

};

class EnemyCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const override
	{
		return new Enemy();
	}
};

