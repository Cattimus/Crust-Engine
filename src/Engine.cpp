#include "Engine.hpp"

Engine::Engine()
{
	screenWidth = 640;
	screenHeight = 480;
	vsync = true;
	maxFps = 60;
	useDelta = true;
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
	scenes = vector<unique_ptr<Scene>>();
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
	scene = scenes.back().get();
	return scene;
}

Scene* Engine::GetScene(string name)
{
	for(auto i = 0; i < scenes.size(); i++)
	{
		auto cur = scenes[i].get();
		if(cur->GetName() == name)
		{
			return cur;
		}
	}

	return NULL;
}

Scene* Engine::SwitchScene(string name)
{
	auto cur = GetScene(name);
	if(cur)
	{
		scene = cur;
	}
	return cur;
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

void Engine::StartMainLoop()
{
	MainLoop();
}

void Engine::LogicStep()
{
	if(scene)
	{
		scene->LogicStep();
	}
}

void Engine::LogicStep(double delta)
{
	if(scene)
	{
		scene->LogicStep(delta);
	}
}

//this is a temporary function for now. This will be modified later.
void Engine::RenderCurrent()
{
	SDL_RenderClear(renderer);

	if(scene)
	{
		auto objects = scene->GetObjectList();
		for(auto i = 0; i < objects->size(); i++)
		{
			auto cur = objects->at(i).get();
			SDL_Rect pos
			{
				.x = cur->GetXPosition(),
				.y = cur->GetYPosition(),
				.w = cur->GetWidth(),
				.h = cur->GetHeight()
			};

			SDL_RenderCopy(renderer, cur->GetTexture(), NULL, &pos);
			//TODO - Switch this to RenderCopyEx for rotation
		}
	}

	SDL_RenderPresent(renderer);
}

void Engine::MainLoop()
{
	bool running = true;
	SDL_Event e;

	while(running)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					//call quit callback here
					break;
			}
		}

		//perform logic step for every object
		if(useDelta)
		{
			LogicStep(delta);
		}
		else
		{
			LogicStep();
		}

		//render scene
		RenderCurrent();
	}
}

void Engine::HandleInput()
{
	return;
}