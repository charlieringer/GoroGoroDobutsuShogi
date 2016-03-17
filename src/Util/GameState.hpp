//
//  GameState.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/03/2016.
//
//

#ifndef GameState_hpp
#define GameState_hpp

#define FRONTEND 0
#define AISETTINGS 1
#define GAME 2
#define GAMEOVERLOSE 3
#define GAMEOVERWIN 4

#include <stdio.h>
#include "ofMain.h"
using namespace std;

//State system heavily influenced from the example shooter code by Marco Gillies.
//https://github.com/marcogillies/ShooterInheritanceExample

class GameState
{
private:
    //Private because they should NEVER be used
    GameState(const GameState &other);
    GameState &operator=(const GameState &state){
        return *this;
    }
    
protected:
    static vector<unique_ptr<GameState>> states;
    static int currentState;
    //This needs to be here for the derived classed
    GameState(){};
    
public:
    static void addGameState(GameState* state) {states.push_back(unique_ptr<GameState> (state)); };
    static void setState(int newState){ currentState = newState;};
    static GameState* getCurrentState(){ return states[currentState].get();};
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void handleClick(int x, int y) = 0;

};


#endif /* GameState_hpp */
