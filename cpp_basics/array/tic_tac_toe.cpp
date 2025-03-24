#include <iostream>
#include <vector>
#include <cstdlib> //provide functionality for general-purpose utility functions
#include <unistd.h>

enum marks {X = 1, O =-1, EMPTY =0}; //custom enum 
int board[3][3]; 
int currentPlayer; 
int moves = 0; 


void clearBoard ()
{
    std::cout << "\033[2J\033[H"; // Clears the screen and moves the cursor to the top-left
    for (int i =0; i <3; i++)
    {
        for (int j=0; j<3; j++)
        {
            board[i][j] = EMPTY; //empty every cell 
        }
    }
    srand(time(NULL));
    currentPlayer = (rand() %2 ==0) ? X:O; 
}


void putMark (int i, int j)
{
    board[i][j] = currentPlayer;
}


bool isWin (int mark)
{
    int win = 3*mark; //in order to win you need to have 3 consecutive marks 

    return ((board[0][0] + board[0][1] + board[0][2] == win) // row 0
    || (board[1][0] + board[1][1] + board[1][2] == win) // row 1
    || (board[2][0] + board[2][1] + board[2][2] == win) // row 2
    || (board[0][0] + board[1][0] + board[2][0] == win) // column 0
    || (board[0][1] + board[1][1] + board[2][1] == win) // column 1
    || (board[0][2] + board[1][2] + board[2][2] == win) // column 2
    || (board[0][0] + board[1][1] + board[2][2] == win) // diagonal
    || (board[2][0] + board[1][1] + board[0][2] == win)); //diagonal
}


int getWinner()
{
    if(isWin(currentPlayer)) return currentPlayer; 
    else return EMPTY; 
}


void printBoard()
{
    std::string player = (currentPlayer == X) ? "X" : "O"; 
    // std::cout << "\033[H"; // Move cursor to the top-left corner
    std::cout << "\033[2J\033[H"; 
    std::cout << "Current player: " << player << "\n\n"; // Display the current player


    for (int i =0; i <3; i++)
    {
        for (int j=0; j<3; j++)
        {
            switch(board[i][j])
            {
                case X: std::cout << "X"; break;
                case O: std::cout << "O"; break;
                case EMPTY: std::cout << " "; break;

            }
            if (j<2) std::cout << "|"; //column separator 
        }
        if (i<2)  std::cout << "\n-----\n";  //row separator 
    }
}



int main ()
{
    clearBoard(); //initialize board 
    int winner;  
    
    do
    {
        printBoard();
        int i; 
        int j; 

        std::cout << std::endl;
        std::cout << "\nEnter your move (row and column): " <<std::endl;
        std::cin >> i >> j;

        if (i >= 0 && i < 3 && j >= 0 && j < 3 && board[i][j] == EMPTY) {
            putMark(i, j);
            printBoard();
            winner = getWinner(); 
            currentPlayer = (currentPlayer == X) ? O : X; //change player 
            moves++;
        } else {
            std::cout << "Invalid move. Try again.";
            usleep(1000000);
        }
    }
    while((winner == EMPTY) ||(moves ==9));
}
