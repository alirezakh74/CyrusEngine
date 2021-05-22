#pragma once

#include <iostream>
#include <vector>

#include "Vector2D.h"
#include "Bullet.h"

class BulletHandler
{
public:

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

	std::vector<PlayerBullet*> m_playerBullets;
	std::vector<EnemyBullet*> m_enemyBullets;
};
