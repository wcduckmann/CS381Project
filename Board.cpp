/*
 * Board.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: wduckhorn
 */

#include "Board.h"

Board::Board(){
	  for(int i = 0; i < 10; i++){
	    for(int j = 0; j < 10; j++){
	      gameBoard[i][j] = 0;
	      shotBoard[i][j] = false;
	    }
	  }
	  isGameOver = false;
}

bool Board::checkGameStatus(){
	return isGameOver;
}

void Board::placeDestroyer(int row, int column){
	for(int i = 0; i < 2; i++){
		gameBoard[row][column + i] = 1;
	}

}

void Board::placeCarrier(int row, int column){
	for(int i = 0; i < 4; i++){
		gameBoard[row][column + i] = 2;
	}

}

void Board::placeSpeedboat(int row, int column){
	for(int i = 0; i < 1; i++){
		gameBoard[row][column + i] = 3;
	}

}

void Board::placeFrigate(int row, int column){
	for(int i = 0; i < 2; i++){
		gameBoard[row][column + i] = 4;
	}

}

void Board::placeAlien(int row, int column){
	for(int i = 0; i < 2; i++){
		gameBoard[row][column + i] = 5;
	}

}


bool Board::Fire(int row, int column){
	if(gameBoard[row][column] != 0){
		shotBoard[row][column] = true;
		return true;
	}
	shotBoard[row][column] = true;
	return false;
}
