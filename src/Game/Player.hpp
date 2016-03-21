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
    shared_ptr<ImageBank> imgBank = nullptr;
    bool ai;
public:
    Player(bool isAI);
    Player(const Player &player);
    virtual ~Player();
    virtual bool isAI() = 0;
    shared_ptr<ImageBank> getImageBank() const{ return imgBank;};
    vector<shared_ptr<GamePiece>>& getBankRef() { return bank;};
    vector<shared_ptr<GamePiece>> getBankConst() const { return bank;};
    virtual void addToBank(PieceType type) = 0;
    void clearBank(){ bank.clear();};
    virtual shared_ptr<Player> clonePlayer() = 0;
};

class HumanPlayer: public Player
{
private:
    
public:
    HumanPlayer(shared_ptr<ImageBank> imgBank);
    HumanPlayer( const HumanPlayer &HumanPlayer);
    virtual ~HumanPlayer();
    void addToBank(PieceType type);
    bool isAI(){ return ai; };
    virtual shared_ptr<Player>  clonePlayer();
    
    
};

class AIPlayer: public Player
{
public:
    AIPlayer(shared_ptr<ImageBank> imgBank);
    AIPlayer( const AIPlayer &player);
    virtual ~AIPlayer();
    void addToBank(PieceType type);
    bool isAI(){ return ai; };
    virtual shared_ptr<Player> clonePlayer();
    
};

#endif /* Player_hpp */
