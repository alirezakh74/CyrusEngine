#include "Level.h"

void Level::update()
{
	for (int i = 0; i < m_layers.size(); ++i)
	{
		m_layers[i]->update();
	}
}

void Level::render()
{
	for (int i = 0; i < m_layers.size(); ++i)
	{
		m_layers[i]->render();
	}
}

void Level::clear()
{
	for (int i = 0; i < m_layers.size(); ++i)
	{
		delete (m_layers[i]);
	}
	m_layers.clear();

	m_tilesets.clear();
}

Level::Level()
{
}

Level::~Level()
{
	//m_tilesets.clear();
	//m_layers.clear();
}
