/* 
 * File:   Snake.cpp
 * Author: Brandon West
 *
 * Created on December 7, 2017, 8:53 PM
 * Purpose: Snake class implementation
 */

#include "Snake.h"
#include "SaveScr.h"
#include <fcntl.h>      // File descriptor manipulator

Snake::Snake() {
    score = 0;
    megaScr = 0;
}
float Snake::totScr = 0;    //static member initialization

/*Copy constructor
 * 
 */
Snake::Snake(const Snake& oldObj) {
    score = oldObj.score;
    megaScr = oldObj.megaScr;
}

Snake::~Snake() {
    delete[] this->xTail;
    delete[] this->yTail;
}

void Snake::sBoard()
{
    if(nTail > 5)
    {
        levThr();   //call level three function
    }
    else if(nTail > 3)
    {
        levTwo();   //call level two function
    }
    else
    {
        //pScore(score,megaScr);//print score
        pause(sec);           //pause console output

        cout << flush;
        for(int i = 0;i < base.size + 2;i++)
        {
            cout << "*";
        }
        cout << endl;
        for(int i = 0;i < base.size;i++)
        {
            for(int j = 0;j < base.size;j++)
            {
                if(j == 0)
                {
                    cout << "*";
                }

                if(i == base.y && j == base.x)
                {
                    cout << "O";
                }
                else if(i == yToken && j == xToken)
                {
                    cout << "Z";//output token
                }
                else if(i == yMega && j == xMega)
                {
                    cout << "8";//output mega token
                }
                else
                {
                    ckPnt = false;
                    ckPrint(j,i);         
                }
                if(j == base.size - 1)
                {
                    cout << "*";
                }
            }
            cout << endl;
    }
}

for(int i = 0;i < base.size + 2;i++)
{
    cout << "*";
}
cout << endl; 
    
}

void Snake::input()
{ 
    nRead = read(0,buff,5);
    if(nRead > 0)
    {
        for(int i = 0;i < nRead;i++)
        {
        switch(buff[i])
            {
                case 'a': Move = LT; 
                          break;
                case 'd': Move = RT;
                          break;
                case 's': Move = DWN;
                          break;
                case 'q': Move = STOP;
                          break;
                case 'w': Move = UP;
                          break;
                default:
                          break;
            }
        }
    }
}

/*Function Definition:
 * Logic of the game.
 */
void Snake::logic()
{
    //swap tail coordinates
    tempX = xTail[0];   //set temporary x,y coordinates to 1st char in element
    tempY = yTail[0];
    xTail[0] = base.x;  //set tail to follow head
    yTail[0] = base.y;
    
    for(int i = 1;i < nTail;i++)
    {
        //swap coordinates
        temp2X = xTail[i];
        temp2Y = yTail[i];
        xTail[i] = tempX;
        yTail[i] = tempY;
        tempX = temp2X;
        tempY = temp2Y;
    }
    switch(Move)
    {
        case PSE: break;    //pause bit, waiting for user input
        case LT: base.x--;  //move left
                 break;     
        case RT: base.x++;  //move right
                 break;
        case DWN:base.y++;  //move down
                 break;
        case UP: base.y--;  //move up
                 break;
        case STOP: ckWin = false;//pause
                   break;
        default:
            break;
    }
    
    if(base.x < 0)   //if row hits left wall
    {
        base.x = base.size;//spawn on opposite side
    }
    if(base.x > base.size)//if row hits right wall
    {
        base.x = 0;
    }
    if(base.y < 0)   //if column hits top of board
    {
        base.y = base.size + 2;
    }
    if(base.y > base.size + 2)//if column hits bottom of board
    {
        base.y = 0;
    }
    
    //Check if level up
    levelUp();
}

/*Function Definition:
 * Check when to print tail
 */
void Snake::ckPrint(int &j,int &i)
{ 
    if(nTail > 5)
    {
            //Print tail
         for(int z = 0;z < nTail;z++)
         {
             //(x,y) tail == head (x,y) then print tail
             if(xTail[z] == j && yTail[z] == i)
             {
                 cout << "X";
                 ckPnt = true;
             }
         }
         if(!ckPnt)
         {
             cout << " ";
         }
    }
    else if(nTail > 3)
    {
            //Print tail
         for(int z = 0;z < nTail;z++)
         {
             //(x,y) tail == head (x,y) then print tail
             if(xTail[z] == j && yTail[z] == i)
             {
                 cout << "O";
                 ckPnt = true;
             }
         }
         if(!ckPnt)
         {
             cout << " ";
         } 
    }
    else
    {
        //Print tail
        for(int z = 0;z < nTail;z++)
        {
            //(x,y) tail == head (x,y) then print tail
            if(xTail[z] == j && yTail[z] == i)
            {
                cout << "o";
                ckPnt = true;
            }
        }
        if(!ckPnt)
        {
            cout << " ";
        }
    }
}

/*Function Definition:
 * Calls template class to calculate new score.
 */
void Snake::levelUp()
{
   //if user eats token
    if(base.x == xToken && base.y == yToken)
    {
        PlusScr<int> s;
        score += 2;       
        xToken = rand() % base.size;//respawn tokens
        yToken = rand() % base.size;
        nTail++;                    //increment tail count
        
        score = s.getScor(score);   //get new score
        totScr += score;
    }
    
    //if player eats Mega Token
    if(base.x == xMega && base.y == yMega)
    {
        PlusScr<float> yea;
        megaScr += 5 ;
        xMega = rand() % base.size;//respawn Mega tokens
        yMega = rand() % base.size;
        megaScr = yea.getScor(megaScr);//get new score
        nTail += 2; //Mega token more points but tail grows faster
        totScr += megaScr;
    } 
}

/*Function Definition:
 * Change snake head if player has scored at least 3 Tails
 */
void Snake::levTwo()
{
    //pScore(score,megaScr);//print score
    pause(sec);           //pause console output

    cout << flush;
    for(int i = 0;i < base.size + 2;i++)
    {
        cout << "*";
    }
    cout << endl;
    for(int i = 0;i < base.size;i++)
    {
        for(int j = 0;j < base.size;j++)
        {
            if(j == 0)
            {
                cout << "*";
            }

            if(i == base.y && j == base.x)
            {
                cout << "Y";
            }
            else if(i == yToken && j == xToken)
            {
                cout << "Z";//output token
            }
            else if(i == yMega && j == xMega)
            {
                cout << "8";//output mega token
            }
            else
            {
                ckPnt = false;
                ckPrint(j,i);         
            }
            if(j == base.size - 1)
            {
                cout << "*";
            }
        }
        cout << endl;
    }
}

void Snake::levThr()
{
    //pScore(score,megaScr);//print score
    pause(sec);           //pause console output

    cout << flush;
    for(int i = 0;i < base.size + 2;i++)
    {
        cout << "*";
    }
    cout << endl;
    for(int i = 0;i < base.size;i++)
    {
        for(int j = 0;j < base.size;j++)
        {
            if(j == 0)
            {
                cout << "*";
            }

            if(i == base.y && j == base.x)
            {
                cout << "9";
            }
            else if(i == yToken && j == xToken)
            {
                cout << "Z";//output token
            }
            else if(i == yMega && j == xMega)
            {
                cout << "8";//output mega token
            }
            else
            {
                ckPnt = false;
                ckPrint(j,i);         
            }
            if(j == base.size - 1)
            {
                cout << "*";
            }
        }
        cout << endl;
    }
}

int Snake::getScr()
{
    return score;
}
 
/*Function Definition:
 * Outputs results depending on how well player did. Polymorphism
 */
void Snake::disScr() const
{
    //Polymorphism
    if(score < 150)
    {
        cout << "You did a meh.. ok job. not very high score" << endl;
    }
    else
    {
        cout << "You got an above amazing score. congrats!" << endl;
    }
}

/*Function Definition:
 * Checks if player has eaten tail. If so Game Over.
 */
bool Snake::gmStop()
{
    if(nTail > 0)
    {
        //Check if player hits/eats themselves Game Over
        for(int i = 0;i < nTail;i++)
        {
            if(xTail[i] == base.x && yTail[i] == base.y)
            {
                cout << endl << "Game Over" << endl;
                ckWin = false;  //game over
            }
        }
    }
    return ckWin;
}

/*Function Definition:
 * Overloads << operator to utilize cout, to output the score to console
 */
ostream &operator<< (ostream &say,const Snake &obj)
{
    cout << "Score: ";
    say << obj.score << " Mega-Score: " << obj.megaScr << endl;
}

/*Function Definition:
 * Calls SaveScr class to write player score to binary file
 */
void Snake::finWrte()
{
    SaveScr cap;

    cap.oFile();    //open file
    cap.wrteScr();  //write score
    cap.close();    //close file
}