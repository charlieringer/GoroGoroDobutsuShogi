//
//  GameState.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/03/2016.
//
//

#include "GameState.hpp"

vector<shared_ptr<GameState> > GameState::states;

int GameState::currentState = -1;