#include "Texture.hpp"

Texture::Texture(string path, SDL_Renderer* renderer)
{
	ref = 0;
	tex = NULL;
	this->path = path;

	SDL_Surface* loadedImage = IMG_Load(path.c_str());
	if(!loadedImage)
	{
		cout << "SDL_Image failed to load " << path << ". Error: " << IMG_GetError() << endl;
		tex = NULL;
		ref = 0;
		this->path = "";
		return;
	}

	tex = SDL_CreateTextureFromSurface(renderer, loadedImage);
	if(!tex)
	{
		cout << "SDL_Image failed to create texture for image " << path << ". Error: " << IMG_GetError() << endl;
		SDL_FreeSurface(loadedImage);
		tex = NULL;
		ref = 0;
		this->path = "";
		return;
	}

	SDL_FreeSurface(loadedImage);
}

Texture::~Texture()
{
	SDL_DestroyTexture(tex);
	tex = NULL;
}

void Texture::RefInc()
{
	ref++;
}

void Texture::RefDec()
{
	if(ref > 0)
	{
		ref--;
	}
}

uint Texture::GetRef()
{
	return ref;
}

SDL_Texture* Texture::Get()
{
	return tex;
}