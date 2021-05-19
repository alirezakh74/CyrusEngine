#pragma once

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:

	Player();
	~Player();

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();

	void handleInput();

	void handleAmimation();

	void resurrect();

private:

	const float m_speed = 4;

	int m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const override
	{
		return new Player();
	}
};

