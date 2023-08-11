#pragma once
#include "GameEntity.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MovingEntity :
	public GameEntity
{
	private:
		float m_Mass;
		float m_MaxSpeed;
		float m_MaxForce;
		float m_MaxTurnRate;
		glm::vec3 m_ForwardHead;
		glm::vec3 m_SideHead;
		glm::vec3 m_Velocity;

	public:
		MovingEntity();

		void SetMass(float);
		float GetMass() const;

		void SetMaxSpeed(float);
		float GetMaxSpeed() const;

		void SetMaxForce(float);
		float GetMaxForce() const;

		void SetTurnRate(float);
		float GetTurnRate() const;

		void SetForwardHead(glm::vec3);
		glm::vec3 GetForwardHead() const;

		void SetSideHead(glm::vec3);
		glm::vec3 GetSideHead() const;

		void SetVelocity(glm::vec3);
		glm::vec3 GetVelocity() const;

		void Render(const IRenderHelpers&) const;
		void RenderGui(const IGuiHelpers&);

};