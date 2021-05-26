#pragma once

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:

	Player();
	~Player();

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();

	void handleInput();

	void handleAmimation();

	void resurrect();

private:

	const float m_speed = 4;

	int m_bInvulnerable;
	unsigned int m_invulnerableCurrentTime;
	unsigned int m_invulnerableLastTime;
	const unsigned int ALL_OF_INVULNERABLE_TIME = 2000/*ms*/;
	const unsigned int TIME_PER_CHANGHE_ALPHA_MOD = 80/*ms*/;
	const unsigned int FIRE_RATE_PER_TIME = 100/*ms*/;

	bool m_bAllowMissile;
	unsigned int m_missileCurrentTime;
	unsigned int m_missileLastTime;
	const unsigned int MISSILE_RATE = 1000/*MS*/;
	const float MISSILE_SPEED = 10;
	float m_missileSpeedX;
	float m_missileSpeedY;

	/*bool m_bBullet;
	unsigned int m_bulletCurrentTime;
	unsigned int m_bulletLastTime;*/
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const override
	{
		return new Player();
	}
};

