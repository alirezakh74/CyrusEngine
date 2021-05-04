#include "GameOverState.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"

const std::string GameOverState::s_GameOverStateID = "GAMEOVERSTATE";

void GameOverState::update()
{
	/*if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->update();
		}
	}*/

	GameState::update();
}

void GameOverState::render()
{
	/*if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->draw();
		}
	}*/

	GameState::render();
}

bool GameOverState::onEnter()
{
	GameState::onEnter();

	StateParser stateParser;
	stateParser.parseState("assets/test.xml", s_GameOverStateID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameoverToMain);
	m_callbacks.push_back(s_restartPlay);

	setCallbacks(m_callbacks);

	std::cout << "entering Game Over State\n";
	return true;
}

bool GameOverState::onExit()
{
	/*for (int i = 0; i < m_textureIDList.size(); ++i)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}*/

	GameState::onExit();

	std::cout << "exiting Game Over State\n";
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(m_callbacks[pButton->getCallbackID()]);
		}
	}
}

void GameOverState::s_gameoverToMain()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new PlayState());
}
