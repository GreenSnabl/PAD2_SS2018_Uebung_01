/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TicTacToe.cpp
 * Author: snbl
 * 
 * Created on April 7, 2018, 7:42 PM
 */

#include "TicTacToe.h"
#include <iostream>
#include <sstream>
using std::cin;


TicTacToe::TicTacToe() {

}


TicTacToe::~TicTacToe() {}

void TicTacToe::play()
{
    Screen screen(15, 15);
    Screen gamefield(7,7);

    screen.fill(' ');

    gamefield.setString({0,0},
            " A B C "
            "1 | | 1"
            " ----- "
            "2 | | 2"
            " ----- "
            "3 | | 3"
            " A B C ");
    
    Screen winner(15,2);
    winner.setString({0,0}, "The winner is: ");
    
    string player1name, player2name;
    cin >> player1name >> player2name;
    
    Screen player1(player1name.size() + 1, 1);
    Screen player2(player2name.size() + 1, 1);
    
    player1.setString({1,0}, player1name);
    player2.setString({1,0}, player2name);
    
    for (int i = 0; i < 9; ++i)
        field[i] = ' ';
    
    
    
    screen.addSubScreen(&player1, {1,0}, "player1");
    screen.addSubScreen(&player2, {1,1}, "player2");
    screen.addSubScreen(&gamefield, {3,3}, "gamefield");
    
    while (true)
    {
        screen.getSubScreen("player1")->setChar({0,0}, '>');
        screen.getSubScreen("player2")->setChar({0,0}, ' ');
        screen.draw();
        if (makeTurn('x')) {
            winner.setString({0,1}, player1name);
            screen.addSubScreen(&winner, {0,13}, "winner");
            updateField(*screen.getSubScreen("gamefield"));
            screen.draw();
            return;
        }
        updateField(*screen.getSubScreen("gamefield"));
        if (fieldFull()) return;
        
        screen.getSubScreen("player2")->setChar({0,0}, '>');
        screen.getSubScreen("player1")->setChar({0,0}, ' ');
        screen.draw();
        if (makeTurn('o')) {
            winner.setString({0,1}, player2name);
            screen.addSubScreen(&winner, {0,13}, "winner");
            updateField(*screen.getSubScreen("gamefield"));
            screen.draw();
            return;
        }
        updateField(*screen.getSubScreen("gamefield"));
        if (fieldFull()) return;
    }
    
}
/*
bool TicTacToe::winningCondition(char c)
{ 
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
        {
            if (field[j + i*3] == c) ++count;        
        }
        if (count == 3) return true;
    }
    count = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
        if (field[i + 3*j] == c) ++count;
        }
        if (count == 3) return true;
    }
    count = 0;
    
    for (int i = 0; i < 3; ++i)
    {
        if (field[i*4] == c) ++count;
    }
    if (count == 3) return true;
    count = 0;
    
    for (int i = 1; i < 4; ++i) {
        if (field[i*2] == c) ++count;
    }
    if (count == 3) return true;
    return false;    
}
*/

bool TicTacToe::winningCondition(char c)
{
    return (checkCols(c) || checkRows(c) || checkDiagonal(c));
}


void TicTacToe::updateField(Screen& screen)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            screen.setChar({1 + 2*j, 1 + 2*i}, field[j + i * 3]);
        }
}

bool TicTacToe::makeTurn(char c)
{
    string str;
    int x, y;
    while (true) {
    cin >> str;
    
    x = columnToInt(str[0]);
    y = columnToInt(str[1]);
    if (field[x + y * 3] == ' '){
        field[x + y * 3] = c;
        break;
        }
    }
    return winningCondition(c);
}

int TicTacToe::columnToInt(char c)
{
    switch (c) {
        case 'A': case 'a': case '1': return 0;
        case 'B': case 'b': case '2': return 1;
        case 'C': case 'c': case '3': return 2;
    }
}

bool TicTacToe::checkRows(char c)
{
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
        {
            if (field[j + i*3] == c) ++count;        
        }
        if (count == 3) return true;
        count = 0;
    }
    return false;
}

bool TicTacToe::checkCols(char c)
{
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
        if (field[i + 3*j] == c) ++count;
        }
        if (count == 3) return true;
        count = 0;
    }
    return false;
}

bool TicTacToe::checkDiagonal(char c)
{
    int count = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (field[i*4] == c) ++count;
    }
    if (count == 3) return true;
    count = 0;
    
    for (int i = 1; i < 4; ++i) {
        if (field[i*2] == c) ++count;
    }
    if (count == 3) return true;
    return false;   
}

bool TicTacToe::fieldFull()
{
    int count = 0;
    for (int i = 0; i < 9; ++i)
    {
        if (field[i] == ' ') ++count;        
    }
    return count == 0;
}