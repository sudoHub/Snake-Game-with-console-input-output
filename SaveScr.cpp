/* 
 * File:   SaveScr.cpp
 * Author: Brandon West
 * 
 * Created on December 9, 2017, 8:38 PM
 * Purpose: SaveScr (Save Score) class implementation
 */

#include "SaveScr.h"
#include <fstream>

SaveScr::SaveScr() {
   
}

SaveScr::~SaveScr() {
}

void SaveScr::disScr() const
{
    if(score < 150)
    {
        cout << "Not a very good job. Sorry maybe next time slugger." << endl;
    }
    else
    {
        cout << "You got an above average score. congrats!" << endl;
    }
}

void SaveScr::setScr(int scr)
{
    score = scr;
}

void SaveScr::oFile()
{   
   script.open("gmData.dat",ios::out | ios::binary);
   
   if(!script)
   {
       cout << "File open." << endl;
   }
}

//Write score to binary file
void SaveScr::wrteScr()
{  
    pos = script.tellp();
    
    if(!script)
    {
        script.seekg(pos,ios::cur);    //place writing position
        cout << "Writing score to bin file: " << endl;
        
        //write regular score
        script.write(reinterpret_cast<char*>(&score),sizeof(score));
        
        //write mega score
        script.write(reinterpret_cast<char*>(&megaScr),sizeof(megaScr));
        
        //write total score
        script.write(reinterpret_cast<char*>(&totScr),sizeof(totScr));
    }
    
}

void SaveScr::close()
{
   script.close(); 
}