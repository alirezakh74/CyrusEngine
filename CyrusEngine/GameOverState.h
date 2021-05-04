#pragma once
#include "MenuState.h"

class GameOverState : public MenuState
{
public:

	void update() override;
	void render() override;

	bool onEnter() override;
	bool onExit() override;

	std::string getStateID() const override { return s_GameOverStateID; }

	virtual void setCallbacks(const std::vector<Callback> &callbacks) override;

private:

	static const std::string s_GameOverStateID;

	//std::vector<GameObject*> m_gameObjects;

	static void s_gameoverToMain();
	static void s_restartPlay();

};

