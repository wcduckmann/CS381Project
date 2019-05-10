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
	  carrierHealth = 4;
	  destroyerHealth = 2;
	  frigateHealth = 2;
	  speedboatHealth = 1;
	  alienHealth = 1;
}

bool Board::checkGameStatus(){
	  for(int i = 0; i < 10; i++){
	    for(int j = 0; j < 10; j++){
	    	if(gameBoard[i][j] != 0){
	    	  return false;
	    	}
	    }
	  }
	isGameOver = true;
	return true;
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
	for(int i = 0; i < 1; i++){
		gameBoard[row][column + i] = 5;
	}

}


bool Board::Fire(int row, int column){
	row--;
	column--;
	if(gameBoard[row][column] != 0){
		if(isShotLegal(row, column)){
			registerShot(gameBoard[row][column]);
			shotBoard[row][column] = true;
			return true;
		}
	}
	shotBoard[row][column] = 0;
	return false;
}

bool Board::isShotLegal(int row, int column){
	if(shotBoard[row][column] == true){
		return false;
	}
	return true;
}

void Board::registerShot(int id){

	switch(id){

	case 1:
	destroyerHealth--;
	if(destroyerHealth == 0)
	  destroyShip(id);
	break;
	case 2:
	carrierHealth--;
	if(carrierHealth == 0)
	  destroyShip(id);
	break;
	case 3:
	speedboatHealth--;
	if(speedboatHealth == 0)
	  destroyShip(id);
	break;
	case 4:
	frigateHealth--;
	if(frigateHealth == 0)
	  destroyShip(id);
	break;
	case 5:
	alienHealth--;
	if(alienHealth == 0)
	  destroyShip(id);
	break;
	default:
	break;
	}
}

void Board::destroyShip(int id){
	  for(int i = 0; i < 10; i++){
	    for(int j = 0; j < 10; j++){
	    	if(gameBoard[i][j] == id){
	    	  gameBoard[i][j] = 0;
	    	}
	    }
	  }
}
