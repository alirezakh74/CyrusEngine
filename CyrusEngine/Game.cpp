#include "Game.h"

#include <iostream>

#include "InputHandler.h"
#include "TextureManager.h"

#include "SplashScreen.h"
//#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "Player.h"
#include "Enemy.h"
#include "ImageObject.h"

Game* Game::s_pInstance = 0;

Game::Game()
{
	//m_bRunning = init();
}

Game::~Game()
{
	
}

Game* Game::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new Game();
	}

	return s_pInstance;
}

void Game::run()
{
	m_bRunning = init();

	Uint32 frameStart, frameTime;

	while (m_bRunning)
	{
		frameStart = SDL_GetTicks();

		handleEvents();
		update();
		draw();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)DELAY_TIME - frameTime);
		}
	}

	clean();
}

SDL_Renderer* Game::getRenderer() const
{
	return m_pRenderer;
}

SDL_Window* Game::getWindow() const
{
	return m_pWindow;
}

void Game::quit()
{
	m_bRunning = false;
}

GameStateMachine* Game::getGameStateMachine() const
{
	return m_pGameStateMachine;
}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer == 0)
			{
				std::cout << "renderer creation failed" << std::endl;
				return false;
			}
			else
			{
				// set rederer draw color
				SDL_SetRenderDrawColor(m_pRenderer, 127, 127, 127, 255);
			}
		}
		else
		{
			std::cout << "window creation failed" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "sdl initilizaion failed" << std::endl;
		return false;
	}

	// init Input Handler
	TheInputHandler::Instance()->initializeJoysticks();

	// register types
	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::Instance()->registerType("ImageObject", new ImageCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new SplashScreen());

	// everything done correctly
	std::cout << "init done" << std::endl;
	return true;
}

void Game::clean()
{

	TheInputHandler::Instance()->clean();

	m_pGameStateMachine->~GameStateMachine();
	delete m_pGameStateMachine;
	m_pGameStateMachine = nullptr;

	std::cout << "clean everything up" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = NULL;
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;

	SDL_Quit();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	/*SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_bRunning = false;
		}

		if (event.type == SDL_KEYDOWN)
		{
		}
	}*/
}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::draw()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}
