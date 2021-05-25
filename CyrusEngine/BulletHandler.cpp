#include "BulletHandler.h"
#include "globals.h"

BulletHandler* BulletHandler::s_pInstance = NULL;

void BulletHandler::addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading)
{
	PlayerBullet* pPlayerBullet = new PlayerBullet();
	pPlayerBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames)), heading);

	m_playerBullets.push_back(pPlayerBullet);
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading)
{
	EnemyBullet* pEnemyBullet = new EnemyBullet();
	pEnemyBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames)), heading);

	m_enemyBullets.push_back(pEnemyBullet);
}

void BulletHandler::updateBullets()
{
	for (auto p_it = m_playerBullets.begin(); p_it != m_playerBullets.end(); )
	{
		if ((*p_it)->getPosition().getX() < 0 || (*p_it)->getPosition().getX() > screen::width
			|| (*p_it)->getPosition().getY() < 0 || (*p_it)->getPosition().getY() > screen::height
			 || (*p_it)->dead())
		{
			delete *p_it;
			p_it = m_playerBullets.erase(p_it);
		}
		else
		{
			(*p_it)->update();
			++p_it;
		}
	}

	for (auto p_it = m_enemyBullets.begin(); p_it != m_enemyBullets.end(); )
	{
		if ((*p_it)->getPosition().getX() < 0 || (*p_it)->getPosition().getX() > screen::width
			|| (*p_it)->getPosition().getY() < 0 || (*p_it)->getPosition().getY() > screen::height
			|| (*p_it)->dead())
		{
			delete* p_it;
			p_it = m_enemyBullets.erase(p_it);
		}
		else
		{
			(*p_it)->update();
			++p_it;
		}
	}
}

void BulletHandler::drawBullets()
{
	for (auto bullet : m_playerBullets)
	{
		bullet->draw();
	}

	for (auto bullet : m_enemyBullets)
	{
		bullet->draw();
	}
}

void BulletHandler::clearBullets()
{
	m_playerBullets.clear();
	m_enemyBullets.clear();
}

BulletHandler::BulletHandler()
{
}

BulletHandler::~BulletHandler()
{
	delete s_pInstance;
	s_pInstance = NULL;
}
