//
//  Frontend.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 23/02/2016.
//
//

#include "Frontend.hpp"
#include "Button.hpp"

Frontend::Frontend(shared_ptr<ImageBank> _imgBank)
{
    imgBank = _imgBank;
    background = imgBank->loadImage("Backgrounds/frontendbackground.jpg");
    //not cliackable
    title  = Button(0,100, 0,0, "title", "Buttons/Title.png", imgBank);
    play = Button(71, 250, 300, 64, "play", "Buttons/play.png", imgBank);
    aiSettings =  Button(71, 375, 300, 72, "settings","Buttons/settings.png", imgBank);
    
}

Frontend::Frontend(const Frontend& other)
{
    imgBank = other.imgBank;
    background = imgBank->loadImage("Backgrounds/Background.jpg");
    title  = Button(0,100, 100,100, "title", "Buttons/Title.png", imgBank);
    play = Button(0, 300, 442, 94, "play", "Buttons/play.png", imgBank);
    aiSettings =  Button(71, 375, 300, 72, "settings","Buttons/settings.png", imgBank);
}

void Frontend::draw()
{
    background->draw(0,0);
    title.draw();
    play.draw();
    aiSettings.draw();
}

void Frontend::handleClick(int x, int y)
{
    if(play.clicked(x,y))
        GameState::setState(GAME);
}
