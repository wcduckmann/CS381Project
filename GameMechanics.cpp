
#include<iostream>

using namespace std;
struct Ship{
  int ID;
  int x;
  int y;
  char Orientation;
  int size;
  int health;
};

struct Board{
	int gameBoard[10][10];
  bool isGameOver;
  Ship ships[5];
  Ship selectedShip;
  int selectedShipIndex;
};

void initializeBoard(Board& Board);
void printBoard(Board& Board);
void placeShips(Board& Board);
void placeCarrier(Board& Board);
void placeDestroyer(Board& Board);
void placeFrigate(Board& Board);
void placeSpeedboat(Board& Board);
void placeAlien(Board& Board);
void selectShip(Board& Board);
bool canForward(Board& Board);
void moveForward(Board& Board);
bool canBackward(Board& Board);
void moveBackward(Board& Board);
void Fire(Board& Board);
void destroyShip(Ship ship, Board& Board);
char selectAction();

int main(){
  Board playerBoard;
  initializeBoard(playerBoard);
  printBoard(playerBoard);
  placeShips(playerBoard);
  printBoard(playerBoard);
  selectShip(playerBoard);
  char selection = selectAction();
  switch(selection){
  case 'F':
  if(canForward(playerBoard)){
    moveForward(playerBoard);
    cout << "moved x:" << playerBoard.selectedShip.x << " y: " << playerBoard.selectedShip.y << endl;
  }
  printBoard(playerBoard);
  break;
  case 'B':
  if(canBackward(playerBoard)){
    moveBackward(playerBoard);
    cout << "moved x:" << playerBoard.selectedShip.x << " y: " << playerBoard.selectedShip.y << endl;
  }
  printBoard(playerBoard);
  break;
  case 'S':
  Fire(playerBoard);
  cout << playerBoard.ships[playerBoard.selectedShipIndex].health << endl;
  printBoard(playerBoard);
  break;
  default:
  cout << "Unsure what command to do." << endl;
  break;
  }
  return 0;
}

void initializeBoard(Board& Board){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      Board.gameBoard[i][j] = 0;
    }
  }

}

void printBoard(Board & Board){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
     cout << Board.gameBoard[i][j] << "  ";
    }
    cout << endl;
  }

}

void placeShips(Board& Board){
  placeCarrier(Board);
  printBoard(Board);

  placeDestroyer(Board);
  printBoard(Board);

  placeFrigate(Board);
  printBoard(Board);

  placeSpeedboat(Board);
  printBoard(Board);

  placeAlien(Board);

}

void placeCarrier(Board& Board){
  int carrierX;
  int carrierY;
  char carrierOrien;
  cout << "Enter the row of the front of your carrier [0 - 9]: ";
  cin >> carrierX;
  cout << "Enter the column of the front of your carrier [0 - 9]: ";
  cin >> carrierY;
  cout << "Enter the orientation of your carrier [H, V]: ";
  cin >> carrierOrien;
  Board.ships[0].ID = 1;
  Board.ships[0].x = carrierX;
  Board.ships[0].y = carrierY;
  Board.ships[0].Orientation = carrierOrien;
  Board.ships[0].size = 5;
  Board.ships[0].health = 5;
  if(carrierOrien == 'H'){
    if(carrierY >= 6){
      cout << "Carrier location invalid." << endl;
      placeCarrier(Board);
    }
    else{
      for(int i = 0; i < 5; i++){
        Board.gameBoard[carrierX][carrierY + i] = 1;
      }
    }
  }
  else if(carrierOrien == 'V'){
    if(carrierX >= 6){
      cout << "Carrier location invalid." << endl;
      placeCarrier(Board);
    }
    else{
      for(int i = 0; i < 5; i++){
        Board.gameBoard[carrierX + i][carrierY] = 1;
      }
    }
  }
}

void placeDestroyer(Board& Board){
  int destX;
  int destY;
  char destOrien;
  bool flag = true;
  cout << "Enter the row of the front of your destroyer [0 - 9]: ";
  cin >> destX;
  cout << "Enter the column of the front of your destroyer [0 - 9]: ";
  cin >> destY;
  cout << "Enter the orientation of your destroyer [H, V]: ";
  cin >> destOrien;
  Board.ships[1].ID = 2;
  Board.ships[1].x = destX;
  Board.ships[1].y = destY;
  Board.ships[1].Orientation = destOrien;
  Board.ships[1].size = 4;
  Board.ships[1].health = 4;
  if(destOrien == 'H'){
    if(destY >= 7){
      cout << "Destroyer location invalid." << endl;
      placeDestroyer(Board);
    }
    else{
      for(int i = 0; i < 4; i++){
        if(Board.gameBoard[destX][destY + i] != 0){
          cout << "Destroyer location invalid." << endl;
          flag = false;
          placeDestroyer(Board);
        }
      }
      if(flag){
        for(int i = 0; i < 4; i++){
          Board.gameBoard[destX][destY + i] = 2;
        }
      }
    }
  }
  else if(destOrien == 'V'){
    if(destX >= 7){
      cout << "Destroyer location invalid." << endl;
      placeDestroyer(Board);
    }
    else{
      for(int i = 0; i < 4; i++){
        if(Board.gameBoard[destX + i][destY] != 0){
          cout << "Destroyer location invalid." << endl;
          flag = false;
          placeDestroyer(Board);
        }
      }
      if(flag){
        for(int i = 0; i < 4; i++){
          Board.gameBoard[destX + i][destY] = 2;
        }
      }
    }
  }
}

void placeFrigate(Board& Board){
  int destX;
  int destY;
  char destOrien;
  bool flag = true;
  cout << "Enter the row of the front of your frigate [0 - 9]: ";
  cin >> destX;
  cout << "Enter the column of the front of your frigate [0 - 9]: ";
  cin >> destY;
  cout << "Enter the orientation of your frigate [H, V]: ";
  cin >> destOrien;
  Board.ships[2].ID = 3;
  Board.ships[2].x = destX;
  Board.ships[2].y = destY;
  Board.ships[2].Orientation = destOrien;
  Board.ships[2].size = 3;
  Board.ships[2].health = 3;
  if(destOrien == 'H'){
    if(destY >= 8){
      cout << "Frigate location invalid." << endl;
      placeFrigate(Board);
    }
    else{
      for(int i = 0; i < 3; i++){
        if(Board.gameBoard[destX][destY + i] != 0){
          cout << "Frigate location invalid." << endl;
          flag = false;
          placeFrigate(Board);
        }
      }
      if(flag){
        for(int i = 0; i < 3; i++){
          Board.gameBoard[destX][destY + i] = 3;
        }
      }
    }
  }
  else if(destOrien == 'V'){
    if(destX >= 8){
      cout << "Frigate location invalid." << endl;
      placeFrigate(Board);
    }
    else{
      for(int i = 0; i < 3; i++){
        if(Board.gameBoard[destX + i][destY] != 0){
          cout << "Frigate location invalid." << endl;
          flag = false;
          placeFrigate(Board);
        }
      }
      if(flag){
        for(int i = 0; i < 3; i++){
          Board.gameBoard[destX + i][destY] = 3;
        }
      }
    }
  }
}

void placeSpeedboat(Board& Board){
  int destX;
  int destY;
  char destOrien;
  bool flag = true;
  cout << "Enter the row of the front of your speedboat [0 - 9]: ";
  cin >> destX;
  cout << "Enter the column of the front of your speedboat [0 - 9]: ";
  cin >> destY;
  cout << "Enter the orientation of your speedboat [H, V]: ";
  cin >> destOrien;
  Board.ships[3].ID = 4;
  Board.ships[3].x = destX;
  Board.ships[3].y = destY;
  Board.ships[3].Orientation = destOrien;
  Board.ships[3].size = 2;
  Board.ships[3].health = 2;
  if(destOrien == 'H'){
    if(destY >= 9){
      cout << "Speedboat location invalid." << endl;
      placeSpeedboat(Board);
    }
    else{
      for(int i = 0; i < 2; i++){
        if(Board.gameBoard[destX][destY + i] != 0){
          cout << "Speedboat location invalid." << endl;
          flag = false;
          placeSpeedboat(Board);
        }
      }
      if(flag){
        for(int i = 0; i < 2; i++){
          Board.gameBoard[destX][destY + i] = 4;
        }
      }
    }
  }
  else if(destOrien == 'V'){
    if(destX >= 9){
      cout << "Speedboat location invalid." << endl;
      placeSpeedboat(Board);
    }
    else{
      for(int i = 0; i < 2; i++){
        if(Board.gameBoard[destX + i][destY] != 0){
          cout << "Speedboat location invalid." << endl;
          flag = false;
          placeSpeedboat(Board);
        }
      }
      if(flag){
        for(int i = 0; i < 2; i++){
          Board.gameBoard[destX + i][destY] = 4;
        }
      }
    }
  }
}

void placeAlien(Board& Board){
  int destX;
  int destY;
  char destOrien;
  bool flag = true;
  cout << "Enter the row of the front of your alien ship [0 - 9]: ";
  cin >> destX;
  cout << "Enter the column of the front of your alien ship [0 - 9]: ";
  cin >> destY;
  cout << "Enter the orientation of your alien ship [H, V]: ";
  cin >> destOrien;
  Board.ships[4].ID = 5;
  Board.ships[4].x = destX;
  Board.ships[4].y = destY;
  Board.ships[4].Orientation = destOrien;
  Board.ships[4].size = 1;
  Board.ships[4].health = 1;
  if(destOrien == 'H'){
    if(destY >= 10){
      cout << "Alien ship location invalid." << endl;
      placeAlien(Board);
    }
    else{
      for(int i = 0; i < 1; i++){
        if(Board.gameBoard[destX][destY + i] != 0){
          cout << "Alien ship location invalid." << endl;
          flag = false;
          placeAlien(Board);
        }
      }
      if(flag){
        for(int i = 0; i < 1; i++){
          Board.gameBoard[destX][destY + i] = 5;
        }
      }
    }
  }
  else if(destOrien == 'V'){
    if(destX >= 10){
      cout << "Alien ship location invalid." << endl;
      placeAlien(Board);
    }
    else{
      for(int i = 0; i < 1; i++){
        if(Board.gameBoard[destX + i][destY] != 0){
          cout << "Alien location invalid." << endl;
          flag = false;
          placeAlien(Board);
        }
      }
      if(flag){
        for(int i = 0; i < 1; i++){
          Board.gameBoard[destX + i][destY] = 5;
        }
      }
    }
  }
}

void selectShip(Board& Board){
  int index;
  cout << "Select ship:";
  cin >> index;

  index -= 1;

  Board.selectedShip = Board.ships[index];
  Board.selectedShipIndex = index;
}

bool canForward(Board& Board){
  if(Board.selectedShip.Orientation == 'H'){
    if(Board.selectedShip.x == 0){
      return false;
    }
    if(Board.gameBoard[Board.selectedShip.x - 1][Board.selectedShip.y] == 0){
      return true;
    }
    return false;
  }
  else if(Board.selectedShip.Orientation == 'V'){
    if(Board.selectedShip.y == 0){
      return false;
    }
    if(Board.gameBoard[Board.selectedShip.x][Board.selectedShip.y - 1] == 0){
      return true;
    }
    return false;
  }
}

void moveForward(Board& Board){
  if(Board.selectedShip.Orientation == 'H'){
    Board.gameBoard[Board.selectedShip.x][Board.selectedShip.y - 1] = Board.selectedShip.ID;
    Board.selectedShip.y--;
    Board.gameBoard[Board.selectedShip.x][Board.selectedShip.y + Board.selectedShip.size] = 0;
    Board.ships[Board.selectedShipIndex].y--;
  }
  else if(Board.selectedShip.Orientation == 'V'){
    Board.gameBoard[Board.selectedShip.x - 1][Board.selectedShip.y] = Board.selectedShip.ID;
    Board.selectedShip.x--;
    Board.gameBoard[Board.selectedShip.x  + Board.selectedShip.size][Board.selectedShip.y] = 0;
    Board.ships[Board.selectedShipIndex].x--;
  }

}

bool canBackward(Board& Board){

  if(Board.selectedShip.Orientation == 'H'){
    if((Board.selectedShip.x + Board.selectedShip.size) == 10){
      return false;
    }
    if(Board.gameBoard[Board.selectedShip.x + Board.selectedShip.size][Board.selectedShip.y] == 0){
      return true;
    }
    return false;
  }
  else if(Board.selectedShip.Orientation == 'V'){
    if((Board.selectedShip.y  + Board.selectedShip.size) == 10){
      return false;
    }
    if(Board.gameBoard[Board.selectedShip.x][Board.selectedShip.y + Board.selectedShip.size] == 0){
      return true;
    }
    return false;
  }

}

void moveBackward(Board& Board){
  if(Board.selectedShip.Orientation == 'H'){
    Board.gameBoard[Board.selectedShip.x][Board.selectedShip.y] = 0;
    Board.gameBoard[Board.selectedShip.x][Board.selectedShip.y + Board.selectedShip.size] = Board.selectedShip.ID;
    Board.selectedShip.y++;
    Board.ships[Board.selectedShipIndex].y++;
  }
  else if(Board.selectedShip.Orientation == 'V'){
    Board.gameBoard[Board.selectedShip.x][Board.selectedShip.y] = 0;
    Board.gameBoard[Board.selectedShip.x + Board.selectedShip.size][Board.selectedShip.y] = Board.selectedShip.ID;
    Board.selectedShip.x++;
    Board.ships[Board.selectedShipIndex].x++;
  }
}

void Fire(Board& Board){
   int xCoord;
   int yCoord;
   cout << "Select row to fire on:";
   cin >> xCoord;

    cout << "Select column to fire on:";
    cin >> yCoord;

    switch(Board.gameBoard[xCoord][yCoord]){
      case 1:
      cout << "Carrier has been hit" << endl;
      Board.ships[0].health--;
      if(Board.ships[0].health == 0)
        destroyShip(Board.ships[0], Board);
      break;
      case 2:
      cout << "Destroyer has been hit" << endl;
      Board.ships[1].health--;
      if(Board.ships[1].health == 0)
        destroyShip(Board.ships[1], Board);
      break;
      case 3:
      cout << "Frigate has been hit" << endl;
      Board.ships[2].health--;
      if(Board.ships[2].health == 0)
        destroyShip(Board.ships[2], Board);
      break;
      case 4:
      cout << "Speedboat has been hit" << endl;
      Board.ships[3].health--;
      if(Board.ships[3].health == 0)
        destroyShip(Board.ships[3], Board);
      break;
      case 5:
      cout << "Alien ship has been hit" << endl;
      Board.ships[4].health--;
      if(Board.ships[4].health == 0)
        destroyShip(Board.ships[4], Board);
      break;
      default:
      cout << "Miss" << endl;
      break;
    }
}

void destroyShip(Ship ship, Board& Board){
  if(ship.Orientation == 'H'){
    for(int i = 0; i < ship.size; i++){
      Board.gameBoard[ship.x][ship.y + i] = 0;
    }
    switch(ship.ID){
      case 1:
      cout << "Carrier has been destroyed" << endl;
      break;
      case 2:
      cout << "Destroyer has been destroyed" << endl;
      break;
      case 3:
      cout << "Frigate has been destroyed" << endl;
      break;
      case 4:
      cout << "Speedboat has been destroyed" << endl;
      break;
      case 5:
      cout << "Alien ship has been destroyed" << endl;
      break;
    }
  }
  if(ship.Orientation == 'V'){
    for(int i = 0; i < ship.size; i++){
      Board.gameBoard[ship.x + i][ship.y] = 0;
    }
    switch(ship.ID){
      case 1:
      cout << "Alien ship has been destroyed" << endl;
      break;
      case 2:
      cout << "Destroyer has been destroyed" << endl;
      break;
      case 3:
      cout << "Frigate has been destroyed" << endl;
      break;
      case 4:
      cout << "Speedboat has been destroyed" << endl;
      break;
      case 5:
      cout << "Alien ship has been destroyed" << endl;
      break;
    }
  }
}

char selectAction(){
  char action;
  cout << "Select which action to do (Move Forward (F), Move Backward (B), Shoot Missile(S)): ";
  cin >> action;
  return action;
}
