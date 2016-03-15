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
    background = imgBank->loadImage("frontendbackground.jpg");
    title  = Button(0,100, 100,100, "title", "Title.png", imgBank);
    play = Button(0, 300, 442, 94, "play", "play.png", imgBank);
    
}

Frontend::Frontend(const Frontend& other)
{
    imgBank = other.imgBank;
    background = imgBank->loadImage("Background.jpg");
    title  = Button(0,100, 100,100, "title", "Title.png", imgBank);
    play = Button(0, 300, 442, 94, "play", "play.png", imgBank);
}

void Frontend::draw()
{
    background->draw(0,0);
    title.draw();
    play.draw();
    //playbutton->draw(0,300);
}

void Frontend::handleClick(int x, int y)
{
    if(play.clicked(x,y))
        GameState::setState(1);
}
