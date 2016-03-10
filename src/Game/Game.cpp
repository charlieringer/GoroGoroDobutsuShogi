//
//  Game.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/02/2016.
//
//

#include "Game.hpp"

Game::Game(State& _state, shared_ptr<ImageBank> _imgBank): xOffset(100), yOffset(160), pieceHeight(80), pieceWidth(80)
{
    state = &_state;
    imgBank = _imgBank;
    background = imgBank->loadImage("Background.jpg");
    player = new HumanPlayer(imgBank);
    ai = new AIPlayer(imgBank);
    
    gameboard.push_back(make_shared<GiraffePiece>(0,0, ai, imgBank));
    gameboard.push_back(make_shared<LionPiece>(1,0, ai, imgBank));
    gameboard.push_back(make_shared<ElephantPiece>(2,0, ai, imgBank));
    
    gameboard.push_back(make_shared<BlankPiece>(0,1, imgBank));
    gameboard.push_back(make_shared<ChickPiece>(1,1, ai, imgBank));
    gameboard.push_back(make_shared<BlankPiece>(2,1, imgBank));

    gameboard.push_back(make_shared<BlankPiece>(0,2, imgBank));
    gameboard.push_back(make_shared<ChickPiece>(1,2, player, imgBank));
    gameboard.push_back(make_shared<BlankPiece>(2,2, imgBank));
    
    gameboard.push_back(make_shared<ElephantPiece>(0,3, player, imgBank));
    gameboard.push_back(make_shared<LionPiece>(1,3, player, imgBank));
    gameboard.push_back(make_shared<GiraffePiece>(2,3, player, imgBank));

}

Game::~Game()
{
    delete player;
    delete ai;
}

void Game::drawGame()
{
    background->draw(0,0);
    
    for(GamePiecePtr &gamePiece : gameboard) gamePiece->drawPiece(xOffset, pieceWidth, yOffset, pieceHeight);
    
    for(GamePiecePtr &gamePiece : player->getBankRef()) gamePiece->drawPiece(xOffset, pieceWidth, yOffset, pieceHeight);
    for(GamePiecePtr &gamePiece : ai->getBankRef()) gamePiece->drawPiece(xOffset, pieceWidth, yOffset, pieceHeight);
    if (playerSelectedPiece != NULL)
    {
     ofSetColor(255, 0, 0);
     ofNoFill();
     ofDrawRectangle(ofRectangle(xOffset+playerSelectedPiece->getX()*(pieceWidth), yOffset+playerSelectedPiece->getY()*(pieceHeight), 80, 80));
        ofFill();
        ofSetColor(255, 255, 255);
    }
}

void Game::takeAITurn()
{
    if(playersTurn) return;
    brain.getNextMove(gameboard, ai, player);
    playersTurn = true;
}

void Game::handlePlayerClick(int x, int y)
{
    if(!playersTurn) return;
    if (playerSelectedPiece != NULL)
    {
        int convertedX = (int)floor((x-xOffset)/pieceWidth+1)-1;
        int convertedY = (int)floor((y-yOffset)/pieceHeight+1)-1;
        if ((playerSelectedPiece->getY() == 5||playerSelectedPiece->getY() == 4) && convertedY >= 0 && convertedY < 4)
        {
            handleDroppedPiece(convertedX,convertedY);
            return;
        }
        //See if we have clicked on a piece we can move/drop
        //we have alreay selected a piece so see if we can move it
        
        if (playerSelectedPiece->canMove(convertedX, convertedY))
        {
            for(GamePiecePtr &piece : gameboard)
            {
                if(piece->getX() == convertedX && piece->getY() == convertedY && piece->getOwner() == playerSelectedPiece->getOwner())
                {
                    playerSelectedPiece = piece;
                    return;
                }
            }
            movePiece(playerSelectedPiece, convertedX, convertedY);
            playerSelectedPiece = NULL;
        }
        
    }
    for(GamePiecePtr &piece : gameboard)
    {
        int realPieceX = ((piece->getX())*pieceWidth+1)+xOffset;
        int realPieceY = ((piece->getY())*pieceHeight+1)+yOffset;
        if (x > realPieceX && x < realPieceX+pieceWidth && y > realPieceY && y < realPieceY+pieceHeight && piece->getOwner() == player)
        {
            playerSelectedPiece = piece;
            return;
        }
    }
    
    for(GamePiecePtr &piece : player->getBankRef())
    {
        int realPieceX = ((piece->getX())*pieceWidth+1)+xOffset;
        int realPieceY = ((piece->getY())*pieceHeight+1)+yOffset;
        if (x > realPieceX && x < realPieceX+pieceWidth && y > realPieceY && y < realPieceY+pieceHeight && piece->getOwner() == player)
        {
            playerSelectedPiece = piece;
            return;
        }
    }
}

void Game::movePiece(GamePiecePtr selectedPiece, int x, int y)
{
    //To move a piece we need to:
    //Check to see what is in the destination.
    //If it is a blank peice we need to just swap the X/Ys of the two pieces.
    //If it is a piece we need to add it the the relevant player's bank
    //And then update the catureing pieces X/Y
    //And replace the old location with a blank piece.
    for(int i = 0; i < gameboard.size(); i++)
    {
        GamePiecePtr piece = gameboard[i];
        if (piece->getX() == x && piece->getY() == y)
        {
            if (piece->getType() == PieceType::BLANK)
            {
                piece->moveTo(selectedPiece->getX(), selectedPiece->getY());
                selectedPiece->moveTo(x, y);
                //check for promotion
                if(selectedPiece->getType() == PieceType::CHICK &&
                   ((selectedPiece->getOwner() == ai && selectedPiece->getY() == 3) || (selectedPiece->getOwner() == player && selectedPiece->getY() == 0)))
                {
                    //And promote if needed
                    promotePiece(selectedPiece);
                }
                return;
            } else {
                //Remove captured piece and replace capturing piece with blank piece.
                Player* capturingPlayer = selectedPiece->getOwner();
                capturingPlayer->addToBank(piece->getType());
                gameboard.push_back(make_shared<BlankPiece>(selectedPiece->getX(),selectedPiece->getY(), imgBank));
                selectedPiece->moveTo(x, y);
                gameboard.erase(gameboard.begin() + i);
                
                //check for promotion
                if(selectedPiece->getType() == PieceType::CHICK &&
                   ((selectedPiece->getOwner() == ai && selectedPiece->getY() == 3) || (selectedPiece->getOwner() == player && selectedPiece->getY() == 0)))
                {
                    //And promote if needed
                    promotePiece(selectedPiece);
                }
                return;
            }
        }
    }
}

void Game::handleDroppedPiece(int x,int y)
{
    for(GamePiecePtr &piece : gameboard)
    {
        if(piece->getX() == x && piece->getY() == y && piece->getType() != PieceType::BLANK) return;
    }
    
    gameboard.erase(
                    std::remove_if(gameboard.begin(), gameboard.end(),
                                   [x,y](GamePiecePtr thisPiece)
                                   { return thisPiece->getX() == x && thisPiece->getY() == y; })
                    );
    
    if(playerSelectedPiece->getType() == PieceType::CHICK)
        gameboard.push_back(make_shared<ChickPiece>(x, y, playerSelectedPiece->getOwner(), imgBank));
    else if(playerSelectedPiece->getType() == PieceType::GIRAFFE)
        gameboard.push_back(make_shared<GiraffePiece>(x, y, playerSelectedPiece->getOwner(), imgBank));
    else if(playerSelectedPiece->getType() == PieceType::ELEPHANT)
        gameboard.push_back(make_shared<ElephantPiece>(x, y, playerSelectedPiece->getOwner(), imgBank));

    int removeX = playerSelectedPiece->getX();
    int removeY = playerSelectedPiece->getY();
    vector<shared_ptr<GamePiece>>& bank = player->getBankRef();
    bank.erase( std::remove_if(bank.begin(), bank.end(), [removeX,removeY](GamePiecePtr thisPiece)
    { return thisPiece->getX() == removeX && thisPiece->getY() == removeY; }) );
    playerSelectedPiece = NULL;
                        
}

void Game::promotePiece(GamePiecePtr piece)
{
    //Turns a piece into a hen
    int x = piece->getX();
    int y = piece->getY();
    Player* owner = piece->getOwner();
    gameboard.erase(
                    std::remove_if(gameboard.begin(), gameboard.end(),
                                 [x,y](GamePiecePtr thisPiece)
                                 { return thisPiece->getX() == x && thisPiece->getY() == y; })
                    );
    gameboard.push_back(make_shared<HenPiece>(x,y, owner, imgBank));
}

void Game::checkEnd()
{
    bool playerHasLion = false;
    bool aiHasLion = false;
    
    for(GamePiecePtr &gamePiece : gameboard)
    {
        if(gamePiece->getOwner() == player && gamePiece->getType() == PieceType::LION)
        {
            playerHasLion = true;
            if (gamePiece->getY() == 0)
            {
                *state = GAMEOVERWIN;
                return;
            }
        }
        if(gamePiece->getOwner() == ai && gamePiece->getType() == PieceType::LION)
        {
            aiHasLion = true;
            if (gamePiece->getY() == 3)
            {
                *state = GAMEOVERLOSE;
                return;
            }
        }
    }
    if(!playerHasLion)
    {
        *state = GAMEOVERLOSE;
        return;
    }
    if(!aiHasLion)
    {
        *state = GAMEOVERWIN;
        return;
    }
}

