#include "ParCe.h"

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
	isGridDisplay{false},
	drawWireframe{false},
	obj{"./Graphics/Models/sphereLowRes.obj"}
{
	this->CONSOLE_HEIGHT = (float)SCREEN_HEIGHT * 0.4f;
	this->PROPERTIES_WIDTH = (float)SCREEN_WIDTH * 0.4f;

    sceneCollider = {0, 0, SCREEN_WIDTH - PROPERTIES_WIDTH, SCREEN_HEIGHT - CONSOLE_HEIGHT};

	runSim = false;
}

Parce::~Parce()
{
	std::cout << "Destructor called" << std::endl;
}

void Parce::RenderConsoleWindow(bool isRunning)
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
		if(isRunning)
		{
			messages.push_back(message);
		}
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

	if(ImGui::Button("Run Simulation"))
	{
		runSim = !runSim;
		if(runSim)
		{
			Utility::AddMessage("Running sim. ");
		}
		else
		{
			Utility::AddMessage("Paused sim. ");
		}
	}

	ImGui::Separator();
	ImGui::Spacing();

	if(ImGui::Button("Show Grid"))
	{
		isGridDisplay = !isGridDisplay;	
	}

	ImGui::SameLine();

	if(ImGui::Button("Wireframe"))
	{
		drawWireframe = !drawWireframe;	
	}

	ImGui::Separator();
	ImGui::Spacing();

	
	if(ImGui::Button("RESET"))
	{
		Reset();
	}

	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Separator();

	if (objects.size() > 0)
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
	pVec3 p = rbds[0]->Pos();
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
			case 'i':
				p = rbds[0]->Pos();
				rbds[0]->SetPosition(p + pVec3(0.0f, 0.0050f, 0.0f));
				break;	
			case 'k':
				p = rbds[0]->Pos();
				rbds[0]->SetPosition(p - pVec3(0.0f, 0.0050f, 0.0f));
				break;	
			case 'j':
				p = rbds[0]->Pos();
				rbds[0]->SetPosition(p - pVec3(0.0050f, 0.0f, 0.0f));
				break;	
			case 'l':
				p = rbds[0]->Pos();
				rbds[0]->SetPosition(p + pVec3(0.0050f, 0.0f, 0.0f));
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

void Parce::ImGuiUI(bool isRunning)
{
	// IMGUI Stuff
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	RenderConsoleWindow(isRunning);
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

	InitializeBoxes(worldSpace, objects);
	// InitializeSphere(worldSpace, objects);
	// InitializeSpheres(worldSpace, objects);
	// InitializeSpheresLoop(worldSpace, objects);
	// InitializeSpheresLine(worldSpace, objects);
	// InitializeSpheresCube(worldSpace, objects);

	// Initialize forces
	InitializeForces(forces);

	// Initialize physics objects
	particles.reserve(objects.size());
	rbds.reserve(objects.size());


	// TODO: IMPROVE THIS SHIT, by shit I mean how we are creting rbdBodys from generic objects	
	CreateBodyFromModel(); // Creating an RBDObject per object

	// rbds[0]->SetActive(false);



	//Camera---------------------------------
	camera = new PCamera(glm::vec3(0.0f, 2.0f, 10.0f));	
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

	if (runSim == true)
	{
		// Update RBDs
		for(auto &rbd_: rbds)
		{
			for (auto &force: forces)
			{
				force->UpdateForce(rbd_);
			}
		}

		// CONSTRAINT FORCES
		// InitializeSpheresLineConstraints(rbds, springs, objects);
		// InitializeSpheresCubeConstraints(rbds, springs, objects);

		// Broadphase
		std::vector< CollisionPair > collisionPairs;
		BroadPhase( rbds, (int)rbds.size(), collisionPairs, dt );


		for(auto &rbd_: rbds)
		{
			rbd_->IntegrateBody(dt, elapsedTime);		
			// Utility::AddMessage(static_cast<pRBDCube*>(rbd_->GetShape())->GetBoundPoints()[0].ToString());
			// Utility::AddMessage(static_cast<pRBDCube*>(rbd_->GetShape())->GetCenterOfMass().ToString());
			// Utility::AddMessage(rbd_->GetCenterOfMassWorldSpace().ToString());
			Utility::AddMessage(std::to_string(static_cast<pRBDCube*>(rbd_->GetShape())->FastestLinearSpeed(rbd_->GetCenterOfMassWorldSpace(), rbd_->AngularVelocity(), rbd_->Vel())));

			CollideInsideBoxSpheres(rbd_, 20, -15);
		}	

		for(auto &rbd_: rbds)
		{
			rbd_->SetIsColliding(false);
		}

		for(int substep = 0; substep < 2; substep++)
		{
			for(int i = 0; i < collisionPairs.size(); i++)
			{
				const CollisionPair &pair = collisionPairs[i];

				pRBDBody *a = rbds[pair.a];
				pRBDBody *b = rbds[pair.b];

				pImpactData impactData;

				if(pCollisionDetection::IsColliding(a, b, impactData, dt))
				{
					a->SetIsColliding(true);
					b->SetIsColliding(true);		

					impactData.ResolveCollision();
				}			
			}
		}

		// Detect and resolve collisions
		// for(int i = 0; i <= rbds.size() - 1; i++)
		// {
		// 	for(int j = i + 1; j < rbds.size(); j++)
		// 	{
		// 		pRBDBody *a = rbds[i];
		// 		pRBDBody *b = rbds[j];

		// 		pImpactData impactData;

		// 		if(pCollisionDetection::IsColliding(a, b, impactData, dt))
		// 		{
		// 			a->SetIsColliding(true);
		// 			b->SetIsColliding(true);		

		// 			impactData.ResolveCollision();
		// 		}			
		// 	}
		// }		
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
		perspectiveGrid->Render(lightShader, Buffer::DrawType::Lines);	
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
		pQuat rot = rbd_->Orient(); 

		glm::vec3 eulerAngles = glm::eulerAngles( glm::quat(rot[0], rot[1], rot[2], rot[3]) );

		rbd_->GetShape()->GetModel()->GetTransform().SetPosition(pos[0], pos[1], pos[2]);		
		rbd_->GetShape()->GetModel()->GetTransform().SetRotation(glm::degrees(eulerAngles.x), glm::degrees(eulerAngles.y), glm::degrees(eulerAngles.z));
		
		if(drawWireframe == true)
		{
			rbd_->GetShape()->GetModel()->Render(lightShader, Buffer::DrawType::Lines);
		} 
		else
		{			
			rbd_->GetShape()->GetModel()->Render(lightShader, Buffer::DrawType::Triangles);
		}

		if (rbd_->IsSleeping())
		{
			rbd_->GetShape()->GetModel()->SetColor(glm::vec4(1.0f, 0.0f, 0.0f,1.0f));
		}
	}	

	// for(auto &obj: objects)
	// {
	// 	obj->Render(lightShader, Buffer::DrawType::Triangles);
	// }

	// for(auto &debugObj: debugObjects)
	// {
	// 	debugObj->Render(lightShader, Buffer::DrawType::Triangles);
	// }


	this->ImGuiUI(runSim);

	
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

	for (auto debugOject: debugObjects)
	{
		delete(debugOject);
	}

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

void Parce::Reset()
{
	// Destroy();
	Initialize();
}


void Parce::CreateBodyFromModel()
{
	for (auto obj: objects)
	{		
		// Get the position of the Graphics Model and store it on objPos
		pVec3 objPos = obj->GetTransform().GetPosition();
		pVec3 objScale =  obj->GetTransform().GetScale();	
		pQuat objOrient = obj->GetTransform().GetOrient();

		pRBDShape *shape = nullptr;

		// Create a new shape and a new body using that shape
		if (obj->GetObjectType() == EmptyObject::ObjectType::Sphere)
		{
			shape = new pRBDSphere(static_cast<assModel*>(obj), objScale[0]/2.0f);
		}
		if (obj->GetObjectType() == EmptyObject::ObjectType::Cube)
		{
			shape = new pRBDCube(static_cast<assModel*>(obj));
		}
		if (obj->GetObjectType() == EmptyObject::ObjectType::Geometry)
		{
			shape = new pRBDConvex(static_cast<assModel*>(obj));
		}
		shapes.push_back(shape);
		
		pRBDBody  *body = new pRBDBody(shape, objPos, objOrient, static_cast<assModel*>(obj)->GetMass());
		body->SetElasticity(0.75);
		body->SetAngularDamping(0.9);
		// body->setLinearDamping(0.9);
		body->SetFriction(0.7);
		rbds.push_back(body);
	}
	rbds[0]->SetVelocity(pVec3(1.0f, 0.0f, 0.0f));
	// rbds[1]->SetVelocity(pVec3(-1.0f, 0.0f, 0.0f));

	// rbds[0]->SetActive(false);
}
