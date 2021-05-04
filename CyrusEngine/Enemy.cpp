#include "Enemy.h"
#include "globals.h"

void Enemy::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_velocity.setX(-m_speed);
}

void Enemy::update()
{
	if (m_position.getX() + m_width < 0)
	{
		m_velocity.setX(m_speed);
	}
	if (m_position.getX() > screen::width)
	{
		m_velocity.setX(-m_speed);
	}

	SDLGameObject::update();
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::clean()
{
}
