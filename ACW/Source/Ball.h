#pragma once
#include "GameEntity.h"
#include "MovingEntity.h"

class SteeringBehavior;

class Ball :
    public MovingEntity
{
private:
       
    float m_Radius;
    float m_Mass;
    glm::vec3 m_Velocity;
    glm::vec3 m_DragCoefficient;
    glm::vec3 m_Thrust;
    float m_ErrorTruncTolerance;

public:
    Ball();
    glm::vec3 m_ImpactForce;
    bool mCollision;
     

    float GetMass() const
    {
        return m_Mass;
    }
    void SetMass(float pMass)
    {
        m_Mass = pMass;
    }

    glm::vec3 GetPosition() const
    {
        glm::mat4 model = GetModel();
        glm::vec3 translation(model[3][0], model[3][1], model[3][2]);
        return translation;
    }
    void SetPosition(glm::vec3 pPosition)
    {
        glm::mat4 & model = GetModel();
        model[3][0] = pPosition.x;
        model[3][1] = pPosition.y;
        model[3][2] = pPosition.z;
    }

    glm::vec3 GetVelocity() const
    {
        return m_Velocity;
    }
    void SetVelocity(glm::vec3 pVelocity)
    {
        m_Velocity = pVelocity;
    }

    glm::vec3 GetThrust() const
    {
        return m_Thrust;
    }
    void SetThrust(glm::vec3 pThrust)
    {
        m_Thrust = pThrust;
    }

    glm::vec3 GetDragCoefficient() const
    {
        return m_DragCoefficient;
    }
    void SetDragCoefficient(glm::vec3 pDragCoefficient)
    {
        m_DragCoefficient = pDragCoefficient;
    }

    float GetRadius() const
    {
        return m_Radius;
    }
    void SetRadius(float pRadius)
    {
        m_Radius = pRadius;
    }
        
    void EulerBasicIntegration(float pDeltaTime);
    void ImprovedEulerIntegration(float pDeltaTime);
    void RungeKutta4Integration(float pDeltaTime);

    void Render(const IRenderHelpers&) const;
    void RenderGui(const IGuiHelpers&);
    void Update(float pDeltaTime);
};

