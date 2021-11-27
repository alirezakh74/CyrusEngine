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

Level::Level()
{
}

Level::~Level()
{
	m_tilesets.clear();
	m_layers.clear();
}
