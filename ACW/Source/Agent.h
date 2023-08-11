#pragma once
#include "MovingEntity.h"
#include "Pipe.h"

class SteeringBehavior;
class State;

class Agent :
    public MovingEntity
{
private:
    SteeringBehavior* m_Steering;
    State* m_CurrentState;
    float m_TimeElapsed;

    Agent& operator=(const Agent&) = default;


public:
    float boundingRadius = 1.2f;
    float mHealth = 10.0f;
    bool mCollision;
    Agent(const Agent&) = default;
    Agent();
    ~Agent();

    SteeringBehavior* Steering() const { return m_Steering; }
    void ChangeState(State* new_state);
    float GetElapsedTime() const { return m_TimeElapsed; }
    
	void Update(float);
    void RedTeam1Update(float pDeltaTime);
    void RedTeam2Update(float pDeltaTime);
    void BlueTeam1Update(float pDeltaTime);
    void BlueTeam2Update(float pDeltaTime);
	void Render(const IRenderHelpers&) const;
	void RenderGui(const IGuiHelpers&);
};


