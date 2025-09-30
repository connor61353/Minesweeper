#pragma once
#ifndef HEADER_H
#define HEADER_H
#endif // !HEADER_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_X 120
#define KEY_F 102
#define KEY_C 99

using namespace std;

//structs
struct square {
	string type; //border, bomb, !bomb
	string display; //what is currently being shown to the player on interface
	int value; //the number of bombs surrounding that sqaure (not the square itself)
	bool flagged; //if the player has flagged the square
	bool bomb; //if the square contains a bomb
	bool selected; //if the square is selected
	bool checked; //if the square has been revealed yet
};

//constants
const string SELECTED_LEFT = ">"; //display character for the left side of selected square
const string SELECTED_RIGHT = "<"; //display character for the right side of selected square
const string UNSELECTED_LEFT = " "; //display character for the left side of unselected squares
const string UNSELECTED_RIGHT = " "; //display character for the right side of unselected squares
const string UNCHECKED = "/"; //display character of unmarked/unchecked square
const string EMPTY = " "; //display character of checked square with no value
const string FLAGGED = "X"; //display character of flagged (unchecked) square
const string BOMB = "*"; //display character of a revealed bomb
const int BOMB_CHANCE = 7; //chance that a bomb will spawn in a square (Ex. 1/10 chance)
const int ROWS = 20 + 2; //number of rows on the field + border spaces
const int COLS = 20 + 2; //number of cols on the field + border spaces

//prototypes
void refresh(square field[ROWS][COLS], int flagCount);
void switchSelect(square field[ROWS][COLS], int& x1, int& y1, int x2, int y2);
void createField(square field[ROWS][COLS], int& flagCount);
void flag(square field[ROWS][COLS], int x1, int y1, int& flagCount);
bool check(square field[ROWS][COLS], int x1, int y1);
bool win(square field[ROWS][COLS]);
void setValues(square field[ROWS][COLS]);
void clearFirstCheck(square field[ROWS][COLS], int& flagCount, int x1, int y1);
void removeBomb(square field[ROWS][COLS], int& flagCount, int x1, int y1);
void revealBombs(square field[ROWS][COLS]);