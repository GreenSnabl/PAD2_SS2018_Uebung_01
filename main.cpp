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
#include <unistd.h>
#include "TicTacToe.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    TicTacToe tic;
    tic.play();
    
    
    /*
    Screen s(40, 50);
    Screen subs(5,5);
    Screen subs2(5,1);
    subs2.setString({0,0}, "hallo");
    subs.fill('a');
    s.fill('b');
    s.setInt({4,7}, 1244);
    s.setString({2,4}, "Hello");
    s.draw();
    usleep(1000000);
    s.addSubScreen(&subs, {3, 29}, "subs");
    s.addSubScreen(&subs2, {20, 15}, "subs2");
    s.draw();
    for (int i = 0; i < 20; ++i){
        s.fill('c');
        s.getSubScreen("subs")->setAnchor({4,i});
        s.getSubScreen("subs2")->setAnchor({i+10,i});
        s.draw();
        usleep(300000);
    }
    */
    return 0;
}

