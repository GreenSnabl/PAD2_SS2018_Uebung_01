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
    TicTacToe(const TicTacToe&) = delete;
    ~TicTacToe();
    void play();
    
private:

    bool makeTurn(char c);
    void updateField(Screen* screen);
    string getName(string playerNr);
    
    
    int columnToInt(char c)  const;
    
    bool winningCondition(char c) const;
    bool fieldFull() const;
    bool checkRows(char c) const;
    bool checkCols(char c) const;
    bool checkDiagonal(char c) const;
    
    char field[9];
    Screen* screen;
    
};

#endif /* TICTACTOE_H */

