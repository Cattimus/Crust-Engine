#include "Texture.hpp"

Texture::Texture(string path, SDL_Renderer* renderer)
{
	//Initialize values
	ref = 0;
	tex = NULL;
	offset[0] = 0;
	offset[1] = 0;
	size[0] = 0;
	size[1] = 0;
	this->path = path;

	//Load image to surface
	SDL_Surface* loadedImage = IMG_Load(path.c_str());
	if(!loadedImage)
	{
		cout << "SDL_Image failed to load " << path << ". Error: " << IMG_GetError() << endl;
		tex = NULL;
		ref = 0;
		this->path = "";
		return;
	}

	//Load texture object
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

	//Set size parameters
	size[0] = loadedImage->w;
	size[1] = loadedImage->h;

	//Free up unused memory
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

string Texture::GetPath()
{
	return path;
}

int Texture::GetWidth()
{
	return size[0];
}

int Texture::GetHeight()
{
	return size[1];
}

int Texture::GetXOffset() 
{
	return offset[0];
}
int Texture::GetYOffset()
{
	return offset[1];
}