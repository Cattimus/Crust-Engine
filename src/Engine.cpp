#include "Engine.hpp"

Engine::Engine()
{
	screenWidth = 640;
	screenHeight = 480;
	vsync = true;
	maxFps = -1;
	useDelta = true;
	useBilinear = true;
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
	OnMouseMove = NULL;
	OnMouseClick = NULL;
	OnMouseWheel = NULL;
	OnWindowResize = NULL;
	OnWindowFocus = NULL;
	OnWindowUnfocus = NULL;
	OnQuitEvent = NULL;
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

	//set our configured flags
	SetFlags();
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

void Engine::RegisterQuitEventCallback(void(*func)())
{
	if(!func)
	{
		return;
	}

	OnQuitEvent = func;
}

void Engine::RegisterKeyboardCallback(void (*func)(bool, char))
{
	if(!func)
	{
		return;
	}

	OnKeyboardInput = func;
}

void Engine::RegisterMouseMoveCallback(void (*func)(int, int, int, int))
{
	if(!func)
	{
		return;
	}

	OnMouseMove = func;
}
void Engine::RegisterMouseClickCallback(void (*func)(bool, int, int, int, int))
{
	if(!func)
	{
		return;
	}

	OnMouseClick = func;
}
void Engine::RegisterMousewheelCallback(void (*func)(int, int))
{
	if(!func)
	{
		return;
	}

	OnMouseWheel = func;
}

void Engine::RegisterWindowResizeCallback(void (*func)(int, int))
{
	if(!func)
	{
		return;
	}

	OnWindowResize = func;
}
void Engine::RegisterWindowFocusCallback(void (*func)())
{
	if(!func)
	{
		return;
	}

	OnWindowFocus = func;
}
void Engine::RegisterWindowUnfocusCallback(void (*func)())
{
	if(!func)
	{
		return;
	}
	
	OnWindowUnfocus = func;
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

	int lastFrame = SDL_GetTicks();

	while(running)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					OnQuitEvent();
					break;

				case SDL_KEYDOWN:
				case SDL_KEYUP:
					OnKeyboardInput((e.type == SDL_KEYUP) ? 1 : 0, (char)e.key.keysym.sym);
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

		int now = SDL_GetTicks();
		auto execTime = (now - lastFrame);

		//limit framerate
		if(maxFps > 0)
		{
			double limit = 1000 / (double)maxFps;
			double wait = limit - execTime;
			if(wait > 0)
			{
				SDL_Delay(wait);
			}
		}

		now = SDL_GetTicks();
		delta = (now - lastFrame);
		lastFrame = now;
	}
}

void Engine::HandleInput()
{
	return;
}

void Engine::SetFlags()
{
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, (vsync) ? "1" : "0");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, (useBilinear) ? "1" : "0");
}

void Engine::UseBilinearScaling()
{
	useBilinear = true;
}
void Engine::UseNearestScaling()
{
	useBilinear = false;
}
void Engine::EnableVsync()
{
	vsync = true;
}
void Engine::DisableVsync()
{
	vsync = false;
}
void Engine::SetFrameLimit(uint limit)
{
	maxFps = limit;
}