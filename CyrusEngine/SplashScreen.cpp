#include "SplashScreen.h"

#include <SDL2/SDL.h>

#include "TextureManager.h"
#include "Game.h"
#include "ImageObject.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "StateParser.h"
#include "SoundManager.h"

const std::string SplashScreen::s_splashID = "SPLASHSTATE";
const Uint32 SplashScreen::s_splashTimeDelay = 5000;

SplashScreen::SplashScreen()
{
	m_timer = 0;

	TheSoundManager::Instance()->load("assets/intro.mp3", "intro", sound_type::SOUND_MUSIC);
	TheSoundManager::Instance()->playMusic("intro", 1);
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::update()
{
	/*if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->update();
		}
	}*/

	GameState::update();

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) || m_timer > s_splashTimeDelay)
	{
		TheGame::Instance()->getGameStateMachine()->changeState(new MainMenuState());
	}

	m_timer = SDL_GetTicks();
}

void SplashScreen::render()
{
	/*for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}*/
	GameState::render();
}

bool SplashScreen::onEnter()
{
	/*if (!TheTextureManager::Instance()->load("assets/logo.png", "logo", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* logo = new ImageObject();
	m_gameObjects.push_back(logo);*/

	GameState::onEnter();

	StateParser stateParser;
	stateParser.parseState("assets/test.xml", s_splashID, &m_gameObjects, &m_textureIDList);

	std::cout << "entering splash state" << std::endl;
	return true;
}

bool SplashScreen::onExit()
{
	//for (int i = 0; i < m_gameObjects.size(); ++i)
	//{
	//	m_gameObjects[i]->clean();
	//	//delete m_gameObjects[i];
	//}

	//m_gameObjects.clear();

	//for (int i = 0; i < m_textureIDList.size(); ++i)
	//{
	//	TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	//}

	GameState::onExit();

	std::cout << "exiting splash state" << std::endl;
	return true;
}

std::string SplashScreen::getStateID() const
{
	return s_splashID;
}
