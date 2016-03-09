//
//  Frontend.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 23/02/2016.
//
//

#include "Frontend.hpp"

Frontend::Frontend(State& _state, shared_ptr<ImageBank> _imgBank)
{
    state = &_state;
    imgBank = _imgBank;
    background = imgBank->loadImage("Background.jpg");
    title  = imgBank->loadImage("Title.png");
    playbutton  = imgBank->loadImage("play.png");
    
}

Frontend::Frontend(const Frontend& other)
{
    state = other.state;
    imgBank = other.imgBank;
    background = imgBank->loadImage("Background.jpg");
    title  = imgBank->loadImage("Title.png");
    playbutton  = imgBank->loadImage("play.png");
}

void Frontend::drawFrontend()
{
    background->draw(0,0);
    title->draw(0,100);
    playbutton->draw(0,300);
}

void Frontend::handleClick()
{
    *state = INGAME;
}
