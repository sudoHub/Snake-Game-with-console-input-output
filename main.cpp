/* 
 * File:   main.cpp
 * Author: Brandon West
 *
 * Created on November 26, 2017, 1:59 PM
 * Purpose: Snake game. Player must eat the 'Z' or '8' without eating 
 * themselves.
 */

#include "Game.h"
#include "Snake.h"
#include "SaveScr.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <termios.h>    // Terminal attributes

using namespace std;

//Function Prototype for input without pause
void stInput();
void outro(const Snake &ref);

int main(int argc, char** argv) {

    char input;
    bool gameOn = true;
    int i = 0;
    int num = 0;

    cout << setw(10) << "Snake" << endl;
    cout <<"Directions: \nYou must move the snake and eat either the standard " << endl
         << "token 'Z' for points, or eat '8' token for mega-points!" << endl;
    cout << " For every token eaten your snake tail grows in length." << endl
         << " If you eat your tail, you Lose." << endl << endl;
    cout << "Snake play Y/N" << endl;
    cin >> input;
    cout << "Enter number of players:" << endl;
    cin >> num;
  
    //Snake *user = {new Snake[num],new SaveScr[num]};
    Snake *user = new Snake[num];
    
    
    stInput();  //enable input

    for(i = 0;i < num;i++)
    {
        while(gameOn)
        {
            user[i].sBoard();   //display board
            user[i].input();    //check input buffer from player
            user[i].logic();    //Game logic
            cout << user[i];    //overload << and display score
            gameOn = user[i].gmStop();//check win
        }
        //output result
        cout << "\nThanks for playing" << endl;
        cout << "Your final " << user[i] << endl;
        
        if(num > 1)
        {
            //the way terminos removes the wait for input, if there is more
            //than one player, I cannot get program to pause for enter. 
            //once rtInput() is called Program immediately goes to next 
            //game, this method was the longest I could get it to pause,
            //and then run as expected.
            gameOn = true;
            cout << "Player " << i + 1 << " it's your turn!" << endl;
            cout << "Press enter when ready" << endl;
            int foo;
            do
            {
                foo = getchar();
            }while(foo != '\n' && foo != EOF);
        }
    }
    
    SaveScr *print = new SaveScr[num];
    int val = 0;    //transfer score
    
    for(i = 0;i < num;i++)
    {
        val = user[i].getScr();
        print[i].setScr(val);
        outro(user[i]);
        outro(print[i]);
    }
    for(i = 0;i < num;i++)
    {
        //write score to bin
        user[i].finWrte();
        
        //delete objects
        user[i].~Snake();
    }
    delete[] user;
    delete[] print;
    
    return 0;
}

/*Function Definition:
 * Terminal interface for serial communication ports. 
 * Purpose: real-time input
 */
void stInput() {
    struct termios t;
    
    // Remove the wait for user input
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    
    // Remove the wait for a newline and echoing
    tcgetattr(0, &t);
    t.c_lflag &= ~ICANON;
    t.c_lflag &= ~ECHO;
    
    t.c_lflag &= ~NOFLSH;
    tcsetattr(0, TCSANOW, &t);
}

void outro(const Snake &ref)
{
    //example polymorphism
    cout << "This is polymorphism for two different objects!" << endl;
    cout << "Thank you for playing" << endl;
   
    ref.disScr();
}