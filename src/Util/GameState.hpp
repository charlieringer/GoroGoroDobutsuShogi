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
#define INSTRUCTIONS 2
#define GAME 3
#define GAMEOVERLOSE 4
#define GAMEOVERWIN 5

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
    //This contains all of our game states
    static vector<shared_ptr<GameState>> states;
    //And this tracks which of our games states is the current one
    static int currentState;
    //This needs to be here for the derived classed
    GameState(){};
    
public:
    static void addGameState(GameState* state) {states.push_back(unique_ptr<GameState> (state)); };
    //Sets the state to a passed in value
    static void setState(int newState){
        assert(newState < states.size());
        currentState = newState;
    };
    //Returns a shared pointer to the current state.
    //This is shared in the hopes that it shows ownership of this data.
    //Therefore noone will get the raw pointer and try to delete it.
    static shared_ptr<GameState> getCurrentState(){ return states[currentState];};
    
    //All game states must be able to do the following (or at least have them defined if they are empty)
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void handleClick(int x, int y) = 0;

};


#endif /* GameState_hpp */
