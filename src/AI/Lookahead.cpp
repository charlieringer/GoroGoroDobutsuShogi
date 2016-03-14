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
#include <thread>

Lookahead::Lookahead(vector<GamePiecePtr>& _gameboard, shared_ptr<Player> _player1, shared_ptr<Player> _player2, Lookahead* _parent, int _depthLevel): parent(_parent), gameboard(_gameboard), player1(_player1), player2(_player2), depthLevel(_depthLevel)
{
    assert(_gameboard.size()==12);
    isTerminal = checkTerminality();
}

Lookahead::Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2): depthLevel(0), parent(nullptr)
{
    assert(_gameboard.size()==12);
    player1 = _player1->clonePlayer();
    player2 = _player2->clonePlayer();
    gameboard = copyGameBoard(_gameboard, player1, player2);
    children = generateChildren();
    isTerminal = checkTerminality();
}

Lookahead::~Lookahead()
{
   //delete player1;
   //delete player2;
}

vector<Lookahead> Lookahead::generateChildren()
{
    vector<Lookahead> returnChildren;
    for (int i = 0; i < gameboard.size(); i++)
    {
        assert(player1);
        if(gameboard[i]->getOwner() == player1.get())
        {
            GamePiecePtr movingPiece = gameboard[i];
            int thisX = movingPiece->getX();
            int thisY = movingPiece->getY();
            
            for(int j = 0; j < gameboard.size(); j++)
            {
                GamePiecePtr targetPosPiece = gameboard[j];
                int targetX = targetPosPiece->getX();
                int targetY = targetPosPiece->getY();
                
                if(targetPosPiece->getOwner() == player1.get()) continue;
                else if(!movingPiece->canMove(targetX,targetY)) continue;
                
                else if (targetPosPiece->getType() == PieceType::BLANK)
                {
                    shared_ptr<Player> cloneOf1 = player1->clonePlayer();
                    shared_ptr<Player> cloneOf2 = player2->clonePlayer();
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
                    assert(cloneOf1);
                    assert(cloneOf2);
                    assert(boardClone.size()==12);
                    returnChildren.push_back(Lookahead(boardClone, cloneOf2, cloneOf1, this, depthLevel+1));
                } else {
                    //Remove captured piece and replace capturing piece with blank piece.
                    shared_ptr<Player> cloneOf1 = player1->clonePlayer();
                    shared_ptr<Player> cloneOf2 = player2->clonePlayer();
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
                    assert(cloneOf1);
                    assert(cloneOf2);
                    assert(boardClone.size()==12);
                    returnChildren.push_back(Lookahead(boardClone, cloneOf2, cloneOf1, this, depthLevel+1));
                }
            }
        }
    }
    vector<GamePiecePtr> playerBank = player1->getBankRef();
    for(int i = 0; i < playerBank.size(); i++)
    {
        for(GamePiecePtr& boardPiece : gameboard)
        {
            if (boardPiece->getType() != PieceType::BLANK) continue;
            shared_ptr<Player> cloneOf1 = player1->clonePlayer();
            shared_ptr<Player> cloneOf2 = player2->clonePlayer();
            vector<GamePiecePtr> copyBoard = copyGameBoard(gameboard, cloneOf1, cloneOf2);
            if(cloneOf1->getBankRef().size() > i)
            {
                simulateDroppedPiece(copyBoard, cloneOf1->getBankRef()[i], cloneOf1, boardPiece->getX(), boardPiece->getY());
                assert(cloneOf1);
                assert(cloneOf2);
                assert(copyBoard.size()==12);
                returnChildren.push_back(Lookahead(copyBoard, cloneOf1, cloneOf2, this, depthLevel+1));
            }
        }
        
    }
    return returnChildren;
}

void Lookahead::simulateDroppedPiece(vector<GamePiecePtr> &board, GamePiecePtr piece, shared_ptr<Player> owner, int x,int y)
{
    if(!piece) return;
    assert(board.size()==12);
    board.erase(
                std::remove_if(board.begin(), board.end(),
                               [x,y](GamePiecePtr thisPiece)
                               { return thisPiece->getX() == x && thisPiece->getY() == y; })
                );
    assert(board.size()==11);
    if(piece->getType() == PieceType::CHICK)
        board.push_back(make_shared<ChickPiece>(x, y, owner.get()));
    else if(piece->getType() == PieceType::GIRAFFE)
        board.push_back(make_shared<GiraffePiece>(x, y, owner.get()));
    else if(piece->getType() == PieceType::ELEPHANT)
        board.push_back(make_shared<ElephantPiece>(x, y, owner.get()));
    else
        board.push_back(make_shared<BlankPiece>(x,y));
    assert(board.size()==12);
    int removeX = piece->getX();
    int removeY = piece->getY();
    vector<shared_ptr<GamePiece>>& bank = owner->getBankRef();
    int currBankSize = bank.size();
    bank.erase( std::remove_if(bank.begin(), bank.end(), [removeX,removeY](GamePiecePtr thisPiece)
                               { return thisPiece->getX() == removeX && thisPiece->getY() == removeY; }) );
    assert(bank.size() == currBankSize-1);
    
}

void Lookahead::simulatePromotion(vector<GamePiecePtr> &board, GamePiecePtr piece, shared_ptr<Player> owner)
{
    //Turns a piece into a hen
    int x = piece->getX();
    int y = piece->getY();
    board.erase(
                    std::remove_if(board.begin(), board.end(),
                                   [x,y](GamePiecePtr thisPiece)
                                   { return thisPiece->getX() == x && thisPiece->getY() == y; })
                    );
    board.push_back(make_shared<HenPiece>(x,y, owner.get()));
}

//This checks whether a lookahead is terminal or not
bool Lookahead::checkTerminality()
{
    //We only care about a capture on player1 as player2 played last turn and you can only win on your turn not lose
    bool player1HasLion = false;
    bool player2HasLion = false;
    for(GamePiecePtr &gamePiece : gameboard)
    {
        if(gamePiece)
        {
            if(gamePiece->getType() == PieceType::LION)
            {
                if (gamePiece->getOwner() == player2.get())
                {
                    player2HasLion = true;
                    if ((gamePiece->getY() == 0 && !(gamePiece->getOwner()->isAI())) ||
                        (gamePiece->getY() == 3 && gamePiece->getOwner()->isAI()) )
                    {
                        return true;
                    }
                } else if (gamePiece->getOwner() == player1.get())
                {
                    player1HasLion = true;
                }
            }
        }
    }
    if(!player2HasLion)
    {
        return true;
    }
   // assert(player2HasLion);
    if(!player1HasLion)
    {
        return true;
    }
    return false;
}

//This just copies a game board and returns it (ready for experiementation)
vector<GamePiecePtr> Lookahead::copyGameBoard(vector<GamePiecePtr> initalBoard, shared_ptr<Player> p1, shared_ptr<Player> p2)
{
    vector<GamePiecePtr> returnBoard;
    
    for(GamePiecePtr piece : initalBoard)
    {
        GamePiecePtr newPiece = piece->clone();
        if(newPiece->getOwner())
        {
            if(newPiece->getOwner()->isAI() == p1->isAI())
            {
                newPiece->setOwner(p1.get());
            } else {
                newPiece->setOwner(p2.get());
            }
        }
        returnBoard.push_back(newPiece);
    }
    assert(returnBoard.size()==12);
    return returnBoard;
}

void Lookahead::randomPlayOut()
{
    if (checkTerminality())
    {
        games++;
        wins++;
        parent->addLoss();
        return;
    }
    //We randomly playout till we reach a terminal state
    bool terminalStateFound = false;
    
    //This are the potential moves
    assert(player1);
    assert(player2);
    vector<Lookahead> playOutChildren = generateChildren();
    //Of which we are selecting a random one
    if(playOutChildren.size() == 0) return;
    int randomIndex = rand()%playOutChildren.size();
    if(playOutChildren[randomIndex].checkTerminality())
    {
        games++;
        wins++;
        parent->addLoss();
        return;
    }
    
    //These are the moves we have looked at (so we are going to build a list which will represent the entire played out game)
    vector<Lookahead> evaluatedMoves;
    //We add the first random child to it
    evaluatedMoves.push_back(playOutChildren[randomIndex]);

    //While we have not found a termina state
    while(!terminalStateFound)
    {
        //We continue
        if(evaluatedMoves[evaluatedMoves.size()-1].terminal())
        {
            if(evaluatedMoves.size()%2 == 0)
            {
                games++;
                losses++;
                parent->addWin();
            }
            else
            {
                games++;
                wins++;
                parent->addLoss();
            }
            terminalStateFound = true;
        } else {
            vector<Lookahead> playOutChildren = evaluatedMoves[evaluatedMoves.size()-1].generateChildren();
            if (evaluatedMoves[evaluatedMoves.size()-1].getDepth() > 16) //78
            {
                games++;
               return;
            }
            randomIndex = rand()%playOutChildren.size();
            evaluatedMoves.push_back(playOutChildren[randomIndex]);
        }
    }
    
}
