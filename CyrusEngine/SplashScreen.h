#pragma once

#include "GameState.h"

#include <vector>

//using Uint32 = uint32_t;

class SplashScreen : public GameState
{
public:
	//typedef uint32_t Uint32;
	using Uint32 = uint32_t;

	SplashScreen();
	~SplashScreen();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	virtual std::string getStateID() const override;

private:
	static const std::string s_splashID;
	//std::vector<GameObject*> m_gameObjects;
	Uint32 m_timer;
	static const Uint32 s_splashTimeDelay;
};

