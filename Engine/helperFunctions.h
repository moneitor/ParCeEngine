#pragma once

#include<cstdlib>
#include<ctime>
#include <random>


#include "Physics/Maths/Core.h"

#include "helperFunctions.h"

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
#include "Physics/PCollisionDetect.h"


#include "vendors/imgui/imgui.h"
#include "vendors/imgui/backends/imgui_impl_opengl3.h"
#include "vendors/imgui/backends/imgui_impl_sdl2.h"

#include <deque>


static float randomFloat()
{
    return (float)(rand()) / (float)(rand());
}


// DEMO INITIALIZATIONS

static void CollideInsideBoxSpheres(pRBDBody *rbd_, int size_box)
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
	} else if (rbd_->Pos()[2] + radius >= size_box)
	{
		rbd_->SetPosition(rbd_->Pos()[0], rbd_->Pos()[1], size_box - radius);
		rbd_->SetVelocity(rbd_->Vel()[0], rbd_->Vel()[1], rbd_->Vel()[2] * rbd_->Elasticity() * -1);
	}		
}

// Initialization helper functions for testing
static void InitializeLights(std::vector<Light*> &lights)
{
	//Lights================================================================
	Light *light1 = new Light();
	light1->SetPosition(10.0f, 10.0f, 0.0f);
	lights.push_back(light1);	

	Light *light2 = new Light();
	light2->SetPosition(-10.0f, 10.0f, 0.0f);
	lights.push_back(light2);	
}

static void InitializeTestObjects(World *worldSpace, std::vector<EmptyObject*> &objects)
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

static void InitializeBoxes(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	std::string obj =  "./Graphics/Models/Cube.obj";

	// //Model------------------------------------------s
	EmptyObject *cube1 = new assModel(worldSpace, EmptyObject::ObjectType::Cube);
	static_cast<assModel*>(cube1)->loadModel(obj);
	cube1->GetTransform().SetPosition(0.0f, 0.0f, 0.0f);
	cube1->GetTransform().SetScale(2.0f);

	objects.push_back(cube1);


	// EmptyObject *cube2 = new assModel(worldSpace, EmptyObject::ObjectType::Cube);
	// static_cast<assModel*>(cube2)->loadModel(obj);
	// cube2->GetTransform().SetPosition(5.0f, 8.0f, 0.0f);
	// cube2->GetTransform().SetRotation(45.0f, -45.70f, 0.0f);
	// cube2->GetTransform().SetScale(5.0f);

	// objects.push_back(cube2);
}

static void InitializeSphere(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	std::string obj =  "./Graphics/Models/sphere.obj";

	// //Model------------------------------------------s
	EmptyObject *sphere = new assModel(worldSpace, EmptyObject::ObjectType::Sphere);
	static_cast<assModel*>(sphere)->loadModel(obj);
	sphere->GetTransform().SetPosition(0.0f, 0.0f, 0.0f);
	sphere->GetTransform().SetScale(1.0f);

	objects.push_back(sphere);
}

static void InitializeSpheres(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	std::string obj =  "./Graphics/Models/sphere.obj";

	//Model------------------------------------------
	EmptyObject *sphere1 = new assModel(worldSpace,  EmptyObject::ObjectType::Sphere, 3.0f);
	static_cast<assModel*>(sphere1)->loadModel(obj);
	sphere1->GetTransform().SetScale(1.0f);
	sphere1->GetTransform().SetPosition(-6.0f, 6.0f, 0.0f);

	objects.push_back(sphere1);

	EmptyObject *sphere2 = new assModel(worldSpace,  EmptyObject::ObjectType::Sphere, 2.0f);
	static_cast<assModel*>(sphere2)->loadModel(obj);
	sphere2->GetTransform().SetScale(1.0f);
	sphere2->GetTransform().SetPosition(-5.0f, 2.0f, 1.0f);

	objects.push_back(sphere2);

	EmptyObject *sphere3 = new assModel(worldSpace,  EmptyObject::ObjectType::Sphere, 1.0f);
	static_cast<assModel*>(sphere3)->loadModel(obj);
	sphere3->GetTransform().SetScale(1.0f);
	sphere3->GetTransform().SetPosition(0.0f, 3.0f, -1.0f);

	objects.push_back(sphere3);

	EmptyObject *sphere4 = new assModel(worldSpace,  EmptyObject::ObjectType::Sphere, 1.0f);
	static_cast<assModel*>(sphere4)->loadModel(obj);
	sphere4->GetTransform().SetScale(1.0f);
	sphere4->GetTransform().SetPosition(1.0f, 5.0f, 2.0f);

	objects.push_back(sphere4);
}

static void InitializeSpheresLoop(World *worldSpace, std::vector<EmptyObject*> &objects)
{
	std::string obj =  "./Graphics/Models/sphereLowRes.obj";
	// std::string obj =  "./Graphics/Models/sphere.obj";

	std::default_random_engine gen;
	std::uniform_real_distribution<double> distribution(-10.0, 10.0f);

	for (int i = 0; i < 100; i++)
	{
		float x = distribution(gen);
		float y = std::abs(distribution(gen));
		float z = distribution(gen);
 
		float scale = std::clamp((float)std::abs(distribution(gen)), 5.0f, 10.0f);

		EmptyObject *newSphere = new assModel(worldSpace,  EmptyObject::ObjectType::Sphere, 3.0f);
		static_cast<assModel*>(newSphere)->loadModel(obj);
		newSphere->GetTransform().SetScale(scale * 0.2);
		newSphere->GetTransform().SetPosition(x, y, z);
		static_cast<assModel*>(newSphere)->SetMass(scale);

		objects.push_back(newSphere);

	}

}

static void InitializeSpheresLine(World *worldSpace, std::vector<EmptyObject*> &objects)
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

static void InitializeSpheresLineConstraints(std::vector <pRBDBody*> &rbds, 
									  std::vector<pForce*> &springs, 
									  std::vector<EmptyObject*> &objects)
{

	float dampening = 0.3f;
	float springMagnitude = 20.0f;

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

static void InitializeSpheresCube(World *worldSpace, std::vector<EmptyObject*> &objects)
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

static void InitializeSpheresCubeConstraints(std::vector <pRBDBody*> &rbds_, 
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

static void InitializeForces(std::vector<pForce*> &forces)
{
	pForce *gravity = new Gravity();
	forces.push_back(gravity);

	pForce *wind = new WindForce(pVec3(-0.05f, 0.0f, 0.0f));
	forces.push_back(wind);

	pForce *drag = new DragForce(0.3);
	forces.push_back(drag);

	pForce *torqueForce = new Torque(pVec3(0.000f, 0.000f, 0.00010f));
	// forces.push_back(torqueForce);
}


