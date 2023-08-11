#include "SteeringBehavior.h"


SteeringBehavior::SteeringBehavior(Agent* pAgent)
{
    m_Agent = pAgent;
    m_SteeringForce = glm::vec3(0.0f);
}

SteeringBehavior::~SteeringBehavior()
{

}

glm::vec3 SteeringBehavior::CalculateWeightedSum()
{
    m_SteeringForce = glm::vec3(1.0f, 0.0f, 0.5f);
    return m_SteeringForce;
}

glm::vec3 SteeringBehavior::Balance()
{
    m_SteeringForce = glm::vec3(0.5f, 0.0f, 0.5f);

    // TO DO: Add other methods as well - Prioritized, Dithered
    // m_SteeringForce = CalculateWeightedSum(); 
    return m_SteeringForce;
}

glm::vec3 SteeringBehavior::Seek(glm::vec3 pTarget)
{
    glm::vec3 desiredVelocity = glm::normalize(pTarget - m_Agent->GetPosition()) * m_Agent->GetMaxSpeed();
    return desiredVelocity - m_Agent->GetVelocity();
}

glm::vec3 SteeringBehavior::Arrive(glm::vec3 pTarget, Decelaration deceleration)
{
    glm::vec3 ToTarget = pTarget - m_Agent->GetPosition();

    //Calculate the distance to the target position 
    double dist = glm::length(ToTarget);

    if(dist > 0)
    {
        //because deceleration is enumerated as an int, this value is required to provide fine tweaking of the deceleration.
        const double DecelerationTweaker = 0.1;

        //Calculate the speed required to reach the target given the desired deceleration 
        double speed = dist / ((double)deceleration * DecelerationTweaker);

        //make sure the velocity does not exceed the max
        speed = glm::min(static_cast<float>(speed), m_Agent->GetMaxSpeed());

        glm::vec3 DesiredVelocity = ToTarget * static_cast<float>(speed / dist);

        return (DesiredVelocity - m_Agent->GetVelocity());

    }
    return glm::vec3(0);
}