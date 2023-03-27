#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

class Scene;
#include "Controllers/Scene.hpp"
#include "Objects/Texture.hpp"
#include "Controllers/EventHandler.hpp"

//TODO - Implement keeping track of average FPS

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
	double delta;

////////////SDL VALUES///////////////////////////////////////////

	//Main window
	SDL_Window* window;

	//Main renderer
	SDL_Renderer* renderer;

	//The background color of the window (blank color)
	uint8_t backgroundColor[3];

	//Selected scene to be rendered
	Scene* scene;

	//List that holds texture references
	unordered_map<string, unique_ptr<Texture>> textures;

	//List that holds scene references
	unordered_map<string, unique_ptr<Scene>> scenes;

	//Event handler
	EventHandler<Engine> events;

////////////////////KEYBOARD INPUT VALUES////////////////////////
	uint32_t lastKeycode;
	bool keyDown;
	bool keyRepeat;

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
	void DeleteScene(string name);

	//Returns a list of all active scene names separated by ','
	string GetSceneList();

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
	double GetDelta();

	void EnableVsync();
	void DisableVsync();
	
	void SetFrameLimit(uint limit);

	//Generate report about the current amount of objects
	string GetReport();

///////////////////EVENT HANDLER FUNCTIONS////////////////////////
	EventHandler<Engine>* GetEventHandler();

///////////////////KEYBOARD EVENT FUNCTIONS//////////////////////

	//Get keyboard keycode
	uint32_t GetKeycode();

	//Get key up/down status
	bool KeyDown();

	//Get key repeat status
	bool KeyRepeat();
};