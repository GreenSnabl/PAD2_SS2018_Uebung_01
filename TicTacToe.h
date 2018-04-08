/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TicTacToe.h
 * Author: snbl
 *
 * Created on April 7, 2018, 7:42 PM
 */

#ifndef TICTACTOE_H
#define TICTACTOE_H
#include "Screen.h"

class TicTacToe {
public:
    TicTacToe();
    ~TicTacToe();
    void play();
    
private:
    bool winningCondition(char c);
    bool makeTurn(char c);
    void updateField(Screen* screen);
    int columnToInt(char c);
    
    bool fieldFull();
    bool checkRows(char c);
    bool checkCols(char c);
    bool checkDiagonal(char c);
    char field[9];
    
    string getName(string playerNr);
    
    
    Screen* screen;
    
};

#endif /* TICTACTOE_H */

