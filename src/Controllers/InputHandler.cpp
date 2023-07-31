#include "InputHandler.hpp"

void InputHandler::Init()
{
	lastKeycode = 0;
	keyDown = false;
	keyRepeat = false;

	mouseX = 0;
	mouseY = 0;
	
	mouseButton = 0;
	mouseButtonDown = false;
	mouseButtonClicks = 0;

	mouseScrolledX = 0;
	mouseScrolledY = 0;
	mouseWheelDirection = 0;

	// Keyboard input event
	events.RegisterEvent(Event<InputHandler>(this, "KeyboardInput"));

	// Mouse events
	events.RegisterEvent(Event<InputHandler>(this, "MouseButton"));
	events.RegisterEvent(Event<InputHandler>(this, "MouseWheel"));
	events.RegisterEvent(Event<InputHandler>(this, "MouseMoved"));
}

InputHandler::InputHandler()
{
	Init();
}

EventHandler<InputHandler>* InputHandler::GetEventHandler()
{
	return &events;
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
	return mouseX;
}

int32_t InputHandler::GetMouseY()
{
	return mouseY;
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
			break;
		
		//mouse motion
		case SDL_MOUSEMOTION:
			mouseX = e.motion.x;
			mouseY = e.motion.y;
			events.DoEvent("MouseMoved");
			break;
		
		//mouse button
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			mouseX = e.button.x;
			mouseY = e.button.y;
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
			break;

	}
}

