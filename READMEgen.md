# Maze Gen in C By Adil Aabideen

This repository contains a Generative algorithm written by Adil Aabideen which creates a maze valid by some rules. The maze is created depending on Widths and Lengths provided by the user. The maze also is further written to a file at the end of the program, filename provided by the user

## Algorithm Description 

1. The Generative algorithm starts by filling the Dynamically Allocated maze full with Hashtags(#) - walls. This is done to initialie it. 
2. Then it randomises a start point within the maze grid 
3. It from there will burrow itself away from the start point to create a pattern, It can be in any direction done by randomisation. If the position is valid, Not of the edges, then it will place a ' '(space) in that square signalling it can move there. This can be done (total area - 1 ( to allow for atleast 1 wall )) times however to increase amount of mazes generated we randomize this number to be no higher than total area - 1
4. Also if it is moving into a square with already a space there it has a 50/50 chance further added to it by randomization that it can place another space there. 
5. This done over and over times create patterns where the user playing can move to 
6. The last iteration of the loop sets that position to a 'E' to make sure that there is a solvable solution
7. results are written to a file specified by user

The algorithm responsible for parts 3,4 and 5 is here below:

``` c

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

        // Update variables and restart again so the algorithm can turn another square into a space
        currentX = new_x;
        currentY = new_y;
    }

    // At the end set startpoint
    maze->mazeGrid[maze->startPoint_y][maze->startPoint_x] = 'S';
}

```

You can see Looping for a randomised time and setting Spaces and E if the position to move to is valid, As well as randomized movement. 

## How to Build and Run

To build and run the Maze Game, you need a C compiler like `gcc`. Here are the steps:

1. Clone or download this repository to your local machine.
2. Navigate to the directory containing `mazegen.c`.
3. Compile the program with the following command:
   ```bash
   gcc -o Maze Maze.c
4. Run your program like this : 
    ./mazegen your_maze_filename.txt width length

## Author

By Adil Aabideen - sc23aa2@leeds.ac.uk - 1st Year Programming Project