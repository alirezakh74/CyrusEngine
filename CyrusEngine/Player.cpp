#include "Player.h"

#include <math.h>

#include "InputHandler.h"
#include "Game.h"
#include "BulletHandler.h"
#include "TextureManager.h"
#include "SoundManager.h"

Player::Player() : ShooterObject()
{
}

Player::~Player()
{
}

void Player::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(pParams);
	m_scale = 0.2f;
	m_bInvulnerable = true;
	m_invulnerableCurrentTime = 0;
	m_invulnerableLastTime = 0;
	m_bStartInvulnerable = true;
	m_startInvulnerableTime = 0;
	m_bStartTime = false;
	/*m_bBullet = true;
	m_bulletCurrentTime = 0;
	m_bulletLastTime = 0;*/

	m_bAllowMissile = true;
	m_missileCurrentTime = 0;
	m_missileLastTime = 0;
	m_missileSpeedX = 0;
	m_missileSpeedY = 0;

	TheSoundManager::Instance()->load("assets/shoot5.wav", "bullet_sfx", sound_type::SOUND_SFX);
	TheSoundManager::Instance()->load("assets/shoot1.wav", "missile_sfx", sound_type::SOUND_SFX);
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput();
	handleAmimation();

	m_fireCurrentTime = TheGame::Instance()->getDeltaTime();
	//std::cout << "time = " << m_fireCurrentTime << "\n";
	if (m_fireCurrentTime - m_fireLastTime >= FIRE_RATE_PER_TIME)
	{
		m_fireLastTime = m_fireCurrentTime;
		m_bAllowFire = true;
	}

	m_missileCurrentTime = TheGame::Instance()->getDeltaTime();
	if (m_missileCurrentTime - m_missileLastTime >= MISSILE_RATE)
	{
		m_missileLastTime = m_missileCurrentTime;
		m_bAllowMissile = true;
	}

	/*if (m_bBullet)
	{

	}*/

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

	ShooterObject::update();

	//std::cout << "Velocity = " << sqrt(m_velocity.getX() * m_velocity.getX() + m_velocity.getY() * m_velocity.getY()) << "\n";
}

void Player::draw()
{
	ShooterObject::draw();
}

void Player::clean()
{
}

void Player::handleInput()
{
	//m_velocity.setX(0);
	//m_velocity.setY(0);

	// keyboard inputs
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		if (m_bAllowFire)
		{
			m_bAllowFire = false;
			TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + (m_width * m_scale / 2) - 5, m_position.getY() + (m_height * m_scale / 2) - 5, 11, 11, "bullet1", 1, Vector2D(0, -10));
			TheSoundManager::Instance()->playSound("bullet_sfx", 0);
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_H))
	{
		if (!m_bInvulnerable)
		{
			setVulnerable();
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z))
	{
		if (m_bAllowMissile)
		{
			m_missileSpeedX = MISSILE_SPEED * cos(m_rotation * M_PI / 180);
			m_missileSpeedY = MISSILE_SPEED * sin(m_rotation * M_PI / 180);

			m_bAllowMissile = false;
			TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + (m_width * m_scale / 2) - 15, m_position.getY() + (m_height * m_scale / 2) - 5, 30, 15, "missilePlayer", 1, Vector2D(m_missileSpeedX, m_missileSpeedY), m_rotation);
			TheSoundManager::Instance()->playSound("missile_sfx", 0);
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-m_speed);
		m_rotation = 180;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(m_speed);
		m_rotation = 0;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-m_speed);
		m_rotation = 270;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(m_speed);
		m_rotation = 90;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)
		&& TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)
		)
	{
		m_velocity.setX(m_speed / sqrt(2));
		m_velocity.setY(-m_speed / sqrt(2));
		m_rotation = 315;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)
		&& TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)
		)
	{
		m_velocity.setX(-m_speed / sqrt(2));
		m_velocity.setY(-m_speed / sqrt(2));
		m_rotation = 225;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)
		&& TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)
		)
	{
		m_velocity.setX(m_speed / sqrt(2));
		m_velocity.setY(m_speed / sqrt(2));
		m_rotation = 45;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)
		&& TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)
		)
	{
		m_velocity.setX(-m_speed / sqrt(2));
		m_velocity.setY(m_speed / sqrt(2));
		m_rotation = 135;
	}

	// joystick inputs
	if (TheInputHandler::Instance()->joysticksInitialized())
	{
		//m_velocity.setX(0);
		//m_velocity.setY(0);

		// joystick 1
		// bullet button set up
		if (TheInputHandler::Instance()->getButtonState(0, 1))
		{
			if (m_bAllowFire)
			{
				m_bAllowFire = false;
				TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + (m_width * m_scale / 2) - 5, m_position.getY() + (m_height * m_scale / 2) - 5, 11, 11, "bullet1", 1, Vector2D(0, -10));
				TheSoundManager::Instance()->playSound("bullet_sfx", 0);
			}
		}
		if (TheInputHandler::Instance()->getButtonState(0, 2))
		{
			if (m_bAllowMissile)
			{
				m_missileSpeedX = MISSILE_SPEED * cos(m_rotation * M_PI / 180);
				m_missileSpeedY = MISSILE_SPEED * sin(m_rotation * M_PI / 180);

				m_bAllowMissile = false;
				TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + (m_width * m_scale / 2) - 15, m_position.getY() + (m_height * m_scale / 2) - 5, 30, 15, "missilePlayer", 1, Vector2D(m_missileSpeedX, m_missileSpeedY), m_rotation);
				TheSoundManager::Instance()->playSound("missile_sfx", 0);
			}
		}
		// arrow buttons
		if ((TheInputHandler::Instance()->getAxisY(0, 1) > 0 || TheInputHandler::Instance()->getAxisY(0, 1) < 0)
			&& TheInputHandler::Instance()->getAxisX(0, 1) == 0)
		{
			if (TheInputHandler::Instance()->getAxisY(0, 1) > 0)
			{
				m_velocity.setY(m_speed);
			}
			else if (TheInputHandler::Instance()->getAxisY(0, 1) < 0)
			{
				m_velocity.setY(-m_speed);
			}

			if (m_velocity.getY() < 0)
			{
				m_rotation = 270;
			}
			else if (m_velocity.getY() > 0)
			{
				m_rotation = 90;
			}
		}

		if ((TheInputHandler::Instance()->getAxisX(0, 1) > 0 || TheInputHandler::Instance()->getAxisX(0, 1) < 0)
			&& TheInputHandler::Instance()->getAxisY(0, 1) == 0)
		{
			if (TheInputHandler::Instance()->getAxisX(0, 1) > 0)
			{
				m_velocity.setX(m_speed);
			}
			else if (TheInputHandler::Instance()->getAxisX(0, 1) < 0)
			{
				m_velocity.setX(-m_speed);
			}

			if (m_velocity.getX() < 0)
			{
				m_rotation = 180;
			}
			else if (m_velocity.getX() > 0)
			{
				m_rotation = 0;
			}
		}

		if (TheInputHandler::Instance()->getAxisX(0, 1) != 0 && TheInputHandler::Instance()->getAxisY(0, 1))
		{
			if (TheInputHandler::Instance()->getAxisX(0, 1) > 0)
			{
				m_velocity.setX(m_speed / sqrt(2));
			}
			else if (TheInputHandler::Instance()->getAxisX(0, 1) < 0)
			{
				m_velocity.setX(-m_speed / sqrt(2));
			}

			if (TheInputHandler::Instance()->getAxisY(0, 1) > 0)
			{
				m_velocity.setY(m_speed / sqrt(2));
			}
			else if (TheInputHandler::Instance()->getAxisY(0, 1) < 0)
			{
				m_velocity.setY(-m_speed / sqrt(2));
			}

			if (m_velocity.getX() < 0 && m_velocity.getY() < 0)
			{
				m_rotation = 225;
			}
			else if (m_velocity.getX() > 0 && m_velocity.getY() < 0)
			{
				m_rotation = 315;
			}
			else if (m_velocity.getX() > 0 && m_velocity.getY() > 0)
			{
				m_rotation = 45;
			}
			else if (m_velocity.getX() < 0 && m_velocity.getY() > 0)
			{
				m_rotation = 135;
			}
		}

		/*if (TheInputHandler::Instance()->getAxisX(0, 2) > 0 || TheInputHandler::Instance()->getAxisX(0, 2) < 0)
		{
			m_velocity.setX(m_speed * TheInputHandler::Instance()->getAxisX(0, 1));
		}

		if (TheInputHandler::Instance()->getAxisY(0, 2) > 0 || TheInputHandler::Instance()->getAxisY(0, 2) < 0)
		{
			m_velocity.setY(m_speed * TheInputHandler::Instance()->getAxisY(0, 1));
		}*/
	}

	// mouse inputs
	/*if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(-m_speed);
	}
	if (TheInputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		m_velocity.setX(m_speed);
	}*/

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

void Player::handleAmimation()
{
	static unsigned int initialTime = TheGame::Instance()->getDeltaTime();
	if (m_bStartInvulnerable)
	{
		m_invulnerableCurrentTime = TheGame::Instance()->getDeltaTime() - initialTime;
		if (m_invulnerableCurrentTime >= ALL_OF_INVULNERABLE_TIME)
		{
			m_bStartInvulnerable = false;
		}

	}
	else
	{
		if (m_bStartTime)
		{
			m_startInvulnerableTime = TheGame::Instance()->getDeltaTime();
			m_bStartTime = false;
		}
		m_invulnerableCurrentTime = TheGame::Instance()->getDeltaTime() - m_startInvulnerableTime;
	}
	//std::cout << "dt = " << m_invulnerableCurrentTime << "\n";

	if (m_bInvulnerable)
	{
		if (m_invulnerableCurrentTime >= ALL_OF_INVULNERABLE_TIME)
		{
			m_alpha = 255;
			m_bInvulnerable = false;
		}
		else if(m_invulnerableCurrentTime >= m_invulnerableLastTime + TIME_PER_CHANGHE_ALPHA_MOD)
		{
			if (m_alpha == 255)
			{
				m_alpha = 0;
			}
			else
			{
				m_alpha = 255;
			}

			m_invulnerableLastTime = m_invulnerableCurrentTime;
		}

		SDL_SetTextureAlphaMod(TheTextureManager::Instance()->getTexture(m_textureID), m_alpha);
	}
}

void Player::resurrect()
{
	TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);

	m_position.setX(100);
	m_position.setY(200);
	m_bDying = false;

	m_textureID = "player";

	m_currentFrame = 0;
	m_numFrames = 1;
	//m_width = ;
	//m_height = ;
	m_dyingCounter = 0;
	m_bInvulnerable = true;
}

void Player::setVulnerable()
{
	m_invulnerableCurrentTime = 0;
	m_invulnerableLastTime = 0;
	m_bInvulnerable = true;
	m_bStartTime = true;
}
