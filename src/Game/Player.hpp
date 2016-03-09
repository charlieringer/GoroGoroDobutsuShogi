//
//  Player.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/02/2016.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <vector>

using namespace std;

#include "ImageBank.hpp"

//Forward declaration of game piece
class GamePiece;


enum class PieceType;


class Player
{
protected:
    vector<shared_ptr<GamePiece>> bank;
    shared_ptr<ImageBank> imgBank;
public:
    Player();
    Player(const Player &player);
    ~Player();
    virtual bool isAI(){};
    shared_ptr<ImageBank> getImageBank() const{ return imgBank;};
    vector<shared_ptr<GamePiece>>& getBankRef() { return bank;};
    vector<shared_ptr<GamePiece>> getBankConst() const { return bank;};
    virtual void addToBank(PieceType type);
};

class HumanPlayer: public Player
{
private:
    
public:
    HumanPlayer(shared_ptr<ImageBank> imgBank);
    HumanPlayer( const HumanPlayer &HumanPlayer);
    void addToBank(PieceType type);
    bool isAI(){ return false; };
    
    
};

class AIPlayer: public Player
{
public:
    AIPlayer(shared_ptr<ImageBank> imgBank);
    AIPlayer( const AIPlayer &player);
    void addToBank(PieceType type);
    bool isAI(){ return true; };
    
};

#endif /* Player_hpp */
