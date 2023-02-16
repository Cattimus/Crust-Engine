#include "Engine.hpp"

Engine::Engine()
{
	screenWidth = 640;
	screenHeight = 480;
	vsync = true;
	maxFps = 60;
	cleanupTextures = true;
	cleanupIntervalFrames = 300;
	delta = 0;
	window = NULL;
	renderer = NULL;
	backgroundColor[0] = 0;
	backgroundColor[1] = 0;
	backgroundColor[2] = 0;
	scene = NULL;
	OnKeyboardInput = NULL;
	OnMouseInput = NULL;
	OnControllerInput = NULL;
}

bool Engine::Init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL failed to initialize. Error: " << SDL_GetError() << endl;
		return false;
	}

	uint imageFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
	if(!(IMG_Init(imageFlags) & imageFlags))
	{
		cout << "SDL_Image failed to initialize. Error: " << IMG_GetError() << endl;
		return false;
	}

	return true;
}