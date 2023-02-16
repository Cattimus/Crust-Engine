#pragma once

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

//#include "Scene.hpp"
#include "Texture.hpp"

class Engine
{
private:
	int screenWidth;
	int screenHeight;

	//flags and configuration options
	bool vsync;
	int maxFps;
	
	//parameters for cleanup passes
	bool cleanupTextures;
	int cleanupIntervalFrames;

	//delta value for logic
	double delta = 0;

	//SDL values
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint8 backgroundColor[3];

	//selected scene to be rendered
	//Scene* scene;

	//lists for data
	vector<unique_ptr<Texture>> textures;
	//vector<unique_ptr<Scene>> scenes;

	//user input callbacks
	void (*OnKeyboardInput)();
	void (*OnMouseInput)();
	void (*OnControllerInput)();

	//helper functions for engine
	void Init();
	void Quit(); //NOTE - destructor must be called on textures before SDL_Quit() is called.
	void SetBackgroundColor();

	/*
	void MainLoop();
	void HandleInput();
	void TextureCleanup(); //Delete unreferenced textures
	*/

	//texture management functions
	Texture* GetTexture(string path);
	//there is no texture delete because textures will be refcounted

public:
	Engine();
	~Engine();

	//create the initial window
	void CreateWindow(string title, int x, int y, int w, int h, bool resizable);
	void CreateWindow(string title, int w, int h, bool resizable);
	void CreateWindow(string title, bool resizable);
	void CreateWindow(string title);

	/*
	//scene management functions
	Scene* CreateScene(string name);
	Scene* SwitchScene(string);
	void   DeleteScene(string);
	string GetSceneList(); //Get a list of scene names separated by ','
	*/

	//assign user input callback
	//WARNING - implementation for these is currently incomplete
	void RegisterKeyboardCallback(void (*)());
	void RegisterMouseCallback(void (*)());
	void RegisterControllerCallback(void (*)());

	//main loop and rendering
	void SetBackgroundColor(uint, uint, uint);
	void RenderCurrent();

	/*
	void StartMainLoop();

	//call logic functions
	void LogicStep();
	void LogicStep(double delta);
	*/
};