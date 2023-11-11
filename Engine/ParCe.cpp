#include "ParCe.h"


// DEMO INITIALIZATIONS

void CollideInsideBoxSpheres(pRBDBody *rbd_, int size_box)
{
	// float radius = rbd_->GetModel()->GetTransform().GetScale()[0] * 0.5;
	float radius = 0.0f;

	if (rbd_->GetShape()->GetShapeType() == pShapeType::SPHERE)
	{
		radius = static_cast<pRBDSphere*>(rbd_->GetShape())->GetRadius();
	}

	
	if(rbd_->Pos()[0] - radius <= -size_box)
		{
			rbd_->SetPosition(-size_box + radius, rbd_->Pos()[1], rbd_->Pos()[2]);
			rbd_->SetVelocity(rbd_->Vel()[0] * rbd_->Elasticity() * -1, rbd_->Vel()[1], rbd_->Vel()[2]);
		} else if (rbd_->Pos()[0] + radius >= size_box)
		{
			rbd_->SetPosition(size_box - radius, rbd_->Pos()[1], rbd_->Pos()[2]);
			rbd_->SetVelocity(rbd_->Vel()[0] * rbd_->Elasticity() * -1, rbd_->Vel()[1], rbd_->Vel()[2]);
		}

		if (rbd_->Pos()[1] - radius <= 0)
		{
			rbd_->SetPosition(rbd_->Pos()[0], radius, rbd_->Pos()[2]);
			rbd_->SetVelocity(rbd_->Vel()[0], rbd_->Vel()[1] * rbd_->Elasticity() * -1, rbd_->Vel()[2]);
		} else if (rbd_->Pos()[1] + radius >= size_box )
		{
			rbd_->SetPosition(rbd_->Pos()[0], size_box - radius, rbd_->Pos()[2]);
			rbd_->SetVelocity(rbd_->Vel()[0], rbd_->Vel()[1] * rbd_->Elasticity() * -1, rbd_->Vel()[2]);
		}

		if(rbd_->Pos()[2] - radius <= -size_box)
		{
			rbd_->SetPosition(rbd_->Pos()[0], rbd_->Pos()[1], -size_box + radius);
			rbd_->SetVelocity(rbd_->Vel()[0], rbd_->Vel()[1], rbd_->Vel()[2] * rbd_->Elasticity() * -1);
		} else if (rbd_->Pos()[0] + radius >= size_box)
		{
			rbd_->SetPosition(size_box - radius, rbd_->Pos()[1], rbd_->Pos()[2]);
			rbd_->SetVelocity(rbd_->Vel()[0], rbd_->Vel()[1], rbd_->Vel()[2] * rbd_->Elasticity() * -1);
		}		
}

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
	// cube->GetTransform().SetScale(1.0f, 1.0f, 1.0f);
	cube->GetTransform().SetPosition(3.0f, 0.0f, 0.0f);
	objects.push_back(cube);
}

void InitializeSphere(World *worldSpace, std::vector<EmptyObject*> &objects)
{

	// EmptyObject *sphere = new Sphere(worldSpace);
	// sphere->GetTransform().SetScale(1.0f, 1.0f, 1.0f);
	// objects.push_back(sphere);

	std::string obj =  "./Graphics/Models/sphere.obj";

	// //Model------------------------------------------s
	EmptyObject *sphere = new assModel(worldSpace, EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere)->loadModel(obj);
	sphere->GetTransform().SetPosition(0.0f, 8.0f, 0.0f);
	sphere->GetTransform().SetScale(5.0f);

	objects.push_back(sphere);
}

void InitializeSpheres(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	std::string obj =  "./Graphics/Models/sphere.obj";

	//Model------------------------------------------
	EmptyObject *sphere1 = new assModel(worldSpace,  EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere1)->loadModel(obj);
	sphere1->GetTransform().SetScale(4.0f);
	sphere1->GetTransform().SetPosition(1.0f, 5.0f, 1.0f);

	objects.push_back(sphere1);

	EmptyObject *sphere2 = new assModel(worldSpace,  EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere2)->loadModel(obj);
	sphere2->GetTransform().SetScale(2.0f);
	sphere2->GetTransform().SetPosition(-4.0f, 8.0f, -3.0f);

	objects.push_back(sphere2);

	EmptyObject *sphere3 = new assModel(worldSpace,  EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere3)->loadModel(obj);
	sphere3->GetTransform().SetScale(1.0f);
	sphere3->GetTransform().SetPosition(3.0f, 3.0f, 5.0f);

	objects.push_back(sphere3);

	EmptyObject *sphere4 = new assModel(worldSpace, EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere4)->loadModel(obj);
	sphere4->GetTransform().SetScale(3.0f);
	sphere4->GetTransform().SetPosition(2.0f, 9.0f, -6.0f);

	objects.push_back(sphere4);
}

void InitializeSpheresLine(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	std::string obj =  "./Graphics/Models/sphere.obj";

	//Model------------------------------------------

	for (int i = 0; i <= 20; i++)
	{
		EmptyObject *sphere = new assModel(worldSpace, EmptyObject::ObjectType::Sphere);
		static_cast<assModel*>(sphere)->loadModel(obj);
		sphere->GetTransform().SetScale(1.0f);
		sphere->GetTransform().SetPosition(0.25f * i - 1, 25.0f, 1.0f * i * 0.1f);

		objects.push_back(sphere);
	}
}

void InitializeSpheresLineConstraints(std::vector <pRBDBody*> &rbds, 
									  std::vector<pForce*> &springs, 
									  std::vector<EmptyObject*> &objects)
{

	float dampening = 0.1f;
	float springMagnitude = 40.0f;

	pForce *springBase = new SpringForce(rbds[0], pVec3(0.0f, 26.0f, 0.0f), 1.0f, 1.0f, 0.3f);
	springBase->UpdateForce(rbds[0]);
	springs.push_back(springBase);
	
	for (int i = 1; i < (int)objects.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pForce *springA = new SpringForce(rbds[i], rbds[i - 1], 0.25f, springMagnitude, dampening);
			static_cast<SpringForce*>(springA)->ApplySpring();
			springs.push_back(springA);
		}
	}		
}

void InitializeSpheresCube(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	std::string obj =  "./Graphics/Models/sphere.obj";

	EmptyObject *sphere0 = new assModel(worldSpace, EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere0)->loadModel(obj);
	sphere0->GetTransform().SetScale(1.0f);
	sphere0->GetTransform().SetPosition(0.0f, 1.5f, 0.0f);
	objects.push_back(sphere0);

	EmptyObject *sphere1 = new assModel(worldSpace, EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere1)->loadModel(obj);
	sphere1->GetTransform().SetScale(1.0f);
	sphere1->GetTransform().SetPosition(5.0f, 1.5f, 0.0f);
	objects.push_back(sphere1);

	EmptyObject *sphere2 = new assModel(worldSpace, EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere2)->loadModel(obj);
	sphere2->GetTransform().SetScale(1.0f);
	sphere2->GetTransform().SetPosition(5.0f, 1.5f, 5.0f);
	objects.push_back(sphere2);

	EmptyObject *sphere3 = new assModel(worldSpace, EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere3)->loadModel(obj);
	sphere3->GetTransform().SetScale(1.0f);
	sphere3->GetTransform().SetPosition(0.0f, 1.5f, 5.0f);
	objects.push_back(sphere3);



}

void InitializeSpheresCubeConstraints(std::vector <pRBDBody*> &rbds_, 
									  std::vector<pForce*> &springs_, 
									  std::vector<EmptyObject*> &objects_)
{
	float damp = 2.80f;
	float springMag = 10.0f;
	float cubeDiag = 1.414213 * 5.0f;

	pForce *spring0 = new SpringForce(rbds_[0], rbds_[1], 5.0f, springMag, damp);
	static_cast<SpringForce*>(spring0)->ApplySpring();
	springs_.push_back(spring0);

	pForce *spring1 = new SpringForce(rbds_[1], rbds_[2], 5.0f, springMag, damp);
	static_cast<SpringForce*>(spring1)->ApplySpring();
	springs_.push_back(spring1);

	pForce *spring2 = new SpringForce(rbds_[2], rbds_[3], 5.0f, springMag, damp);
	static_cast<SpringForce*>(spring2)->ApplySpring();
	springs_.push_back(spring2);

	pForce *spring3 = new SpringForce(rbds_[3], rbds_[0], 5.0f, springMag, damp);
	static_cast<SpringForce*>(spring3)->ApplySpring();
	springs_.push_back(spring3);

	pForce *spring4 = new SpringForce(rbds_[0], rbds_[2], cubeDiag, springMag, damp);
	static_cast<SpringForce*>(spring4)->ApplySpring();
	springs_.push_back(spring4);

	pForce *spring5 = new SpringForce(rbds_[1], rbds_[3], cubeDiag, springMag, damp);
	static_cast<SpringForce*>(spring5)->ApplySpring();
	springs_.push_back(spring5);
}

// FORCES ///////////

void InitializeForces(std::vector<pForce*> &forces)
{
	pForce *gravity = new Gravity();
	forces.push_back(gravity);

	pForce *wind = new WindForce(pVec3(-1.5f, 0.0f, 0.0f));
	forces.push_back(wind);

	pForce *drag = new DragForce(0.15);
	forces.push_back(drag);
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
	mouseCollider{0},
	isGridDisplay{true}
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

	ImGui::SetScrollHereY(1.0f);


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

		auto position = rbds[0]->Pos();
		glm::vec3 temp = glm::vec3(position.GetX(), position.GetY(), position.GetZ());
		ImGui::SliderFloat3("Position", &temp.x, -50.0f, 50.0f, "%.4f");
		rbds[0]->SetPosition(temp.x, temp.y, temp.z);

		auto rotation = rbds[0]->GetShape()->GetModel()->GetTransform().GetRotation();
		ImGui::SliderFloat3("Rotation", &rotation.x, -360.0f, 360.0f, "%.4f");
		rbds[0]->GetShape()->GetModel()->GetTransform().SetRotation(rotation.x, rotation.y, rotation.z);

		auto scale = rbds[0]->GetShape()->GetModel()->GetTransform().GetScale();
		ImGui::SliderFloat3("Scale", &scale.x, 0.001f, 20.0f, "%.4f");
		rbds[0]->GetShape()->GetModel()->GetTransform().SetScale(scale.x, scale.y, scale.z);
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

	if (Input::Instance()->GetKeyDown() == 'g' && !keyAlreadyPressed)
	{
		isGridDisplay = !isGridDisplay;
		keyAlreadyPressed = true;
	}
	if (Input::Instance()->GetKeyUp() == 'g')
	{
		keyAlreadyPressed = false;
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

	// InitializeTestObjects(worldSpace, objects);
	// InitializeSingleBox(worldSpace, objects);
	InitializeSphere(worldSpace, objects);
	// InitializeSpheresLine(worldSpace, objects);
	// InitializeSpheresCube(worldSpace, objects);

	// Initialize forces
	InitializeForces(forces);

	// Initialize physics objects
	particles.reserve(objects.size());
	rbds.reserve(objects.size());

	// Temporary creating an RBDObject per object
	for (auto obj: objects)
	{		
		// Get the position of the Graphics Model and store it on objPos
		glm::vec3 modelPos = obj->GetTransform().GetPosition();
		glm::vec3 modelScale = obj->GetTransform().GetScale();
		pVec3 objPos = pVec3(modelPos.x, modelPos.y, modelPos.z); 
		pVec3 objScale = pVec3(modelScale.x, modelScale.y, modelScale.z);	

		pRBDShape *shape = nullptr;

		// Create a new shape and a new body using that shape
		if (obj->GetObjectType() == EmptyObject::ObjectType::Sphere)
		{
			shape = new pRBDSphere(static_cast<assModel*>(obj), objScale[0]/2.0f);
		}
		shapes.push_back(shape);
		
		pRBDBody  *body = new pRBDBody(shape, objPos, 1.0f);
		rbds.push_back(body);
	}


	//Camera---------------------------------
	camera = new PCamera(glm::vec3(0.0f, 10.0f, 40.0f));	
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
	dt *= GLOBAL_SCALE * 0.05; // GlobalScale is an arbitrary value defined in the Core.h file
	elapsedTime += dt;	

	// INPUT UPDATE
	Input::Instance()->Update();

	// PROCESS INPUT
	ProcessInput();


	// Update RBDs
	for(auto &rbd_: rbds)
	{
		for (auto &force: forces)
		{
			force->UpdateForce(rbd_);
		}
	}

	// InitializeSpheresLineConstraints(rbds, springs, objects);
	// InitializeSpheresCubeConstraints(rbds, springs, objects);

	for(auto &rbd_: rbds)
	{
		rbd_->Integrate(dt);
		CollideInsideBoxSpheres(rbd_, 20);
	}	

	// Check for mouse outside viewport
	mouseCollider = {Input::Instance()->GetMousePositionX(), Input::Instance()->GetMousePositionY(), 1,	1};
	isMouseColliding = SDL_HasIntersection(&mouseCollider, &sceneCollider);

	isAppRunning = !Input::Instance()->IsXClicked();
}

void Parce::Render()
{
	Screen::Instance()->ClearScreen();

	// RENDER GRID
	if(isGridDisplay == true)
	{
		perspectiveGrid->Render(lightShader);	
	}

	// RENDER CAMERA
	camera->SendToShader(lightShader);	

	// RENDER LIGHTS
	for (auto &light: lights)
	{
		// light->Render(lightShader); // Uncomment if you want to see the lights
		light->SendToShader(lightShader);
	}

	// Iterating through RBD Objects and rendering them
	for (auto &rbd_: rbds)
	{
		pVec3 pos = rbd_->Pos();
		pQuat test = pQuat(0.7071f, 0.0f, 0.7071f, 0.0f);
		test.SetW(elapsedTime * 9000);
		glm::quat  glm_test = glm::quat(test[0], test[1], test[2], test[3]);

		glm::vec3 eulers = glm::eulerAngles(glm_test);
		pVec3 testEuler = pVec3(eulers.x, eulers.y, eulers.z);
		

		rbd_->GetShape()->GetModel()->GetTransform().SetPosition(pos[0], pos[1], pos[2]);		
		// rbd_->GetShape()->GetModel()->GetTransform().SetRotation(0.0f, 0.0f, elapsedTime * 90);	
		rbd_->GetShape()->GetModel()->GetTransform().SetRotation(testEuler[0], testEuler[1], testEuler[2]);
		Utility::AddMessage("X: " + std::to_string(testEuler[0]) + "   Y: " + std::to_string(testEuler[1]) + "   Z: " + std::to_string(testEuler[2]));
		rbd_->GetShape()->GetModel()->Render(lightShader);
	}	
	
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

	// for (auto shape: shapes)
	// {
	// 	delete(shape);
	// }

	for (auto partic: particles)
	{
		delete(partic);
	}
	
	for (auto force: forces)
	{
		delete(force);
	}

	for (auto spring: springs)
	{
		delete(spring);
	}
	

	delete(worldSpace);
	delete(camera);

	// for (auto rbd: rbds)
	// {
	// 	delete rbd;
	// }
	Screen::Instance()->Shutdown();		
}

bool Parce::IsRunning()
{
    return isAppRunning;
}
