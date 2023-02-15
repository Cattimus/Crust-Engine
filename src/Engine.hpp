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

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	Scene* selectedScene = NULL;
	uint background_color[3];

	//list of textures
	vector<unique_ptr<Texture>> textures;

	//list of scenes
	vector<unique_ptr<Scene>> scenes;

	//user input callback
	void (*OnKeyboardInput)() = NULL;
	void (*OnMouseInput)() = NULL;
	void (*OnControllerInput)() = NULL;

	//helper functions for engine
	bool Init();
	void RenderBlank();

public:
	Engine();
	~Engine();

	//create the initial window
	void CreateWindow(uint, uint, uint, uint, bool resizable);

	//scene management functions
	Scene* CreateScene(string name);
	Scene* SwitchScene(string);
	void   DeleteScene(string);
	//mechanism to get the names of every scene

	//texture management functions
	Texture* CreateTexture(string path);
	Texture* GetTexture(string path);
	//there is no texture delete because textures will be refcounted

	//assign user input callback
	void RegisterKeyboardCallback(void (*)());
	void RegisterMouseCallback(void (*)());
	void RegisterControllerCallback(void (*)());

	//main logic and rendering
	void StartMainLoop();
	void RenderScene();
	void SetBackgroundColor(uint, uint, uint);
};