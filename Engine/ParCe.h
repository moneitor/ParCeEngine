#pragma once

#include "Physics/Maths/Core.h"

#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Graphics/Entity/PerspectiveGrid.h"
#include "Graphics/Entity/PCamera.h"
#include "Graphics/Entity/Model.h"
#include "Graphics/Entity/World.h"
#include "Graphics/Entity/Light.h"
#include "Graphics/Entity/Quad.h"
#include "Graphics/Entity/Cube.h"     
#include "Graphics/Entity/Sphere.h"     
#include "Graphics/Screen.h"
#include "Graphics/Input.h"
#include "Graphics/Shader.h"
#include "Physics/Utilities/Timer.h"
#include "Graphics/Entity/AssModel.h" 

#include "../vendors/glad/glad.h"

#include "Physics/Maths/PVec.h"
#include "Physics/Maths/PVec2.h"
#include "Physics/Maths/PVec3.h"
#include "Physics/Maths/PMat3.h"
#include "Physics/Maths/PMat4.h"
#include "Physics/Maths/PQuat.h"

#include "Physics/PParticle.h"
#include "Physics/PRBDBody.h"
#include "Physics/Forces/PForces.h"

#include "vendors/imgui/imgui.h"
#include "vendors/imgui/backends/imgui_impl_opengl3.h"
#include "vendors/imgui/backends/imgui_impl_sdl2.h"

#include <deque>



class Parce
{
private:
    Parce();
	Parce& operator=(const Parce&) = delete;

    std::deque<std::string> messages;
    std::vector<EmptyObject*> objects;
    std::vector<Light*> lights;

    std::vector<PParticle*> particles;
    std::vector<pRBDShape*> shapes;
    std::vector<pRBDBody*> rbds;
    std::vector<pForce*> forces;
    std::vector<pForce*> springs;

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

    bool isMouseColliding;
    bool isGridDisplay;
    bool keyAlreadyPressed;

    bool runSim;

    Shader lightShader;
    World *worldSpace;
    PCamera *camera;



public:
    Parce(const Parce&) = delete;
    static Parce* Instance();
    ~Parce();

    void RenderConsoleWindow();
    void RenderPropertiesWindow();
    void ProcessInput();
    void ImGuiUI();
    void Initialize();
    void Update();
    void Render();
    void Destroy();
    bool IsRunning();
};