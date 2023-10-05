#include "ParCe.h"



// Initialization helper functions for testing
void InitializeLights(std::vector<Light*> &lights)
{
	//Lights================================================================
	Light *light1 = new Light();
	light1->SetPosition(10.0f, 10.0f, 0.0f);
	lights.push_back(light1);	

	Light *light2 = new Light();
	light2->SetPosition(-10.0f, 10.0f, 0.0f);
	lights.push_back(light2);	
}

void InitializeTestObjects(World *worldSpace, std::vector<EmptyObject*> &objects)
{
    std::string obj =   "./Graphics/Models/Armchair.obj";
    const std::string obj2 =   "./Graphics/Models/squab.obj";
    const std::string obj3 =   "./Graphics/Models/crag.obj";

	//Model------------------------------------------
	EmptyObject *model = new Model(worldSpace);
	static_cast<Model*>(model)->Load(obj2);

	EmptyObject *amodel = new assModel(worldSpace);
	static_cast<assModel*>(amodel)->loadModel(obj3);

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
}

void InitializeSingleBox(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	EmptyObject *cube = new Cube(worldSpace);
	cube->GetTransform().SetScale(1.0f, 1.0f, 1.0f);
	cube->GetTransform().SetPosition(5.0f, 0.0f, 0.0f);
	objects.push_back(cube);
}

void InitializeSphere(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	// EmptyObject *sphere = new Sphere(worldSpace);
	// sphere->GetTransform().SetScale(2.0f, 2.0f, 2.0f);
	// sphere->GetTransform().SetPosition(0.0f, 10.0f, 0.0f);
	// objects.push_back(sphere);

	std::string obj =  "./Graphics/Models/sphere.obj";

	//Model------------------------------------------
	EmptyObject *sphere = new assModel(worldSpace);
	static_cast<assModel*>(sphere)->loadModel(obj);
	sphere->GetTransform().SetScale(1.0f, 1.0f, 1.0f);

	objects.push_back(sphere);
}


Parce* Parce::Instance()
{
	static Parce* parce = new Parce;
	
	return parce;
}

Parce::Parce()
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


Parce::~Parce()
{
	std::cout << "Destructor called" << std::endl;
}

void Parce::RenderConsoleWindow()
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

void Parce::RenderPropertiesWindow()
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

	if (objects.size() > 1)
	{
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
	}




	ImGui::End();
}

void Parce::ProcessInput()
{
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

	if (IsMouseColliding)
	{
		if (Input::Instance()->IsKeyPressed())
		{
			if (Input::Instance()->IsLeftButtonClicked())
			{
				if (Input::Instance()->GetKeyDown() == SDLK_SPACE)
				{
					// Modify World
					auto rotationWorld = worldSpace->GetTransform().GetRotation();
					rotationWorld.x += Input::Instance()->GetMouseMotionY();
					rotationWorld.y += Input::Instance()->GetMouseMotionX();
					worldSpace->GetTransform().SetRotation(rotationWorld.x, rotationWorld.y, rotationWorld.z);
				} 
			}
		}
	}

}

void Parce::ImGuiUI()
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


void Parce::Initialize()
{
	if(!Screen::Instance()->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return;
	}

	worldSpace = new World();
		
	//Shader-----------------------------------------
	std::string LightVert =  "./Graphics/Shaders/Light.vert";
    std::string LightFrag =  "./Graphics/Shaders/Light.frag";
	lightShader.Create(LightVert, LightFrag);
	lightShader.Use();

	// Perspective reference Grid
	perspectiveGrid = new PerspectiveGrid(worldSpace);

	// Objects and lights
	InitializeLights(lights);

	// InitializeTestObjects(worldSpace, objects, lights);
	// InitializeSingleBox(worldSpace, objects);
	InitializeSphere(worldSpace, objects);

	// Initialize physics objects
	particles.reserve(objects.size());
	rbds.reserve(objects.size());

	PParticle *particle = new PParticle(5.0f, 5.0f, 0.0f);
	particles.push_back(particle);

	// Temporary creating an RBDObject per object
	for (auto obj: objects)
	{
		pRBDObject *rbd = new pRBDObject(static_cast<assModel*>(obj), pVec3(-1.0f, -3.0f, 0.0f));
		rbds.push_back(rbd);
	}
	

	//Camera---------------------------------
	camera = new PCamera(glm::vec3(0.0f, 3.0f, 20.0f));	
	camera->SetSpeed(0.01f);
	camera->SetFov(45.0f);
	camera->Projection();
	camera->SetViewport(0, CONSOLE_HEIGHT, SCREEN_WIDTH - PROPERTIES_WIDTH, SCREEN_HEIGHT - CONSOLE_HEIGHT);
}

void Parce::Update()
{
	// Timer stuff
	Timer::Instance()->Tick();
	dt = Timer::Instance()->GetDeltaTime();
	elapsedTime += dt;	

	// INPUT UPDATE
	Input::Instance()->Update();

	// PROCESS INPUT
	ProcessInput();


	mouseCollider = {Input::Instance()->GetMousePositionX(), Input::Instance()->GetMousePositionY(), 1,	1};

	IsMouseColliding = SDL_HasIntersection(&mouseCollider, &sceneCollider);

	isAppRunning = !Input::Instance()->IsXClicked();
	
}

void Parce::Render()
{
	Screen::Instance()->ClearScreen();

	// RENDER GRID
	perspectiveGrid->Render(lightShader);	
	
	// RENDER CAMERA
	camera->SendToShader(lightShader);	

	// RENDER LIGHTS
	for (auto &light: lights)
	{
		light->Render(lightShader);
		light->SendToShader(lightShader);
	}

	// RENDER OBJECTS
	unsigned int counter = 0;
	for (auto &obj: objects)
	{
		float x = particles[counter]->GetPosition().GetX();
		float y = particles[counter]->GetPosition().GetY();
		float z = particles[counter]->GetPosition().GetZ();
		obj->GetTransform().SetPosition(x, y, z);
		obj->Render(lightShader);
		counter++;
	}

	// // Iterating through RBD Objects and rendering them
	// for (auto &rbd_: rbds)
	// {
	// 	float x = rbd_->GetPosition().GetX();
	// 	float y = rbd_->GetPosition().GetY();
	// 	float z = rbd_->GetPosition().GetZ();
	// 	rbd_->GetObject()->GetTransform().SetPosition(x, y, z);
	// 	rbd_->GetObject()->Render(lightShader);
	// }

	perspectiveGrid->Render(lightShader);


	this->ImGuiUI();

	Screen::Instance()->Present();
}



void Parce::Destroy()
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

	for (auto partic: particles)
	{
		delete(partic);
	}

	delete(worldSpace);
	delete(camera);
	Screen::Instance()->Shutdown();		
}

bool Parce::IsRunning()
{
    return isAppRunning;
}
