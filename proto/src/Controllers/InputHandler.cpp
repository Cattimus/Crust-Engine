#include "InputHandler.hpp"

void InputHandler::Init()
{
	lastKeycode = 0;
	keyDown = false;
	keyRepeat = false;

	mousePosX = 0;
	mouseMovedX = 0;
	mousePosY = 0;
	mouseMovedY = 0;
	
	mouseButton = 0;
	mouseButtonDown = false;
	mouseButtonClicks = 0;

	mouseScrolledX = 0;
	mouseScrolledY = 0;
	mouseWheelDirection = 0;

	// Keyboard input event
	events.RegisterEvent(Event("KeyboardInput"));

	// Mouse events
	events.RegisterEvent(Event("MouseButton"));
	events.RegisterEvent(Event("MouseDrag"));
	events.RegisterEvent(Event("MouseWheel"));
	events.RegisterEvent(Event("MouseMoved"));
}

InputHandler::InputHandler()
{
	Init();
}

uint32_t InputHandler::GetKeycode()
{
	return lastKeycode;
}

bool InputHandler::KeyDown()
{
	return keyDown;
}

bool InputHandler::KeyRepeat()
{
	return keyRepeat;
}

int32_t InputHandler::GetMouseX()
{
	return mousePosX;
}

int32_t InputHandler::GetMouseMovedX()
{
	return mouseMovedX;
}

int32_t InputHandler::GetMouseY()
{
	return mousePosY;
}

int32_t InputHandler::GetMouseMovedY()
{
	return mouseMovedY;
}

void InputHandler::ParseEvent(SDL_Event &e)
{
	switch (e.type)
	{
		// keyboard input
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			keyDown = e.key.state;
			lastKeycode = e.key.keysym.sym;
			keyRepeat = e.key.repeat;
			events.DoEvent("KeyboardInput");

			keyRepeat = 0;
			break;
		
		//mouse motion
		case SDL_MOUSEMOTION:
			mousePosX = e.motion.x;
			mouseMovedX = e.motion.xrel;
			mousePosY = e.motion.y;
			mouseMovedY = e.motion.yrel;

			if(mouseButtonDown)
			{
				events.DoEvent("MouseDrag");
			}
			else 
			{
				events.DoEvent("MouseMoved");
			}

			mouseMovedX = 0;
			mouseMovedY = 0;
			break;
		
		//mouse button
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			mousePosX = e.button.x;
			mousePosY = e.button.y;
			mouseButtonDown = (e.button.state == (uint8_t)SDL_MOUSEBUTTONDOWN);
			mouseButton = e.button.button;
			mouseButtonClicks = e.button.clicks;
			events.DoEvent("MouseButton");
			break;
		
		//mousewheel scroll
		case SDL_MOUSEWHEEL:
			mouseScrolledX = e.wheel.x;
			mouseScrolledY = e.wheel.y;
			mouseWheelDirection = e.wheel.direction;
			events.DoEvent("MouseWheel");

			mouseScrolledX = 0;
			mouseScrolledY = 0;
			break;
	}
}

uint8_t InputHandler::GetMouseButton()
{
	return mouseButton;
}

uint8_t InputHandler::GetMouseButtonClicks()
{
	return mouseButtonClicks;
}

bool InputHandler::MouseButtonDown()
{
	return mouseButtonDown;
}

bool InputHandler::LeftMouseClicked()
{
	return (mouseButton == SDL_BUTTON_LEFT) && mouseButtonDown && (mouseButtonClicks >= 1);
}

bool InputHandler::LeftMouseDoubleClicked()
{
	return (mouseButton == SDL_BUTTON_LEFT) && mouseButtonDown && (mouseButtonClicks == 2);
}

bool InputHandler::RightMouseClicked()
{
	return (mouseButton == SDL_BUTTON_RIGHT) && mouseButtonDown && (mouseButtonClicks >= 1);
}

bool InputHandler::RightMouseDoubleClicked()
{
	return (mouseButton == SDL_BUTTON_RIGHT) && mouseButtonDown && (mouseButtonClicks == 2);
}

bool InputHandler::MiddleMouseClicked()
{
	return (mouseButton == SDL_BUTTON_MIDDLE) && mouseButtonDown && (mouseButtonClicks >= 1);

}

bool InputHandler::MiddleMouseDoubleClicked()
{
	return (mouseButton == SDL_BUTTON_MIDDLE) && mouseButtonDown && (mouseButtonClicks == 2);
}

int32_t InputHandler::GetWheelScrolledX()
{
	return mouseScrolledX;
}

int32_t InputHandler::GetWheelScrolledY()
{
	return mouseScrolledY;
}

uint32_t InputHandler::GetWheelDirection()
{
	return mouseWheelDirection;
}
