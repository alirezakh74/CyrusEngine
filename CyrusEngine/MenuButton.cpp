#include "MenuButton.h"

#include "InputHandler.h"

MenuButton::MenuButton()
{
}

MenuButton::~MenuButton()
{
}

void MenuButton::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(pParams);
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (
		pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY()
		)
	{
		//m_currentFrame = MOUSE_OVER;

		/*if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
		{
			m_currentFrame = CLICKED;
			m_callback();
			m_bReleased = false;
		}*/

		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_callback();
			m_bReleased = false;
		}
		else if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::draw()
{
	ShooterObject::draw();
}

void MenuButton::clean()
{
	ShooterObject::clean();
}
