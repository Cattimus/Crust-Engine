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

//TODO - implement keeping track of average FPS


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
	void (*OnKeyboardInput)(bool, char); //(bool pressed/released, char key)
	
	//mouse
	void (*OnMouseMove)(int, int, int, int); //(x, y, x(relative), y(relative))
	void (*OnMouseClick)(bool, int, int, int, int); //(bool(up/down), button, # of clicks, x, y)
	void (*OnMouseWheel)(int, int); //(horizontal scroll, vertical scroll)

	//window
	void (*OnWindowResize)(int, int); //(width, height)
	void (*OnWindowFocus)();
	void (*OnWindowUnfocus)();

	void (*OnQuitEvent)();

	//helper functions for engine
	void Init();
	void Quit();
	void SetBackgroundColor();

	void MainLoop();
	void HandleInput();
	void SetFlags();
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

	//SDL quit event callback
	void RegisterQuitEventCallback(void(*)());

	//assign user input callback
	void RegisterKeyboardCallback(void (*)(bool, char));

	//mouse callbacks
	void RegisterMouseMoveCallback(void (*)(int, int, int, int));
	void RegisterMouseClickCallback(void (*)(bool, int, int, int, int));
	void RegisterMousewheelCallback(void (*)(int, int));

	//window callbacks
	void RegisterWindowResizeCallback(void (*OnWindowResize)(int, int));
	void RegisterWindowFocusCallback(void (*OnWindowFocus)());
	void RegisterWindowUnfocusCallback(void (*OnWindowUnfocus)());

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