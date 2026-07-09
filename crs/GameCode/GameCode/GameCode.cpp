#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const char ship = '#';
const char water = '~';
const char hit = 'X';
const char miss = '.';

const int boardSize = 10;

class Game {
private:
	char field[boardSize][boardSize];

public:
	void initializeField() {
		for (int row = 0; row < boardSize; row++) {
			for (int col = 0; col < boardSize; col++) {
				field[row][col] = water;
			}
		}
	}

	void printField() {
		char alphabet[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

		cout << "      ";

		for (int col = 0; col < boardSize; col++) {
			cout << alphabet[col] << " ";
		}

		cout << endl;

		for (int row = 0; row < boardSize; row++) {
			if (row == 9) {
				cout << " [" << row + 1 << "] ";
			}
			else {
				cout << " [ " << row + 1 << "] ";
			}

			for (int col = 0; col < boardSize; col++) {
				cout << field[row][col] << " ";
			}

			cout << endl;
		}
	}

	bool menu() {
		int choice;

		cout << " ----WELCOME TO SEA BATTLE----" << endl;
		cout << "|   [1] Start Game            |" << endl;
		cout << "|   [2] Exit                  |" << endl;
		cout << " -----------------------------" << endl;

		cin >> choice;

		switch (choice) {
		case 1: {
			int type;

			do {
				cout << "Choose a way to deploy ships:" << endl;
				cout << "[1] Automatic way" << endl;
				cout << "[2] Manual way" << endl;

				cin >> type;

				if (type == 1) {
					automaticShips();
				}
				else if (type == 2) {
					manualShips();
				}
				else {
					cout << "Error. Please try again." << endl;
				}

			} while (type != 1 && type != 2);

			return true;
		}

		case 2:
			cout << "Exit" << endl;
			return false;

		default:
			cout << "Error. Please try again." << endl;
			return menu();
		}
	}

	void automaticShips() {
		srand(time(0));

		int ships = 10;
		int count = 0;

		while (count < ships) {
			int row = rand() % boardSize;
			int col = rand() % boardSize;

			if (field[row][col] == water) {
				field[row][col] = ship;
				count++;
			}
		}

		cout << endl;
		cout << "Ships are placed automatically" << endl;
	}

	void manualShips() {
		int row;
		char colLetter;

		cout << endl;
		cout << "You need to place 10 ships" << endl;

		for (int i = 0; i < 10; i++) {
			printField();

			cout << endl;
			cout << "Ship " << i + 1 << endl;

			cout << "Row (1-10): ";
			cin >> row;

			cout << "Column (A-J): ";
			cin >> colLetter;

			int col;

			if (colLetter >= 'A' && colLetter <= 'J') {
				col = colLetter - 'A';
			}
			else if (colLetter >= 'a' && colLetter <= 'j') {
				col = colLetter - 'a';
			}
			else {
				cout << "Wrong column!" << endl;
				i--;
				continue;
			}

			if (row < 1 || row > 10) {
				cout << "Wrong row!" << endl;
				i--;
				continue;
			}

			if (field[row - 1][col] == ship) {
				cout << "There is already a ship here!" << endl;
				i--;
				continue;
			}

			field[row - 1][col] = ship;
		}

		cout << endl;
		cout << "Ships are placed." << endl;
	}
};

int main() {
	Game game;

	game.initializeField();

	bool gameStarted = game.menu();

	if (gameStarted) {
		cout << endl;
		game.printField();
	}

	return 0;
}




//