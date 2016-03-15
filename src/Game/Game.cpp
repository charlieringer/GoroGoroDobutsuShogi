//
//  Game.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/02/2016.
//
//

#include "Game.hpp"
#include "Lookahead.hpp"

Game::Game(State& _state, shared_ptr<ImageBank> _imgBank): xOffset(100), yOffset(170), pieceHeight(80), pieceWidth(80), state(&_state), imgBank(_imgBank)
{
    //Lo
    bool fontLoaded = dispFont.load("CHOWFUN_.TTF", 42);
    assert(fontLoaded);
    background = imgBank->loadImage("blurredbackground.jpg");
    gameBackground = imgBank->loadImage("gamebackground.jpg");
    player = new HumanPlayer(imgBank);
    ai = new AIPlayer(imgBank);
    brain = new AIBrain();
    
    //This is the inital game board
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
    //Nearly everthing in game is either a value or a shared_ptr so this is all we need to delete
    delete player;
    delete ai;
    delete brain;
}

void Game::drawGame()
{
    //This is the game background
    background->draw(0,0);
    gameBackground->draw(xOffset,yOffset);
    
    if(playersTurn)
        dispFont.drawString("Players Turn", 10, 100);
    
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
    
    if(!aiStarted)
    {
        aiStarted = true;
        brain->startAI(gameboard, ai, player);
        return;
    } else if(brain->hasNextMove())
    {
        gameboard.clear();
        Lookahead stateFromAI = brain->getMoveandReset();
        vector<GamePiecePtr> aiBoard = stateFromAI.getBoard();
        for(auto piece : aiBoard)
        {
            int x = piece->getX();
            int y = piece->getY();
            PieceType type = piece->getType();
            if(type == PieceType::BLANK)
            {
                gameboard.push_back(make_shared<BlankPiece>(x,y, imgBank));
            } else if(piece->getOwner()->isAI())
            {
                if (type == PieceType::GIRAFFE)
                    gameboard.push_back(make_shared<GiraffePiece>(x,y, ai, imgBank));
                else if (type == PieceType::LION)
                    gameboard.push_back(make_shared<LionPiece>(x,y, ai, imgBank));
                else if (type == PieceType::ELEPHANT)
                    gameboard.push_back(make_shared<ElephantPiece>(x,y, ai, imgBank));
                else if (type == PieceType::CHICK)
                    gameboard.push_back(make_shared<ChickPiece>(x,y, ai, imgBank));
                else if (type == PieceType::HEN)
                    gameboard.push_back(make_shared<HenPiece>(x,y, ai, imgBank));
            } else  if(!(piece->getOwner()->isAI()))
            {
                if (type == PieceType::GIRAFFE)
                    gameboard.push_back(make_shared<GiraffePiece>(x,y, player, imgBank));
                else if (type == PieceType::LION)
                    gameboard.push_back(make_shared<LionPiece>(x,y, player, imgBank));
                else if (type == PieceType::ELEPHANT)
                    gameboard.push_back(make_shared<ElephantPiece>(x,y, player, imgBank));
                else if (type == PieceType::CHICK)
                    gameboard.push_back(make_shared<ChickPiece>(x,y, player, imgBank));
                else if (type == PieceType::HEN)
                    gameboard.push_back(make_shared<HenPiece>(x,y, player, imgBank));
            }
        }
        player->clearBank();
        ai->clearBank();
    
        for(auto piece: stateFromAI.getPlayer1()->getBankRef())
        {
            if (stateFromAI.getPlayer1()->isAI())
                ai->addToBank(piece->getType());
            else
                player->addToBank(piece->getType());
        }
    
        for(auto piece: stateFromAI.getPlayer2()->getBankRef())
        {
            if (stateFromAI.getPlayer2()->isAI())
                ai->addToBank(piece->getType());
            else
                player->addToBank(piece->getType());
        }
        playersTurn = true;
        checkEnd();
        aiStarted = false;
    }
}


void Game::handlePlayerClick(int x, int y)
{
    if(!playersTurn) return;
    if (playerSelectedPiece != nullptr)
    {
        int convertedX = (int)floor((x-xOffset)/pieceWidth+1)-1;
        int convertedY = (int)floor((y-yOffset)/pieceHeight+1)-1;
        if ((playerSelectedPiece->getY() == 5||playerSelectedPiece->getY() == 4) && convertedY >= 0 && convertedY < 4)
        {
            bool dropped = handleDroppedPiece(convertedX,convertedY);
            if(dropped)
                playerSelectedPiece = nullptr;
                playersTurn = false;
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
            playerSelectedPiece = nullptr
            ;
            playersTurn = false;
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

bool Game::handleDroppedPiece(int x,int y)
{
    for(GamePiecePtr &piece : gameboard)
    {
        if(piece->getX() == x && piece->getY() == y && piece->getType() != PieceType::BLANK) return false;
        if(piece->getX() == x && piece->getY() == y && piece->getOwner() == player)
        {
            playerSelectedPiece = piece;
            return false;
  
        }
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
    return true;
                        
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

