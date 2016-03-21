//
//  AISettings.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 16/03/2016.
//
//

#include "AISettings.hpp"
#include "AIValues.hpp"


AISettings::AISettings(shared_ptr<ImageBank> imgBank):
    back(0,550,100,39, "Buttons/back.png", imgBank),
    title(71,0,0,0, "Buttons/settings.png", imgBank),
    rArrowItt(342,200,50,50, "Buttons/rightarrow.png", imgBank),
    lArrowItt(50,200,50,50, "Buttons/leftarrow.png", imgBank),
    rArrowExp(342,400,50,50, "Buttons/rightarrow.png", imgBank),
    lArrowExp(50,400,50,50, "Buttons/leftarrow.png", imgBank)
{
    background = imgBank->loadImage("Backgrounds/frontendbackground.jpg");
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 18);
    assert(fontLoaded);
}

AISettings::AISettings(const AISettings& other): back(other.back), title(other.title), rArrowItt(other.rArrowItt),
    lArrowItt(other.lArrowItt), rArrowExp(other.rArrowExp), lArrowExp(other.lArrowExp), background(other.background)
{
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 18);
    assert(fontLoaded);
}

AISettings::~AISettings(){}

void AISettings::draw()
{
    //Draws backgrounds and buttons
    background->draw(0,0);
    title.draw();
    back.draw();
    rArrowItt.draw();
    lArrowItt.draw();
    rArrowExp.draw();
    lArrowExp.draw();
    
    //We want to resize the explore weight to cut off unneeded 0s
    string exploreWeight = to_string(AIValues::getExploreConstant());
    if (AIValues::getExploreConstant() < 10)
    {
        exploreWeight.resize(3);
    } else {
        exploreWeight.resize(4);
    }
    //Draws the current settings
    dispFont.drawString("Number of iterations:", 90, 170);
    dispFont.drawString(to_string(AIValues::getNumIterations()), 200, 230);
    dispFont.drawString("Explore weighting:", 100, 370);
    dispFont.drawString(exploreWeight, 210, 430);

}

void AISettings::handleClick(int x,int y)
{
    //Handles the click and responds accordingly
    if (rArrowItt.clicked(x,y))
        AIValues::incrementNumIterations();
    else if (lArrowItt.clicked(x,y))
        AIValues::decrementNumIterations();
    else if (rArrowExp.clicked(x,y))
        AIValues::incrementExploreConstant();
    else if (lArrowExp.clicked(x,y))
        AIValues::decrementExploreConstant();
    else if(back.clicked(x,y))
        GameState::setState(FRONTEND);
}