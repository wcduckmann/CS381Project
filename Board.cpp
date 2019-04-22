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
	    }
	  }
	  isGameOver = false;
}

bool Board::checkGameStatus(){
	return isGameOver;
}
