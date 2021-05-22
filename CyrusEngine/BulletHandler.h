#pragma once

#include <iostream>
#include <vector>

#include "Vector2D.h"
#include "Bullet.h"

class BulletHandler
{
public:

	static BulletHandler* Instance()
	{
		if (s_pInstance == NULL)
			s_pInstance = new BulletHandler();

		return s_pInstance;
	}

	void addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);
	void addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);

	void updateBullets();
	void drawBullets();

	void clearBullets();

	const std::vector<PlayerBullet*> getPlayerBullets() { return m_playerBullets; }
	const std::vector<EnemyBullet*> getEnemyBullets() { return m_enemyBullets; }

private:

	BulletHandler();
	~BulletHandler();

	static BulletHandler* s_pInstance;

	std::vector<PlayerBullet*> m_playerBullets;
	std::vector<EnemyBullet*> m_enemyBullets;
};

typedef BulletHandler TheBulletHandler;
