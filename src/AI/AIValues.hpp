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
    static int numbItters;
    static float exploreConst;
    
public:
    static int getNumIterations(){ return numbItters;};
    static float getExploreConstant(){ return exploreConst;};
    
    static void setNumIterations(int newItters){ numbItters = newItters;};
    static void setExploreConstant(float newConst){ exploreConst = newConst;};
    
    static void incrementNumIterations(){ if(numbItters< 3000) numbItters+=100;}
    static void incrementExploreConstant(){ if(exploreConst < 2) exploreConst+=0.2;}
    
    static void decrementNumIterations(){ if (numbItters >100) numbItters-=100;}
    static void decrementExploreConstant(){ if (exploreConst> 0.2) exploreConst-=0.2;}
    
};
#endif /* AIValues_hpp */
