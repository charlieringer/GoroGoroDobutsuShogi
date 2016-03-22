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

//Constuctor for the top level lookahead (when constucted from a real game)
Lookahead::Lookahead(vector<GamePiecePtr>& _gameboard, shared_ptr<Player> _player1, shared_ptr<Player> _player2, Lookahead* _parent, int _depthLevel): parent(_parent), gameboard(_gameboard), player1(_player1), player2(_player2), depthLevel(_depthLevel)
{
    assert(_gameboard.size()==12);
    isTerminal = checkTerminality();
}

//Constructor for when we make look aheads deeper into the AI
Lookahead::Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2): depthLevel(0), parent(nullptr)
{
    assert(_gameboard.size()==12);
    player1 = _player1->clonePlayer();
    player2 = _player2->clonePlayer();
    gameboard = copyGameBoard(_gameboard, player1, player2);
    children = generateChildren();
    isTerminal = checkTerminality();
}

//Copy constructor
Lookahead::Lookahead(const Lookahead& other): depthLevel(other.depthLevel),parent(other.parent)
{
    player1 = other.player1.get()->clonePlayer();
    player2 = other.player2.get()->clonePlayer();
    gameboard = copyGameBoard(other.gameboard, player1, player2);
    isTerminal = checkTerminality();
}

//Nothing is owned on the heap so nothing to delete
Lookahead::~Lookahead(){}

vector<Lookahead> Lookahead::generateChildren()
{
    //This is what we are going to return
    vector<Lookahead> returnChildren;
    assert(player1);
    for (int i = 0; i < gameboard.size(); i++)
    {
        //We go through the game board
        //The player one owns it..
        if(gameboard[i]->getOwner() == player1.get())
        {
            GamePiecePtr movingPiece = gameboard[i];
            int thisX = movingPiece->getX();
            int thisY = movingPiece->getY();
            
            //We loop though again looking for places to move it
            for(int j = 0; j < gameboard.size(); j++)
            {
                GamePiecePtr targetPosPiece = gameboard[j];
                int targetX = targetPosPiece->getX();
                int targetY = targetPosPiece->getY();
                
                //If this position is owned but p1 we cannot move so continue
                if(targetPosPiece->getOwner() == player1.get()) continue;
                //Likewise if the peice can't move here continue
                else if(!movingPiece->canMove(targetX,targetY)) continue;
                
                else if (targetPosPiece->getType() == PieceType::BLANK)
                {
                    //Otherwise clone the game
                    shared_ptr<Player> cloneOf1 = player1->clonePlayer();
                    shared_ptr<Player> cloneOf2 = player2->clonePlayer();
                    vector<GamePiecePtr> boardClone = copyGameBoard(gameboard, cloneOf1, cloneOf2);
                    GamePiecePtr clonedCurrentPiece = boardClone[i];
                    GamePiecePtr clonedTargetPiece = boardClone[j];
                    //Make the move
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
                    //And add this as a child
                    returnChildren.push_back(Lookahead(boardClone, cloneOf2, cloneOf1, this, depthLevel+1));
                } else {
                    //Remove captured piece and replace capturing piece with blank piece.
                    shared_ptr<Player> cloneOf1 = player1->clonePlayer();
                    shared_ptr<Player> cloneOf2 = player2->clonePlayer();
                    vector<GamePiecePtr> boardClone = copyGameBoard(gameboard, cloneOf1, cloneOf2);
                    GamePiecePtr clonedCurrentPiece = boardClone[i];
                    GamePiecePtr clonedTargetPiece = boardClone[j];

                    cloneOf1->addToBank(clonedTargetPiece->getType());
                   
                    //Add new blank peice
                    boardClone.push_back(make_shared<BlankPiece>(clonedCurrentPiece->getX(), clonedCurrentPiece->getY()));
                    //move capturing peice
                    clonedCurrentPiece->moveTo(clonedTargetPiece->getX(), clonedTargetPiece->getY());
                    //Remove captured piece
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
                    //And add this as a child
                    returnChildren.push_back(Lookahead(boardClone, cloneOf2, cloneOf1, this, depthLevel+1));
                }
            }
        }
    }
    //Simulates droping peices from hand
    vector<GamePiecePtr> playerBank = player1->getBankRef();
    for(int i = 0; i < playerBank.size(); i++)
    {
        for(GamePiecePtr& boardPiece : gameboard)
        {
            //If it is not blank we cannot drop here
            if (boardPiece->getType() != PieceType::BLANK) continue;
            //Otherwise clone all info
            shared_ptr<Player> cloneOf1 = player1->clonePlayer();
            shared_ptr<Player> cloneOf2 = player2->clonePlayer();
            vector<GamePiecePtr> boardClone = copyGameBoard(gameboard, cloneOf1, cloneOf2);
            //Simulate the dropped piece
            simulateDroppedPiece(boardClone, cloneOf1->getBankRef()[i], cloneOf1, boardPiece->getX(), boardPiece->getY());
            assert(cloneOf1);
            assert(cloneOf2);
            assert(boardClone.size()==12);
            //And add this as a child
            returnChildren.push_back(Lookahead(boardClone, cloneOf2, cloneOf1, this, depthLevel+1));
        }
        
    }
    //We set our children as these
    children = returnChildren;
    //And also return them
    return returnChildren;
}

void Lookahead::simulateDroppedPiece(vector<GamePiecePtr>& board, GamePiecePtr piece, shared_ptr<Player> owner, int x,int y)
{
    //Incase the piece is null
    if(!piece) return;
    assert(board.size()==12);
    //We erase the old piece
    board.erase(
                std::remove_if(board.begin(), board.end(),
                               [x,y](GamePiecePtr thisPiece)
                               { return thisPiece->getX() == x && thisPiece->getY() == y; })
                );
    assert(board.size()==11);
    //Then add a piece to the board based on the type of the dropped peice
    if(piece->getType() == PieceType::CHICK)
        board.push_back(make_shared<ChickPiece>(x, y, owner.get()));
    else if(piece->getType() == PieceType::GIRAFFE)
        board.push_back(make_shared<GiraffePiece>(x, y, owner.get()));
    else if(piece->getType() == PieceType::ELEPHANT)
        board.push_back(make_shared<ElephantPiece>(x, y, owner.get()));
    else
        board.push_back(make_shared<BlankPiece>(x,y));
    assert(board.size()==12);
    //Then remove the piece from have
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
    for(GamePiecePtr &gamePiece : gameboard)
    {
        if(gamePiece)
        {
            if(gamePiece->getType() == PieceType::LION)
            {
                if (gamePiece->getOwner() == player2.get())
                {
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
        //clone every peice
        GamePiecePtr newPiece = piece->clone();
        if(newPiece->getOwner())
        {
            //Set there owner
            if(newPiece->getOwner()->isAI() == p1->isAI())
            {
                newPiece->setOwner(p1.get());
            } else {
                newPiece->setOwner(p2.get());
            }
        }
        //And add it to the board
        returnBoard.push_back(newPiece);
    }
    assert(returnBoard.size()==12);
    return returnBoard;
}


