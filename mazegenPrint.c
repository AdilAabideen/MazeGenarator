#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // Include for sleep function
// #include <windows.h>  // Include for Sleep function for windows

// Including Bool.h to do Bool functions
#include <stdbool.h>


// Defining the constants
#define MAX_SIZE  100
#define MIN_SIZE  5
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3

// Struct to hold information about the Maze
typedef struct 
{
    int startPoint_x;
    int startPoint_y;
    // Pointer to pointer for the dynamic 2d array
    char **mazeGrid ;
    int width, length;

}Maze;

/**
 * @brief Free the allocated memory to the Maze Struct
 *
 * @param maze The pointer to the maze to be freed
 */
void freeMaze(Maze *maze) {
    // Frees every single Point and row
    if (maze) {
        for (int i = 0; i < maze->length; i++) {
            free(maze->mazeGrid[i]);
        }
        free(maze->mazeGrid);
    }
}

/**
 * @brief Creates the maze and Allocates memory dynamically to the 2d grid
 *
 * @param maze The pointer to the Maze for memory to be allocated to
 */
void createMaze(Maze *maze){

    // Allocate the maze grid dynamically as it can vary in size, this is for the length
    maze->mazeGrid = malloc(maze->length * sizeof(char*));
    if (maze->mazeGrid == NULL) {
        fprintf(stderr, "Failed to allocate memory for maze grid\n");
        // Cleanup incase of error 
        free(maze);
        exit(EXIT_MAZE_ERROR);
    }

    // This is for allocating memory for the width, dynamically
    for (int i = 0; i < maze->length; i++) {
        maze->mazeGrid[i] = malloc((maze->width + 1) * sizeof(char)); // +1 for '\0'
        if (maze->mazeGrid[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for grid row %d\n", i);
            // Cleanup previously allocated rows by freeing the memory incase of error
            for (int j = 0; j < i; j++) {
                free(maze->mazeGrid[j]);
            }
            free(maze->mazeGrid);
            free(maze);
            exit(EXIT_MAZE_ERROR);
        }
    }
}

/**
 * @brief Sets the width and Height of the Maze to be generated
 *
 * @param width Pointer to the char width of the maze
 * @param width Pointer to the char height of the maze
 * @param width Pointer to the Maze to generate
 */
void setMazeParams(char *width, char *height, Maze *maze){
    maze->width = atoi(width);
    maze->length = atoi(height);
}

/**
 * @brief Randomizes a Start point in the whole maze to generate maze
 *
 * @param maze The pointer to the Maze where the start point will be 
 */
void generateStartPoint(Maze *maze){

    // Uses random to find a random collumn and row to start
    int randomRow = rand() % maze->width;
    int randomCol = rand() % maze->length ;

    // set startPoint for future use
    maze->startPoint_x = randomRow;
    maze->startPoint_y = randomCol;

}

/**
 * @brief Prints the Maze in a grid format
 *
 * @param maze The pointer to the Maze to be printed
 * @param gamer The pointer to the gamers current location
 */
void printMaze(const Maze *maze) {

    // New leading line
    printf("\n");  

    for (int i = 0; i < maze->length; i++) {
        for (int j = 0; j < maze->width; j++) {
            printf("%c", maze->mazeGrid[i][j]);
        }
        // Each row on a newline
        printf("\n");  
    }
}

/**
 * @brief Validates the movement, See if the algorithm is moving beyond the maze
 *
 * @param maze Pointer the maze where movement is occuring
 * @param x the X - coordinate of the future position
 * @param y the Y - Coordinate to the future position
 */
bool validateMovement(Maze *maze, int x, int y){
    int outOfBounds = true;
    int alreadySpace = true;

    // If the future position is beyond the maze
    if (x < 0 || x >= maze->width || y < 0 || y >= maze->length){
        // Illegal Movement
        outOfBounds = false ;
        // exit function as rest doesnt matter if it is an illegal position
        return false;
    } else {
        // Legal Movement
        outOfBounds = true ;
    }

    // Further randomization if the space algorithm trying to move into is already a Space
    // Further increases amount of mazes that can be generated, Uses randomization to allow algorithm to move into that space if it is already a ' '
    
    // get random num
    int numOfChoice = 2;
    int choice = rand() % numOfChoice ;

    if (maze->mazeGrid[y][x] == ' '){
        // legal or illegal based on random number
        if ( choice == 0 ){
            alreadySpace = true;
        } else {
            alreadySpace = false;
        }
    }

    return alreadySpace && outOfBounds ; 
}

/**
 * @brief sets the pattern of movement based on coordinates and flags passed
 *
 * @param maze Pointer the maze where movement is occuring
 * @param x the X - coordinate of the future position
 * @param y the Y - Coordinate to the future position
 * @param flag whether it is the end point or not 
 */
void setMovement(int x, int y, Maze *maze, int flag){

    switch (flag){
        // If it just a regular movement
        case 1 :
            // Space to justify movement
            maze->mazeGrid[y][x] = ' ';
            break;
        // If End Point
        case 2 :
            // E to justify End Point
            maze->mazeGrid[y][x] = 'E';
            break;
    }
}

/**
 * @brief Creates a pattern of spaces for movement in the maze
 *
 * @param maze Pointer to the maze which is being generated
 */
void createMazePattern(Maze *maze) {

    // Initalise variables - start points
    int currentX = maze->startPoint_x;
    int currentY = maze->startPoint_y;

    // We find the amount of possibles squares to have ' ' and -1 becuase according to rules we need 1 Wall #
    int totalArea = (maze->width * maze->length) - 1;

    // Random number of amount of spaces we can get in the maze, Increases randomization and amount of mazes generated
    int randomNumOfMovement = rand() % totalArea;

    // Loop for the random number of spaces, so algorithm can keep moving across the maze
    for (int x = 0; x <= randomNumOfMovement; x++) {
        bool validatedMovement = false;
        int new_x = currentX;
        int new_y = currentY;

        // There are 4 movements which can occur W - A - S - D
        int numMovement = 4;

        while (!validatedMovement) {
            // Choose a random direction and create new coordinates for that direction
            int direction = rand() % numMovement;
            switch (direction) {
                // W movement
                case 0:
                    new_y = currentY - 1;
                    break;
                // A Movement
                case 1:
                    new_x = currentX - 1;
                    break;
                // S Movement
                case 2:
                    new_y = currentY + 1;
                    break;
                // D Movement
                case 3:
                    new_x = currentX + 1;
                    break;
            }
            // Check if the movment is not beyond the maze bounds
            validatedMovement = validateMovement(maze, new_x, new_y);
            if (!validatedMovement) {
                // Reset to last valid y and Reset to last valid X
                new_x = currentX;
                new_y = currentY;
            }
        }
        // If its endPoint set to E
        if (x == randomNumOfMovement) {
            // As the last iteration of the loop is E there will always be a solution to the maze
            setMovement(new_x, new_y, maze, 2); 
        } else {
            // If not set it to Space " " as we can move there
            setMovement(new_x, new_y, maze, 1); 
        }
        sleep(1);
        // windows Sleep(1000);
        system("clear");
        // window system("cls");

        printMaze(maze);


        // Update variables and restart again so the algorithm can turn another square into a space
        currentX = new_x;
        currentY = new_y;
    }

    // At the end set startpoint
    maze->mazeGrid[maze->startPoint_y][maze->startPoint_x] = 'S';
}

/**
 * @brief Intitalises maze with full of # walls to let algorithm burrow spaces through them
 *
 * @param maze Pointer to the maze which is being initialised
 */
void initialiseMaze(Maze *maze){
    for ( int x = 0 ; x< maze->length ; x++){
        for ( int i = 0; i < maze->width ; i++){
            // Makes the whole maze full of Walls
            maze->mazeGrid[x][i] = '#';
        }
    }
}

/**
 * @brief Writes the maze to a file 
 *
 * @param maze Pointer to the maze which is being 
 * @param filename Pointer to the filename which is beign written to
 */
void writeToFile(Maze *maze, char *filename){

    FILE *file = fopen(filename, "w");

    // Error management
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        // Clean up before exiting
        freeMaze(maze);  
        exit(EXIT_FILE_ERROR);
    }

    // Write the Point to the file
    for (int i = 0; i < maze->length; i++) {
        for (int j = 0; j < maze->width; j++) {
            fprintf(file, "%c", maze->mazeGrid[i][j]);
        }
        // Each row on a new line
        fprintf(file, "\n");
    }

    fclose(file);
}


int main(int argc, char *argv[]) {

    // Seed the random generator so it generates random every time, Using time
    srand(time(NULL));

    // Error Checking for arguments and widths and lengths supplies
    if (argc != 4){
        printf("Usage: mazegen <filename> <width> <length>");
        return EXIT_ARG_ERROR;
    }
    if (atoi(argv[2]) > 100 || atoi(argv[2]) < 5 || atoi(argv[3]) > 100 || atoi(argv[3]) < 5 ){
        printf("Usage: width and length should > 5 and < 100");
        return EXIT_ARG_ERROR;
    }

    // setup Maze struct
    Maze maze;

    // Call to set the Length and Width
    setMazeParams(argv[2], argv[3], &maze);

    // Call to dynamically allocate memory based on lengths and widths 
    createMaze(&maze);

    // Call to create the whole maze full of # walls
    initialiseMaze(&maze);

    // Generate a start point random
    generateStartPoint(&maze); 

    // Algorithm to burrow Spaces ' ' through a maze of walls
    createMazePattern(&maze);

    // write finished maze to a file
    writeToFile(&maze, argv[1]);
    
    // Free to stop inefiicent memory allocatio 
    freeMaze(&maze);
    return EXIT_SUCCESS;

}