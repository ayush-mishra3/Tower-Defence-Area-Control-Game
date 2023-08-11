#include "World.h"
#include "Collision.h"
#include "Ball.h"
#include "helpers/IRenderHelpers.h"
#include "helpers/IGuiHelpers.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define _GROUND_PLANE 1.0f
#define _RESTITUTION 0.6f
#define _TIMESTEP 0.1f


World::World()
{
	
	glm::vec3 redPosition(2, 0, 2);
	glm::vec3 bluePosition(25, 0, 25);

	for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	{
		if (i % 2 == 0)
		{
			_agents[i].Translate(redPosition);
			_agents[i].GetColour() = glm::vec3(1, 0, 0);
			redPosition.x += 1;
		}
		else
		{
			_agents[i].GetColour() = glm::vec3(0, 0, 1);
			_agents[i].Translate(bluePosition);
			bluePosition.x += 1;
		}
	}

	//Placing tower on the map at fixed location 

	_pipes[0].Translate(glm::vec3(10, 0, 10));
	_pipes[1].Translate(glm::vec3(20, 0, 10));
	_pipes[2].Translate(glm::vec3(10, 0, 20));
	_pipes[3].Translate(glm::vec3(20, 0, 20));

	_balls[0].Translate(glm::vec3(10, 3, 10));
	_balls[1].Translate(glm::vec3(20, 3, 10));
	_balls[2].Translate(glm::vec3(10, 3, 20));
	_balls[3].Translate(glm::vec3(20, 3, 20));
	
	//Coloring the tower and balls 
	for (int i = 0; i < NUMBER_OF_PIPES; i++)
	{

		//_pipes[i].Translate(position);
		//_balls[i].Translate(position);
		//position.x += 2;
		_pipes[i].GetColour() = glm::vec3(0, 1, 0);
		_balls[i].GetColour() = glm::vec3(1, 1, 1);

	}

	//for (int i = 0; i < NUMBER_OF_BALLS; i++)
	//{
	//	_balls[i].Translate(postion);
	//	postion.x += 2;
	//	_balls[i].GetColour() = glm::vec3(1, 1, 1);
	//}
	//_balls.Translate(postion);

	// Build boundaries
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		_gridHeights[i][0] = 2;
		_gridHeights[i][GRID_DEPTH - 1] = 2;
	}

	for (int i = 0; i < GRID_DEPTH; i++)
	{
		_gridHeights[0][i] = 5;
		_gridHeights[GRID_WIDTH - 1][i] = 3;
	}

	glm::vec3 colours[3] = { glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1) };

	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_DEPTH; j++)
		{
			_gridColours[i][j] = colours[rand() % 3];
		}
	}

	//for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	//{
	//	int x = rand() % (GRID_WIDTH - 3) + 1;
	//	int z = rand() % (GRID_DEPTH - 3) + 1;
	//	_agents[i].Translate(glm::vec3(x, 0, z));
	//}


	//glm::vec3 towerPosition(0, 0, 0);
	//for (int i = 0; i < NUMBER_OF_PIPES; i++)
	//{
	//	
	//	//int x = rand() % 10 + 2;
	//	//int z = rand() % 10 + 2;
	//	int x = 10;
	//	int z = 10;
	//	int a = 20;
	//	if (x < GRID_WIDTH && z < GRID_DEPTH) {
	//		_pipes[i].Translate(glm::vec3(x, 0, z));
	//		_balls[i].Translate(glm::vec3(x, 4.0, z));
	//		x += 10;
	//	}
	//}

	//for (int i = 0; i < NUMBER_OF_BALLS; i++)
	//{
	//	int x = rand() % (GRID_WIDTH - 3) + 1;
	//	int z = rand() % (GRID_DEPTH - 3) + 1;
	//	_balls[i].SetPosition(glm::vec3(x, 1.0, z));
	////	_balls[i].Translate(glm::vec3(x, 0, z));
	//}

	//_balls.SetPosition(glm::vec3(1.0, 5.0, 1.0));
}

World::~World()
{

}

void World::ChangeTowerColor(Agent* a) {
	float d = glm::length(a->GetPosition() - glm::vec3(10, 0, 10));
	float d1 = glm::length(a->GetPosition() - glm::vec3(10, 0, 20));
	float d2 = glm::length(a->GetPosition() - glm::vec3(20, 0, 10));
	float d3 = glm::length(a->GetPosition() - glm::vec3(20, 0, 20));
		if (d < 2.0) {
			r1_Influence += 1;
		}
		else if (d1 < 1.5) {
			b1_Influence += 1;
		}
		else if (d2 < 2.0) {
			r2_Influence += 1;
		}
		else if (d3 < 1.8) {
			b2_Influence += 1;
		}
		
	   if (r1_Influence == 25) {
		_pipes[0].SetColour(glm::vec3(1, 0, 0));
		}
	   else if (b1_Influence == 25) {
		   _pipes[1].SetColour(glm::vec3(0, 0, 1));
	   }
	   else if (r2_Influence == 25) {
		   _pipes[2].SetColour(glm::vec3(1, 0, 0));
	   }
	   else if (b2_Influence == 25) {
		   _pipes[3].SetColour(glm::vec3(0, 0, 1));
	   }
}

//Sphere Ground Collision Detection and Response
void World::SphereGroundCollision(Ball* b) {
	//  𝑉 = 𝑈− 1 + 𝑒 ∗ 𝑁.𝑈 ∗𝑁
	float e = 0.6f;
	glm::vec3 U = b->GetVelocity();
	glm::vec3 GroundNormal = {0,1,0};
	glm::vec3 V = U - ((1.0f + e) * ((glm::dot(GroundNormal, U)) * GroundNormal));

	if (b->GetPosition().y + 0.5 <= (_GROUND_PLANE + b->GetRadius())) 
	{
		b->SetVelocity(glm::vec3(V.x , V.y + 0.25 , V.z));
		//b->SetVelocity(glm::vec3(b->GetVelocity().x, -(b->GetVelocity().y), b->GetVelocity().z ));
	}
}

//Sphere Wall Collision Detction and Response 
bool World::BallWallCollisions(Ball* b) {
	float RWlength, LWlength, FWlength, BWlength;
	RWlength = (GRID_WIDTH - 1.5) - b->GetPosition().x;
	LWlength = b->GetPosition().x - 0.5;
	FWlength = (GRID_DEPTH - 1.5) - b->GetPosition().z;
	BWlength = b->GetPosition().z - 0.5;
	if (RWlength < b->GetRadius() || LWlength < b->GetRadius() || FWlength < b->GetRadius() || BWlength < b->GetRadius())	//Collision Detection
	{
		std::cout << "Ball Colliding With Wall" << std::endl;
		b->SetVelocity(-(b->GetVelocity()));
	}
	return true;
}

// Sphere Sphere Collision Detction and Response 
void World::SphereSphereCollision(Ball* b1, Ball* b2) {
	float e = 1.0f;		 
	glm::vec3 d = b1->GetPosition() - b2->GetPosition();
	glm::vec3 N = glm::normalize(d);
	glm::vec3 VN1 = (((b1->GetMass() - (e * b2->GetMass())) * (glm::dot(b1->GetVelocity(), N)) * N) + ((b2->GetMass() + e * b2->GetMass()) * (glm::dot(b2->GetVelocity(), N)) * N)) / (b1->GetMass() + b2->GetMass());
	glm::vec3 VN2 = (((b1->GetMass() + (e * b1->GetMass())) * (glm::dot(b1->GetVelocity(), N)) * N) + ((b2->GetMass() - e * b1->GetMass()) * (glm::dot(b2->GetVelocity(), N)) * N)) / (b1->GetMass() + b2->GetMass());
	glm::vec3 V1 = b1->GetVelocity() - (glm::dot(b1->GetVelocity(), N) * N) + VN1;
	glm::vec3 V2 = b2->GetVelocity() - (glm::dot(b2->GetVelocity(), N) * N) + VN1;
	if (glm::length(d) < b2->GetRadius() + b1->GetRadius()) {				//Collision Detection
		b1->SetVelocity(V1);
		b2->SetVelocity(-V2);
	}
}

// Sphere Cylinder Collision Detection and Response 
bool World::SphereCylinderCollision(Ball* b)
{
	for (int i = 0; i < NUMBER_OF_PIPES; i++) {

		//float e = 0.5f;
		glm::vec3 U = b->GetVelocity();

		// Vector from sphere center to cylinder center
		glm::vec3 d = b->GetPosition() - _pipes[i].GetPosition();
		// Project d onto cylinder axis
		float dist = glm::dot(d, glm::vec3(0, 1, 0));
		// Check if sphere is within cylinder height
		float Height = _pipes[i].m_BaseHeight + _pipes[i].m_LipHeight;

		glm::vec3 N = glm::normalize(d);
		//glm::vec3 V = U - ((1.0f + e) * ((glm::dot(N, U)) * N));
		glm::vec3 V = glm::reflect(b->GetVelocity(), N);

		if (dist < 0 || dist > Height) {
			return false;
		}
		// Calculate distance from sphere center to cylinder surface
		//float distSquared = glm::length(d - dist * glm::vec3(0, 1, 0));
		// Check if distance is less than sphere radius plus cylinder radius
		if (glm::length(d) < b->GetRadius() + _pipes[i].m_BaseRadius) {
			std::cout << "Ball Pipe Colliding" << std::endl;
			b->SetVelocity(V);
			return true;
		}
	}
	return false;
}

//bool World::CheckForCollisionsGround(Ball* b) {
//	glm::vec3 GroundNormal;
//	glm::vec3 RelativeVeloctity;
//	float VRN;
//	float Impulse;
//	glm::vec3 ImpactForce;
//	bool hasCollision = false;
//	glm::vec3 NewPosition;
//
//	//Reset aggregate impact force 
//	//b->SetImpactForce(glm::vec3(0.0f, 0.0f, 0.0f));
//	b->m_ImpactForce.x = 0.0f;
//	b->m_ImpactForce.y = 0.0f;
//	b->m_ImpactForce.z = 0.0f;
//
//	//check for collisions with ground plane 
//	if (b->GetPosition().y <= (_GROUND_PLANE + b->GetRadius())) {
//	/*	std::cout << "Ground Collision Happening " << std::endl;*/
//		GroundNormal.x = 0;
//		GroundNormal.y = 1;
//		GroundNormal.z = 0;
//		RelativeVeloctity = b->GetVelocity();
//		VRN = glm::dot(RelativeVeloctity, GroundNormal);
//
//		//check to see if the particle is moving towards the ground 
//		if (VRN < 0.0f) {
//			Impulse = -(glm::dot(RelativeVeloctity, GroundNormal)) * (_RESTITUTION + 1.0f) * b->GetMass();
//			ImpactForce = GroundNormal;
//			ImpactForce *= Impulse / _TIMESTEP;
//			b->m_ImpactForce += ImpactForce;
//
//			NewPosition.y = (_GROUND_PLANE + b->GetRadius());
//			NewPosition.x = (_GROUND_PLANE + b->GetRadius() - b->GetPosition().y) /
//				(NewPosition.y - b->GetPosition().y) *
//				(NewPosition.x - b->GetPosition().x) +
//				b->GetPosition().x;
//
//			hasCollision = true;
//		}
//	}
//	return hasCollision;
//}

//bool World::CheckForCollisionSphereSphere(Ball* b1, Ball* b2)
//{
//	glm::vec3 Dist = b2->GetPosition() - b1->GetPosition();
//	float D = glm::length(Dist);
//
//	if (D < b2->GetRadius() + b1->GetRadius()) {
//		std::cout << "Ball Ball Colliding" << std::endl;
//		return true;
//	}
//	return false;
//}

//void World::sphereCylinderCollisionResponse(Ball* b)
//{
//	//for (int i = 0 ; i < NUMBER_OF_PIPES; i++){
//	//	glm::vec3 pipePos = _pipes[i].GetPosition();
//	//	glm::vec3 d = pipePos - b->GetPosition();
//	//	if(d )
//	//}
//	float e = 0.6f;
//	glm::vec3 U = b->GetVelocity();
//	glm::vec3 TowerNormal = { 0,1,0 };
//	glm::vec3 V = U - ((1.0f + e) * ((glm::dot(GroundNormal, U)) * GroundNormal));
//
//	if (b->GetPosition().y + 0.5 <= (_GROUND_PLANE + b->GetRadius()))
//	{
//		b->SetVelocity(glm::vec3(V.x, V.y + 0.25, V.z));
//		//b->SetVelocity(glm::vec3(b->GetVelocity().x, -(b->GetVelocity().y), b->GetVelocity().z ));
//	}
//}

//bool World::checkForCollisionsAgentWall(Agent* a) {
//	float RWlength, LWlength, FWlength, BWlength;
//	RWlength = (GRID_WIDTH - 1) - a->GetPosition().x;
//	LWlength = a->GetPosition().x;
//	FWlength = (GRID_DEPTH - 1) - a->GetPosition().z;
//	BWlength = a->GetPosition().z;
//	if (RWlength < a->boundingRadius || LWlength < a->boundingRadius || FWlength < a->boundingRadius || BWlength < a->boundingRadius)
//	{
//		a->SetVelocity(-(a->GetVelocity()));
//	}
//	return true;
//}

void World::AgentHit(Agent* a, Ball* b)
{
	glm::vec3 D = a->GetPosition() - b->GetPosition();
	float length = glm::length(D);
	if (length < b->GetRadius() + a->boundingRadius) {
		std::cout << "Agent HIT!" << std::endl;
		a->mHealth -= 1;
	}
}


void World::Update(float pSeconds)
{
	gameTime += pSeconds;

	//for (int i = 0; i < NUMBER_OF_AGENTS; i++) {
	//	for (int j = 0; j < NUMBER_OF_BALLS; j++) {
	//		AgentHit(&_agents[i], &_balls[j]);
	//	}
	//}
	ChangeTowerColor(&_agents[0]);
	ChangeTowerColor(&_agents[1]);
	ChangeTowerColor(&_agents[2]);
	ChangeTowerColor(&_agents[3]);
	_agents[0].RedTeam1Update(pSeconds);
	_agents[2].RedTeam2Update(pSeconds);
	_agents[1].BlueTeam1Update(pSeconds);
	_agents[3].BlueTeam2Update(pSeconds);

	SphereSphereCollision(&(_balls[0]), &(_balls[1]));
	SphereSphereCollision(&(_balls[0]), &(_balls[2]));
	SphereSphereCollision(&(_balls[0]), &(_balls[3]));
	SphereSphereCollision(&(_balls[1]), &(_balls[2]));
	SphereSphereCollision(&(_balls[1]), &(_balls[3]));
	SphereSphereCollision(&(_balls[2]), &(_balls[3]));

	AgentHit(&(_agents[0]), &(_balls[0]));
	AgentHit(&(_agents[0]), &(_balls[1]));
	AgentHit(&(_agents[0]), &(_balls[2]));
	AgentHit(&(_agents[0]), &(_balls[3]));

	AgentHit(&(_agents[1]), &(_balls[0]));
	AgentHit(&(_agents[1]), &(_balls[1]));
	AgentHit(&(_agents[1]), &(_balls[2]));
	AgentHit(&(_agents[1]), &(_balls[3]));

	AgentHit(&(_agents[2]), &(_balls[0]));
	AgentHit(&(_agents[2]), &(_balls[1]));
	AgentHit(&(_agents[2]), &(_balls[2]));
	AgentHit(&(_agents[2]), &(_balls[3]));

	AgentHit(&(_agents[3]), &(_balls[0]));
	AgentHit(&(_agents[3]), &(_balls[1]));
	AgentHit(&(_agents[3]), &(_balls[2]));
	AgentHit(&(_agents[3]), &(_balls[3]));

	for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	{
	//	_agents[i].Update(pSeconds);
		
		//_agents[i].mCollision = checkForCollisionsAgentWall(&(_agents[i]));
	}

	for (int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		_pipes[i].Update(pSeconds);
	}

	for (int i = 0; i < NUMBER_OF_BALLS; i++)
	{

	//	_balls[i].mCollision = CheckForCollisionsGround(&(_balls[i]));
		SphereGroundCollision(&_balls[i]);
		
		if (GetIntegrationMethod() == 0)
		{
			_balls[i].EulerBasicIntegration(pSeconds);
		}
		else if (GetIntegrationMethod() == 1)
		{
			_balls[i].ImprovedEulerIntegration(pSeconds);

		}
		else if (GetIntegrationMethod() == 2)
		{
			_balls[i].RungeKutta4Integration(pSeconds);
		}
		
		//_balls[i].mCollision = CheckForCollisionSphereSphere(&(_balls[i]), &(_balls[i + 1]));
	    SphereCylinderCollision(&(_balls[i]));
		BallWallCollisions(&(_balls[i]));
	}
}

void World::Render(const IRenderHelpers& pHelper) const
{
	pHelper.Render(this);

	for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	{
		pHelper.Render(&_agents[i]);
	}

	for (int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		pHelper.Render(&_pipes[i]);
	}

	for (int i = 0; i < NUMBER_OF_BALLS; i++)
	{
		pHelper.Render(&_balls[i]);
	}

}

void World::RenderGui(const IGuiHelpers& pHelper)
{
	pHelper.RenderGui(this);

	for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	{
		pHelper.RenderGui(&_agents[i]);
	}

	for (int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		pHelper.RenderGui(&_pipes[i]);
	}


	for (int i = 0; i < NUMBER_OF_BALLS; i++)
	{
		pHelper.RenderGui(&_balls[i]);
	}
}