#include "header.h"

int main() {

	//field variable modified for borders
	square field[ROWS][COLS];

	//selection movement variables
	int x1 = ROWS/2; //starting selection row
	int y1 = COLS/2; //starting selection col
	int x2 = x1; //ending selection row
	int y2 = y1; //ending selection col
	bool change; //if field has been modified in a loop
	bool gameOver = false; //checks if bomb has been checked
	bool won = false;
	bool firstCheck = true;

	//game variables
	int flagCount = 0; //number of flags/bombs left to use

	//initiates game
	cout << "-Welcome to Minesweeper!-\n\n";
	cout << "Press C to clear a space\n";
	cout << "Press F to flag a space\n\n";
	system("pause");

	//creates field
	createField(field, flagCount);

	//sets values of all spaces next to a bomb
	setValues(field);

	//sets starting selection square
	field[x1][y1].selected = true;

	//displays field
	refresh(field, flagCount);

	while (gameOver == false) {
		//sets change to false
		change = false;

		switch (_getch()) {

		case KEY_C:
			//gurentees first check to be safe
			if (firstCheck) {
				clearFirstCheck(field, flagCount, x1, y1);
				firstCheck = false;
			}
			//checks bomb
			if (field[x1][y1].checked == false && field[x1][y1].flagged == false) {
				gameOver = check(field, x1, y1);
			}
			break;

		case KEY_F:
			//flags square
			if (!firstCheck) {
				if (field[x1][y1].checked == false) {
					flag(field, x1, y1, flagCount);
				}
			}
			break;

		case KEY_UP:
			//moves selection square up
			if (field[x1 - 1][y1].type != "border") {
				x2 = x1 - 1;
			}
			change = true;
			break;

		case KEY_DOWN:
			//moves selection square left
			if (field[x1 + 1][y1].type != "border") {
				x2 = x1 + 1;
			}
			change = true;
			break;

		case KEY_LEFT:
			//moves selection square left
			if (field[x1][y1 - 1].type != "border") {
				y2 = y1 - 1;
			}
			change = true;
			break;

		case KEY_RIGHT:
			//moves selection square right
			if (field[x1][y1 + 1].type != "border") {
				y2 = y1 + 1;
			}
			change = true;
			break;
		}

		if (change) {
			switchSelect(field, x1, y1, x2, y2);
		}

		refresh(field, flagCount);

		//win check
		if (flagCount <= 0) {
			if (win(field)) {
				gameOver = true;
				won = true;
			}
		}
	}

	if (won) {
		cout << "\n-You Win!-\n\n";
	}
	else {
		revealBombs(field);
		refresh(field, flagCount);
		cout << "\n-You Lose!-\n\n";
	}

	system("pause");
	return 0;
}