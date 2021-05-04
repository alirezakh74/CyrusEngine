#pragma once

#include "GameState.h"

#include "Level.h"

class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	virtual std::string getStateID() const override;

private:
	static const std::string s_playStateID;

	Level* m_pLevel;

	//std::vector<GameObject*> m_gameObjects;
};

