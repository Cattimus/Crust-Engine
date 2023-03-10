#include "Engine.hpp"

Engine::Engine()
{
	windowHeight = 720;
	windowWidth = 1280;
	windowResizable = true;
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

	//Keyboard input event
	events.RegisterEvent(Event<Engine>(this, "KeyboardInput", [](auto p){return false;}, NULL));
}

Engine::~Engine()
{
	Quit();
}

void Engine::Init()
{
	//initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL failed to initialize. Error: " << SDL_GetError() << endl;
		exit(-1);
	}

	//Initialize SDL_IMG with png, jpg, and webp support
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
	scenes = unordered_map<string, unique_ptr<Scene>>();
	textures = unordered_map<string, unique_ptr<Texture>>();

	//These steps are unecessary but it is good practice
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

//initialize SDL and create a window
void Engine::CreateWindow(string title, int x, int y, int w, int h, bool resizable)
{
	Init();

	//Initialize a new window. Shown is always active, resizable is optional
	uint flags = SDL_WINDOW_SHOWN;
	if(resizable)
	{
		flags |= SDL_WINDOW_RESIZABLE;
	}
	else
	{
		windowResizable = false;
	}

	//If x and y are not defined, we pass SDL_WINDOWPOS_UNDEFINED for a random location
	if(x < 1)
	{
		x = SDL_WINDOWPOS_UNDEFINED;
	}
	if(y < 1)
	{
		y = SDL_WINDOWPOS_UNDEFINED;
	}

	//Set the width and height
	if(w < 1 || h < 1)
	{
		w = windowWidth;
		h = windowHeight;
	}
	else
	{
		windowWidth = w;
		windowHeight = h;
	}

	//Set our configured flags
	SetFlags();
	window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	if(!window)
	{
		cout << "Window creation failed. Error: " << SDL_GetError() << endl;
		exit(-1);
	}

	//Create renderer from window
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
int Engine::GetWindowWidth()
{
	return windowWidth;
}
int Engine::GetWindowHeight()
{
	return windowHeight;
}
void Engine::SetWindowSize(int w, int h)
{
	if(!windowResizable)
	{
		return;
	}

	if(w > 0)
	{
		windowWidth = w;
	}
	if(h > 0)
	{
		windowHeight = h;
	}

	SDL_SetWindowSize(window, windowWidth, windowHeight);
}

Texture* Engine::GetTexture(string path)
{
	if(textures.find(path) != textures.end())
	{
		return textures[path].get();
	}

	//Create a new texture if an existing one isn't found
	return (textures[path] = make_unique<Texture>(path, renderer)).get();
}

Scene* Engine::CreateScene(string name)
{
	auto to_return = (scenes[name] = make_unique<Scene>(name, this)).get();
	scene = to_return;
	return to_return;
}

Scene* Engine::GetScene(string name)
{
	if(scenes.find(name) != scenes.end())
	{
		return scenes[name].get();
	}

	return NULL;
}

Scene* Engine::SwitchScene(string name)
{
	//Get scene from list
	auto cur = GetScene(name);

	//If scene exists, set the current scene to that
	if(cur)
	{
		scene = cur;
	}

	//If the scene does not exist, this will return null. if it does, it will return the scene
	return cur;
}

void Engine::DeleteScene(string name)
{
	if(scenes.find(name) != scenes.end())
	{
		scenes.erase(scenes.find(name));
	}
}

string Engine::GetSceneList()
{
	//Go through each scene one by one
	string to_return = "";
	for(auto &i : scenes)
	{
		//Append the scene's name to our string
		auto cur = i.second.get();
		to_return += cur->GetName();
		to_return += ",";
	}

	to_return.pop_back();
	return to_return;
}

void Engine::StartMainLoop()
{
	MainLoop();
}

void Engine::RenderCurrent()
{
	//Clear the existing screen by filling it with background color
	SDL_RenderClear(renderer);

	if(scene)
	{
		//Iterate through the list of objects in our scene
		auto objects = scene->GetObjectList();
		for(auto &i : *objects)
		{
			auto cur = i.second.get();

			//Construct an SDL_Rect for the object based on position and size
			SDL_Rect objPos
			{
				.x = (int)cur->GetXPosition(),
				.y = (int)cur->GetYPosition(),
				.w = cur->GetWidth(),
				.h = cur->GetHeight()
			};

			//calculate center of object
			SDL_Point center;
			center.x = objPos.w / 2 + cur->GetRotationOffsetX();
			center.y = objPos.h / 2 + cur->GetRotationOffsetY();

			//Render to the screen
			SDL_RenderCopyEx(renderer, cur->GetTexture(), NULL, &objPos, cur->GetRotation(), &center, SDL_FLIP_NONE);
		}
	}

	SDL_RenderPresent(renderer);
}

void Engine::MainLoop()
{
	bool running = true;
	SDL_Event e;

	//Time since the last frame was executed
	int lastFrame = SDL_GetTicks();

	while(running)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			switch(e.type)
			{
				//Quit out of the program
				case SDL_QUIT:
					running = false;
				break;

				//keyboard input
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					keyDown = e.key.state;
					lastKeycode = e.key.keysym.sym;
					keyRepeat = e.key.repeat;
					events.DoEvent("KeyboardInput");
				break;

			}
		}

		//Execute events
		events.CheckEvents();
		scene->CheckEvents();

		//render scene
		RenderCurrent();

		//See how long the scene took to render
		int now = SDL_GetTicks();
		auto execTime = (now - lastFrame);

		//Limit framerate (if required)
		if(maxFps > 0)
		{
			double limit = 1000 / (double)maxFps;
			double wait = limit - execTime;
			if(wait > 0)
			{
				SDL_Delay(wait);
			}
		}

		//Update delta time
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

void Engine::UseBilinearFiltering()
{
	useBilinear = true;
}
void Engine::UseNearestFiltering()
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

void Engine::TextureCleanup()
{
	for(auto &i : textures)
	{
		Texture* cur = i.second.get();

		//Delete texture if it is no longer referenced
		if(cur->GetRef() == 0)
		{
			textures.erase(textures.find(cur->GetPath()));
		}
	}
}

void Engine::EnableDelta()
{
	useDelta = true;
}

void Engine::DisableDelta()
{
	useDelta = false;
}

//TODO - this may need a rework
string Engine::GetReport()
{
	string toReturn = "";

	toReturn += "Textures[" + to_string(textures.size()) + "]\n\n";
	for(auto &i : scenes)
	{
		auto cur = i.second.get();

		int objects = cur->GetObjectList()->size();
		toReturn += cur->GetName() + ": " + "Objects[" + to_string(objects) + "]\n";
	}

	return toReturn;
}

EventHandler<Engine>* Engine::GetEventHandler()
{
	return &events;
}

uint32_t Engine::GetKeycode()
{
	return lastKeycode;
}

//Get key up/down status
bool Engine::KeyDown()
{
	return keyDown;
}

//Get key repeat status
bool Engine::KeyRepeat()
{
	return keyRepeat;
}