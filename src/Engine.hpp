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

//TODO - implement frame limiting if vsync isn't set


class Engine
{
private:
	int screenWidth;
	int screenHeight;

	//flags and configuration options
	bool vsync;
	bool useDelta;
	bool useBilinear;
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
	Scene* scene;

	//lists for data
	vector<unique_ptr<Texture>> textures;
	vector<unique_ptr<Scene>> scenes;

	//user input callbacks
	void (*OnKeyboardInput)();
	void (*OnMouseInput)();
	void (*OnControllerInput)();
	void (*OnQuitEvent)();

	//helper functions for engine
	void Init();
	void Quit();
	void SetBackgroundColor();

	void MainLoop();
	void HandleInput();
	void AdjustFlags();
	//void TextureCleanup(); //Delete unreferenced textures

public:
	Engine();
	~Engine();

	//create the initial window
	void CreateWindow(string title, int x, int y, int w, int h, bool resizable);
	void CreateWindow(string title, int w, int h, bool resizable);
	void CreateWindow(string title, bool resizable);
	void CreateWindow(string title);

	//scene management functions
	Scene* CreateScene(string name);
	Scene* GetScene(string name);
	Scene* SwitchScene(string name);
	void   DeleteScene(string name);
	string GetSceneList(); //Get a list of scene names separated by ','

	//assign user input callback
	//WARNING - implementation for these is currently incomplete
	void RegisterKeyboardCallback(void (*)());
	void RegisterMouseCallback(void (*)());
	void RegisterControllerCallback(void (*)());
	void RegisterQuitCallback(void (*)());

	//main loop and rendering
	void SetBackgroundColor(uint, uint, uint);
	void RenderCurrent();
	void StartMainLoop();

	//texture functions
	Texture* GetTexture(string path);

	//call logic functions
	void LogicStep();
	void LogicStep(double delta);

	//functions to adjust engine parameters
	void UseBilinearScaling();
	void UseNearestScaling();
	void EnableVsync();
	void DisableVsync();
	void SetFrameLimit(uint limit);
};