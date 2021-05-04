#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton();
	~MenuButton();

	void load(const LoaderParams* pParams);
	void update();
	void draw();
	void clean();

	void (*m_callback)();

	void setCallback(void (*callback)()) { m_callback = callback; }
	int getCallbackID() const { return m_callbackID; }


private:

	enum button_state
	{
		MOUSE_OUT = 1,
		MOUSE_OVER = 2,
		CLICKED = 3
	};

	bool m_bReleased;
	int m_callbackID;
};

class MenuButtonCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const override
	{
		return new MenuButton();
	}
};

