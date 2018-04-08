/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: snbl
 *
 * Created on April 7, 2018, 11:42 AM
 */

#include "Screen.h"
#include "TicTacToe.h"
/*
 * 
 */
int main(int argc, char** argv) {
    /*
    Screen screen(20, 20);
    
    screen.fill('a');
    screen.draw();
    
    Screen screen2(screen);
    screen2.draw();
    
    Screen screen3(5, 5);
    screen3.fill('5');
    screen.addSubScreen(&screen3, {5,5}, "geier");
    screen.draw();
    */
    
    TicTacToe tic;
    tic.play();
    
    return 0;
}

