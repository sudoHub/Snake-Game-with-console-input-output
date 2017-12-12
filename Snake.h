/* 
 * File:   Snake.h
 * Author: Brandon West
 * Created on December 10, 2017, 8:53 PM
 * Purpose: Snake class declaration
 */

#ifndef SNAKE_H
#define SNAKE_H

#include "Game.h"

class Snake;
ostream &operator << (ostream &,const Snake &);

class Snake : public Game{
protected:
    int lev;                //level up multiplier
    int score;              //Regular points accumulator
    float megaScr;          //Mega points accumulator
    static float totScr;        //total score of all players
public:
    Snake();                   //constructor
    Snake(const Snake& oldObj);//copy constructor
    virtual ~Snake();
    void sBoard();  //generate map
    void input();   //determine user input
    void logic();   //game logic
    void ckPrint(int &,int &);
    void levelUp(); //increase pause function based off score
    void levTwo();  //level two
    void levThr();  //level three
    virtual void disScr() const;   //return statement
    int getScr();   //return score
    bool gmStop();  //check for loser
    void finWrte(); //calls SaveScr class write to bin
    
    friend ostream &operator<< (ostream &,const Snake &);//overload cout
};


template <class T>
class PlusScr : public Snake
{
    private:
        T newScr;
    public:
        PlusScr();
        T getScor(T); //Get new score

};

template <class T>
PlusScr<T>::PlusScr(){newScr = 2;}; //constructor

/*Function Definition:
 * Accepts score count (integer) or Mega-score count (float) calculates new
 * total.
 */
template <class T>
T PlusScr<T>::getScor(T pts)
{
    //newScr = point multiplier;
    newScr *= pts;
    //totScr = newScr;    //total points for print to binary file
    
    return newScr;
}
#endif /* SNAKE_H */