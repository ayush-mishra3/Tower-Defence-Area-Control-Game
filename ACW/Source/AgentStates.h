#pragma once
#ifndef AGENTS_STATES_H
#define AGENTS_STATES_H
//------------------------------------------------------------------------
//
//  Name:   AgentStates.h
//
//  Desc:   All the states that can be assigned to the Agent class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "State.h"


class Agent;


//------------------------------------------------------------------------
//
//  In this state the miner will walk to a goldmine and pick up a nugget
//  of gold. If the miner already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class IDLE : public State
{
private:

    IDLE() {}

    //copy ctor and assignment should be private
    IDLE(const IDLE&);
    IDLE& operator=(const IDLE&);

public:

    //this is a singleton
    static IDLE* Instance();

    virtual void Enter(Agent* a);

    virtual void Execute(Agent* a);

    virtual void Exit(Agent* a);
};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any nuggets he is carrying. If the 
//  miner is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more gold
//------------------------------------------------------------------------
class MOVE : public State
{
private:

    MOVE() {}

    //copy ctor and assignment should be private
    MOVE(const MOVE&);
    MOVE& operator=(const MOVE&);

public:

    //this is a singleton
    static MOVE* Instance();

    virtual void Enter(Agent* a);

    virtual void Execute(Agent* a);

    virtual void Exit(Agent* a);
};


//------------------------------------------------------------------------
//
//  miner will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class ATTACK : public State
{
private:

    ATTACK() {}

    //copy ctor and assignment should be private
    ATTACK(const ATTACK&);
    ATTACK& operator=(const ATTACK&);

public:

    //this is a singleton
    static ATTACK* Instance();

    virtual void Enter(Agent* a);

    virtual void Execute(Agent* a);

    virtual void Exit(Agent* a);
};


//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class DIE : public State
{
private:

    DIE() {}

    //copy ctor and assignment should be private
    DIE(const DIE&);
    DIE& operator=(const DIE&);

public:

    //this is a singleton
    static DIE* Instance();

    virtual void Enter(Agent* a);

    virtual void Execute(Agent* a);

    virtual void Exit(Agent* a);
};

#endif