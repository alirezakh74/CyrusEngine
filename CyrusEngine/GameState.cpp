#include "GameState.h"
#include "TextureManager.h"

void GameState::update()
{
	if (!m_gameObjects.empty() && !m_bExitingFromState)
	{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->update();
		}
	}
}

void GameState::render()
{
	if (!m_gameObjects.empty() && !m_bExitingFromState)
	{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->draw();
		}
	}
}

bool GameState::onEnter()
{
	m_bExitingFromState = false;
	return true;
}

bool GameState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->clean();
		//delete m_gameObjects[i];
	}

	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); ++i)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	m_bExitingFromState = true;

	return true;
}
