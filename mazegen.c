#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    char **mazeGrid ; // Pointer to pointer for the dynamic 2d array
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
        // Cleanup
        free(maze);
        exit(EXIT_MAZE_ERROR);
    }

    // This is for allocating memory for the width, dynamically
    for (int i = 0; i < maze->length; i++) {
        maze->mazeGrid[i] = malloc((maze->width + 1) * sizeof(char)); // +1 for '\0'
        if (maze->mazeGrid[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for grid row %d\n", i);
            // Cleanup previously allocated rows by freeing the memory
            for (int j = 0; j < i; j++) {
                free(maze->mazeGrid[j]);
            }
            free(maze->mazeGrid);
            free(maze);
            exit(EXIT_MAZE_ERROR);
        }
    }
    
    
}

void setMazeParams(char *width, char *height, Maze *maze){
    maze->width = atoi(width);
    maze->length = atoi(height);


}

void generateStartPoint(Maze *maze){
    int randomRow = rand() % maze->width;
    int randomCol = rand() % maze->length ;

    maze->startPoint_x = randomRow;
    maze->startPoint_y = randomCol;

}

bool validateMovement(Maze *maze, int x, int y){
    if (x < 0 || x >= maze->width || y < 0 || y >= maze->length){
        return false;
    } else {
        return true;
    }
}

void setMovement(int x, int y, Maze *maze, int flag){

    switch (flag){
        case 1 :
            maze->mazeGrid[y][x] = ' ';
            break;
        case 2 :
            maze->mazeGrid[y][x] = 'E';
            break;
        
    }
    
}

void createMazePattern(Maze *maze) {
    int currentX = maze->startPoint_x;
    int currentY = maze->startPoint_y;
    int totalArea = (maze->width * maze->length) * 0.9;
    int randomNumOfMovement = rand() % totalArea;


    for (int x = 0; x <= randomNumOfMovement; x++) {
        bool validatedMovement = false;
        int new_x = currentX;
        int new_y = currentY;
        int numMovement = 4;

        while (!validatedMovement) {
            int direction = rand() % numMovement;
            switch (direction) {
                case 0:
                    new_y = currentY - 1;
                    break;
                case 1:
                    new_x = currentX - 1;
                    break;
                case 2:
                    new_y = currentY + 1;
                    break;
                case 3:
                    new_x = currentX + 1;
                    break;
            }
            validatedMovement = validateMovement(maze, new_x, new_y);
            if (!validatedMovement) {
                new_x = currentX; // Reset to last valid x
                new_y = currentY; // Reset to last valid y
            }
        }
        if (x == randomNumOfMovement) {
            setMovement(new_x, new_y, maze, 2); // Set 'E'
        } else {
            setMovement(new_x, new_y, maze, 1); // Set ' '
        }

        currentX = new_x;
        currentY = new_y;
    }
    maze->mazeGrid[maze->startPoint_y][maze->startPoint_x] = 'S';
}



void initialiseMaze(Maze *maze){
    for ( int x = 0 ; x< maze->length ; x++){
        for ( int i = 0; i < maze->width ; i++){
            maze->mazeGrid[x][i] = '#';
        }
    }
}

void writeToFile(Maze *maze, char *filename){

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        freeMaze(maze);  // Clean up before exiting
        exit(EXIT_FILE_ERROR);
    }

    for (int i = 0; i < maze->length; i++) {
        for (int j = 0; j < maze->width; j++) {
            fprintf(file, "%c", maze->mazeGrid[i][j]);
        }
        fprintf(file, "\n");  // Each row on a new line
    }

    fclose(file);
}


int main(int argc, char *argv[]) {

    srand(time(NULL));

     if (argc != 4){
        printf("Usage: mazegen <filename> <width> <length>");
        return EXIT_ARG_ERROR;
    }

    if (atoi(argv[2]) > 100 || atoi(argv[2]) < 5 || atoi(argv[3]) > 100 || atoi(argv[3]) < 5 ){
        printf("Usage: width and length should > 5 and < 100");
        return EXIT_ARG_ERROR;
    }

    Maze maze;
    setMazeParams(argv[2], argv[3], &maze); // works
    createMaze(&maze); // work
    initialiseMaze(&maze); // work
    generateStartPoint(&maze); 
    createMazePattern(&maze);
    writeToFile(&maze, argv[1]);
    
    freeMaze(&maze);  // Free maze resources

    return EXIT_SUCCESS;

}