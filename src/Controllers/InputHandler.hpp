#pragma once

#include <iostream>
using namespace std;

#include <SDL2/SDL.h>

#include "Controllers/EventHandler.hpp"

/*
 	* The goal of this class is to handle inputs of all kinds
 	* the Engine class will pull input values and register callbacks to this class
 	* in order to deal with user input.
 	*
 	*  - Keyboard events
 	*  - Mouse events
 	*  - Audio events (input only)
 	*  - Controller events
*/

class InputHandler
{
private:

////////////////////KEYBOARD INPUT VALUES////////////////////////
	uint32_t lastKeycode;
	bool keyDown;
	bool keyRepeat;

///////////////////MOUSE POSITION VALUES//////////////////////////
	int32_t mouseX;
	int32_t mouseY;

	//mouse click
	uint8_t mouseButton;
	bool mouseButtonDown;
	uint8_t mouseButtonClicks;

	//mouse wheel
	int32_t mouseScrolledX;
	int32_t mouseScrolledY;
	uint32_t mouseWheelDirection;
	
	//Event handler for user input
	EventHandler<InputHandler> events;

	void Init();

public:

	InputHandler();

	EventHandler<InputHandler>* GetEventHandler();
	
	void HandleInput(SDL_Event &e);
	
///////////////////////KEYBOARD EVENTS///////////////////////////
	uint32_t GetKeycode();
	bool KeyDown();
	bool KeyRepeat();

///////////////////MOUSE POSITION////////////////////////////////
	int32_t GetMouseX();
	int32_t GetMouseY();
	
	//mouse click
	uint8_t GetMouseButton();
	uint8_t GetMouseButtonClicks();
	bool MouseButtonDown();

	//mouse wheel
};
