/* 
 * File:   Game.cpp
 * Author: Brandon West
 *
 * Created on November 26, 2017, 1:59 PM
 * Purpose: Game Class Implementation
 */

#include "Game.h"
#include <fcntl.h>      // File descriptor manipulator

//Constructor
Game::Game() { 
    base.size = 20;
    base.x = base.size / 2;
    base.y = base.size / 2;
    xToken = rand() % base.size;    //Standard token worth 10 pts
    yToken = rand() % base.size;    //Standard token worth 10 pts
    xMega = rand() % base.size + 1;     //Mega Token worth 20 pts
    yMega = rand() % base.size + 1;     //Mega Token worth 20 pts
    ckWin = true;
    sleep = 1;
    tempX = 0;
    tempY = 0;
    temp2X = 0;
    temp2Y = 0;
    ckPnt = false;
    nTail = 0;
    sec = 1; //pause in seconds
    xTail = new int[base.size * 5];
    yTail = new int[base.size * 5];
    
    //initialize board
    for(int i = 0;i < base.size + 2;i++)
    {
        cout << "*";
    }
    cout << endl;
    for(int i = 0;i < base.size + 2;i++) //height 
    {
        for(int j = 0;j < base.size + 2;j++)//width
        {
            if(j == 0)
            {
                cout << "*";
            }
         
                cout << " ";
            
            if(j == base.size - 1)
            {
                cout << "*";
            }
        }

        cout << endl;
    }
    
    for(int i = 0;i < base.size + 2;i++)
    {
        cout << "*";
    }
    cout << endl;

    //Check if tokens randomly generate same value, if true add 1 or minus 1
    if(xMega == xToken)
    {
        xMega += 1;
    }  
    else if(yMega == yToken)
    {
        yMega -= 1;
    }
}

Game::~Game() {
}

/*Function Definition:
 * pause game so console out is more manageable for player
 */
void Game::pause(float sleep)
{
    int beg = time(0),end;
    do
    {
        end = time(0);
    }while(sleep > end - beg);
}