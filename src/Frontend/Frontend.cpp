//
//  Frontend.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 23/02/2016.
//
//

#include "Frontend.hpp"
#include "Button.hpp"

Frontend::Frontend(shared_ptr<ImageBank> _imgBank):
    //title is not clickable so H/W is 0,0
    title(0,100, 0,0, "Buttons/Title.png", _imgBank),
    play(71, 250, 300, 64, "Buttons/play.png", _imgBank),
    aiSettings(71, 375, 300, 72, "Buttons/settings.png", _imgBank),
    instructions(71, 450, 300, 72, "Buttons/inst.png", _imgBank)
{
    background = _imgBank->loadImage("Backgrounds/frontendbackground.jpg");
}

//Only pointer is an image (which we do not own) so nothing to delete.
Frontend::~Frontend(){}

Frontend::Frontend(const Frontend& other): background(other.background), title(other.title), play(other.play),aiSettings(other.aiSettings), instructions(other.instructions){}

void Frontend::draw()
{
    //Draws the background and all the buttons
    background->draw(0,0);
    title.draw();
    play.draw();
    aiSettings.draw();
    instructions.draw();
}

void Frontend::handleClick(int x, int y)
{
    //we check which button was clicked and update the state accordingly
    if(play.clicked(x,y))
        GameState::setState(GAME);
    else if(aiSettings.clicked(x,y))
        GameState::setState(AISETTINGS);
    else if(instructions.clicked(x,y))
        GameState::setState(INSTRUCTIONS);
    
}
