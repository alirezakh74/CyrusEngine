#include "Player.h"

#include "InputHandler.h"

Player::Player() : SDLGameObject()
{
}

Player::~Player()
{
}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void Player::update()
{
	//m_velocity.setX(0);
	//m_velocity.setY(0);
	handleInput();
	/*if (m_velocity.getX() < 0)
	{
		m_bFlipHorizontal = true;
		m_currentFrame = int((SDL_GetTicks() / 100) % 4);
	}
	if (m_velocity.getX() > 0)
	{
		m_bFlipHorizontal = false;
		m_currentFrame = int((SDL_GetTicks() / 100) % 4);
	}*/

	SDLGameObject::update();
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::clean()
{
}

void Player::handleInput()
{
	m_velocity.setX(0);
	m_velocity.setY(0);

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-m_speed);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(m_speed);
	}

	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(-m_speed);
	}
	if (TheInputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		m_velocity.setX(m_speed);
	}

	/*if (TheInputHandler::Instance()->getButtonState(0, 1))
	{
		m_velocity.setX(m_speed);
	}
	else if (TheInputHandler::Instance()->getButtonState(0, 3))
	{
		m_velocity.setX(-m_speed);
	}
	else
	{
		m_velocity.setX(0);
	}

	if (TheInputHandler::Instance()->getButtonState(0, 2))
	{
		m_velocity.setY(m_speed);
	}
	else if (TheInputHandler::Instance()->getButtonState(0, 0))
	{
		m_velocity.setY(-m_speed);
	}
	else
	{
		m_velocity.setY(0);
	}*/

	/*if (TheInputHandler::Instance()->joysticksInitialized())
	{
		m_velocity.setX(0);
		m_velocity.setY(0);*/

	//	if (TheInputHandler::Instance()->yvalue(0, 1) > 0 || TheInputHandler::Instance()->yvalue(0, 1) < 0)
	//	{
	//		m_velocity.setY(m_speed * TheInputHandler::Instance()->yvalue(0, 1));
	//	}

	//	if (TheInputHandler::Instance()->xvalue(0, 1) > 0 || TheInputHandler::Instance()->xvalue(0, 1) < 0)
	//	{
	//		m_velocity.setX(m_speed * TheInputHandler::Instance()->xvalue(0, 1));
	//	}

	//	/*if (TheInputHandler::Instance()->xvalue(0, 2) > 0 || TheInputHandler::Instance()->xvalue(0, 2) < 0)
	//	{
	//		m_velocity.setX(m_speed * TheInputHandler::Instance()->xvalue(0, 1));
	//	}

	//	if (TheInputHandler::Instance()->yvalue(0, 2) > 0 || TheInputHandler::Instance()->yvalue(0, 2) < 0)
	//	{
	//		m_velocity.setY(m_speed * TheInputHandler::Instance()->yvalue(0, 1));
	//	}*/
	//}

	//if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	//{
	//	m_velocity.setX(-1 * m_speed);
	//}
	//if (TheInputHandler::Instance()->getMouseButtonState(RIGHT))
	//{
	//	m_velocity.setX(1 * m_speed);
	//}

	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	//{
	//	m_velocity.setX(-1 * m_speed);
	//}
	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	//{
	//	m_velocity.setX(1 * m_speed);
	//}
	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	//{
	//	m_velocity.setY(-1 * m_speed);
	//}
	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	//{
	//	m_velocity.setY(1 * m_speed);
	//}
}