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

}