#pragma once
#ifndef STATE_H
#define STATE_H
//------------------------------------------------------------------------
//
//  Name:   State.h
//
//  Desc:   abstract base class to define an interface for a state
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

class Agent;

class State
{
public:

	virtual ~State() {}

	//this will execute when the state is entered
	virtual void Enter(Agent*) = 0;

	//this is the state's normal update function
	virtual void Execute(Agent*) = 0;

	//this will execute when the state is exited. 
	virtual void Exit(Agent*) = 0;

};

#endif