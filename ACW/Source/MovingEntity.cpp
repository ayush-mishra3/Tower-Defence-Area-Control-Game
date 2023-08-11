#include "MovingEntity.h"
#include "helpers/IRenderHelpers.h"
#include "helpers/IGuiHelpers.h"

MovingEntity::MovingEntity()
{
	// TO DO Truncate velocity function
	m_Velocity = glm::vec3(0.0f);

	m_ForwardHead = glm::vec3(0.0f);
	m_SideHead = glm::vec3(0.0f);

	m_Mass = 1.0f;
	m_MaxSpeed = 5.0f;
	m_MaxForce = 20.0f;
	m_MaxTurnRate = 10.0f;
}

void MovingEntity::SetMass(float pMass)
{
	m_Mass = pMass;
}
float MovingEntity::GetMass() const
{
	return m_Mass;
}

void MovingEntity::SetMaxSpeed(float pMaxSpeed)
{
	m_MaxSpeed = pMaxSpeed;
}
float MovingEntity::GetMaxSpeed() const
{
	return m_MaxSpeed;
}

void MovingEntity::SetMaxForce(float pMaxForce)
{
	m_MaxForce = pMaxForce;
}
float MovingEntity::GetMaxForce() const
{
	return m_MaxForce;
}

void MovingEntity::SetTurnRate(float pMaxTurnRate)
{
	m_MaxTurnRate = pMaxTurnRate;
}
float MovingEntity::GetTurnRate() const
{
	return m_MaxTurnRate;
}

void MovingEntity::SetForwardHead(glm::vec3 pForwardHead)
{
	m_ForwardHead = pForwardHead;
}
glm::vec3 MovingEntity::GetForwardHead() const
{
	return m_ForwardHead;
}

void MovingEntity::SetSideHead(glm::vec3 pSideHead)
{
	m_SideHead = pSideHead;
}
glm::vec3 MovingEntity::GetSideHead() const
{
	return m_SideHead;
}

void MovingEntity::SetVelocity(glm::vec3 pVelocity)
{
	m_Velocity = pVelocity;
}
glm::vec3 MovingEntity::GetVelocity() const
{
	return m_Velocity;
}

void MovingEntity::Render(const IRenderHelpers& pHelper) const
{
	pHelper.Render(this);
}
void MovingEntity::RenderGui(const IGuiHelpers& pHelper)
{
	pHelper.RenderGui(this);
}