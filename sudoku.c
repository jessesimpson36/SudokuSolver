#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

//this is the game board.
int board[9][9] = {};

//this is the possible numbers that the chosen box can be.
//true means that it is possible for the number to be chosen.
bool possibleNumbers[9] = {true, true, true, true, true, true, true, true, true};

//if the program is stuck, it will need to set this flag and speculate possible outcomes
bool isBlocked = false;


//prints the current board.
void printBoard(){

    printf("\n\n");
    printf("------------------------------------\n");
    for(int i = 0; i < 9; i++){
        for(int j = 0 ; j < 9; j++){
            printf(" %d |", board[i][j]);
        }
        printf("\n------------------------------------\n");
    }
    printf("\n\n");
}

//this will check if there are no zeroes on the board.
//when this is completely filled. The game will be completed.
bool checkIfBoardIsComplete(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if (board[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}

//clears the possible numbers
void clearPossibleNumbers(){
    for(int i = 0; i < 9; i++){
        possibleNumbers[i] = true;
    }
}

// assigns the possible Numbers array.
bool checkBox( int x, int y){
    for( int i = 0; i < 9; i++ ){
        //check the boxes vertically.
        if ( board[i][y] != 0){
            possibleNumbers[board[i][y] - 1] = false;
        }

        //checks the boxes horizontally.
        if (board[x][i] != 0){
            possibleNumbers[board[x][i] - 1] = false;
        }
    }

    //to find out what sector the box is,
    //we must use integer division and divide by 3
    int divX = x / 3;
    int divY = y / 3;

    int sectorXStart = divX * 3;
    int sectorYStart = divY * 3;

    //now that we have the sector, we have to iterate within the sector.
    for(int i = 0;  i < 3; i++){
        for(int j = 0; j < 3; j++){
            if ( board[sectorXStart + i][sectorYStart + j] != 0){
                possibleNumbers[board[sectorXStart + i][sectorYStart + j] - 1] = false;
            }
        }
    }
    return true;
}

//solves the current box given the index.
bool solveBox( int x, int y ){

    checkBox(x, y);

    //now that we've checked horizontal, vertical, and sector, we should now
    //check if there is only one  value in the possible numbers box.
    int possibleCount = 0;
    int savedValue = 0;
    for(int i = 1; i <= 9; i++){
        if( possibleNumbers[i - 1] == true){
            possibleCount++;
            savedValue = i;
        }
    }

    if (possibleCount == 1){
        board[x][y] = savedValue;
        printf("%d %d\n", x, y);
        clearPossibleNumbers();
        printBoard();
        isBlocked = false;
        return true;
    }
    clearPossibleNumbers();
    return false;
}


// reads the board from standard input.
void readBoard(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            char c = getchar();
            if (c == '\n'){
                c = getchar();
            }
            char string[2] = {};
            string[0] = c;
            string[1] = '\0';
            int number = atoi(string);
            board[i][j] = number;
        }
    }
}


//this is the main execution code.
int main(){
    readBoard();
    printBoard();
    while ( checkIfBoardIsComplete() == false){

        if( isBlocked == true ){
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    //do something
                }
            }
        }

        isBlocked = true;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if ( board[i][j] == 0){
                    solveBox(i, j);
                }
            }
        }
    }
    printBoard();
}
