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
	scenes = vector<unique_ptr<Scene>>();
	textures = vector<unique_ptr<Texture>>();

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
	//Search for existing textures
	for(auto i = 0; i < textures.size(); i++)
	{
		Texture* cur = textures[i].get();
		if(cur->GetPath() == path)
		{
			return cur;
		}
	}

	//Create a new texture if an existing one isn't found
	textures.push_back(make_unique<Texture>(path, renderer));
	return textures.back().get();
}

void Engine::RegisterQuitEventCallback(QuitEventCallback func)
{
	if(!func)
	{
		return;
	}

	OnQuitEvent = func;
}
void Engine::ClearQuitEventCallback()
{
	OnQuitEvent = NULL;
}

void Engine::RegisterKeyboardCallback(KeyboardEventCallback func)
{
	if(!func)
	{
		return;
	}

	OnKeyboardInput = func;
}
void Engine::ClearKeyboardCallback()
{
	OnKeyboardInput = NULL;
}

void Engine::RegisterMouseMoveCallback(MouseMoveCallback func)
{
	if(!func)
	{
		return;
	}

	OnMouseMove = func;
}
void Engine::ClearMouseMoveCallback()
{
	OnMouseMove = NULL;
}

void Engine::RegisterMouseClickCallback(MouseClickCallback func)
{
	if(!func)
	{
		return;
	}

	OnMouseClick = func;
}
void Engine::ClearMouseClickCallback()
{
	OnMouseClick = NULL;
}

void Engine::RegisterMousewheelCallback(MouseWheelCallback func)
{
	if(!func)
	{
		return;
	}

	OnMouseWheel = func;
}
void Engine::ClearMousewheelCallback()
{
	OnMouseWheel = NULL;
}

void Engine::RegisterWindowResizeCallback(WindowResizeCallback func)
{
	if(!func)
	{
		return;
	}

	OnWindowResize = func;
}
void Engine::ClearWindowResizeCallback()
{
	OnWindowResize = NULL;
}

void Engine::RegisterWindowFocusCallback(WindowFocusCallback func)
{
	if(!func)
	{
		return;
	}

	OnWindowFocus = func;
}
void Engine::ClearWindowFocusCallback()
{
	OnWindowFocus = NULL;
}

void Engine::RegisterWindowUnfocusCallback(WindowUnfocusCallback func)
{
	if(!func)
	{
		return;
	}

	OnWindowUnfocus = func;
}
void Engine::ClearWindowUnfocusCallback()
{
	OnWindowUnfocus = NULL;
}

Scene* Engine::CreateScene(string name)
{
	scenes.push_back(make_unique<Scene>(name, this));
	scene = scenes.back().get();
	return scene;
}

Scene* Engine::GetScene(string name)
{
	//Search for an existing scene
	for(auto i = 0; i < scenes.size(); i++)
	{
		auto cur = scenes[i].get();
		if(cur->GetName() == name)
		{
			return cur;
		}
	}

	//Return NULL to signify scene does not exist
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
	//Get index of scene
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

	//Delete scene
	if(index > -1)
	{
		scenes.erase(scenes.begin() + index);
	}
}

string Engine::GetSceneList()
{
	//Go through each scene one by one
	string to_return = "";
	for(auto i = 0; i < scenes.size(); i++)
	{
		//Append the scene's name to our string
		auto cur = scenes[i].get();
		to_return += cur->GetName();

		//Append a , to that, unless it is the last element
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

void Engine::RenderCurrent()
{
	//Clear the existing screen by filling it with background color
	SDL_RenderClear(renderer);

	if(scene)
	{
		//Iterate through the list of objects in our scene
		auto objects = scene->GetObjectList();
		for(auto i = 0; i < objects->size(); i++)
		{
			//Construct an SDL_Rect for the object based on position and size
			auto cur = objects->at(i).get();
			SDL_Rect pos
			{
				.x = (int)cur->GetXPosition(),
				.y = (int)cur->GetYPosition(),
				.w = cur->GetWidth(),
				.h = cur->GetHeight()
			};

			//Render to the screen
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
					if(OnQuitEvent)
					{
						OnQuitEvent();
					}
					break;

				//Keyboard input
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					if(OnKeyboardInput)
					{
						OnKeyboardInput((e.type == SDL_KEYUP) ? 1 : 0, (char)e.key.keysym.sym);
					}
				break;

			}
		}

		//Perform logic step for every object
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
	//Theoretically this for loop is fine. it will check the size every time since it is using textures.size()
	for(auto i = 0; i < textures.size(); i++)
	{
		Texture* cur = textures[i].get();

		//Delete texture if it is no longer referenced
		if(cur->GetRef() == 0)
		{
			textures.erase(textures.begin() + i);

			//Check the same index again, since we have deleted the texture at this index
			i--;
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