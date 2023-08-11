//
//#include "MovingEntity.h"
//#include "AgentStates.h"
//#include "State.h"
//#include "Agent.h"
//#include <iostream>
//
////define this to output to a file
//#ifdef TEXTOUTPUT
//#include <fstream>
//extern std::ofstream os;
//#define cout os
//#endif
//
//
//
////--------------------------------------methods for IDLE
//
//IDLE* IDLE::Instance()
//{
//    static IDLE instance;
//
//    return &instance;
//}
//
//void IDLE::Enter(Agent* a)
//{
//    //if the miner is not already located at the goldmine, he must
//    //change location to the gold mine
//    if (pMiner->Location() != goldmine)
//    {
//        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' to the goldmine";
//
//        pMiner->ChangeLocation(goldmine);
//    }
//}
//
//
//void IDLE::Execute(Agent* a)
//{
//    //the miner digs for gold until he is carrying in excess of MaxNuggets. 
//    //If he gets thirsty during his digging he packs up work for a while and 
//    //changes state to go to the saloon for a whiskey.
//    pMiner->AddToGoldCarried(1);
//
//    pMiner->IncreaseFatigue();
//
//    SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Pickin' up a nugget";
//
//    //if enough gold mined, go and put it in the bank
//    if (pMiner->PocketsFull())
//    {
//        pMiner->ChangeState(VisitBankAndDepositGold::Instance());
//    }
//
//    if (pMiner->Thirsty())
//    {
//        pMiner->ChangeState(QuenchThirst::Instance());
//    }
//}
//
//
//void IDLE::Exit(Agent* a)
//{
//    SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
//        << "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
//}
//
//
//
////----------------------------------------methods for MOVE
//
//MOVE* MOVE::Instance()
//{
//    static MOVE instance;
//
//    return &instance;
//}
//
//
//void MOVE::Enter(Agent* a)
//{
//    //on entry the miner makes sure he is located at the bank
//    if (pMiner->Location() != bank)
//    {
//        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Goin' to the bank. Yes siree";
//
//        pMiner->ChangeLocation(bank);
//    }
//}
//
//
//void MOVE::Execute(Agent* a)
//{
//
//    //deposit the gold
//    pMiner->AddToWealth(pMiner->GoldCarried());
//
//    pMiner->SetGoldCarried(0);
//
//    SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
//        << "Depositing gold. Total savings now: " << pMiner->Wealth();
//
//    //wealthy enough to have a well earned rest?
//    if (pMiner->Wealth() >= ComfortLevel)
//    {
//        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
//            << "WooHoo! Rich enough for now. Back home to mah li'lle lady";
//
//        pMiner->ChangeState(GoHomeAndSleepTilRested::Instance());
//    }
//
//    //otherwise get more gold
//    else
//    {
//        pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
//    }
//}
//
//
//void MOVE::Exit(Agent* a)
//{
//    SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leavin' the bank";
//}
//
//
////----------------------------------------methods for ATTACK
//
//ATTACK* ATTACK::Instance()
//{
//    static ATTACK instance;
//
//    return &instance;
//}
//
//void ATTACK::Enter(Agent* a)
//{
//   
//}
//
//void ATTACK::Execute(Agent* a)
//{
//    //if miner is not fatigued start to dig for nuggets again.
//    if (!pMiner->Fatigued())
//    {
//        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
//            << "What a God darn fantastic nap! Time to find more gold";
//
//        pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
//    }
//
//    else
//    {
//        //sleep
//        pMiner->DecreaseFatigue();
//
//        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ... ";
//    }
//}
//
//void ATTACK::Exit(Agent* a)
//{
//    SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leaving the house";
//}
//
//
//
//
////------------------------------------------------methods for DIE
//
//DIE* DIE::Instance()
//{
//    static DIE instance;
//
//    return &instance;
//}
//
//void DIE::Enter(Agent* a)
//{
//
//}
//
//void DIE::Execute(Agent* a)
//{
//    if (a->mHealth == 0)
//    {
//        a->~Agent();
//        std::cout << " Agent Dead" << std::endl;
//        a->ChangeState(IDLE::Instance());
//    }
//}
//
//void DIE::Exit(Agent* a)
//{
//}
