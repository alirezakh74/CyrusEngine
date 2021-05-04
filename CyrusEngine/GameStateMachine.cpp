#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() : newState(nullptr), popStateFlag(false), changeStateFlag(false)
{
}

GameStateMachine::~GameStateMachine()
{
	/*while (!m_gameStates.empty())
	{
		static int i = 0;
		m_gameStates.back()->onExit();
		delete m_gameStates.back();
		m_gameStates.pop_back();

		++i;
		std::cout << i << " state cleared" << std::endl;
	}*/
}

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popStatePrivate()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeStatePrivate(GameState* pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return; // do nothing
		}

		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}

		// We check if the State exists in the StateMachine, if it exists
		// we eliminate them to free memory and an unneeded State
		for (auto it = m_gameStates.begin(); it != m_gameStates.end(); ++it)
		{
			if (((*it)->getStateID() == pState->getStateID()) && ((*it)->onExit()))
			{
				delete (*it);
				m_gameStates.erase(it);
				break;
			}
		}
	}

	// push back our new state
	m_gameStates.push_back(pState);

	// initialise it
	m_gameStates.back()->onEnter();
}

void GameStateMachine::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}

	if (changeStateFlag)
	{
		changeStatePrivate(newState);
		changeStateFlag = false;
	}
	else if (popStateFlag)
	{
		popStatePrivate();
		popStateFlag = false;
	}
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}

void GameStateMachine::popState()
{
	popStateFlag = true;
}

void GameStateMachine::changeState(GameState* pState)
{
	changeStateFlag = true;
	newState = pState;
}

//void GameStateMachine::pushState(GameState* pState)
//{
//	m_gameStates.push_back(pState);
//	m_gameStates.back()->onEnter();
//}
//
//void GameStateMachine::changeState(GameState* pState)
//{
//	if (!m_gameStates.empty())
//	{
//		if (m_gameStates.back()->getStateID() == pState->getStateID())
//		{
//			return; //do nothing
//		}
//		if(m_gameStates.back()->onExit())
//		{
//			delete m_gameStates.back();
//			m_gameStates.pop_back();
//		}
//	}
//
//	// push back our new State and Initialize it
//	m_gameStates.push_back(pState);
//	m_gameStates.back()->onEnter();
//}
//
//void GameStateMachine::popState()
//{
//	if (!m_gameStates.empty())
//	{
//		if (m_gameStates.back()->onExit())
//		{
//			delete m_gameStates.back();
//			m_gameStates.pop_back();
//		}
//	}
//}
//
//void GameStateMachine::update()
//{
//	if (!m_gameStates.empty())
//	{
//		m_gameStates.back()->update();
//	}
//}
//
//void GameStateMachine::render()
//{
//	if (!m_gameStates.empty())
//	{
//		m_gameStates.back()->render();
//	}
//}
