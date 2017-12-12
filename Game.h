/* 
 * File:   Game.h
 * Author: Brandon West
 * Created on November 26, 2017, 1:59 PM
 * Purpose: Game Class declaration
 */

#ifndef GAME_H
#define GAME_H

//#include <cstdlib>      //
#include <iostream>     //console out
#include <vector>       //STL Lib
#include <ctime>        //pause function
#include <fcntl.h>      // File descriptor manipulator
#include <termios.h>    // Terminal attributes
#include <unistd.h>     // POSIX APIs: read() function
using namespace std;

class Game {
protected:
    int xToken;              //Token coordinates
    int yToken;
    float xMega;
    float yMega;
    bool ckWin;             //check game status
    int sleep;      
    int nTail;               //track length of tail
    int tempX;               //tail swap coordinates
    int tempY;
    int temp2X;
    int temp2Y;              //tail swap coordinates
    int *xTail;              //hold row-tail characters
    int *yTail;              //hold col-tail characters
    bool ckPnt;              //check if print tail
    int sec;                 //pause multiplier
    
    struct bVal
    {
        int x;     //rows
        int y;     //columns
        int size;  //game board size
    }base;  //bVal object
    
    char buff[5];           //array check buffer
    int nRead;              //for POSIX APIs
    
    enum dir {PSE,STOP,LT,RT,DWN,UP};
    dir Move;
public:
    Game();
    virtual ~Game();
    void pause(float);//pause console output 
};

#endif /* GAME_H */