#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "Vector2D.h"

enum button_states
{
	LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance();


	void initializeJoysticks();
	bool joysticksInitialized();
	void update();
	void clean();

	void reset();

	int getAxisX(int joy, int stick);
	int getAxisY(int joy, int stick);

	bool getButtonState(int joy, int buttonNumber) const;

	bool getMouseButtonState(int buttonNumber) const;

	Vector2D* getMousePosition() const;

	bool isKeyDown(SDL_Scancode key) const;

private:
	InputHandler();
	~InputHandler();

	static InputHandler* s_pInstance;

	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoystickInitialized;

	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	static const int m_joystickDeadZone = 10000;

	std::vector<std::vector<bool>> m_buttonStates;

	std::vector<bool> m_mouseButtonStates;

	Vector2D* m_mousePosition;

	const Uint8* m_keystates;

	void onKeyDown();
	void onKeyUp();

	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);
};

typedef InputHandler TheInputHandler;
