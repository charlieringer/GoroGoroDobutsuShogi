//
//  Button.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 27/02/2016.
//
//

#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ImageBank.hpp"

class Button
{
private:
    //XY for top left corner
    int x;
    int y;
    //Height and width
    int h;
    int w;
    ofImage* dispImage;
public:
    Button(int _x, int _y, int _w, int _h, string imgPath, shared_ptr<ImageBank>& imgBank);
    Button(const Button& other);
    ~Button();

    void draw();
    bool clicked(int mX, int mY);
};

#endif /* Button_hpp */
