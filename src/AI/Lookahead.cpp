//
//  Move.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 01/03/2016.
//
//

#include "Lookahead.hpp"
#include "BlankPiece.hpp"
#include "HenPiece.hpp"
#include "GiraffePiece.hpp"
#include "ElephantPiece.hpp"
#include "ChickPiece.hpp"

Lookahead::Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2, Lookahead* _parent, int _depthLevel): parent(_parent), gameboard(_gameboard), player1(_player1), player2(_player2), depthLevel(_depthLevel)
{
    assert(_gameboard.size()==12);
    depthLevel = _depthLevel;
    isTerminal = checkTerminality();
    if (isTerminal)
    {
       parent->addChildWin(); 
    }
    else
    {
       if(depthLevel < 12)
       {
           cout << depthLevel <<endl;
         generateChildren();
       }
    }
}

Lookahead::Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2): depthLevel(0)
{
    assert(_gameboard.size()==12);
    player1 = _player1->clonePlayer();
    player2 = _player2->clonePlayer();
    gameboard = copyGameBoard(_gameboard, player1, player2);
    if (depthLevel == 0)
        generateChildren();
}

Lookahead::~Lookahead()
{
  //  delete player1;
   // delete player2;
}

void Lookahead::generateChildren()
{
    for (int i = 0; i < gameboard.size(); i++)
    {
        if(gameboard[i]->getOwner() == player1)
        {
            GamePiecePtr movingPiece = gameboard[i];
            int thisX = movingPiece->getX();
            int thisY = movingPiece->getY();
            
            for(int j = 0; j < gameboard.size(); j++)
            {
                GamePiecePtr targetPosPiece = gameboard[j];
                int targetX = targetPosPiece->getX();
                int targetY = targetPosPiece->getY();
                
                if(targetPosPiece->getOwner() == player1) continue;
                else if(!movingPiece->canMove(targetX,targetY)) continue;
                
                else if (targetPosPiece->getType() == PieceType::BLANK)
                {
                    Player* cloneOf1 = player1->clonePlayer();
                    Player* cloneOf2 = player2->clonePlayer();
                    vector<GamePiecePtr> boardClone = copyGameBoard(gameboard, cloneOf1, cloneOf2);
                    GamePiecePtr clonedCurrentPiece = boardClone[i];
                    GamePiecePtr clonedTargetPiece = boardClone[j];
                    clonedCurrentPiece->moveTo(targetX, targetY);
                    clonedTargetPiece->moveTo(thisX, thisY);
                    //check for promotion
                    if(clonedCurrentPiece->getType() == PieceType::CHICK &&
                       ((clonedCurrentPiece->getOwner()->isAI() && clonedCurrentPiece->getY() == 3)
                        || (!(clonedCurrentPiece->getOwner()->isAI()) && clonedCurrentPiece->getY() == 0)))
                    {
                        //And promote if needed
                        simulatePromotion(boardClone, clonedCurrentPiece, cloneOf1);
                    }
                    assert(boardClone.size()==12);
                    children.push_back(Lookahead(boardClone, cloneOf2, cloneOf1, this, ++depthLevel));
                } else {
                    //Remove captured piece and replace capturing piece with blank piece.
                    Player* cloneOf1 = player1->clonePlayer();
                    Player* cloneOf2 = player2->clonePlayer();
                    vector<GamePiecePtr> boardClone = copyGameBoard(gameboard, cloneOf1, cloneOf2);
                    GamePiecePtr clonedCurrentPiece = boardClone[i];
                    GamePiecePtr clonedTargetPiece = boardClone[j];

                    cloneOf1->addToBank(clonedTargetPiece->getType());
                   
                    boardClone.push_back(make_shared<BlankPiece>(clonedCurrentPiece->getX(), clonedCurrentPiece->getY()));
                    clonedCurrentPiece->moveTo(clonedTargetPiece->getX(), clonedTargetPiece->getY());
                    boardClone.erase(boardClone.begin() + j);
                    
                    //check for promotion
                    if(clonedCurrentPiece->getType() == PieceType::CHICK &&
                       ((clonedCurrentPiece->getOwner()->isAI() && clonedCurrentPiece->getY() == 3)
                        || (!(clonedCurrentPiece->getOwner()->isAI())&& clonedCurrentPiece->getY() == 0)))
                    {
                        //And promote if needed
                        simulatePromotion(boardClone, clonedCurrentPiece, cloneOf1);
                    }
                    assert(boardClone.size()==12);
                    children.push_back(Lookahead(boardClone, cloneOf2, cloneOf1, this, ++depthLevel));
                }
            }
        }
    }
    vector<GamePiecePtr> playerBank = player1->getBankRef();
    for(int i = 0; i < playerBank.size(); i++)
    {
        for(GamePiecePtr boardPiece : gameboard)
        {
            if (boardPiece->getType() != PieceType::BLANK) continue;
            Player* cloneOf1 = player1->clonePlayer();
            Player* cloneOf2 = player2->clonePlayer();
            vector<GamePiecePtr> copyBoard = copyGameBoard(gameboard, cloneOf1, cloneOf2);
            simulateDroppedPiece(copyBoard, cloneOf1->getBankRef()[i], cloneOf1, boardPiece->getX(), boardPiece->getY());
            assert(copyBoard.size()==12);
            children.push_back(Lookahead(copyBoard, cloneOf1, cloneOf2, this, ++depthLevel));
        }
        
    }
}

void Lookahead::simulateDroppedPiece(vector<GamePiecePtr> &board, GamePiecePtr piece, Player* owner, int x,int y)
{
    assert(board.size()==12);
    board.erase(
                std::remove_if(board.begin(), board.end(),
                               [x,y](GamePiecePtr thisPiece)
                               { return thisPiece->getX() == x && thisPiece->getY() == y; })
                );
    assert(board.size()==11);
    if(piece->getType() == PieceType::CHICK)
        board.push_back(make_shared<ChickPiece>(x, y, owner));
    else if(piece->getType() == PieceType::GIRAFFE)
        board.push_back(make_shared<GiraffePiece>(x, y, owner));
    else if(piece->getType() == PieceType::ELEPHANT)
        board.push_back(make_shared<ElephantPiece>(x, y, owner));
    assert(board.size()==12);
    int removeX = piece->getX();
    int removeY = piece->getY();
    vector<shared_ptr<GamePiece>>& bank = owner->getBankRef();
    bank.erase( std::remove_if(bank.begin(), bank.end(), [removeX,removeY](GamePiecePtr thisPiece)
                               { return thisPiece->getX() == removeX && thisPiece->getY() == removeY; }) );
    
}

void Lookahead::simulatePromotion(vector<GamePiecePtr> &board, GamePiecePtr piece, Player* owner)
{
    //Turns a piece into a hen
    int x = piece->getX();
    int y = piece->getY();
    board.erase(
                    std::remove_if(board.begin(), board.end(),
                                   [x,y](GamePiecePtr thisPiece)
                                   { return thisPiece->getX() == x && thisPiece->getY() == y; })
                    );
    board.push_back(make_shared<HenPiece>(x,y, owner));
}

//This checks whether a lookahead is terminal or not
bool Lookahead::checkTerminality()
{
    //We only care about a capture on player1 as player2 played last turn and you can only win on your turn not lose
    bool player1HasLion = false;
    for(GamePiecePtr &gamePiece : gameboard)
    {
        if(gamePiece)
        {
            if(gamePiece->getType() == PieceType::LION)
            {
                if (gamePiece->getOwner() == player2)
                {
                    if ((gamePiece->getY() == 0 && !(gamePiece->getOwner()->isAI())) ||
                        (gamePiece->getY() == 3 && gamePiece->getOwner()->isAI()) )
                    {
                        return true;
                    }
                } else if (gamePiece->getOwner() == player1)
                {
                    player1HasLion = true;
                }
            }
        }
    }
    if(!player1HasLion)
    {
        return true;
    }
    return false;
}

//This just copies a game board and returns it (ready for experiementation)
vector<GamePiecePtr> Lookahead::copyGameBoard(vector<GamePiecePtr> initalBoard, Player* p1, Player* p2)
{
    vector<GamePiecePtr> returnBoard;
    
    for(GamePiecePtr piece : initalBoard)
    {
        GamePiecePtr newPiece = piece->clone();
        if(newPiece->getOwner())
        {
            if(newPiece->getOwner()->isAI() == p1->isAI())
            {
                newPiece->setOwner(p1);
            } else {
                newPiece->setOwner(p2);
            }
        }
        returnBoard.push_back(newPiece);
    }
    assert(returnBoard.size()==12);
    return returnBoard;
}


