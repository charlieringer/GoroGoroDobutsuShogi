//
//  Button.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 27/02/2016.
//
//

#include "Button.hpp"
//Constructor
Button::Button(int _x, int _y, int _w, int _h, string imgPath, shared_ptr<ImageBank>& imgBank): x(_x), y(_y), w(_w), h(_h)
{
    dispImage = imgBank->loadImage(imgPath);
}

//Copy constructor
Button::Button(const Button& other): x(other.x), y(other.y), w(other.w), h(other.h), dispImage(other.dispImage){}

//The button does not own the image (the image bank does) so nothing needs deleting.
Button::~Button(){}

void Button::draw()
{
    //draws the image
    dispImage->draw(x,y);
}

bool Button::clicked(int mX, int mY)
{
    //returns true if the mouse is inside of the button
    return mX > x && mX < x+w && mY > y && mY < y+h;
}