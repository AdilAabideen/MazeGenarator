
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Including Bool.h to do Bool functions
#include <stdbool.h>


// Defining the constants
#define MAX_SIZE = 100;
#define MIN_SIZE = 5;


// Struct to hold information about the Maze
typedef struct 
{
    int startPoint_x;
    int startPoint_y;
    char mazeGrid[MAX_SIZE][MAX_SIZE];
    int width, length;

}Maze;

// Struct to hold information about the Gamer
typedef struct
{
    int x, y;

} Gamer;

// Functions (1-4) to setup the game

void readMaze(Maze *maze, const char *filename, Gamer *gamer){

    // open and check file ( Exists, Is not empty, Has permissions to open file)

    // Call checkMaze function to verify the Maze meets the rules

    // If false is returned exit program else countinue

    // read in file line by line 

    // realloc

    // Seperate each character and assign each character to array Position 

    // Close file

    // Call findStartPosition to find the star position
}

bool checkMaze(char *filename, Maze *maze){

    // read in file and check if length and width is < 100 and > 5 if so print error message and return False

    // Check for irregular width and heights by checking len of every collumn and row and comparing , if so print error message and return False

    // Check for Other characters than #" "SE , if so print error message and return False

    // If succesfully return True


}

void findStartPosition(Maze *maze, Gamer *gamer){

    // for i to the end of number of rows and j to the number of collums its loops through the array 

    // find the start point and the X and Y coordinates and set it in the Maze struct

    // call set Player function to set gamers start point
}

void setPlayerPosition(int x, int y, Maze *maze, Gamer *gamer){

    // Set Gamers Start positions with X and Y passed in

}

void updateMap(Gamer *gamer, Maze *maze){
    
    // Takes current coordinates of gamer from struct and replaces it with an X to represent current position
}



bool checkPosition(Maze *maze, int x, int y) {

    // Checks the coordinate of the position to move to 

    // Checks if it is a # if it is prints error message and returns false 

    // Checks if it is a edge if it is prints an error message and returns fasle

    // If not any returns true
}

bool reachEnd(Maze *maze, int x, int y) {

    // takes in integer coordinates

    // checks if that position moving to is End Point 

    // If yes returns false and calls SetPlayer position as well as Prints a success Message 

    // if not returns true 
}



void showMap(Maze *maze){

    // calls update Map to update the gamers location

    // for i to the end of number of rows and j to the number of collums its loops through the array

    // prints whole maze out in grid style 

    
}
bool ValidateMovement(Maze *maze, int x, int y){

    // takes in the Coordinates of position to move to 

    // Calls checkPosition to see if the Movement is legal

    // Calls checkEnd to see if the movement results in the game Ending

    // If true is returned return true to MovePlayer 


}

void movePlayer(Maze *maze, Gamer *gamer, char movement){

    // case statement withe character WASD, inside them the coordinates within gamer struct will be changed 

    // eg: for W y = y -1 and for D x = x+1

    // Passes coordinates to ValidateMovement to validate it 

    // If true it calls setPlayerPosition

}



int main(int argc, char *argv[]){

    // Setup structs and variables
    Maze maze;
    Gamer gamer;
    char userChar ;

    // Checking for correct number of command-line arguments
    if (argc != 2){
        printf("Usage: Maze <filename>");
        return EXIT_FAILIURE;
    }

    // Call readMaze to open CSV file and read it in 
    readMaze(maze, argv[1], gamer);


    // Function will set up the game then the player will be requested to play
    // Will keep running until program quits
    while ( true )
    {
        // Print options for movement 
        printf("\nPlease enter W - A - S - D - M - Q(quit)");
        scanf("%c", &userChar);

        // for movement based on input
        switch (userChar) {
            case 'w':
            case 'W':
                movePlayer(maze, gamer, 'W');
                break;
            case 'a':
            case 'A':
                movePlayer(maze, gamer, 'A');
                break;
            case 's':
            case 'S':
                movePlayer(maze, gamer, 'S');
                break;
            case 'd':
            case 'D':
                movePlayer(maze, gamer, 'D');
                break;
            case 'm':
            case 'M':
                showMap(maze);
                break;
            case 'q':
            case 'Q':
                exit(0);
                break;
            default:
                printf("Error\n");
        }
    }return 0 ;


    
}