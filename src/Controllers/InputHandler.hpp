#pragma once

#include <iostream>
using namespace std;

#include <SDL2/SDL.h>

#include "Controllers/EventHandler.hpp"

//TODO - make sure to re-initialize values at the appropriate time
//TODO - add a way to know what keycode/scancode represents

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
	int32_t mousePosX;   //absolute mouse X position
	int32_t mouseMovedX; //mouse movement X (since last event/frame)
	int32_t mousePosY;   //absolute mouse Y position
	int32_t mouseMovedY; //mouse movement Y (since last event/frame)

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
	
	void ParseEvent(SDL_Event &e);
	
///////////////////////KEYBOARD EVENTS///////////////////////////
	uint32_t GetKeycode();
	bool KeyDown();
	bool KeyRepeat();

///////////////////MOUSE POSITION////////////////////////////////
	int32_t GetMouseX();
	int32_t GetMouseMovedX();
	int32_t GetMouseY();
	int32_t GetMouseMovedY();
	
	//mouse click
	uint8_t GetMouseButton();
	uint8_t GetMouseButtonClicks();
	bool MouseButtonDown();
	
	//button specific click
	bool LeftMouseClicked();
	bool LeftMouseDoubleClicked();
	bool RightMouseClicked();
	bool RightMouseDoubleClicked();
	bool MiddleMouseClicked();
	bool MiddleMouseDoubleClicked();
	
	//button specific drag
	bool LeftMouseDrag();
	bool RightMouseDrag();
	bool MiddleMouseDrag();

	//mouse wheel
	int32_t GetWheelScrolledX();
	int32_t GetWheelScrolledY();
	uint32_t GetWheelDirection();
};
