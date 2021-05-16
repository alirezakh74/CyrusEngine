#pragma once

#include "LoaderParams.h"
#include <memory>
#include "Vector2D.h"

class GameObject
{

public:
	// movement variables
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	// size variables
	int m_width;
	int m_height;
	// animation variables
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	std::string m_textureID;
	// common boolean variables
	bool m_bUpdating;
	bool m_bDead;
	bool m_bDying;
	// rotation
	double m_angle;
	// blending
	int m_alpha;

public:
	virtual ~GameObject();

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;

	virtual void collision() = 0;
	virtual std::string type() = 0;
	Vector2D& getPosition() { return m_position; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	// void scroll(float scrollSpeedX, scrollSpeedY)
	bool updating() const { return m_bUpdating; }
	bool dead() const { return m_bDead; }
	bool dying() const { return m_bDying; }
	void setUpdating(bool updating) { m_bUpdating = updating; }

protected:

	GameObject();

	/*GameObject(const LoaderParams* pParams);
	virtual ~GameObject();*/
};

