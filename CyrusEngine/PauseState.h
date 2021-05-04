#pragma once
#include "MenuState.h"

class PauseState : public MenuState
{
public:

	void update() override;
	void render() override;

	bool onEnter() override;
	bool onExit() override;

	std::string getStateID() const override { return s_pauseStateID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:

	static const std::string s_pauseStateID;

	static void s_pauseToMain();
	static void s_resumePlay();
	static void s_restartPlay();

};

