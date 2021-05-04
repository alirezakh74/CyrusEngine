#include "PauseState.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"

const std::string PauseState::s_pauseStateID = "PAUSESTATE";

void PauseState::update()
{
	if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->update();
		}
	}
}

void PauseState::render()
{
	if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->draw();
		}
	}
}

bool PauseState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", s_pauseStateID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);
	m_callbacks.push_back(s_restartPlay);

	setCallbacks(m_callbacks);

	std::cout << "entering pause state\n";
	return true;
}

bool PauseState::onExit()
{
	GameState::onExit();

	std::cout << "exiting pause state\n";
	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getGameStateMachine()->popState();
}

void PauseState::s_restartPlay()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new PlayState());
}
