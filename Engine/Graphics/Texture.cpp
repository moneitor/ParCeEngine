#include <iostream>
#include <SDL2/SDL_image.h>
#include "Texture.h"

Texture::Texture()
	:m_ID{0}
{
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

bool Texture::Load(const std::string& filename)
{

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG; 

	if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
		Utility::AddMessage("SDL_image could not initialize! SDL_image Error: " + static_cast<std::string>(IMG_GetError()));
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
    }

	SDL_Surface* textureData = IMG_Load(filename.c_str());

	if (!textureData)
	{
		Utility::AddMessage("SDL Error internal: " + static_cast<std::string>(IMG_GetError()));
		std::cout << "SDL Error internal: " << IMG_GetError() << std::endl;
		std::cout << "Trying to load file: " << filename  << std::endl;
		std::cout << "Error loading texture." << std::endl;
		return 0;
	}

	GLsizei width = textureData->w;
	GLsizei height = textureData->h;
	Uint8* pixels = (Uint8*)textureData->pixels;
	Uint8 depth = textureData->format->BytesPerPixel;
	GLint format = ((depth == 4) ? GL_RGBA : GL_RGB);

	glGenTextures(1, &m_ID);

	glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(textureData);

	return true;

}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Unload()
{
	glDeleteTextures(1, &m_ID);
}