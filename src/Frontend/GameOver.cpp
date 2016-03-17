//
//  GameOver.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 28/02/2016.
//
//

#include "GameOver.hpp"

GameOver::GameOver(shared_ptr<ImageBank>& _imgBank)
{
    background = _imgBank->loadImage("Backgrounds/frontendbackground.jpg");
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 42);
    assert(fontLoaded);
    playAgain = Button(71,250,300,74, "playagain", "Buttons/playagain.png", _imgBank);
    mainMenu = Button(71,375,300,59, "mainmenu", "Buttons/mainmenu.png", _imgBank);
}

void GameOver::draw()
{
   background->draw(0,0);
   playAgain.draw();
   mainMenu.draw();
}

void GameOver::handleClick(int x, int y)
{
    if(playAgain.clicked(x,y))
    {
        GameState::setState(GAME);
    } else if (mainMenu.clicked(x,y))
    {
        GameState::setState(FRONTEND);
    }
}

GameOverWin::GameOverWin(shared_ptr<ImageBank>& _imgBank): GameOver(_imgBank)
{
}



void GameOverWin::draw()
{
    GameOver::draw();
    dispFont.drawString("You won!", 100, 100);
}

GameOverLose::GameOverLose(shared_ptr<ImageBank>& _imgBank): GameOver(_imgBank)
{
    
}

void GameOverLose::draw()
{
    GameOver::draw();
    dispFont.drawString("You lost!", 100, 100);
}