#include "Player.h"

#include "InputHandler.h"
#include <math.h>

Player::Player() : SDLGameObject()
{
}

Player::~Player()
{
}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_scale = 0.2f;
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

	//std::cout << "Velocity = " << sqrt(m_velocity.getX() * m_velocity.getX() + m_velocity.getY() * m_velocity.getY()) << "\n";
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
		m_rotation = 270;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(m_speed);
		m_rotation = 90;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-m_speed);
		m_rotation = 0;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(m_speed);
		m_rotation = 180;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)
		&& TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)
		)
	{
		m_velocity.setX(m_speed / sqrt(2));
		m_velocity.setY(-m_speed / sqrt(2));
		m_rotation = 45;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)
		&& TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)
		)
	{
		m_velocity.setX(-m_speed / sqrt(2));
		m_velocity.setY(-m_speed / sqrt(2));
		m_rotation = 320;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)
		&& TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)
		)
	{
		m_velocity.setX(m_speed / sqrt(2));
		m_velocity.setY(m_speed / sqrt(2));
		m_rotation = 135;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)
		&& TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)
		)
	{
		m_velocity.setX(-m_speed / sqrt(2));
		m_velocity.setY(m_speed / sqrt(2));
		m_rotation = 225;
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
