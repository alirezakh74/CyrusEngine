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

	const int m_speed = 5;
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const override
	{
		return new Player();
	}
};

