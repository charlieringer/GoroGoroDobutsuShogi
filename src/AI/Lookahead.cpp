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

Lookahead::Lookahead(vector<GamePiecePtr> gameboard, Player* player1, Player* player2, Lookahead* parent, int depthLevel)
{
    isTerminal = checkTerminality();
    
}

void Lookahead::generateChildren()
{
    vector<GamePiecePtr> boardCopy = gameboard;
    for (int i = i; i < gameboard.size(); i++)
    {
        GamePiecePtr gamePiece = gameboard[i];
        if(gamePiece->getOwner() == player1)
        {
            int thisX = gamePiece->getX();
            int thisY = gamePiece->getY();
            if(gamePiece->canMove(thisX-1, thisY-1))
            {
                vector<GamePiecePtr> boardCopy = copyGameBoard(gameboard);
                boardCopy[i]->moveTo(thisX-1, thisY-1);
                children.push_back(Lookahead(boardCopy, player1, player2, this, depthLevel+1));
            }
            if(gamePiece->canMove(thisX-1, thisY))
            {
                vector<GamePiecePtr> boardCopy = copyGameBoard(gameboard);
                boardCopy[i]->moveTo(thisX-1, thisY);
                children.push_back(Lookahead(boardCopy, player1, player2, this, depthLevel+1));
            }
            if(gamePiece->canMove(thisX-1, thisY+1))
            {
                vector<GamePiecePtr> boardCopy = copyGameBoard(gameboard);
                boardCopy[i]->moveTo(thisX-1, thisY+1);
                children.push_back(Lookahead(boardCopy, player1, player2, this, depthLevel+1));
            }
            if(gamePiece->canMove(thisX, thisY-1))
            {
                vector<GamePiecePtr> boardCopy = copyGameBoard(gameboard);
                boardCopy[i]->moveTo(thisX, thisY-1);
                children.push_back(Lookahead(boardCopy, player1, player2, this, depthLevel+1));
                
            }
            if(gamePiece->canMove(thisX, thisY+1))
            {
                vector<GamePiecePtr> boardCopy = copyGameBoard(gameboard);
                boardCopy[i]->moveTo(thisX, thisY+1);
                children.push_back(Lookahead(boardCopy, player1, player2, this, depthLevel+1));
            }
            if(gamePiece->canMove(thisX-1, thisY+1))
            {
                vector<GamePiecePtr> boardCopy = copyGameBoard(gameboard);
                boardCopy[i]->moveTo(thisX-1, thisY+1);
                children.push_back(Lookahead(boardCopy, player1, player2, this, depthLevel+1));
            }
            if(gamePiece->canMove(thisX, thisY+1))
            {
                vector<GamePiecePtr> boardCopy = copyGameBoard(gameboard);
                boardCopy[i]->moveTo(thisX, thisY+1);
                children.push_back(Lookahead(boardCopy, player1, player2, this, depthLevel+1));
            }
            if(gamePiece->canMove(thisX+1, thisY+1))
            {
                vector<GamePiecePtr> boardCopy = copyGameBoard(gameboard);
                boardCopy[i]->moveTo(thisX+1, thisY+1);
                children.push_back(Lookahead(boardCopy, player1, player2, this, depthLevel+1));
            }
        }
    }
    
    //Drop moves for player one
}

vector<GamePiecePtr> Lookahead::simulateMove(vector<GamePiecePtr> board, int index, int x, int y)
{
    GamePiecePtr movedPiece = board[index];
    for(int i = 0; i < gameboard.size(); i++)
    {
        GamePiecePtr piece = board[i];
        if (piece->getType() == PieceType::BLANK)
        {
            piece->moveTo(movedPiece->getX(), movedPiece->getY());
            movedPiece->moveTo(x, y);
            //check for promotion
            if(movedPiece->getType() == PieceType::CHICK &&
                ((movedPiece->getOwner()->isAI() && movedPiece->getY() == 3) || (!(movedPiece->getOwner()->isAI()) && movedPiece->getY() == 0)))
            {
                //And promote if needed
                simulatePromotion(board, movedPiece);
            }
            return;
        } else {
            //Remove captured piece and replace capturing piece with blank piece.
            Player* capturingPlayer = movedPiece->getOwner();
            capturingPlayer->addToBank(piece->getType());
            gameboard.push_back(make_shared<BlankPiece>(movedPiece->getX(),movedPiece->getY()));
            movedPiece->moveTo(x, y);
            gameboard.erase(gameboard.begin() + i);
                    
            //check for promotion
            if(movedPiece->getType() == PieceType::CHICK &&
               ((movedPiece->getOwner()->isAI() && movedPiece->getY() == 3) || (!(movedPiece->getOwner()->isAI())&& movedPiece->getY() == 0)))
            {
                //And promote if needed
                simulatePromotion(board, movedPiece);
            }
            return;
        }
    }
}

void Lookahead::simulateDroppedPiece(vector<GamePiecePtr> board, int x,int y)
{
    board.erase(
                std::remove_if(board.begin(), board.end(),
                               [x,y](GamePiecePtr thisPiece)
                               { return thisPiece->getX() == x && thisPiece->getY() == y; })
                );
    
    
}

void Lookahead::simulatePromotion(vector<GamePiecePtr> board, GamePiecePtr piece)
{
    //Turns a piece into a hen
    int x = piece->getX();
    int y = piece->getY();
    Player* owner = piece->getOwner();
    board.erase(
                    std::remove_if(board.begin(), board.end(),
                                   [x,y](GamePiecePtr thisPiece)
                                   { return thisPiece->getX() == x && thisPiece->getY() == y; })
                    );
    gameboard.push_back(make_shared<HenPiece>(x,y, owner));
}

bool Lookahead::checkTerminality()
{
    bool player2HasLion = false;
    for(GamePiecePtr &gamePiece : gameboard)
    {
        if(gamePiece->getType() == PieceType::LION)
        {
            if (gamePiece->getOwner() == player1)
            {
                if ((gamePiece->getY() == 0 && !(gamePiece->getOwner()->isAI())) ||
                    (gamePiece->getY() == 3 && gamePiece->getOwner()->isAI()) )
                {
                    return true;
                }
            } else if (gamePiece->getOwner() == player2)
            {
                player2HasLion = true;
            }
        }
    }
    if(!player2HasLion)
    {
        return true;
    }
    return false;
}

vector<GamePiecePtr> Lookahead::copyGameBoard(vector<GamePiecePtr> initalBoard)
{
    vector<GamePiecePtr> returnBoard;
    
    for(GamePiecePtr piece : initalBoard)
    {
        GamePiecePtr newPiece = piece->clone();
        returnBoard.push_back(newPiece);
    }
    return returnBoard;
}


