#include "Ball.h"
#include "helpers/IRenderHelpers.h"
#include "helpers/IGuiHelpers.h"
#include "SteeringBehavior.h"
#include "glm/gtx/string_cast.hpp"
#include "helpers/IRenderHelpers.h"
#include "helpers/IGuiHelpers.h"
#include <iostream>

#define _GROUND_PLANE 1.0f

Ball::Ball()
{
	glm::vec3& colour = GetColour();
	colour.x = 0.8f;
	colour.y = 0.1f;
	colour.z = 0.2f;

	m_Radius = 0.5f;
	m_Mass = 0.5f;
	m_Velocity = glm::vec3(6.0f, 5.0f, 6.0f);
	m_DragCoefficient = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Thrust = glm::vec3(0.1f, 0.0f, 0.0f);
	m_ErrorTruncTolerance = 1.0f;
	mCollision;
	glm::vec3 m_ImpactForce;
}

void Ball::EulerBasicIntegration(float pDeltaTime)
{
	glm::vec3 gravity(0.0f, -9.8f, 0.0f);
	glm::vec3 totalForce, acceleration, newVelocity, newPosition;

	float errorTruncation, newDeltaTime;
	glm::vec3 v1, v2;

	totalForce = gravity + m_Thrust - (m_DragCoefficient * m_Velocity);
	acceleration = totalForce / m_Mass;
	v1 = m_Velocity + acceleration * pDeltaTime;

	totalForce = gravity + m_Thrust - (m_DragCoefficient * m_Velocity);
	acceleration = totalForce / m_Mass;
	v2 = m_Velocity + acceleration * (pDeltaTime / 2);

	totalForce = gravity + m_Thrust - (m_DragCoefficient * v2);
	acceleration = totalForce / m_Mass;
	v2 = v2 + acceleration * (pDeltaTime / 2);

	errorTruncation = glm::abs(glm::length(v1) - glm::length(v2));
	newDeltaTime = pDeltaTime * glm::sqrt(m_ErrorTruncTolerance / errorTruncation);

	if (newDeltaTime < pDeltaTime)
	{
		totalForce = gravity + m_Thrust - (m_DragCoefficient * m_Velocity);
		acceleration = totalForce / m_Mass;
		newVelocity = m_Velocity + acceleration * newDeltaTime;
		newPosition = GetPosition() + newVelocity * newDeltaTime;
	}
	else
	{
		newVelocity = v1;
		newPosition = GetPosition() + newVelocity * pDeltaTime;
	}

	//std::cout << "Position : [" << newPosition.x << "," << newPosition.y << "," << newPosition.z << "]" << std::endl;
	SetVelocity(newVelocity);
	SetPosition(newPosition);
}

void Ball::ImprovedEulerIntegration(float pDeltaTime)
{
	glm::vec3 gravity(0.0f, -9.8f, 0.0f);
	glm::vec3 totalForce, acceleration, newVelocity, newPosition;
	glm::vec3 k1, k2;

	totalForce = gravity + m_Thrust - (m_DragCoefficient * m_Velocity);
	acceleration = totalForce / m_Mass;
	k1 = acceleration * pDeltaTime;

	totalForce = gravity + m_Thrust - (m_DragCoefficient * (m_Velocity + k1));
	acceleration = totalForce / m_Mass;
	k2 = acceleration * pDeltaTime;

	newVelocity = m_Velocity + (k1 + k2) / 2.0f;
	newPosition = GetPosition() + newVelocity * pDeltaTime;

	//std::cout << "Position : [" << newPosition.x << "," << newPosition.y << "," << newPosition.z << "]" << std::endl;
	SetVelocity(newVelocity);
	SetPosition(newPosition);
}

void Ball::RungeKutta4Integration(float pDeltaTime)
{
	glm::vec3 gravity(0.0f, -9.8f, 0.0f);
	glm::vec3 totalForce, acceleration, newVelocity, newPosition;
	glm::vec3 k1, k2, k3, k4;

	//if (mCollision) {
	//	//Add Impact Forces 
	//	totalForce = m_ImpactForce;
	//}
	//else {
		totalForce = gravity + m_Thrust - (m_DragCoefficient * m_Velocity);
//	}
	acceleration = totalForce / m_Mass;
	k1 = acceleration * pDeltaTime;

//	if (mCollision) {
//		//Add Impact Forces
//		totalForce = m_ImpactForce;
//	}
//	else {
		totalForce = gravity + m_Thrust - (m_DragCoefficient * (m_Velocity + k1 / 2.0f));
//	}
	acceleration = totalForce / m_Mass;
	k2 = acceleration * pDeltaTime;

	//if (mCollision) {
	//	//Add Impact Forces
	//	totalForce = m_ImpactForce;
	//}
	//else {
		totalForce = gravity + m_Thrust - (m_DragCoefficient * (m_Velocity + k2 / 2.0f));
//	}
	acceleration = totalForce / m_Mass;
	k3 = acceleration * pDeltaTime;

	//if (mCollision) {
	//	//Add Impact Forces
	//	totalForce = m_ImpactForce;
	//}
	//else {
		totalForce = gravity + m_Thrust - (m_DragCoefficient * (m_Velocity + k3));
//	}
	acceleration = totalForce / m_Mass;
	k4 = acceleration * pDeltaTime;


	newVelocity = m_Velocity + (k1 + 2.0f * k2 + 2.0f * k3 + k4) / 6.0f;
	newPosition = GetPosition() + newVelocity * pDeltaTime;

	//std::cout << "Position : [" << newPosition.x << "," << newPosition.y << "," << newPosition.z << "]" << std::endl;
	SetVelocity(newVelocity);
	SetPosition(newPosition);

}

void Ball::Render(const IRenderHelpers& pHelper) const
{
	pHelper.Render(this);
}

void Ball::RenderGui(const IGuiHelpers& pHelper)
{
	pHelper.RenderGui(this);
}

void Ball::Update(float pDeltaTime)
{
}