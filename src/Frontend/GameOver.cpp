//
//  GameOver.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 28/02/2016.
//
//

#include "GameOver.hpp"

GameOver::GameOver(shared_ptr<ImageBank>& _imgBank):
    playAgain(71,250,300,74, "Buttons/playagain.png", _imgBank),
    mainMenu(71,375,300,59, "Buttons/mainmenu.png", _imgBank)
{
    background = _imgBank->loadImage("Backgrounds/frontendbackground.jpg");
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 42);
    assert(fontLoaded);
}

GameOver::GameOver(const GameOver& other): background(other.background),playAgain(other.playAgain), mainMenu(other.mainMenu)
{
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 42);
    assert(fontLoaded);
}

GameOver::~GameOver(){}

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

//------WIN SCREEN --------------

GameOverWin::GameOverWin(shared_ptr<ImageBank>& _imgBank): GameOver(_imgBank){}
GameOverWin::GameOverWin(const GameOverWin& other): GameOver(other){}
GameOverWin::~GameOverWin(){}



void GameOverWin::draw()
{
    //Draws the super class
    GameOver::draw();
    //And then displays specific info
    dispFont.drawString("You won!", 100, 100);
}

//------LOSE SCREEN --------------

GameOverLose::GameOverLose(shared_ptr<ImageBank>& _imgBank): GameOver(_imgBank){}
GameOverLose::GameOverLose(const GameOverLose& other): GameOver(other){}
GameOverLose::~GameOverLose(){}

void GameOverLose::draw()
{
    //Draws the super class
    GameOver::draw();
    //And then displays specific info
    dispFont.drawString("You lost!", 100, 100);
}