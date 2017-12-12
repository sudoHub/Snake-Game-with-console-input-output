/* 
 * File:   SaveScr.h
 * Author: Brandon West
 *
 * Created on November 10, 2017, 1:59 PM
 * Purpose: SaveScr (Save Score) Class declaration.
 */

#ifndef SAVESCR_H
#define SAVESCR_H

#include "Snake.h"
#include <fstream>

class SaveScr : public Snake {
private:
    fstream script;
    int pos;
public:
    SaveScr();
    virtual ~SaveScr();
    virtual void disScr() const;
    void setScr(int);  //set score
    void oFile();   //opens file stream 
    void wrteScr(); //write score to file
    void close();   //close file stream
};

#endif /* SAVESCR_H */