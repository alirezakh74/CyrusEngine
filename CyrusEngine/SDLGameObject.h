#pragma once

#include "GameObject.h"

#include <iostream>

#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject();
	~SDLGameObject();

	virtual void load(const LoaderParams* pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();

protected:
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
};

