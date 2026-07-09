#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const char ship = '#';
const char water = '~';
const char hit = 'X';
const char miss = '.';

const int boardSize = 10;


class Ship {
public:
    int size;

        Ship(int s) {
            size = s;
        }
};

class Game {
private:
    char playerField[boardSize][boardSize];
    char botField[boardSize][boardSize];

    int playerShipElements;
    int botShipElements;
    int playerHits;
    int botHits;
    int playerShots;
    int botShots;

public:
        void initializeField() {
            playerShipElements = 0;
            botShipElements = 0;
            playerHits = 0;
            botHits = 0;
            playerShots = 0;
            botShots = 0;
    
         for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {

                   playerField[row][col] = water;
                   botField[row][col] = water;
             }
          }
        }

        int getNumber(int min, int max) {
            int number;

            do { cin >> number;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error. Try again: ";
                    number = 0;
                } else if (
                    number < min || number > max) {
                    cout << "Try again: ";
                }

            } while (number < min || number > max);

                return number ;
        }

        int getColumn() {
            char Letter;
            int col = -1;

            do { cin >> Letter;
                if (Letter >= 'A' && Letter <= 'J') {
                    col = Letter - 'A';

                }  else if (Letter >= 'a' && Letter <= 'j') {
                    col = Letter - 'a';

                } else {
                    cout << " Try enter A-J: ";
                }

            } while (col == -1);

            return col;
        }

        char Direction() {
            char direction;

			do { cout << "Direction H - horizontal, V - vertical: ";
                 cin >> direction;

                if (direction >= 'a' && direction <= 'z') {
                    direction = direction -  32;
                } else if (direction != 'H' && direction != 'V') {
                    cout << "Try enter H or V: ";
                }
            } while (direction != 'H' && direction != 'V');

            return direction;
        }

        bool isInside(int row, int col) {
            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                return true;
            } else {
                return false;
            }
        }

        bool canPlaceShip (char field[boardSize][boardSize], int row, int col, int size, char direction) {

            for (int i = 0; i < size; i++) {
                 int currentRow = row;
                 int currentCol = col;

                 if (direction == 'H') {
                     currentCol = col + i;
                 } else {
                    currentRow = row + i;
                 }

                if (!isInside (currentRow, currentCol)) {
                    return false;
                }

                for (int r = currentRow - 1; r <= currentRow + 1; r++) {
                    for (int c = currentCol - 1; c <= currentCol + 1; c++) {
                        if (isInside(r, c) && field[r][c] == ship) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }

        void placeShip(char field[boardSize][boardSize], int row, int col, int size, char direction) {
            for (int i = 0; i < size; i++) {
                if (direction == 'H') {
                    field[row][col + i] = ship;
                } else {
                    field[row + i][col] = ship;
                }
            }
        }

        void automaticShips (char field[boardSize][boardSize], int& shipElements) {
            int shipSizes[10] = {4,3,3,2,2,2,1,1,1,1 };

            for (int i = 0; i < 10; i++) {
                Ship currentShip(shipSizes[i]);

                    bool placed = false;

                while (!placed) {
                    int row = rand() % boardSize;
                    int col = rand() % boardSize;

                    char direction;

                    if (rand() % 2 == 0) {
                        direction = 'H';
                    } else {
                        direction = 'V';
                    }

                    if ( canPlaceShip(field, row, col, currentShip.size, direction)) {
                         placeShip(field, row, col, currentShip.size, direction);
                         shipElements = shipElements + currentShip.size;
                         placed = true;
                    }
                }
            }
        }

        void manualShips() {
            int shipSizes[10] = {4,3,3,2,2,2,1,1,1,1};

            cout << endl;
            cout << "Place your ships:" << endl;

            for (int i = 0; i < 10; i++) {
                Ship currentShip(shipSizes[i]);

                printOneField(playerField, true);

                cout << endl;
                cout << "Ship " << i + 1 << ", size: " << currentShip.size << endl;

                cout << "Row (1-10): ";
                int row = getNumber(1, 10);
                row = row - 1;

                cout << "Column (A-J): ";
                int col = getColumn();

                char direction = 'H';

                if (currentShip.size > 1) {
 
                    direction = Direction();
                }
                if (!canPlaceShip(playerField, row, col, currentShip.size, direction)) {
                    cout << "You cannot place ship here!" << endl;
                    i--;
                 continue;
                }

                placeShip (playerField, row, col, currentShip.size, direction);
                playerShipElements = playerShipElements + currentShip.size;
            }
        }

         void printOneField(char field[boardSize][boardSize], bool showShips) {
             char alphabet[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

             cout << "      ";

             for (int col = 0; col < boardSize; col++) {
                 cout << alphabet[col] << " ";
             }

                cout << endl;

             for (int row = 0; row < boardSize; row++) {
                 if (row == 9) {
                     cout << " [" << row + 1 << "] ";
                 } else {
                     cout << " [ " << row + 1 << "] ";
                 }

                 for (int col = 0; col < boardSize; col++) {
                     if (field[row][col] == ship && showShips == false) {
                         cout << water << " ";
                     } else {
                         cout << field[row][col] << " ";
                     }
                 }
                    cout << endl;
             }
         }

        void printBothFields() {
            char alphabet[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

            cout << endl;
            cout << "    | YOUR FIELD                        | BOT FIELD" << endl;
            cout << "      ";

            for (int col = 0; col < boardSize; col++) {
                cout << alphabet[col] << " ";
            }

            cout << "          ";
            cout << "      ";

            for (int col = 0; col < boardSize; col++) {
                cout << alphabet[col] << " ";
            }

            cout << endl;

            for (int row = 0; row < boardSize; row++) {
                if (row == 9) {
                    cout << " [" << row + 1 << "] ";
                } else {
                    cout << " [ " << row + 1 << "] ";
                }

                for (int col = 0; col < boardSize; col++) {
                    cout << playerField[row][col] << " ";
                }

                cout << "          ";

                if (row == 9) {
                    cout << " [" << row + 1 << "] ";
                } else {
                    cout << " [ " << row + 1 << "] ";
                }

                for (int col = 0; col < boardSize; col++) {
                    if (botField[row][col] == ship) {
                        cout << water << " ";
                    } else {
                        cout << botField[row][col] << " ";
                    }
                }
                   cout << endl;
            }
        }

        void playerShoot() {
            cout << endl;
            cout << "Your shot" << endl;

            cout << "Row (1-10): ";
            int row = getNumber(1, 10);
            row = row - 1;

            cout << "Column (A-J): ";
            int col = getColumn();

            if (botField[row][col] == hit || botField[row][col] == miss) {
                cout << " You already shot here!" << endl;
                playerShoot();
             return;
            }

            playerShots++;

            if (botField[row][col] == ship) {
                botField[row][col] = hit;
                playerHits++;
                cout << "You hit!" << endl;
            } else {
                botField[row][col] = miss;
                cout << "You missed !" << endl;
            }
        }

         void botShoot() {
             int row;
             int col;

             do { row = rand() % boardSize;
                  col = rand() % boardSize;
             } while (playerField[row][col] == hit || playerField[row][col] == miss);

             botShots++;

             cout << endl;
             cout << "Bot shot: row " << row + 1 << ", column " << char('A' + col) << endl;

             if (playerField[row][col] == ship) {
                 playerField[row][col] = hit;

                 botHits++;

                 cout << "Bot hit your ship!" << endl;
             } else {
                 playerField[row][col] = miss;
                 cout << "Bot missed!" << endl;
             }
         }

         void printScore() {
         cout << endl;
         cout << "Your shots: " << playerShots << endl;
         cout << "Your hits: " << playerHits << " / " << botShipElements << endl;
         cout << "Your misses: " << playerShots - playerHits << endl;

         cout << endl;
         cout << "Bot shots: " << botShots << endl;
         cout << "Bot hits: " << botHits << " / " << playerShipElements << endl;
         cout << "Bot misses: " << botShots - botHits << endl;
          }

        bool playerWon() {
            if (playerHits == botShipElements) {
                return true;
            } else {
                return false;
            }
        }

        bool botWon() {
            if (botHits == playerShipElements) {
                return true;
            } else {
                return false;
            }
        }

        void play() {
            while (!playerWon() && !botWon()) {
                printBothFields();
                printScore();
                playerShoot();

                if (!playerWon()) {
                    botShoot();
                }
            }

         cout << endl;
         cout << "!!!!!!!!!! GAME OVER !!!!!!!!!!" << endl;

         printBothFields();
         printScore();

         if (playerWon()) {
             cout << endl;
             cout << "YOU WIN!" << endl;
         } else {
             cout << endl;
             cout << "YOU LOSE!" << endl;
         }
        }

    void menu() {
        int choice;

        cout << " ----WELCOME TO SEA BATTLE----" << endl;
        cout << "|   [1] Start Game            |" << endl;
        cout << "|   [2] Exit                  |" << endl;
        cout << " -----------------------------" << endl;

        choice = getNumber(1, 2);

        switch (choice) {
        case 1: {
            int type;

            cout << "Choose a way to deploy your ships:" << endl;
            cout << "[1] Automatic way" << endl;
            cout << "[2] Manual way" << endl;

            type = getNumber(1, 2);

            if (type == 1) {
                automaticShips(playerField, playerShipElements);
                cout << "Your ships are placed automatically" << endl;
            } else {
                manualShips();
            }

            automaticShips(botField, botShipElements);
            cout << "Bot ships are placed" << endl;

            play();

         break;
        }

        case 2:
            cout << "Exit" << endl;
         break;
        }
    }
};

int main() {
    srand(time(0));

    Game game;

    game.initializeField();
    game.menu();

    return 0;
}

