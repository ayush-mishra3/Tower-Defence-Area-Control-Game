#pragma once
#include "GameEntity.h"
#include "Agent.h"
#include "Pipe.h"
#include "Ball.h"
#include <vector>
#include <cstdlib>

#define GAME_TIME 240.0f

class World :
	public GameEntity
{
	public:
		const static int GRID_WIDTH = 30;
		const static int GRID_DEPTH = 30;		
		int IntegrationMethod = 2;
		float r1_Influence = 1.0f;
		float r2_Influence = 1.0f;
		float b1_Influence = 1.0f;
		float b2_Influence = 1.0f;
		float gameTime = 0;

	private:
		const static int NUMBER_OF_AGENTS = 4;
		const static int NUMBER_OF_PIPES = 4;
		const static int NUMBER_OF_BALLS = 4;

		int _gridHeights[GRID_WIDTH][GRID_DEPTH];
		glm::vec3 _gridColours[GRID_WIDTH][GRID_DEPTH];
		
		Agent _agents[NUMBER_OF_AGENTS];
		Pipe _pipes[NUMBER_OF_PIPES];
		Pipe _pipe;
		Ball _balls[NUMBER_OF_BALLS];


	public:

	World();
	~World();


	int GetGridHeight(int pX, int pZ) const
	{
		return _gridHeights[pX][pZ];
	}

	glm::vec3 GetGridColour(int pX, int pZ) const
	{
		return _gridColours[pX][pZ];
	}

	bool GameOver() 
	{
		return gameTime >= GAME_TIME;
	}

	float GetMatchTime() { return gameTime; }


	int GetIntegrationMethod()
	{
		return IntegrationMethod;
	}
	void SetIntegrationMethod(int id)
	{
		IntegrationMethod = id;
	};

	void ChangeTowerColor(Agent* a);
	void SphereGroundCollision(Ball* b);	//Sphere Ground Collision 
	bool BallWallCollisions(Ball* b);		//Sphere Wall Collision 
	void SphereSphereCollision(Ball* b1, Ball* b2);	//Sphere Sphere Collision
	bool SphereCylinderCollision(Ball* b);	// Sphere Cylider Collision Detection
	void AgentHit(Agent* a, Ball* b);
	//bool CheckForCollisionsGround(Ball* b);			
	//bool CheckForCollisionSphereSphere(Ball* b1, Ball* b2);  
	//void sphereCylinderCollisionResponse(Ball* b);
	//bool checkForCollisionsAgentWall(Agent* a);


	void Update(float pSeconds);
	void Render(const IRenderHelpers&) const;
	void RenderGui(const IGuiHelpers&);
};

