#pragma once

#include "GameState.h"

#include <vector>

#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
	MainMenuState();
	~MainMenuState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	virtual std::string getStateID() const override;

private:

	virtual void setCallbacks(const std::vector<Callback> &callbacks) override;

	static const std::string s_mainMenuStateID;

	//static functions
	static void s_menuToPlay();
	static void s_exitFromMenu();
};

