/*
 * Board.h
 *
 *  Created on: Apr 22, 2019
 *      Author: wduckhorn
 */

#ifndef INC_BOARD_H_
#define INC_BOARD_H_

class Board{
public:
	int gameBoard[10][10];
	bool isGameOver;

	Board();
	//void gameToBoard();
    bool checkGameStatus();

};



#endif /* INC_BOARD_H_ */
