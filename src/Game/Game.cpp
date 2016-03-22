//
//  Game.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/02/2016.
//
//

#include "Game.hpp"
#include "Lookahead.hpp"

Game::Game(shared_ptr<ImageBank> _imgBank): xOffset(100), yOffset(170), pieceHeight(80), pieceWidth(80), imgBank(_imgBank)
{
    //Loads the font
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 42);
    assert(fontLoaded);
    background = imgBank->loadImage("Backgrounds/blurredbackground.jpg");
    gameBackground = imgBank->loadImage("Backgrounds/gamebackground.jpg");
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
    
    //Random starting player
    int chooseStarter = rand()%2;
    if(chooseStarter == 0)
        playersTurn = false;
}

Game::Game(const Game& other): xOffset(100), yOffset(170), pieceHeight(80), pieceWidth(80)
{
    //Loads the font
    bool fontLoaded = dispFont.load("Fonts/CHOWFUN_.TTF", 42);
    assert(fontLoaded);
    imgBank = other.imgBank;
    background = imgBank->loadImage("Backgrounds/blurredbackground.jpg");
    gameBackground = imgBank->loadImage("Backgrounds/gamebackground.jpg");
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

void Game::draw()
{
    //This is the game backgrounds
    background->draw(0,0);
    gameBackground->draw(xOffset,yOffset);
    
    //And instructions
    if(playersTurn)
        dispFont.drawString("Your Turn", 80, 80);
    else
       dispFont.drawString("AI thinking...", 40, 80);
    
    //Finally we draw all of the game peices on the board...
    for(GamePiecePtr &gamePiece : gameboard) gamePiece->drawPiece(xOffset, pieceWidth, yOffset, pieceHeight);
    
    //And in the players banks
    for(GamePiecePtr &gamePiece : player->getBankRef()) gamePiece->drawPiece(xOffset, pieceWidth, yOffset, pieceHeight);
    for(GamePiecePtr &gamePiece : ai->getBankRef()) gamePiece->drawPiece(xOffset, pieceWidth, yOffset, pieceHeight);
    //if we have selected a pice
    if (playerSelectedPiece)
    {
        //draw the highlight
     ofSetColor(255, 0, 0);
     ofNoFill();
     ofDrawRectangle(ofRectangle(xOffset+playerSelectedPiece->getX()*(pieceWidth), yOffset+playerSelectedPiece->getY()*(pieceHeight), 80, 80));
        ofFill();
        ofSetColor(255, 255, 255);
    }
}

void Game::update()
{
    //All we need to do when updating is take the AIs turn
    takeAITurn();
}

void Game::takeAITurn()
{
    //If it not the AIs turn we exit early
    if(playersTurn) return;
    
    //Otherwise we have AI work to do
    if(!aiStarted)
    {
        //If the AI is not started we start it.
        aiStarted = true;
        brain->startAI(gameboard, ai, player);
        return;
    } else if(brain->hasNextMove())
    {
        //Then when we have the next move the AI is done thinking so we can update the board
        //First we clear it
        gameboard.clear();
        //Then we get the state from the lookahead
        Lookahead stateFromAI = brain->getMoveandReset();
        vector<GamePiecePtr> aiBoard = stateFromAI.getBoard();
        //And remake the board with it
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
        //and the players banks
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
        //then switch the players turn and check the end
        playersTurn = true;
        checkEnd();
        aiStarted = false;
    }
}


void Game::handleClick(int x, int y)
{
    //No interaction if it is not the players turn
    if(!playersTurn) return;
    
    //If we have selected a piece
    if (playerSelectedPiece)
    {
        //Work out the converted XY of the click
        int convertedX = (int)floor((x-xOffset)/pieceWidth+1)-1;
        int convertedY = (int)floor((y-yOffset)/pieceHeight+1)-1;
        //Work out if the already selected piece is one from the bank and we clicked on te grid
        if ((playerSelectedPiece->getY() == 5||playerSelectedPiece->getY() == 4) && convertedY >= 0 && convertedY < 4)
        {
            //And if it is see if we can drop the piece
            bool dropped = handleDroppedPiece(convertedX,convertedY);
            if(dropped)
            {
                //If we did then the players turn is done
                playerSelectedPiece = nullptr;
                playersTurn = false;
            }
            //We return here becuase this is all that happens in this case
            return;
        }
        //See if we have clicked on a piece we can move/drop
        //we have already selected a piece so see if we can move it
        if (playerSelectedPiece->canMove(convertedX, convertedY))
        {
            for(GamePiecePtr &piece : gameboard)
            {
                //If the piece we have clicked on is one of your own
                //Then set your selected piece to that
                if(piece->getX() == convertedX && piece->getY() == convertedY && piece->getOwner() == playerSelectedPiece->getOwner())
                {
                    playerSelectedPiece = piece;
                    return;
                }
            }
            //Otherwise move the piece (which also captures pieces)
            movePiece(playerSelectedPiece, convertedX, convertedY);
            //Reset the selected piece
            playerSelectedPiece = nullptr;
            //The player has taken their turn
            playersTurn = false;
            return;
        }
    }
    //Otherwise we have no piece selected
    //So loop through the board
    for(GamePiecePtr &piece : gameboard)
    {
        //And see if you have clicked on anything your own
        int convertedX = (int)floor((x-xOffset)/pieceWidth+1)-1;
        int convertedY = (int)floor((y-yOffset)/pieceHeight+1)-1;
        if (convertedX == piece->getX() && convertedY == piece->getY() && piece->getOwner() == player)
        {
            //If we have set the selected peice to that
            playerSelectedPiece = piece;
            return;
        }
    }
    
    //And lastly we go through the bank and see if we have clicked on anything
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
        //If we clicked on one of our own peices
        if(piece->getX() == x && piece->getY() == y && piece->getOwner() == player)
        {
            //set the selected piece to that
            playerSelectedPiece = piece;
            return false;
            
        }
        //Otherwise if it is not blank
        if(piece->getX() == x && piece->getY() == y && piece->getType() != PieceType::BLANK)
        {
            //We cannot drop there so return false
            return false;
        }
    }
    
    //If we get this far we have a viable drop
    //Remove the old object (a blank piece)
    gameboard.erase(
                    std::remove_if(gameboard.begin(), gameboard.end(),
                                   [x,y](GamePiecePtr thisPiece)
                                   { return thisPiece->getX() == x && thisPiece->getY() == y; })
                    );
    
    //Then add a new piece based on the type of the dropped piece
    if(playerSelectedPiece->getType() == PieceType::CHICK)
        gameboard.push_back(make_shared<ChickPiece>(x, y, playerSelectedPiece->getOwner(), imgBank));
    else if(playerSelectedPiece->getType() == PieceType::GIRAFFE)
        gameboard.push_back(make_shared<GiraffePiece>(x, y, playerSelectedPiece->getOwner(), imgBank));
    else if(playerSelectedPiece->getType() == PieceType::ELEPHANT)
        gameboard.push_back(make_shared<ElephantPiece>(x, y, playerSelectedPiece->getOwner(), imgBank));

    //Then remove the dropped piece from the players bank
    int removeX = playerSelectedPiece->getX();
    int removeY = playerSelectedPiece->getY();
    vector<shared_ptr<GamePiece>>& bank = player->getBankRef();
    bank.erase( std::remove_if(bank.begin(), bank.end(), [removeX,removeY](GamePiecePtr thisPiece)
    { return thisPiece->getX() == removeX && thisPiece->getY() == removeY; }) );
    playerSelectedPiece = NULL;
    //We dropped something so return true
    return true;
                        
}

void Game::promotePiece(GamePiecePtr piece)
{
    //Turns a piece into a hen
    int x = piece->getX();
    int y = piece->getY();
    Player* owner = piece->getOwner();
    //Removes the old chick
    gameboard.erase(
                    std::remove_if(gameboard.begin(), gameboard.end(),
                                 [x,y](GamePiecePtr thisPiece)
                                 { return thisPiece->getX() == x && thisPiece->getY() == y; })
                    );
    //And add a new hen
    gameboard.push_back(make_shared<HenPiece>(x,y, owner, imgBank));
}

void Game::checkEnd()
{
    bool playerHasLion = false;
    bool aiHasLion = false;
    
    for(GamePiecePtr &gamePiece : gameboard)
    {
        //Inspect every element of the gameboard looking for the players lion
        if(gamePiece->getOwner() == player && gamePiece->getType() == PieceType::LION)
        {
            //We found it!
            playerHasLion = true;
            if (gamePiece->getY() == 0)
            {
                //Player got the lion to the end
                //Game won!
                reset();
                GameState::setState(GAMEOVERWIN);
                return;
            }
        }
        //Or the ai's lion
        if(gamePiece->getOwner() == ai && gamePiece->getType() == PieceType::LION)
        {
            //Found it!
            aiHasLion = true;
            if (gamePiece->getY() == 3)
            {
                //AI got the lion to the end
                //Game lost!
                reset();
                GameState::setState(GAMEOVERLOSE);
                return;
            }
        }
    }
    if(!playerHasLion)
    {
        //Player's lion captured
        //Game lost!
        reset();
        GameState::setState(GAMEOVERLOSE);
        return;
    }
    if(!aiHasLion)
    {
        //AIs lion captured
        //Game won!
        reset();
        GameState::setState(GAMEOVERWIN);
        return;
    }
}

void Game::reset()
{
    //This resets the imporant parts of the game.
    playerSelectedPiece = nullptr;
    player->clearBank();
    ai->clearBank();
    gameboard.clear();
    //And rebuilds the game board
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
    
    //Random starting player
    int chooseStarter = rand()%2;
    if(chooseStarter == 0)
        playersTurn = false;
}

