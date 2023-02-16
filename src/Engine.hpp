#pragma once

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

#include "Scene.hpp"
#include "Texture.hpp"

class Engine
{
private:
	int screenWidth = 640;
	int screenHeight = 480;

	//flags and configuration options
	bool vsync = true;
	int maxFps = 60;
	
	//parameters for cleanup passes
	bool cleanupTextures = true;
	int cleanupIntervalFrames = 300;

	//delta value for logic
	double delta = 0;

	//SDL values
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	uint background_color[3];

	//selected scene to be rendered
	Scene* scene = NULL;

	//lists for data
	vector<unique_ptr<Texture>> textures;
	vector<unique_ptr<Scene>> scenes;

	//user input callbacks
	void (*OnKeyboardInput)() = NULL;
	void (*OnMouseInput)() = NULL;
	void (*OnControllerInput)() = NULL;

	//helper functions for engine
	bool Init();
	void Quit(); //NOTE - destructor must be called on textures before SDL_Quit() is called.
	void MainLoop();
	void HandleInput();
	void TextureCleanup(); //Delete unreferenced textures

public:
	Engine();
	~Engine();

	//create the initial window
	void CreateWindow(uint, uint, uint, uint, bool resizable);

	//scene management functions
	Scene* CreateScene(string name);
	Scene* SwitchScene(string);
	void   DeleteScene(string);
	string GetSceneList(); //Get a list of scene names separated by ','

	//texture management functions
	Texture* CreateTexture(string path);
	Texture* GetTexture(string path);
	//there is no texture delete because textures will be refcounted

	//assign user input callback
	void RegisterKeyboardCallback(void (*)());
	void RegisterMouseCallback(void (*)());
	void RegisterControllerCallback(void (*)());

	//main loop and rendering
	void SetBackgroundColor(uint, uint, uint);
	void RenderCurrent();
	void StartMainLoop();

	//call logic functions
	void LogicStep();
	void LogicStep(double delta);
};