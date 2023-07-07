#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

// Define constants for the game board dimensions and number of mines
const int SIDE = 9;    // Side length of the game board
const int MINES = 10;  // Number of mines in the game

void clear();
bool isValid(int row, int col);
bool isMine(int row, int col, char board[][SIDE]);
void makeMove(int* x, int* y);
void printBoard(char board[][SIDE]);
int countAdjacentMines(int row, int col, int mines[][2], char realBoard[][SIDE]);
bool playMinesUntil(char myBoard[][SIDE], char realBoard[][SIDE], int mines[][2], int row, int col, int* movesLeft);
void placeMines(int mines[][2], char realBoard[][SIDE]);
void initialize(char realBoard[][SIDE], char myBoard[][SIDE]);
void playMinesweeper();

int main()
{
    playMinesweeper();
    return 0;
}

// Function to clear the console screen
void clear()
{
    // Clears the console screen and positions the cursor at the top - left corner, provides a way to create a clear screen before printing new content
    cout << "\033[2J\033[1;1H";
}

// Function to check if given cell coordinates are valid
bool isValid(int row, int col)
{
    return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
}

// Function to check if the given cell contains a mine
bool isMine(int row, int col, char board[][SIDE])
{
    return (board[row][col] == '*');
}

// Function to get the user's move coordinates
void makeMove(int* x, int* y)
{
    cout << "\nEnter your move: [row] [column] -> ";
    cin >> *x >> *y;
}

// Function to print the game board
void printBoard(char board[][SIDE])
{
    clear();
    // Print the column headers (numbers) at the top of the board
    cout << "\n\n\t\t\t    ";

    // If the column number is greater than 9, print only the tens digit followed by a space
    for (int i = 0; i < SIDE; i++)
    {
        if (i > 9) 
        {
            cout << i / 10 << " ";
        }
        else
        {
            // Otherwise, print two spaces to align the numbers properly
            cout << "  ";
        }
    }
    // Print the column numbers (ones digit) at the top of the board
    cout << "\n\t\t\t    ";

    for (int i = 0; i < SIDE; i++)
    {
        // Print the ones digit of the column number followed by a space    
        cout << i % 10 << " ";
    }
    cout << "\n\n";

    // Print the game board row by row
    for (int i = 0; i < SIDE; i++)
    {
        cout << "\t\t\t    "; // Add indentation for better visualization

        // Print each cell of the current row followed by a space
        for (int j = 0; j < SIDE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << " " << i; // Print the row number at the end of the row
        cout << "\n"; // Move to the next line for the next row
    }
}

// Function to count the number of adjacent mines to a given cell
int countAdjacentMines(int row, int col, int mines[][2], char realBoard[][SIDE])
{
    int count = 0;

    // Check the cell above
    if (isValid(row - 1, col) && isMine(row - 1, col, realBoard))
    {
        count++;
    }

    // Check the cell below
    if (isValid(row + 1, col) && isMine(row + 1, col, realBoard))
    {
        count++;
    }

    // Check the cell to the right
    if (isValid(row, col + 1) && isMine(row, col + 1, realBoard))
    {
        count++;
    }

    // Check the cell to the left
    if (isValid(row, col - 1) && isMine(row, col - 1, realBoard))
    {
        count++;
    }

    // Check the cell at the top left
    if (isValid(row - 1, col - 1) && isMine(row - 1, col - 1, realBoard))
    {
        count++;
    }

    // Check the cell at the top right
    if (isValid(row - 1, col + 1) && isMine(row - 1, col + 1, realBoard))
    {
        count++;
    }

    // Check the cell at the bottom left
    if (isValid(row + 1, col - 1) && isMine(row + 1, col - 1, realBoard))
    {
        count++;
    }

    // Check the cell at the bottom right
    if (isValid(row + 1, col + 1) && isMine(row + 1, col + 1, realBoard))
    {
        count++;
    }

    return count;
}

// Function to recursively play the game until a mine is encountered or the game is won
bool playMinesUntil(char myBoard[][SIDE], char realBoard[][SIDE], int mines[][2], int row, int col, int* movesLeft)
{
    // Check if the current cell has already been uncovered
    if (myBoard[row][col] != '-') 
    {
        return false;
    }
    // Check if the current cell contains a mine
    if (realBoard[row][col] == '*')
    {
        // Game over, mine encountered
        // Update the player's board to reveal the mine and all other mines        
        for (int i = 0; i < MINES; i++) 
        {
            myBoard[mines[i][0]][mines[i][1]] = '*';
        }
        printBoard(myBoard);
        cout << "\nYou lost!\n";
        return true;
    }
    else
    {
        // No mine encountered, continue playing

        // Count the number of adjacent mines to the current cell
        int count = countAdjacentMines(row, col, mines, realBoard);

        (*movesLeft)--; // Decrement the number of remaining moves
        myBoard[row][col] = count + '0'; // Update the player's board with the count of adjacent mines 

        // Allows the game to automatically uncover adjacent cells when a cell with no adjacent mines is selected
        if (!count)
        {
            // If no adjacent mines, recursively play for adjacent cells

            // Check the cell above
            if (isValid(row - 1, col) && (myBoard[row - 1][col] == '-'))
            {
                playMinesUntil(myBoard, realBoard, mines, row - 1, col, movesLeft);
            }
            // Check the cell below
            if (isValid(row + 1, col) && (myBoard[row + 1][col] == '-'))
            {
                playMinesUntil(myBoard, realBoard, mines, row + 1, col, movesLeft);
            }
            // Check the cell to the right
            if (isValid(row, col + 1) && (myBoard[row][col + 1] == '-'))
            {
                playMinesUntil(myBoard, realBoard, mines, row, col + 1, movesLeft);
            }
            // Check the cell to the left
            if (isValid(row, col - 1) && (myBoard[row][col - 1] == '-'))
            {
                playMinesUntil(myBoard, realBoard, mines, row, col - 1, movesLeft);
            }
            // Check the cell at the top left
            if (isValid(row - 1, col - 1) && (myBoard[row - 1][col - 1] == '-'))
            {
                playMinesUntil(myBoard, realBoard, mines, row - 1, col - 1, movesLeft);
            }
            // Check the cell at the top right
            if (isValid(row - 1, col + 1) && (myBoard[row - 1][col + 1] == '-'))
            {
                playMinesUntil(myBoard, realBoard, mines, row - 1, col + 1, movesLeft);
            }
            // Check the cell at the bottom left
            if (isValid(row + 1, col - 1) && (myBoard[row + 1][col - 1] == '-'))
            {
                playMinesUntil(myBoard, realBoard, mines, row + 1, col - 1, movesLeft);
            }
            // Check the cell at the bottom right
            if (isValid(row + 1, col + 1) && (myBoard[row + 1][col + 1] == '-'))
            {
                playMinesUntil(myBoard, realBoard, mines, row + 1, col + 1, movesLeft);
            }
        }

        // Checks if the number of remaining moves (*movesLeft) is equal to the total number of cells on the game board minus the number of mines
        if (*movesLeft == SIDE * SIDE - MINES)
        {
            // Game won, all non-mine cells uncovered
            printBoard(myBoard);
            cout << "\nYou won!\n";
            return true;
        }

        return false;
    }
}

// Function to randomly place mines on the board
void placeMines(int mines[][2], char realBoard[][SIDE])
{
    // Ensure that each mine is placed in a unique cell on the game board
    bool mark[SIDE * SIDE];

    // Initialize the mark array to false
    memset(mark, false, sizeof(mark));

    for (int i = 0; i < MINES;)
    {
        // Generate a random number between 0 and the total number of cells on the game board
        int random = rand() % (SIDE * SIDE);
        int x = random / SIDE;
        int y = random % SIDE;

        // Check if the current random number has already been marked
        if (mark[random] == false)
        {
            // If the random number has not been marked, assign the mine coordinates
            mines[i][0] = x;
            mines[i][1] = y;

            // Place the mine on the real board
            realBoard[mines[i][0]][mines[i][1]] = '*';

            // Mark the random number as true in the mark array to indicate that it has been used
            mark[random] = true;
            i++;// Increment the mine counter
        }
    }
}

// Function to initialize the game board
void initialize(char realBoard[][SIDE], char myBoard[][SIDE])
{
    srand(time(NULL)); // Seed the random number generator with the current time

    // Iterate over each cell of the game board
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            // Set the initial value of the cells on both the player's board and the real board to '-'
            myBoard[i][j] = realBoard[i][j] = '-';
        }
    }
}

// Function to play the Minesweeper game
void playMinesweeper()
{
    bool gameOver = false; // Variable to track if the game is over
    char realBoard[SIDE][SIDE];// Array to represent the real game board
    char myBoard[SIDE][SIDE]; // Array the player's board
    int movesLeft = SIDE * SIDE - MINES; // Variable to track the number of remaining moves
    int x, y; // Variables to store the user's move coordinates
    int mines[MINES][2]; // Array to store the positions of the mines
    initialize(realBoard, myBoard); // Initialize the game board
    placeMines(mines, realBoard); // Place the mines randomly on the board

    int currentMoveIndex = 0; // Variable to track the current move index
    while (gameOver == false)
    {
        cout << "Current Status of Board:\n";
        printBoard(myBoard); // Display the current state of the player's board

        makeMove(&x, &y); // Get the user's move coordinates

        currentMoveIndex++; // Increment the current move index
        gameOver = playMinesUntil(myBoard, realBoard, mines, x, y, &movesLeft); // Play the current move and check if the game is over
    }
}
