//
//  AIValues.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 17/03/2016.
//
//

#ifndef AIValues_hpp
#define AIValues_hpp

#include <stdio.h>

class AIValues
{
private:
    //Static data
    static int numbItters;
    static float exploreConst;
    
public:
    //Returns the current AI values
    static int getNumIterations(){ return numbItters;};
    static float getExploreConstant(){ return exploreConst;};
    
    //Sets them to a given number
    static void setNumIterations(int newItters){ numbItters = newItters;};
    static void setExploreConstant(float newConst){ exploreConst = newConst;};
    
    //Increments the values (within a given bound)
    static void incrementNumIterations(){ if(numbItters< 2000) numbItters+=50;}
    static void incrementExploreConstant(){ if(exploreConst < 2) exploreConst+=0.1;}
    
    //Decrements the values (within a given bound)
    static void decrementNumIterations(){ if (numbItters >50) numbItters-=50;}
    static void decrementExploreConstant(){ if (exploreConst> 0.1) exploreConst-=0.1;}
    
};
#endif /* AIValues_hpp */
