#include "header.h"

//creates field
void createField(square field[ROWS][COLS], int& flagCount) {
	//seeds rand
	srand(time(NULL));

	square row[COLS]; //row building variable to be added to field
	int bombRoll; //rolls for if a space will have a bomb in it
	square bomb = { "bomb", UNCHECKED, 0, false, true, false, false };
	square notBomb = { "!bomb", UNCHECKED, 0, false, false, false, false };
	square border = { "border", "", 0, false, false, false, false };

	//each row
	for (int i = 0; i < ROWS; i++) {
		//top and bottom row
		if (i == 0 || i == ROWS - 1) {
			//fills row with borders
			for (int j = 0; j < COLS; j++) {
				field[i][j] = border;
			}
		}
		//middle rows
		else {
			//each col for a row
			for (int j = 0; j < COLS; j++) {
				//puts borders on row enders
				if (j == 0 || j == COLS - 1) {
					field[i][j] = border;
				}
				//fills field with randomized bombs
				else {
					bombRoll = rand() % BOMB_CHANCE;
					if (bombRoll == 0) {
						field[i][j] = bomb;
						flagCount++;
					}
					else {
						field[i][j] = notBomb;
					}
				}
			}
		}
	}
}

//finds all bombs and sets values
void setValues(square field[ROWS][COLS]) {
	//rows
	for (int i = 1; i < ROWS - 1; i++) {
		//cols
		for (int j = 1; j < COLS - 1; j++) {
			//if bomb is found
			if (field[i][j].bomb == true) {
				//increments values of all surrounding squares
				field[i-1][j-1].value++;
				field[i-1][j].value++;
				field[i-1][j+1].value++;
				field[i][j-1].value++;
				field[i][j+1].value++;
				field[i+1][j-1].value++;
				field[i+1][j].value++;
				field[i+1][j+1].value++;
			}
		}
	}
}

//displays field
void refresh(square field[ROWS][COLS], int flagCount) {
	system("cls");

	cout << "Flags: " << flagCount << endl;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			
			if (field[i][j].selected == false && field[i][j].type != "border") {
				cout << UNSELECTED_LEFT + field[i][j].display + UNSELECTED_RIGHT;
			}
			else if (field[i][j].selected == true){
				cout << SELECTED_LEFT + field[i][j].display + SELECTED_RIGHT;
			}
		}
		cout << endl;
	}
	cout << endl;
}

//moves selection
void switchSelect(square field[ROWS][COLS], int& x1, int& y1, int x2, int y2) {

	//moves selection status
	field[x1][y1].selected = false;
	field[x2][y2].selected = true;

	//sets selected position variables to new positions
	x1 = x2;
	y1 = y2;
}

//flags/unflags unchecked square
void flag(square field[ROWS][COLS], int x1, int y1, int& flagCount) {
	if (field[x1][y1].flagged == false && flagCount > 0) {
		field[x1][y1].flagged = true;
		field[x1][y1].display = FLAGGED;
		flagCount--;
	}
	else if (field[x1][y1].flagged == true) {
		field[x1][y1].flagged = false;
		field[x1][y1].display = UNCHECKED;
		flagCount++;
	}
}

//checks square for bomb, returns true if bomb is found
bool check(square field[ROWS][COLS], int x1, int y1) {
	bool change = true;

	field[x1][y1].checked = true;

	//checks for bomb
	if (field[x1][y1].bomb == true) {
		field[x1][y1].display = BOMB;
		return true;
	}
	//if no bomb
	else {
		//if square has value, reveals value
		if (field[x1][y1].value > 0 && field[x1][y1].type != "border") {
			field[x1][y1].display = to_string(field[x1][y1].value);
		}
		//if square is empty, reveals nearby spaces
		else {
			while (change == true) {
				change = false;
				field[x1][y1].display = EMPTY;
				//reveals all nearby squares
				if (field[x1 - 1][y1 - 1].type != "border" && field[x1 - 1][y1 - 1].checked == false) {
					check(field, x1 - 1, y1 - 1);
					change = true;
				}
				if (field[x1 - 1][y1].type != "border" && field[x1 - 1][y1].checked == false) {
					check(field, x1 - 1, y1);
					change = true;
				}
				if (field[x1 - 1][y1 + 1].type != "border" && field[x1 - 1][y1 + 1].checked == false) {
					check(field, x1 - 1, y1 + 1);
					change = true;
				}
				if (field[x1][y1 - 1].type != "border" && field[x1][y1 - 1].checked == false) {
					check(field, x1, y1 - 1);
					change = true;
				}
				if (field[x1][y1 + 1].type != "border" && field[x1][y1 + 1].checked == false) {
					check(field, x1, y1 + 1);
					change = true;
				}
				if (field[x1 + 1][y1 - 1].type != "border" && field[x1 + 1][y1 - 1].checked == false) {
					check(field, x1 + 1, y1 - 1);
					change = true;
				}
				if (field[x1 + 1][y1].type != "border" && field[x1 + 1][y1].checked == false) {
					check(field, x1 + 1, y1);
					change = true;
				}
				if (field[x1 + 1][y1 + 1].type != "border" && field[x1 + 1][y1 + 1].checked == false) {
					check(field, x1 + 1, y1 + 1);
					change = true;
				}
			}
		}
	}
	return false;
}

//returns true if all bombs have been flagged and all unflagged spaces are checked
bool win(square field[ROWS][COLS]) {
	bool win = true;

	//traverses field
	for (int i = 1; i < ROWS - 1; i++) {
		for (int j = 1; j < COLS - 1; j++) {
			//if a square contains a bomb
			if (field[i][j].bomb == true) {
				//and has not been flagged
				if (field[i][j].flagged != true) {
					//player has not won
					win = false;
				}
			}
			//if a square does not contain a bomb
			else {
				//and has not been checked yet
				if (field[i][j].checked == false) {
					//player has not won
					win = false;
				}
			}
		}
	}

	return win;
}

//removes bombs from first checked area
void clearFirstCheck(square field[ROWS][COLS], int& flagCount, int x1, int y1) {
	removeBomb(field, flagCount, x1-1, y1-1);
	removeBomb(field, flagCount, x1-1, y1);
	removeBomb(field, flagCount, x1-1, y1+1);
	removeBomb(field, flagCount, x1, y1-1);
	removeBomb(field, flagCount, x1, y1);
	removeBomb(field, flagCount, x1, y1+1);
	removeBomb(field, flagCount, x1+1, y1-1);
	removeBomb(field, flagCount, x1+1, y1);
	removeBomb(field, flagCount, x1+1, y1+1);

}

//removes bomb from a square
void removeBomb(square field[ROWS][COLS], int& flagCount, int x1, int y1) {
	//if bomb exists
	if (field[x1][y1].bomb == true) {
		//changes info markers
		field[x1][y1].type = "!bomb";
		field[x1][y1].bomb = false;
		flagCount--;

		//removes value marker from each square around removed bomb
		field[x1 - 1][y1 - 1].value--;
		field[x1 - 1][y1].value--;
		field[x1 - 1][y1 + 1].value--;
		field[x1][y1 - 1].value--;
		field[x1][y1 + 1].value--;
		field[x1 + 1][y1 - 1].value--;
		field[x1 + 1][y1].value--;
		field[x1 + 1][y1 + 1].value--;
	}
}

//reveals unflagged bombs on game loss
void revealBombs(square field[ROWS][COLS]) {
	for (int i = 1; i < ROWS - 1; i++) {
		for (int j = 1; j < COLS - 1; j++) {
			if (field[i][j].bomb == true && field[i][j].flagged == false) {
				field[i][j].display = BOMB;
			}
		}
	}
}

