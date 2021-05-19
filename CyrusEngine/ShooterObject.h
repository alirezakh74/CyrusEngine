#pragma once

#include "GameObject.h"

#include <iostream>

#include "Vector2D.h"

class ShooterObject : public GameObject
{
public:
	virtual ~ShooterObject();

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();
	virtual void setScale(float scale);

	virtual void collision() { }
	std::string type() { return "SDLGameObject"; }

protected:
	ShooterObject();

	void doDyingAnimation();

	int m_bulletFiringSpeed;
	int m_bulletCounter;

	int m_moveSpeed;

	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;

	std::string m_textureID;
	/*int m_x;
	int m_y;*/
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;
	int m_numFrames;

	bool m_bFlipHorizontal;
	int m_rotation;
	float m_scale;
};

