#pragma once

#include "ShooterObject.h"
#include "Vector2D.h"

class PlayerBullet : public ShooterObject
{
public:

	PlayerBullet() : ShooterObject() {}
	virtual ~PlayerBullet() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams, Vector2D heading);
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;
	virtual void collision() override;
	virtual std::string type() override { return "PlayerBall"; }

private:

	Vector2D m_heading;
};

class EnemyBullet : public PlayerBullet
{
public:

	EnemyBullet() : PlayerBullet() {}
	virtual ~EnemyBullet() {}

	virtual std::string type() override { return "EnemyBullet"; }
};

