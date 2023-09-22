#pragma once

#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Graphics/Entity/PerspectiveGrid.h"
#include "Graphics/Entity/Camera.h"
#include "Graphics/Entity/Model.h"
#include "Graphics/Entity/World.h"
#include "Graphics/Entity/Light.h"
#include "Graphics/Entity/Quad.h"
#include "Graphics/Entity/Cube.h"     
#include "Graphics/Screen.h"
#include "Graphics/Input.h"
#include "Graphics/Shader.h"
#include "Graphics/Utilities/Timer.h"
#include "Graphics/Entity/AssModel.h" 

#include "../vendors/glad/glad.h"

#include "vendors/imgui/imgui.h"
#include "vendors/imgui/backends/imgui_impl_opengl3.h"
#include "vendors/imgui/backends/imgui_impl_sdl2.h"

#include <deque>



class ParCe
{
private:
    ParCe();
	ParCe(const ParCe&);
	ParCe& operator=(const ParCe&);

    std::vector<EmptyObject*> objects;
    std::deque<std::string> messages;
    std::vector<Light*> lights;
    bool isAppRunning;

    GLfloat CAMERA_SPEED;

    GLint SCREEN_WIDTH;
    GLint SCREEN_HEIGHT;
    GLint CONSOLE_HEIGHT;
    GLint PROPERTIES_WIDTH ;   

    float dt;
    float elapsedTime;

    SDL_Rect mouseCollider;
    SDL_Rect sceneCollider;

    EmptyObject *perspectiveGrid;

    Shader lightShader;
    World *worldSpace;
    Camera *camera;



public:

    static ParCe* Instance();
    ~ParCe();

    void RenderConsoleWindow();
    void RenderPropertiesWindow();
    void ImGuiUI();
    void Initialize();
    void Update();
    void Destroy();
};