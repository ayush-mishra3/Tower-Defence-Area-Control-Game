#pragma once
#include "Floor.h"
#include "Agent.h"
#include "helpers/IRenderHelpers.h"

class CollisionPlane : public Floor
{
public:
	CollisionPlane()
	{
		Scale(glm::vec3(5.0f, 10.0f, 10.0f));
		Translate(glm::vec3(5.0f, 0.0f, 0.0f));
	}

	bool isColliding(Agent pAgent)
	{
		if (glm::length(GetPosition() - pAgent.GetPosition()) > glm::exp2(pAgent.boundingRadius))
			return true;
		return false;
	}

	void Render(IRenderHelpers& pHelper)
	{
		pHelper.Render(this);
	}
};

