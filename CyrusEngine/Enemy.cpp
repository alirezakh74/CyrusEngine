#include "Enemy.h"
#include "globals.h"

void Enemy::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(pParams);
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

	ShooterObject::update();
}

void Enemy::draw()
{
	ShooterObject::draw();
}

void Enemy::clean()
{
}
