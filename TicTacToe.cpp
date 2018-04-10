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
    for (int i = 0; i < 9; ++i) {
        field[i] = ' ';
    }
    
    Screen background(30,15);
    screen->addSubScreen(&background, {0,0}, "background");
    screen->getSubScreen("background")->fill(' ');

    Screen players(11, 2);
    screen->addSubScreen(&players, {7,0}, "players");
    screen->getSubScreen("players")->fill(' ');
    
    Screen controlInstruction(30, 2);
    screen->addSubScreen(&controlInstruction, {0,12}, "controlInstruction");
    screen->getSubScreen("controlInstruction")->fill(' ');
    screen->getSubScreen("controlInstruction")->setString({0,0}, "Enter position ColRow ie.:");
    screen->getSubScreen("controlInstruction")->setString({6,1}, "A1, a1, 11");
    
    Screen gamefield(7,7);
    screen->addSubScreen(&gamefield, {7,3}, "gamefield");
    screen->getSubScreen("gamefield")->setString({0,0},
            " A B C "
            "1 | | 1"
            " ----- "
            "2 | | 2"
            " ----- "
            "3 | | 3"
            " A B C ");
    
    Screen winner(30,3);
    screen->addSubScreen(&winner, {0,12}, "winner");
    screen->getSubScreen("winner")->fill(' ');
    screen->getSubScreen("winner")->setString({4,0}, "The winner is: ");
    screen->getSubScreen("winner")->setVisibility(false);
        
    Screen draw(27,1);
    screen->addSubScreen(&draw, {0,13}, "draw");
    screen->getSubScreen("draw")->fill(' ');
    screen->getSubScreen("draw")->setString({0,0}, "The game ended in a draw :(");        
    screen->getSubScreen("draw")->setVisibility(false);
    
    
}


TicTacToe::~TicTacToe() {
    delete screen;
}

void TicTacToe::play()
{
    
    string player1name, player2name;
    
    player1name = getName("player 1");
    player2name = getName("player 2");
    
    screen->getSubScreen("players")->setString({1,0}, player1name);
    screen->getSubScreen("players")->setString({1,1}, player2name);

    
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

string TicTacToe::getName(std::string playerName)
{
    
    string input;
    ostringstream os;
    Screen greeting(30, 15);
    screen->addSubScreen(&greeting, {0,0}, "greeting");
    screen->getSubScreen("greeting")->fill(' ');   
    os << "Hello " << playerName << "!";
    screen->getSubScreen("greeting")->setString({5,3},os.str());
    screen->getSubScreen("greeting")->setString({2,5},"Please enter your name");
    screen->getSubScreen("greeting")->setString({9,9}, "Length:");
    screen->getSubScreen("greeting")->setString({5,10}, "1-10 characters");
    screen->draw();
    
    while (true) {
        cin >> input;
        if (input.size() <= 10 && input.size() > 0) break;
        
        screen->getSubScreen("greeting")->setString({0,13}, "Please enter a valid name!");
        screen->draw();
    }
    screen->deleteSubScreen("greeting");
    return input;

}


bool TicTacToe::takeTurn(const string& name, int playerNumber, char c) {
        screen->getSubScreen("players")->setChar({0, (playerNumber + 1) % 2 }, '>');
        screen->getSubScreen("players")->setChar({0,  playerNumber % 2      }, ' ');
        screen->draw();
        
        if (setSquare(c)) {
            screen->getSubScreen("winner")->setString({8,2}, name);
            screen->getSubScreen("winner")->setVisibility(true);
            updateField(screen->getSubScreen("gamefield"));
            screen->getSubScreen("controlInstruction")->setVisibility(false);
            screen->draw();
            return true;
        }
        
        updateField(screen->getSubScreen("gamefield"));
        if (fieldFull()) {
            screen->getSubScreen("draw")->setVisibility(true);
            updateField(screen->getSubScreen("gamefield"));
            screen->getSubScreen("controlInstruction")->setVisibility(false);
            screen->draw();
            return true;
        }
        return false;
}