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
	bool shotBoard[10][10];
	bool isGameOver;
	int carrierHealth, destroyerHealth, frigateHealth, speedboatHealth, alienHealth;

	Board();
    bool checkGameStatus();
    void initializeBoard();
    void placeDestroyer(int row, int column);
    void placeCarrier(int row, int column);
    void placeSpeedboat(int row, int column);
    void placeFrigate(int row, int column);
    void placeAlien(int row, int column);
    bool Fire(int row, int column);
    bool isShotLegal(int row, int column);
    void registerShot(int id);
    void destroyShip(int id);



};



#endif /* INC_BOARD_H_ */
