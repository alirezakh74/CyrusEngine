#include "ShooterObject.h"

#include "TextureManager.h"
#include "Game.h"
#include "ShooterObject.h"

ShooterObject::ShooterObject()
	: GameObject(), m_rotation(0), m_scale(1), m_moveSpeed(0)
{
	/*m_x = pParams->getX();
	m_y = pParams->getY();*/

	/*m_textureID = pParams->getTextureID();

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_currentFrame = 1;
	m_currentRow = 1;

	m_bFlipHorizontal = false;*/
}

void ShooterObject::doDyingAnimation()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));

	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}

	m_dyingCounter++;
}

ShooterObject::~ShooterObject()
{
}

void ShooterObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
	m_position = Vector2D(pParams->getX(), pParams->getY());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
	m_numFrames = pParams->getNumFrames();
	m_bFlipHorizontal = false;
}

void ShooterObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;

	/*if (m_velocity.getX() < 0)
	{
		m_bFlipHorizontal = false;
	}
	if (m_velocity.getX() > 0)
	{
		m_bFlipHorizontal = true;
	}*/

	m_currentFrame++;
	if (m_currentFrame > m_numFrames)
	{
		m_currentFrame = 1;
	}
}

void ShooterObject::draw()
{
	if (!m_bFlipHorizontal)
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, m_rotation, m_scale, TheGame::Instance()->getRenderer());
	}
	else
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, m_rotation, m_scale, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
}

void ShooterObject::clean()
{
}

void ShooterObject::setScale(float scale)
{
	m_scale = scale;
}

