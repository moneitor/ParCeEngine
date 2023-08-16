#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Entity/PerspectiveGrid.h"
#include "Entity/Camera.h"
#include "Entity/Model.h"
#include "Entity/World.h"
#include "Entity/Light.h"
#include "Entity/Quad.h"
#include "Entity/Cube.h"     
#include "Entity/Grid.h"
#include "Screen.h"
#include "Input.h"
#include "Shader.h"
#include "Utilities/Timer.h"
#include "Entity/assModel.h"

#include "../vendors/glad/glad.h"

#include "../vendors/imgui/imgui.h"
#include "../vendors/imgui/backends/imgui_impl_opengl3.h"
#include "../vendors/imgui/backends/imgui_impl_sdl2.h"

#include <deque>


// Objects -------------------------------------
std::vector<EmptyObject*> objects;
std::deque<std::string> messages;


const GLfloat CAMERA_SPEED = 0.02f;

const GLint SCREEN_WIDTH = 1280;
const GLint SCREEN_HEIGHT = 720;
const GLint CONSOLE_HEIGHT = SCREEN_HEIGHT * 0.4;
const GLint PROPERTIES_WIDTH = SCREEN_WIDTH * 0.4;

GLfloat dt = 0.0f;
GLfloat elapsedTime = 0.0f;

std::string LightVert =  "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Shaders/Light.vert";
std::string LightFrag =  "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Shaders/Light.frag";
std::string DefaultVert =  "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Shaders/Default.vert";
std::string DefaultFrag =  "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Shaders/Default.frag";
std::string obj =   "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Models/Armchair.obj";
const std::string obj2 =   "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Models/Armchair.obj";


SDL_Rect mouseCollider = {0};
SDL_Rect sceneCollider = {
	0,
	0,
	SCREEN_WIDTH - PROPERTIES_WIDTH,
	SCREEN_HEIGHT - CONSOLE_HEIGHT
};


void RenderConsoleWindow()
{
	ImGui::StyleColorsDark();
	// ImGui::Begin("Console", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize  );
	ImGui::Begin("Console", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
								     ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
									 ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

	auto windowPos = ImVec2(0, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.3));
	auto WindowSize = ImVec2(SCREEN_WIDTH - PROPERTIES_WIDTH, CONSOLE_HEIGHT);

	ImGui::SetWindowPos("Console", windowPos);
	ImGui::SetWindowSize("Console", WindowSize);

	auto message = Utility::ReadMessage();
	if(!message.empty())
	{
		messages.push_back(message);
	} 

	for (const auto &message : messages)
	{
		ImGui::Text("%s", message.c_str());
	}


	ImGui::End();
}

void RenderPropertiesWindow()
{
	// ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
								     ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
									 ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

	auto windowPos = ImVec2(SCREEN_WIDTH - PROPERTIES_WIDTH, 0);
	auto WindowSize = ImVec2(SCREEN_WIDTH - PROPERTIES_WIDTH, SCREEN_HEIGHT + CONSOLE_HEIGHT);

	ImGui::SetWindowPos("Properties", windowPos);
	ImGui::SetWindowSize("Properties", WindowSize);


	ImVec4 geoColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGui::ColorEdit3("clear color", (float*)&geoColor);
	ImGui::Separator();
	ImGui::Spacing();

	
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Button("Run Simulation");

	ImGui::Separator();

	auto color = objects[0]->GetColor();
	ImGui::ColorEdit4("Color", (float*)&color);
	objects[0]->SetColor(color);

	auto position = objects[0]->GetTransform().GetPosition();
	ImGui::SliderFloat3("Position", &position.x, -10.0f, 10.0f, "%.4f");
	objects[0]->GetTransform().SetPosition(position.x, position.y, position.z);

	auto rotation = objects[0]->GetTransform().GetRotation();
	ImGui::SliderFloat3("Rotation", &rotation.x, -360.0f, 360.0f, "%.4f");
	objects[0]->GetTransform().SetRotation(rotation.x, rotation.y, rotation.z);

	auto scale = objects[0]->GetTransform().GetScale();
	ImGui::SliderFloat3("Scale", &scale.x, 0.001f, 20.0f, "%.4f");
	objects[0]->GetTransform().SetScale(scale.x, scale.y, scale.z);

	ImGui::End();
}


bool isAppRunning = true;

int main(int argc, char* argv[])
{	

	if(!Screen::Instance()->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return 1;
	}
	GLint windowX = Screen::Instance()->GetX();
	GLint windowY = Screen::Instance()->GetY();

	World worldSpace;
		
	//Shader-----------------------------------------
	Shader lightShader, defaultShader;
	lightShader.Create(LightVert, LightFrag);
	lightShader.Use();

	// Perspective reference Grid
	EmptyObject *perspectiveGrid = new PerspectiveGrid(&worldSpace);

	//Model------------------------------------------
	EmptyObject *model = new Model(&worldSpace);
	static_cast<Model*>(model)->Load(obj);

	assModel amodel = assModel(obj2);

	//Cube-------------------------------------------
	EmptyObject *cube = new Cube(&worldSpace);


	EmptyObject *cube2 = new Cube(&worldSpace);


	//Quad ----------------------------------
	EmptyObject *quad = new Quad(&worldSpace);
	quad->GetTransform().SetRotation(-90.0f, 0.0f, 0.0f);
	quad->GetTransform().SetScale(20.5f, 20.5f, 20.5f);
	quad->GetTransform().SetPosition(0.0f, -10.0f, 0.0f);

	

	objects.push_back(cube);
	objects.push_back(cube2);
	objects.push_back(quad);
	objects.push_back(model);

	//Camera---------------------------------
	Camera camera(glm::vec3(0.0f, 3.0f, 20.0f));	
	camera.SetSpeed(0.01f);
	camera.SetFov(45.0f);
	camera.Projection();
	camera.SetViewport(0, 
					   CONSOLE_HEIGHT, 
					   SCREEN_WIDTH - PROPERTIES_WIDTH,
					   SCREEN_HEIGHT - CONSOLE_HEIGHT);


	//Lights---------------------------------
	Light light;

	//================================================================

	while (isAppRunning)
	{
		// Timer stuff
		Timer::Instance()->Tick();
		dt = Timer::Instance()->GetDeltaTime();
		elapsedTime += dt;

		Screen::Instance()->ClearScreen();

		Input::Instance()->Update();

		mouseCollider = {
			Input::Instance()->GetMousePositionX(),
			Input::Instance()->GetMousePositionY(),
			1,
			1
		};

		bool isMouseColliding = SDL_HasIntersection(&mouseCollider, &sceneCollider);

		perspectiveGrid->Render(lightShader);

		if(Input::Instance()->IsKeyPressed())
		{
			switch (Input::Instance()->GetKeyDown())
			{
				case 'w':
					camera.MoveForward(CAMERA_SPEED);
					break;
				case 's':
					camera.MoveBackward(CAMERA_SPEED);
					break;
				case 'a':
					camera.MoveLeft(CAMERA_SPEED);
					break;
				case 'd':
					camera.MoveRight(CAMERA_SPEED);
					break;
				case 'q':
					camera.MoveDown(CAMERA_SPEED);
					break;
				case 'e':
					camera.MoveUp(CAMERA_SPEED);
					break;
			}
		}

		if(Input::Instance()->GetMouseWheel() > 0)
		{
			camera.MoveBackward(CAMERA_SPEED * 50);
		} 

		if(Input::Instance()->GetMouseWheel() < 0)
		{
			camera.MoveForward(CAMERA_SPEED * 50);
		} 


		if (isMouseColliding)
		{
			if (Input::Instance()->IsKeyPressed())
			{
				if (Input::Instance()->GetKeyDown() == 'c')
				{
					// Modify World
					auto rotationWorld = worldSpace.GetTransform().GetRotation();
					rotationWorld.x += Input::Instance()->GetMouseMotionY();
					rotationWorld.y += Input::Instance()->GetMouseMotionX();
					worldSpace.GetTransform().SetRotation(rotationWorld.x, rotationWorld.y, rotationWorld.z);
				} 
			}
		}

		isAppRunning = !Input::Instance()->IsXClicked();

		camera.SendToShader(lightShader);

		light.Render(lightShader);
		light.SendToShader(lightShader);


		for (auto &obj: objects)
		{
			obj->Render(lightShader);
		}

		// amodel.Render(lightShader);

		// glm::vec3 offset = glm::vec3(0.0f, 0.0f, 10.0f);		
		// objects[0]->GetTransform().SetRotation(0.0f, 45.0f, 0.0f);
		// objects[0]->GetTransform().SetPosition(glm::sin(elapsedTime * 0.1), offset.y, offset.z);


		// glm::mat4 ident = glm::mat4(1.0f);
		// glm::vec3 axis = glm::normalize(glm::vec3(0.0f, 1.0, 0.0f));
		// ident = glm::rotate(ident, glm::radians(glm::sin(elapsedTime * 0.1f)) * 45, axis);
		// ident = glm::translate(ident, glm::vec3(0.0f, glm::sin(elapsedTime * 0.1), 0.0f));
		// objects[3]->GetTransform().SetTransform(ident);

		// IMGUI Stuff
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		RenderConsoleWindow();
		RenderPropertiesWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		Screen::Instance()->Present();
		// std::cout << dt << std::endl;

	}

	lightShader.Destroy();	

	Screen::Instance()->Shutdown();	
	

	return 0;
}