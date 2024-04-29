# Maze Game in C By Adil Aabideen

This repository contains a C program that simulates a maze game. The program reads a maze from a text file, where the player navigates from a start point (S) to an end point (E) while avoiding walls (#). The game is played via command line, and the player moves using W, A, S, D keys.

## Description

The Maze Game is a simple, text-based game written in C. The player is placed in a maze loaded from a file and must navigate to the exit using keyboard controls. The maze supports walls and open spaces, and the game checks for valid movements and the end condition dynamically.

## How to Build and Run

To build and run the Maze Game, you need a C compiler like `gcc`. Here are the steps:

1. Clone or download this repository to your local machine.
2. Navigate to the directory containing `Maze.c`.
3. Compile the program with the following command:
   ```bash
   gcc -o Maze Maze.c
4. Run your program like this : 
    ./Maze your_maze_file.txt

## Usage

After starting the program with a valid maze file, use the following keys to navigate within the maze:

- `W` or `w`: Move up
- `A` or `a`: Move left
- `S` or `s`: Move down
- `D` or `d`: Move right
- `M` or `m`: Display the current maze on the screen
- `Q` or `q`: Quit the game

The game will print the maze each time you request by pressing 'M', and will end when you reach the end point 'E' or quit the game.

## Memory Allocation 

We allocate Gamer and Maze statically within this program. However for the Maze it can be various different sizes with lengths and widths ranging from 5 - 100 giving us many possibilities. This means we have to allocate memory dynamically to minimize leaks and make sure we are optimally allocating memory. The rest of the Maze struct is Allocated statically, such as wdith and startPoints. 

```markdown
Here is the Create Maze Function:

``` c

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
        // Cleanup if error occurs
        free(maze);
        exit(EXIT_MAZE_ERROR);
    }

    // This is for allocating memory for the width, dynamically
    for (int i = 0; i < maze->length; i++) {
        maze->mazeGrid[i] = malloc((maze->width + 1) * sizeof(char)); // +1 for '\0'
        if (maze->mazeGrid[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for grid row %d\n", i);
            // Cleanup previously allocated rows by freeing the memory if error occurs
            for (int j = 0; j < i; j++) {
                free(maze->mazeGrid[j]);
            }
            free(maze->mazeGrid);
            free(maze);
            exit(EXIT_MAZE_ERROR);
        }
    }
}

```

It will initially allocate memory for the size of the row, the length of the maze, then for each point within the row, so the width. This ensures memory is allocated efficienty, dynamically and optimally. 


## Author

By Adil Aabideen - sc23aa2@leeds.ac.uk - 1st Year Programming Project