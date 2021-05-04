#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"

class GameState
{
public:
	
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const = 0;

protected:

	bool m_bExitingFromState;
	std::vector<std::string> m_textureIDList;
	std::vector<GameObject*> m_gameObjects;
};

