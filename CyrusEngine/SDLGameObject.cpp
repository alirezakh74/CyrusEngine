#include "SDLGameObject.h"

#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject()
	: GameObject()
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

SDLGameObject::~SDLGameObject()
{
}

void SDLGameObject::load(const LoaderParams* pParams)
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

void SDLGameObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;

	if (m_velocity.getX() < 0)
	{
		m_bFlipHorizontal = false;
	}
	if (m_velocity.getX() > 0)
	{
		m_bFlipHorizontal = true;
	}

	m_currentFrame++;
	if (m_currentFrame > m_numFrames)
	{
		m_currentFrame = 1;
	}
}

void SDLGameObject::draw()
{
	if (!m_bFlipHorizontal)
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
	}
	else
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
}

void SDLGameObject::clean()
{
}
