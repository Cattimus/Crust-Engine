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

Engine::~Engine()
{
	Quit();
}

void Engine::Init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL failed to initialize. Error: " << SDL_GetError() << endl;
		exit(-1);
	}

	uint imageFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
	if(!(IMG_Init(imageFlags) & imageFlags))
	{
		cout << "SDL_Image failed to initialize. Error: " << IMG_GetError() << endl;
		exit(-1);
	}
}

void Engine::Quit()
{
	//destroy our values before SDL goes out of scope
	//the only reliable way I have found to do this is to overwrite the vector.
	textures = vector<unique_ptr<Texture>>();

	if(window != NULL)
	{
		if(renderer != NULL)
		{
			SDL_DestroyRenderer(renderer);
			renderer = NULL;
		}

		SDL_DestroyWindow(window);
		window = NULL;
	}

	IMG_Quit();
	SDL_Quit();
}

//background color functions
void Engine::SetBackgroundColor(uint r, uint g, uint b)
{
	backgroundColor[0] = r;
	backgroundColor[1] = g;
	backgroundColor[2] = b;
	SetBackgroundColor();
}
void Engine::SetBackgroundColor()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor[0], backgroundColor[1], backgroundColor[2], 0xFF);
}

void Engine::CreateWindow(string title, int x, int y, int w, int h, bool resizable)
{
	Init();

	uint flags = SDL_WINDOW_SHOWN;
	if(resizable)
	{
		flags |= SDL_WINDOW_RESIZABLE;
	}

	if(x < 1)
	{
		x = SDL_WINDOWPOS_UNDEFINED;
	}

	if(y < 1)
	{
		y = SDL_WINDOWPOS_UNDEFINED;
	}

	if(w < 1 || h < 1)
	{
		w = screenWidth;
		h = screenHeight;
	}

	window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	if(!window)
	{
		cout << "Window creation failed. Error: " << SDL_GetError() << endl;
		exit(-1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SetBackgroundColor();
}
void Engine::CreateWindow(string title, int w, int h, bool resizable)
{
	CreateWindow(title, -1, -1, w, h, resizable);
}
void Engine::CreateWindow(string title, bool resizable)
{
	CreateWindow(title, -1, -1, -1, -1, resizable);
}
void Engine::CreateWindow(string title)
{
	CreateWindow(title, -1, -1, -1, -1, false);
}

//this is a temporary function for now. This will be modified later.
void Engine::RenderCurrent()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

Texture* Engine::GetTexture(string path)
{
	//search for existing textures
	for(auto i = 0; i < textures.size(); i++)
	{
		Texture* cur = textures[i].get();
		if(cur->GetPath() == path)
		{
			return cur;
		}
	}

	//create a new texture
	textures.push_back(make_unique<Texture>(path, renderer));
	return textures.back().get();
}

void Engine::RegisterKeyboardCallback(void (*func)())
{
	OnKeyboardInput = func;
}
void Engine::RegisterMouseCallback(void (*func)())
{
	OnMouseInput = func;
}
void Engine::RegisterControllerCallback(void (*func)())
{
	OnControllerInput = func;
}

Scene* Engine::CreateScene(string name)
{
	scenes.push_back(make_unique<Scene>(name, this));
	return scenes.back().get();
}

Scene* Engine::SwitchScene(string name)
{
	for(auto i = 0; i < scenes.size(); i++)
	{
		auto cur = scenes[i].get();
		if(cur->GetName() == name)
		{
			scene = cur;
			return cur;
		}
	}

	return NULL;
}

void Engine::DeleteScene(string name)
{
	//get index of scene
	int index = -1;
	for(auto i = 0; i < scenes.size(); i++)
	{
		auto cur = scenes[i].get();
		if(cur->GetName() == name)
		{
			index = i;
			break;
		}
	}

	//delete scene
	if(index > -1)
	{
		scenes.erase(scenes.begin() + index);
	}
}

string Engine::GetSceneList()
{
	string to_return = "";
	for(auto i = 0; i < scenes.size(); i++)
	{
		auto cur = scenes[i].get();
		to_return += cur->GetName();

		if(i < scenes.size() - 1)
		{
			to_return += ",";
		}
	}

	return to_return;
}