//
//  Instructions.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 17/03/2016.
//
//

#include "Instructions.hpp"


Instructions::Instructions(shared_ptr<ImageBank> imgBank)
{
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 18);
    assert(fontLoaded);
    background = imgBank->loadImage("Backgrounds/frontendbackground.jpg");
    title = Button(71,0,0,0, "title", "Buttons/inst.png", imgBank);
    back = Button(0,550,100,39, "back", "Buttons/back.png", imgBank);
}

void Instructions::draw()
{
    background->draw(0,0);
    title.draw();
    back.draw();
    dispFont.drawString("To Win:", 10, 100);
    dispFont.drawString("Capture the opposing Lion", 10, 140);
    dispFont.drawString("or get yours to the other side.", 10, 180);
    dispFont.drawString("Each turn chose a piece to move", 10, 260);
    dispFont.drawString("or a piece you captured to drop", 10, 300);
    dispFont.drawString("onto the board.", 10, 340);
    dispFont.drawString("The dots on each piece show how", 10, 420);
    dispFont.drawString("they move.", 10, 460);
    dispFont.drawString("And if you get your chick to", 10, 500);
    dispFont.drawString("the end it grows into a hen!", 10, 540);
}

void Instructions::handleClick(int x, int y)
{
    if(back.clicked(x,y))
        GameState::setState(FRONTEND);
}