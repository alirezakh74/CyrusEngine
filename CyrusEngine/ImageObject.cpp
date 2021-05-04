#include "ImageObject.h"
#include "Game.h"

#include <SDL2/SDL.h>

#include "TextureManager.h"

ImageObject::ImageObject() : SDLGameObject()
{
	m_bRightMoving = true;
	//m_velocity.setX(m_speed);

	m_r = m_g = m_b = m_a = 0;
}

ImageObject::~ImageObject()
{
}

void ImageObject::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void ImageObject::update()
{
	static int counter = 0;
	//static Uint8 r = 0, b = 0, g = 0, a = 255;

	/*if (m_position.getX() >= (WINDOW_WIDTH - m_width) && m_bRightMoving)
	{
		m_velocity.setX(-m_speed);
		m_bRightMoving = false;
	}
	else if(m_position.getX() <= 0 && !m_bRightMoving)
	{
		m_velocity.setX(m_speed);
		m_bRightMoving = true;
	}*/

	/*SDL_SetTextureAlphaMod(
		TheTextureManager::Instance()->getTexture(m_textureID)
		, myAlpha);

	if (myAlpha < 255)
	{
		myAlpha += 5;
	}*/

	//bool test = SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), r, g, b, a);

	SDL_SetTextureColorMod(TheTextureManager::Instance()->getTexture(m_textureID), m_r, m_g, m_b);

	if (counter % 1 == 0)
	{
		if (m_r < 255)
		{
			m_r++;
			m_b++;
			m_g++;
			//a++;
		}
	}

	counter++;

	if (m_velocity.getX() > 0)
	{
		m_bFlipHorizontal = true;
	}
	if (m_velocity.getX() < 0)
	{
		m_bFlipHorizontal = false;
	}

	SDLGameObject::update();
}

void ImageObject::draw()
{
	SDLGameObject::draw();
}

void ImageObject::clean()
{
	SDLGameObject::clean();
}
