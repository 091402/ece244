//
//  playMove.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

void playMove(GameState& game_state) {
    int row = game_state.get_selectedRow();
    int col = game_state.get_selectedColumn();
    if (game_state.get_gameBoard(row, col) == Empty) {
        game_state.set_moveValid(true);
        if (game_state.get_turn() == true) {
            game_state.set_gameBoard(row, col, X);
            if (game_state.get_gameBoard(0, 0) == X && game_state.get_gameBoard(0, 1) == X && game_state.get_gameBoard(0, 2) == X) {
                game_state.set_winCode(1);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(1, 0) == X && game_state.get_gameBoard(1, 1) == X && game_state.get_gameBoard(1, 2) == X) {
                game_state.set_winCode(2);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(2, 0) == X && game_state.get_gameBoard(2, 1) == X && game_state.get_gameBoard(2, 2) == X) {
                game_state.set_winCode(3);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 0) == X && game_state.get_gameBoard(1, 0) == X && game_state.get_gameBoard(2, 0) == X) {
                game_state.set_winCode(4);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 1) == X && game_state.get_gameBoard(1, 1) == X && game_state.get_gameBoard(2, 1) == X) {
                game_state.set_winCode(5);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 2) == X && game_state.get_gameBoard(1, 2) == X && game_state.get_gameBoard(2, 2) == X) {
                game_state.set_winCode(6);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 0) == X && game_state.get_gameBoard(1, 1) == X && game_state.get_gameBoard(2, 2) == X) {
                game_state.set_winCode(7);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 2) == X && game_state.get_gameBoard(1, 1) == X && game_state.get_gameBoard(2, 0) == X) {
                game_state.set_winCode(8);
                game_state.set_gameOver(true);
            }
            int flag = 0;
            for (int i = 0; i <= 2; i++)
                for (int j = 0; j <= 2; j++)
                    if (game_state.get_gameBoard(i, j) == Empty)
                        flag = 1;
            if (flag == 0) {
                game_state.set_gameOver(true);
                game_state.set_winCode(0);
            }
        }
        if (game_state.get_turn() == false) {
            game_state.set_gameBoard(row, col, O);
            if (game_state.get_gameBoard(0, 0) == O && game_state.get_gameBoard(0, 1) == O && game_state.get_gameBoard(0, 2) == O) {
                game_state.set_winCode(1);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(1, 0) == O && game_state.get_gameBoard(1, 1) == O && game_state.get_gameBoard(1, 2) == O) {
                game_state.set_winCode(2);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(2, 0) == O && game_state.get_gameBoard(2, 1) == O && game_state.get_gameBoard(2, 2) == O) {
                game_state.set_winCode(3);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 0) == O && game_state.get_gameBoard(1, 0) == O && game_state.get_gameBoard(2, 0) == O) {
                game_state.set_winCode(4);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 1) == O && game_state.get_gameBoard(1, 1) == O && game_state.get_gameBoard(2, 1) == O) {
                game_state.set_winCode(5);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 2) == O && game_state.get_gameBoard(1, 2) == O && game_state.get_gameBoard(2, 2) == O) {
                game_state.set_winCode(6);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 0) == O && game_state.get_gameBoard(1, 1) == O && game_state.get_gameBoard(2, 2) == O) {
                game_state.set_winCode(7);
                game_state.set_gameOver(true);
            }
            if (game_state.get_gameBoard(0, 2) == O && game_state.get_gameBoard(1, 1) == O && game_state.get_gameBoard(2, 0) == O) {
                game_state.set_winCode(8);
                game_state.set_gameOver(true);
            }
        }
        game_state.set_turn(!game_state.get_turn());
    }
    else {
        game_state.set_moveValid(false);
    }
}