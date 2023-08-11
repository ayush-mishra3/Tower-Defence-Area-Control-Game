#include "Agent.h"
#include "World.h"
#include "SteeringBehavior.h"
#include "AgentStates.h"
#include "helpers/IRenderHelpers.h"
#include "helpers/IGuiHelpers.h"
#include <iostream>


Agent::Agent() : MovingEntity()
{
	std::cout << "Agent initializing" << std::endl;
	m_Steering = new SteeringBehavior(this);
	m_TimeElapsed = 0.0f;
	mCollision = false;

}

Agent::~Agent()
{
	delete m_Steering;
}

// -------------------------- - ChangeState------------------------------------ -
//-----------------------------------------------------------------------------
void Agent::ChangeState(State * pNewState)
{
	//make sure both states are both valid before attempting to 
	//call their methods
	assert(m_CurrentState && pNewState);

	//call the exit method of the existing state
	m_CurrentState->Exit(this);

	//change state to the new state
	m_CurrentState = pNewState;

	//call the entry method of the new state
	m_CurrentState->Enter(this);
}

void Agent::Update(float pDeltaTime)
{
	
	float m_Mass = GetMass();
	glm::vec3 currentPosition = GetPosition();
	glm::vec3 currentVelocity = GetVelocity();

	//glm::vec3 steeringForces = m_Steering->Balance();

	//glm::vec3 steeringForces = m_Steering->Seek(glm::vec3(20,1,20));
	glm::vec3 steeringForces = m_Steering->Arrive(glm::vec3(10 , 1, 20), SteeringBehavior::Decelaration(1));
	//glm::vec3 steeringForces = m_Steering->Arrive(_pipes[1].GetPosition(), SteeringBehavior::Decelaration(1));
	//glm::vec3 steeringForces = m_Steering->Seek(_pipes[0].GetPosition());
//	glm::vec3  acceleration = steeringForces / m_Mass;
	
	glm::vec3 newVelocity, newPosition;
	
	newVelocity = currentVelocity + steeringForces * pDeltaTime;
	//newVelocity = currentVelocity + acceleration * pDeltaTime;
	newPosition = currentPosition + newVelocity * pDeltaTime;

	SetPosition(newPosition);
	SetVelocity(newVelocity);
}

void Agent::RedTeam1Update(float pDeltaTime) {

	float m_Mass = GetMass();
	glm::vec3 currentPosition = GetPosition();
	glm::vec3 currentVelocity = GetVelocity();

	glm::vec3 steeringForces = m_Steering->Seek(glm::vec3(8, 0, 8));

	glm::vec3 newVelocity, newPosition;

	newVelocity = currentVelocity + steeringForces * pDeltaTime;
	newPosition = currentPosition + newVelocity * pDeltaTime;

	SetPosition(newPosition);
	SetVelocity(newVelocity);
}

void Agent::RedTeam2Update(float pDeltaTime)
{
	float m_Mass = GetMass();
	glm::vec3 currentPosition = GetPosition();
	glm::vec3 currentVelocity = GetVelocity();

	glm::vec3 steeringForces = m_Steering->Seek(glm::vec3(8.5, 0, 19));

	glm::vec3 newVelocity, newPosition;

	newVelocity = currentVelocity + steeringForces * pDeltaTime;
	newPosition = currentPosition + newVelocity * pDeltaTime;

	SetPosition(newPosition);
	SetVelocity(newVelocity);
}

void Agent::BlueTeam1Update(float pDeltaTime)
{
	float m_Mass = GetMass();
	glm::vec3 currentPosition = GetPosition();
	glm::vec3 currentVelocity = GetVelocity();

	glm::vec3 steeringForces = m_Steering->Seek(glm::vec3(22, 0, 10));

	glm::vec3 newVelocity, newPosition;

	newVelocity = currentVelocity + steeringForces * pDeltaTime;
	newPosition = currentPosition + newVelocity * pDeltaTime;

	SetPosition(newPosition);
	SetVelocity(newVelocity);
}

void Agent::BlueTeam2Update(float pDeltaTime)
{
	float m_Mass = GetMass();
	glm::vec3 currentPosition = GetPosition();
	glm::vec3 currentVelocity = GetVelocity();

	glm::vec3 steeringForces = m_Steering->Seek(glm::vec3(22, 0, 20));

	glm::vec3 newVelocity, newPosition;

	newVelocity = currentVelocity + steeringForces * pDeltaTime;
	newPosition = currentPosition + newVelocity * pDeltaTime;

	SetPosition(newPosition);
	SetVelocity(newVelocity);
}

void Agent::Render(const IRenderHelpers& pHelper) const
{
	pHelper.Render(this);
}

void Agent::RenderGui(const IGuiHelpers& pHelper)
{
	pHelper.RenderGui(this);
}