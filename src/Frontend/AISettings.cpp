//
//  AISettings.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 16/03/2016.
//
//

#include "AISettings.hpp"
#include "AIValues.hpp"


AISettings::AISettings(shared_ptr<ImageBank> imgBank)
{
    background = imgBank->loadImage("Backgrounds/frontendbackground.jpg");
    back = Button(0,550,100,39, "back", "Buttons/back.png", imgBank);
    title = Button(71,0,0,0, "title", "Buttons/settings.png", imgBank);
    rArrowItt = Button(342,200,50,50, "rArrowItt", "Buttons/rightarrow.png", imgBank);
    lArrowItt = Button(50,200,50,50, "rArrowItt", "Buttons/leftarrow.png", imgBank);
    rArrowExp = Button(342,400,50,50, "rArrowItt", "Buttons/rightarrow.png", imgBank);
    lArrowExp = Button(50,400,50,50, "rArrowItt", "Buttons/leftarrow.png", imgBank);
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 18);
    assert(fontLoaded);
}

void AISettings::draw()
{
    background->draw(0,0);
    title.draw();
    back.draw();
    rArrowItt.draw();
    lArrowItt.draw();
    rArrowExp.draw();
    lArrowExp.draw();
    
    string exploreWeight = to_string(AIValues::getExploreConstant());
    if (AIValues::getExploreConstant() < 10)
    {
        exploreWeight.resize(3);
    } else {
        exploreWeight.resize(4);
    }
    
    dispFont.drawString("Number of iterations:", 90, 170);
    dispFont.drawString(to_string(AIValues::getNumIterations()), 200, 230);
    dispFont.drawString("Explore weighting:", 100, 370);
    dispFont.drawString(exploreWeight, 210, 430);

}

void AISettings::handleClick(int x,int y)
{
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