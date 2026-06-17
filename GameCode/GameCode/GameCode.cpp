#include <iostream>
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
				char alphabet[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

				cout << "  ";

				for (int col = 0; col < boardSize; col++) {
						cout << alphabet[col] << " ";
				}
				cout << endl;

				for (int row = 0; row < boardSize; row++) {
						cout<< row+1 << " ";

					for (int col = 0; col < boardSize; col++) {

						cout << field[row][col] << " ";
					}
					cout << endl;
				}

			}
	};


int main() {

	Game game;	
	game.initializeField();
	game.printField();

	return 0;
}