//
//  GameState.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/03/2016.
//
//

#ifndef GameState_hpp
#define GameState_hpp

#include <stdio.h>
#include "ofMain.h"
using namespace std;

class GameState
{
private:
    //Private because they should NEVER be used
    GameState(const GameState &other);
    GameState &operator=(const GameState &gs){
        return *this;
    }
    
protected:
    
    static vector<unique_ptr<GameState>> states;
    static int currentState;

    
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
