#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../vendors/glad/glad.h"

#include "../vendors/imgui/imgui.h"
#include "../vendors/imgui/backends/imgui_impl_opengl3.h"
#include "../vendors/imgui/backends/imgui_impl_sdl2.h"

class Screen
{

public:

	static Screen* Instance();

	bool Initialize(GLint resx, GLint resy);
	void ClearScreen();
	void Present();
	void Shutdown();
	GLint GetX();
	GLint GetY();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

	GLint windowX;
	GLint windowY;

	SDL_Window* window;
	SDL_GLContext context;

};