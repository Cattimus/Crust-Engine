#pragma once

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

class Scene;
#include "Scene.hpp"
#include "Texture.hpp"

//TODO - Implement keeping track of average FPS
//TODO - Implement fullscreen mode

//Params: (pressed/released, keycode)
typedef void (*KeyboardEventCallback)(bool, char);

//Params: (x position, y position, x movement, y movement)
typedef void (*MouseMoveCallback)(int, int, int, int);	
//Params: (pressed/released, mouse button, # of clicks (single or double), x position, y position)
typedef void (*MouseClickCallback)(bool, int, int, int, int);
//Params: (horizontal scroll amount, vertical scroll amount)
typedef void (*MouseWheelCallback)(int, int);

//Params: (width, height)
typedef void (*WindowResizeCallback)(int, int);
typedef void (*WindowFocusCallback)();
typedef void (*WindowUnfocusCallback)();

typedef void (*QuitEventCallback)();

class Engine
{
private:
/////////////////WINDOW OPTIONS////////////////////////

	int windowWidth;
	int windowHeight;
	bool windowResizable;

////////////FLAGS AND CONFIGURATION OPTIONS////////////////////

	//Option for vsync support
	bool vsync;

	//Option for delta time support
	bool useDelta;

	//Option for bilinear(true) or nearest(false) filtering
	bool useBilinear;

	//FPS cap which will be active if it is set to a positive value
	int maxFps;

//////////PARAMETERS FOR CLEANUP PASSES/////////////////////////
	
	//Flag for if textures should be deleted if they are unused
	bool cleanupTextures;

	//How many frames should pass between checks to see if there are unused textures
	int cleanupIntervalFrames;

	//Delta time value for step logic
	double delta = 0;

////////////SDL VALUES///////////////////////////////////////////

	//Main window
	SDL_Window* window;

	//Main renderer
	SDL_Renderer* renderer;

	//The background color of the window (blank color)
	Uint8 backgroundColor[3];

	//Selected scene to be rendered
	Scene* scene;

	//List that holds texture references
	vector<unique_ptr<Texture>> textures;

	//List that holds scene references
	vector<unique_ptr<Scene>> scenes;

//////////USER INPUT CALLBACKS////////////////////////////////

	//Callback that will activate on keyboard input
	//Params: (pressed/released, keycode)
	KeyboardEventCallback OnKeyboardInput;
	
/////////////MOUSE CALLBACKS/////////////////////////////////

	//Callback that will activate when the mouse is moved
	//Params: (x position, y position, x movement, y movement)
	MouseMoveCallback OnMouseMove;

	//Callback that will activate when the mouse is clicked
	//Params: (pressed/released, mouse button, # of clicks (single or double), x position, y position)
	MouseClickCallback OnMouseClick;

	//Callback that will activate when the mouse wheel is scrolled
	//Params: (horizontal scroll amount, vertical scroll amount)
	MouseWheelCallback OnMouseWheel;

////////////WINDOW CALLBACKS//////////////////////////////////////

	//Callback that will activate when the window is resized
	//Params: (width, height)
	WindowResizeCallback OnWindowResize;

	//Callback that will activate when the window gains focus
	WindowFocusCallback OnWindowFocus;

	//Callback that will activate when the window loses focus
	WindowUnfocusCallback OnWindowUnfocus;

	//Callback that will activate when SDL has shut down
	QuitEventCallback OnQuitEvent;

//////////////HELPER FUNCTIONS FOR ENGINE///////////////////////////

	//Helper function to initialize SDL
	void Init();

	//Helper function to shut down SDL
	void Quit();

	//Helper function to manage background color
	void SetBackgroundColor();

	//The main loop that will run continuously. The "game loop"
	void MainLoop();

	//Possible helper function that might be used to handle SDL inputs and activating callbacks
	void HandleInput();

	//Helper function to set SDL flags
	void SetFlags();

	//Helper function to delete unreferenced textures
	//WARNING - THIS IS NOT IMPLEMENTED YET
	void TextureCleanup();

public:
	Engine();
	~Engine();

////////////////WINDOW MANAGEMENT FUNCTIONS////////////////////////////

	void CreateWindow(string title, int x, int y, int w, int h, bool resizable);
	void CreateWindow(string title, int w, int h, bool resizable);
	void CreateWindow(string title, bool resizable);
	void CreateWindow(string title);
	int GetWindowWidth();
	int GetWindowHeight();

	//Change window size. -1 may be passed to keep that parameter the same.
	void SetWindowSize(int w, int h);

///////////////SCENE MANAGEMENT FUNCTIONS//////////////////////////////

	//Creates a new scene with name. Returns a reference to the new scene
	Scene* CreateScene(string name);

	//Returns a reference to the scene by name
	Scene* GetScene(string name);

	//Switch the current scene to the scene with name. Returns a reference to that scene
	Scene* SwitchScene(string name);

	//Delete a scene
	void   DeleteScene(string name);

	//Returns a list of all active scene names separated by ','
	string GetSceneList();

///////////////CALLBACK MANAGEMENT//////////////////////////////////

	void RegisterQuitEventCallback(QuitEventCallback func);
	void ClearQuitEventCallback();

	void RegisterKeyboardCallback(KeyboardEventCallback func);
	void ClearKeyboardCallback();

	void RegisterMouseMoveCallback(MouseMoveCallback func);
	void ClearMouseMoveCallback();

	void RegisterMouseClickCallback(MouseClickCallback func);
	void ClearMouseClickCallback();

	void RegisterMousewheelCallback(MouseWheelCallback func);
	void ClearMousewheelCallback();

	void RegisterWindowResizeCallback(WindowResizeCallback func);
	void ClearWindowResizeCallback();

	void RegisterWindowFocusCallback(WindowFocusCallback func);
	void ClearWindowFocusCallback();

	void RegisterWindowUnfocusCallback(WindowUnfocusCallback func);
	void ClearWindowUnfocusCallback();

//////////////MAIN LOOP AND RENDERING//////////////////////////

	void SetBackgroundColor(uint, uint, uint);

	//Render the currently selected scene. Will do nothing if 'scene' is null.
	void RenderCurrent();

	//User-accessable function to start the main loop
	void StartMainLoop();

	//Get a reference to a texture. Intended to be only used by Scene class (This may need to be updated in the future to hide from users.)
	Texture* GetTexture(string path);

	//Call logic functions without delta time
	void LogicStep();

	//Call logic functions with delta time
	void LogicStep(double delta);

///////////PARAMETER ADJUST FUNCTIONS////////////////////////

	//Use bilinear texture filtering
	void UseBilinearFiltering();

	//Use nearest texture filtering
	void UseNearestFiltering();

	void EnableDelta();
	void DisableDelta();

	void EnableVsync();
	void DisableVsync();
	
	void SetFrameLimit(uint limit);
};