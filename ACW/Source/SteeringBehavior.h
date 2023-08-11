#pragma once
#include "glm/glm.hpp"
#include "Agent.h"

class Agent;

class SteeringBehavior
{
private:
	Agent* m_Agent;
	glm::vec3 m_SteeringForce;

	SteeringBehavior(const SteeringBehavior&) = default;
	SteeringBehavior& operator=(const SteeringBehavior&) = default;

public:
	SteeringBehavior(Agent*);
	~SteeringBehavior();
	enum Decelaration {slow = 3, normal = 2, fast = 1 };

	Agent* GetAgent() const { return m_Agent; };
	glm::vec3 GetSteeringForce() const { return m_SteeringForce; };

	glm::vec3 CalculateWeightedSum();
	glm::vec3 Balance();

	// TO DO Add all behaviors.. flee, arrive, pursuit.. and combinations
	glm::vec3 Seek(glm::vec3);

	glm::vec3 Arrive(glm::vec3, Decelaration);

	// TO DO other functions
	// 
	// Forward and Side Component
	// Set Path
	// Set TargetAgent

};