#pragma once
#include "GameEntity.h"
#include "Agent.h"

class Pipe :
    public GameEntity
{
private: 


public:
    Pipe();
    float m_BaseRadius;
    float m_LipRadius;
    float m_BaseHeight;
    float m_LipHeight;
   

    void Update(const float pSeconds);
    void Render(const IRenderHelpers&) const;
    void RenderGui(const IGuiHelpers&);
};

