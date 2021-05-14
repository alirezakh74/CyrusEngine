#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public:

	Player();
	~Player();

	virtual void load(const LoaderParams* pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();

	void handleInput();

private:

	const float m_speed = 4;
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const override
	{
		return new Player();
	}
};

