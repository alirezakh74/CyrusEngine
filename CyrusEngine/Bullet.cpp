#include "Bullet.h"

void PlayerBullet::load(std::unique_ptr<LoaderParams> const& pParams, Vector2D heading)
{
	ShooterObject::load(pParams);
	m_heading = heading;
}

void PlayerBullet::update()
{
	m_velocity.setX(m_heading.getX());
	m_velocity.setY(m_heading.getY());

	ShooterObject::update();
}

void PlayerBullet::draw()
{
	ShooterObject::draw();
}

void PlayerBullet::clean()
{
	ShooterObject::clean();
}

void PlayerBullet::collision()
{
	m_bDead = true;
}
