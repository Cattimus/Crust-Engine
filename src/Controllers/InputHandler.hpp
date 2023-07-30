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
	
	//Event handler for user input
	EventHandler<InputHandler> events;

public:

	InputHandler();

	EventHandler<InputHandler>* GetEventHandler();
	
///////////////////////KEYBOARD EVENTS///////////////////////////
	uint32_t GetKeycode();
	bool KeyDown();
	bool KeyUp();

///////////////////MOUSE POSITION////////////////////////////////
	int32_t GetMouseX();
	int32_t GetMouseY();
};
