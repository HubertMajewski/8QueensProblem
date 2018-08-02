/* 
 * File:   main.cpp
 * Author: Hubert Majewski (23476002)
 * Section: 22B
 *
 * Created on March 13, 2018, 3:21 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

//Global vars
static short size = 8; //Size is dynamic for 2D array
static int *board = NULL; // Collection of Column {y} indexes of x.
static int numSolutions = 0;

bool placeQueen(int);
bool printBoard();
bool checkPlacement(int);
bool printData();

int main(int argc, char *argv[]) {
    cout << "Enter A Positive Number: ";
    cin >> size; //size recieved from console
    while (size <= 0) { //If it is negative or 0
		cout << "Re-enter Positive Num: ";
		cin >> size;
    }
    
    board = new int[size]; //create a dynamic pointer which contains the dynamic size of the queens placed.
    placeQueen(0);
    printData();
    delete [] board;
}

bool placeQueen(int x) {
    for (board[x] = 0; board[x] < size; board[x]++) { // Column count
        if (checkPlacement(x)) { // Check for each on current working column. 

            if (x >= size - 1) {
                printBoard();
                numSolutions++;
                continue;
            } // Print next possible Solution if there exists if not, loop will run out and call ending

            if (!placeQueen(++x)) { // If Queen cannot be placed ANYWHERE on next column
                x--;
                continue; // Skip current for count and try next Column
            }
            return true;
        } else { // If there is no possible placement
            continue; // Cut for loop to try next y index
        }
    }

    x--;
    return false;
}

bool checkPlacement(int x) {
    for (int i = 0; i < x; i++) {
        if (board[x] == board[i]) //Vertical Test 
            return false;
        if ((x - i) == abs(board[x] - board[i])) //Diagnal Test
            return false;
    }
    return true;
}

bool printBoard() {
    int i, j, k, l; // i and j are main board's x and y while k and l are the tile's x and y
    typedef char box[5][7]; //Create me a datatype which makes 5 by 7 char variables (array).
    box bb, wb, *boardp[size][size]; //Had to rename board to board p on this line due to name conflict.
    box qb, qw; //Create black and qhite queen placed tiles.
    char b = (char) 219, w = ' ';
	
    //Fill in bb=black box and wb=whitebox
    for (i = 0; i < 5; i++)
        for (j = 0; j < 7; j++) {
            wb[i][j] = b;
            bb[i][j] = w;

            //Make Queens black and white tiles 
            if (i == 0 || i == 4) {
                qw[i][j] = w;
                qb[i][j] = b;
                continue;
            }
            if (i == 1) {
                if (j % 2 == 0) {
                    qw[i][j] = w;
                    qb[i][j] = b;
                } else {
                    qw[i][j] = b;
                    qb[i][j] = w;
                }
                continue;
            }
            if ((i >= 2 && i < 4) && (j > 0 && j < 6)) {
                qw[i][j] = b;
                qb[i][j] = w;
            } else {
                qw[i][j] = w;
                qb[i][j] = b;
            }
        }
		
    //fill board with pointers to bb and wb in alternate positions
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if ((i + j) % 2 == 0)
                if (board[i] == j) {
                    boardp[i][j] = &qb;
                } else {
                    boardp[i][j] = &wb;
                } else
                if (board[i] == j)
                boardp[i][j] = &qw;
            else
                boardp[i][j] = &bb;

    // print the board via the pointers in array board
    // first print upper border
    //    cout << " ";
    //    for (i = 0; i < 7 * size; i++)
    //        cout << '_';
    //    cout << endl;

    // now print the board
    for (i = 0; i < size; i++)
        for (k = 0; k < 5; k++) {
            cout << " " /*<< char(179)*/; //print left border
            for (j = 0; j < size; j++)
                for (l = 0; l < 7; l++)
                    cout << (*boardp[i][j])[k][l];
            cout /*<< char(179) */ << endl; // at end of line print bar and then newline
        }
    //before exiting print lower border
    //    cout << " ";
    //    for (i = 0; i < 7 * size; i++)
    //        cout << char(196);
    cout << endl;
}

bool printData() {
    cout << "There are " << numSolutions << " solutions for the " << size << " x " << size << " board." << endl;
}
