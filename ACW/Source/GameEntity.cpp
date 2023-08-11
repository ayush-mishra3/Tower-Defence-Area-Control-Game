#include "GameEntity.h"
#include "helpers/IRenderHelpers.h"
#include "helpers/IGuiHelpers.h"

unsigned int GameEntity::s_NextID = 0;

glm::vec3 GameEntity::GetPosition() const
{
	glm::mat4 model = GetModel();
	glm::vec3 position(model[3][0], model[3][1], model[3][2]);
	return position;
}

void GameEntity::SetPosition(glm::vec3 pPosition)
{
	glm::mat4& model = GetModel();
	model[3][0] = pPosition.x;
	model[3][1] = pPosition.y;
	model[3][2] = pPosition.z;
}

void GameEntity::Render(const IRenderHelpers& pHelper) const
{
	pHelper.Render(this);
};

void GameEntity::RenderGui(const IGuiHelpers& pGuiHelper)
{
	pGuiHelper.RenderGui(this);
}