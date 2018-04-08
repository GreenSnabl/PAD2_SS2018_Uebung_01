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
using std::ostringstream;


TicTacToe::TicTacToe() {
    screen = new Screen(30,15);
    for (int i = 0; i < 9; ++i)
    field[i] = ' ';
}


TicTacToe::~TicTacToe() {
    delete screen;
}

void TicTacToe::play()
{
    
    string player1name, player2name;
    
    player1name = getName("player 1");
    player2name = getName("player 2");
    
    Screen background(30,15);
    background.fill(' ');

    Screen players(11, 2);
    players.fill(' ');
    
    Screen controlInstruction(30, 2);
    controlInstruction.fill(' ');
    controlInstruction.setString({0,0}, "Enter position ColRow ie.:");
    controlInstruction.setString({6,1}, "A1, a1, 11");
    
    players.setString({1,0}, player1name);
    players.setString({1,1}, player2name);
    
    
    Screen gamefield(7,7);
    gamefield.setString({0,0},
            " A B C "
            "1 | | 1"
            " ----- "
            "2 | | 2"
            " ----- "
            "3 | | 3"
            " A B C ");
   
    screen->addSubScreen(&background, {0,0}, "background");
    screen->addSubScreen(&gamefield, {7,3}, "gamefield");
    screen->addSubScreen(&players, {7,0}, "players");
    screen->addSubScreen(&controlInstruction, {0,12}, "controlInstruction");
                
    while (true)
    {
        if (takeTurn(player1name, 1, 'x')) return;
        if (takeTurn(player2name, 2, 'o')) return;
    }    
}

bool TicTacToe::winningCondition(char c) const
{
    return (checkCols(c) || checkRows(c) || checkDiagonal(c));
}


void TicTacToe::updateField(Screen* screen)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            screen->setChar({1 + 2*j, 1 + 2*i}, field[j + i * 3]);
        }
}

bool TicTacToe::setSquare(char c)
{
    string str;
    int x, y;
    while (true) {
    cin >> str;
    
    x = columnToInt(str[0]);
    y = columnToInt(str[1]);
    if (x < 3 && x >= 0 && y < 3 && y >= 0) {
    if (field[x + y * 3] == ' '){
        field[x + y * 3] = c;
        break;
     }
    }
    }
    return winningCondition(c);
}

int TicTacToe::columnToInt(char c)  const
{
    switch (c) {
        case 'A': case 'a': case '1': return 0;
        case 'B': case 'b': case '2': return 1;
        case 'C': case 'c': case '3': return 2;
    }
}

bool TicTacToe::checkRows(char c) const
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

bool TicTacToe::checkCols(char c) const
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

bool TicTacToe::checkDiagonal(char c) const
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

bool TicTacToe::fieldFull() const
{
    int count = 0;
    for (int i = 0; i < 9; ++i)
    {
        if (field[i] == ' ') ++count;        
    }
    return count == 0;
}

string TicTacToe::getName(std::string playerNr)
{
    
    string input;
    ostringstream os;
    Screen greeting(30, 15);
    greeting.fill(' ');

    
    os << "Hello " << playerNr << "!";
    greeting.setString({5,3},os.str());
    greeting.setString({2,5},"Please enter your name");
    greeting.setString({9,9}, "Length:");
    greeting.setString({5,10}, "1-10 characters");
    screen->addSubScreen(&greeting, {0,0}, "greeting");
    screen->draw();
    
    while (true) {
        cin >> input;
        if (input.size() <= 10 && input.size() > 0) break;
        
        screen->getSubScreen("greeting")->setString({0,13}, "Please enter a valid name!");
        screen->draw();
    }
    screen->clearSubScreens();
    return input;

}


bool TicTacToe::takeTurn(const string& name, int playerNumber, char c) {
        screen->getSubScreen("players")->setChar({0, (playerNumber + 1) % 2 }, '>');
        screen->getSubScreen("players")->setChar({0,  playerNumber % 2      }, ' ');
        screen->draw();
        
        if (setSquare(c)) {
            Screen winner(30,3);
            winner.fill(' ');
            winner.setString({4,0}, "The winner is: ");
            winner.setString({8,2}, name);
            
            screen->addSubScreen(&winner, {0,12}, "winner");
            updateField(screen->getSubScreen("gamefield"));
            screen->deleteSubScreen("controlInstruction");
            screen->draw();
            return true;
        }
        
        updateField(screen->getSubScreen("gamefield"));
        if (fieldFull()) {
            Screen draw(30,2);
            draw.fill(' ');
            draw.setString({0,0}, "The game ended in a draw :(");
            screen->addSubScreen(&draw, {0,13}, "draw");
            updateField(screen->getSubScreen("gamefield"));
            screen->deleteSubScreen("controlInstruction");
            screen->draw();
            return true;
        }
        return false;
}