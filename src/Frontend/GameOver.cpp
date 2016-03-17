//
//  GameOver.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 28/02/2016.
//
//

#include "GameOver.hpp"

GameOver::GameOver(shared_ptr<ImageBank> _imgBank)
{
    background = _imgBank->loadImage("Backgrounds/frontendbackground.jpg");
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 42);
    assert(fontLoaded);
}

GameOverWin::GameOverWin(shared_ptr<ImageBank> _imgBank): GameOver(_imgBank)
{
    
}

void GameOverWin::draw()
{
    background->draw(0,0);
    dispFont.drawString("You won!", 100, 100);
}

GameOverLose::GameOverLose(shared_ptr<ImageBank> _imgBank): GameOver(_imgBank)
{
    
}

void GameOverLose::draw()
{
    background->draw(0,0);
    dispFont.drawString("You lost!", 100, 100);
}