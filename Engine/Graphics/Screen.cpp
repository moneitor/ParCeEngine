
#include "Screen.h"


Screen* Screen::Instance()
{
	static Screen* screen = new Screen;
	
	return screen;
}

Screen::Screen()
	:window{nullptr}, context{nullptr}
{
	SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "1");
}

bool Screen::Initialize(GLint resx, GLint resy)
{
	SDL_setenv("SDL_VIDEO_HIGHDPI_DISABLED", "1", 1);

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Error initializing SDL" << std::endl;
		return false;
	}

	int imgFlags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted=IMG_Init(imgFlags);


	if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	window = SDL_CreateWindow("ParCe",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  resx, resy,
							  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
							  );

	if (!window)
	{
		std::cout << "Error creating SDL window" << std::endl;
		return false;
	}

	windowX = 0;
	windowY = 0;

	SDL_GL_GetDrawableSize(window, &windowX, &windowY);	

	Utility::AddMessage("Screen Size: " + std::to_string(windowX) + " x " + std::to_string(windowY));

	context = SDL_GL_CreateContext(window);

	SDL_GL_MakeCurrent(window, context);

	if (!context)
	{
		std::cout << "Error creating OpenGL context." << std::endl;
		return false;
	}

	if (!gladLoadGL())
	{
		std::cout << "Error loading extensions!" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplSDL2_InitForOpenGL(window, context);

	return true;
}

void Screen::ClearScreen()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::Present()
{
	SDL_GL_SwapWindow(window);
}

void Screen::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

GLint Screen::GetX()
{
    return windowX;
}

GLint Screen::GetY()
{
    return windowY;
}
