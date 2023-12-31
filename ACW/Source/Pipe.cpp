#include "Pipe.h"
#include "helpers/IRenderHelpers.h"
#include "helpers/IGuiHelpers.h"


Pipe::Pipe()
{
	glm::vec3& colour = GetColour();
	colour.x = 0.53f;
	colour.y = 0.85f;
	colour.z = 0.0f;

	m_BaseHeight = 2.75f;
	m_BaseRadius = 1.2f;
	m_LipHeight = 0.8;
	m_LipRadius = 1.5;

}

void Pipe::Update(float pSeconds)
{
	
}

void Pipe::Render(const IRenderHelpers& pHelper) const
{
	pHelper.Render(this);
}

void Pipe::RenderGui(const IGuiHelpers& pHelper)
{
	pHelper.RenderGui(this);
}

