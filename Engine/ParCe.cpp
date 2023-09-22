#include "ParCe.h"

ParCe* ParCe::Instance()
{
	static ParCe* parce = new ParCe;
	
	return parce;
}

ParCe::ParCe()
	:isAppRunning{true},
	CAMERA_SPEED{0.02f},
	SCREEN_WIDTH{1280},
	SCREEN_HEIGHT{720},
	dt{0.0f},
	elapsedTime{0.0f},
	mouseCollider{0}
{
	this->CONSOLE_HEIGHT = (float)SCREEN_HEIGHT * 0.4f;
	this->PROPERTIES_WIDTH = (float)SCREEN_WIDTH * 0.4f;

    sceneCollider = {0, 0, SCREEN_WIDTH - PROPERTIES_WIDTH, SCREEN_HEIGHT - CONSOLE_HEIGHT};
}

ParCe::~ParCe()
{
	std::cout << "Destructor called" << std::endl;
}

void ParCe::RenderConsoleWindow()
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


void ParCe::RenderPropertiesWindow()
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


void ParCe::ImGuiUI()
{
	// IMGUI Stuff
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	RenderConsoleWindow();
	RenderPropertiesWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ParCe::Initialize()
{
    std::string LightVert =  "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Shaders/Light.vert";
    std::string LightFrag =  "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Shaders/Light.frag";
    std::string DefaultVert =  "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Shaders/Default.vert";
    std::string DefaultFrag =  "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Shaders/Default.frag";
    std::string obj =   "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Models/Armchair.obj";
    const std::string obj2 =   "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Models/squab.obj";
    const std::string obj3 =   "/Users/hernan/Documents/learn/ParCePhysics/Engine/Graphics/Models/crag.obj";
	

	if(!Screen::Instance()->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return;
	}

	worldSpace = new World();
		
	//Shader-----------------------------------------
	lightShader.Create(LightVert, LightFrag);
	lightShader.Use();

	// Perspective reference Grid
	perspectiveGrid = new PerspectiveGrid(worldSpace);

	//Model------------------------------------------
	EmptyObject *model = new Model(worldSpace);
	static_cast<Model*>(model)->Load(obj2);

	EmptyObject *amodel = new assModel(worldSpace);
	static_cast<assModel*>(amodel)->loadModel(obj3);

	//Cube-------------------------------------------
	EmptyObject *cube = new Cube(worldSpace);
	cube->GetTransform().SetScale(2.5f, 1.5f, 1.5f);
	cube->GetTransform().SetPosition(-10.0f, 0.0f, 0.0f);


	EmptyObject *cube2 = new Cube(worldSpace);
	cube2->GetTransform().SetScale(2.5f, 1.5f, 1.5f);
	cube2->GetTransform().SetPosition(10.0f, 0.0f, 0.0f);


	//Quad ----------------------------------
	EmptyObject *quad = new Quad(worldSpace);
	quad->GetTransform().SetRotation(-90.0f, 0.0f, 0.0f);
	quad->GetTransform().SetScale(20.5f, 20.5f, 20.5f);
	quad->GetTransform().SetPosition(0.0f, -10.0f, 0.0f);	

	objects.push_back(amodel);
	objects.push_back(model);
	objects.push_back(cube);
	objects.push_back(cube2);
	objects.push_back(quad);

	//Camera---------------------------------
	camera = new Camera(glm::vec3(0.0f, 3.0f, 20.0f));	
	camera->SetSpeed(0.01f);
	camera->SetFov(45.0f);
	camera->Projection();
	camera->SetViewport(0, CONSOLE_HEIGHT, SCREEN_WIDTH - PROPERTIES_WIDTH, SCREEN_HEIGHT - CONSOLE_HEIGHT);

	//Lights================================================================

	Light *light1 = new Light();
	light1->SetPosition(10.0f, 10.0f, 0.0f);
	lights.push_back(light1);	

	Light *light2 = new Light();
	light2->SetPosition(-10.0f, 10.0f, 0.0f);
	lights.push_back(light2);	
}

void ParCe::Update()
{
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
					camera->MoveForward(CAMERA_SPEED);
					break;
				case 's':
					camera->MoveBackward(CAMERA_SPEED);
					break;
				case 'a':
					camera->MoveLeft(CAMERA_SPEED);
					break;
				case 'd':
					camera->MoveRight(CAMERA_SPEED);
					break;
				case 'q':
					camera->MoveDown(CAMERA_SPEED);
					break;
				case 'e':
					camera->MoveUp(CAMERA_SPEED);
					break;
			}
		}

		if(Input::Instance()->GetMouseWheel() > 0)
		{
			camera->MoveBackward(CAMERA_SPEED * 50);
		} 

		if(Input::Instance()->GetMouseWheel() < 0)
		{
			camera->MoveForward(CAMERA_SPEED * 50);
		} 


		if (isMouseColliding)
		{
			if (Input::Instance()->IsKeyPressed())
			{
				if (Input::Instance()->GetKeyDown() == 'c')
				{
					// Modify World
					auto rotationWorld = worldSpace->GetTransform().GetRotation();
					rotationWorld.x += Input::Instance()->GetMouseMotionY();
					rotationWorld.y += Input::Instance()->GetMouseMotionX();
					worldSpace->GetTransform().SetRotation(rotationWorld.x, rotationWorld.y, rotationWorld.z);
				} 
			}
		}

		isAppRunning = !Input::Instance()->IsXClicked();

		camera->SendToShader(lightShader);
		// Light light;
		// light.Render(lightShader);
		// light.SendToShader(lightShader);

		for (auto &light: lights)
		{
			light->Render(lightShader);
			light->SendToShader(lightShader);
		}

		for (auto &obj: objects)
		{
			obj->Render(lightShader);
		}


		this->ImGuiUI();

		Screen::Instance()->Present();
	}
}



void ParCe::Destroy()
{
	lightShader.Destroy();	

	for (auto light: lights)
	{
		delete(light);
	}

	for (auto object: objects)
	{
		delete(object);
	}

	Screen::Instance()->Shutdown();		
}



int main(int argc, char* argv[])
{
	ParCe::Instance()->Initialize();
	ParCe::Instance()->Update();
	ParCe::Instance()->Destroy();
	return 0;
}