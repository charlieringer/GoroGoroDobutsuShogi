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
    background = _imgBank->loadImage("Background.jpg");
    bool fontLoaded = dispFont.load("CHOWFUN_.TTF", 42);
    assert(fontLoaded);
}
void GameOver::display(){}

GameOverWin::GameOverWin(shared_ptr<ImageBank> _imgBank): GameOver(_imgBank)
{
    
}

void GameOverWin:: display()
{
    background->draw(0,0);
    dispFont.drawString("You won!", 100, 100);
}

GameOverLose::GameOverLose(shared_ptr<ImageBank> _imgBank): GameOver(_imgBank)
{
    
}

void GameOverLose:: display()
{
    background->draw(0,0);
    dispFont.drawString("You lost!", 100, 100);
}