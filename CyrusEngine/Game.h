#pragma once

#include "globals.h"

#include <SDL2/SDL.h>

#include "GameStateMachine.h"

class Game
{
	//Public Functions
public:

	static Game* Instance();

	void run();

	SDL_Renderer* getRenderer() const;
	SDL_Window* getWindow() const;

	void quit();

	GameStateMachine* getGameStateMachine() const;

	void setPlayerLives(int lives) { m_playerLives = lives; }
	int getPlayerLives() const { return m_playerLives; }

	//Uint32 getFrameStart() const { return m_frameStart; }
	//Uint32 getFrameTime() const { return m_frameTime; }
	Uint32 getDeltaTime() const { return m_deltaTime; }

	// Private Variables
private:

	static Game* s_pInstance;

	bool m_bRunning;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	Uint32 m_frameStart;
	Uint32 m_frameTime;
	Uint32 m_deltaTime;
	const int FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;

	GameStateMachine* m_pGameStateMachine;

	int m_playerLives;

	//Private Functions
private:
	Game();
	~Game();

	bool init();
	void clean();

	void handleEvents();
	void update();
	void draw();
};

typedef Game TheGame;

