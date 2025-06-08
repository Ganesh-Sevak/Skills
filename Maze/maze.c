#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/*
* In this MP we were tasked to Solve a maze using a DFS recursion backtracking algorithm
* To do this we had to implement 4 functions, createMaze destroyMaze printMaze and solveMazeDFS
* 
* In the createMaze function I first opened the file, then checked to see if the file operation was successfull
* by checking if the file pointer was NULL. The I created a pointer of type maze_t which would point to 
* a maze. Then I dynamically alloacted memory for the maze. Then I checked to see if the memory allocation was 
* successfull via checking the value of the pointer. Then I parsed the file to get the hieght and width 
* of the maze so that I can assign them to their respective members in the maze struct.
* Then I dynamically allocated the memory for the cells member of the maze_t struct. I casted the return value
* of the malloc to be a doulbe pointer thus the malloc was (sizeof(char*)*MAZE_PTR->hieght) becasue the double pointer is still
* pointing to another pointer. Then once again I checked to see if memory allocation was successfull.
* Then I dnyamically allocated memory (sizeof(char)*(MAZE_PTR->width)) for each of the things that the single pointer was pointing to. Once again checking if memory allocation
* was successfull. This in essance created a 2d array which could be accessed via MAZE_PTR->cells. 
* Then I simply looped through the file and assigned the charecters in the file to its respective spot in the 2d array, being mindfull 
* of the new line charecter. To deal with that, when I hit a new line charecter, I decremented my col index then simply continued to be
* keep fopen and the loop in synch. Then whilst looping through, if the START or the END charecter were hit then we would assign their
* indexs to their respective member of the maze_t struct. Then I closed the file.

* In destroyMaze all we had to do was free every single thing that we dynamically allocated. To do this, we had to free the
* things that the single pointers were pointing too, then free the thing the double pointer is pointing too. Then freeing
* what the maze pointer is pointing to. To free what the single pointers were pointing too, iterated through the hieght. Then I freed the 
* double pointer via free(maze->cells); and then freed the maze via free(maze);

* In printMaze all I did was iterate through the entirety of the 2D array and then print to the screen, when I was done printing a row
* I simply put in a new line charecter.

* In solveMazeDFS I had to solve the maze via DFS and recursion, I had to check if we were out of bounds, if we were then return 0, If we 
* if we were on the start we had to check if any of the adjacent cells were * if they were return a 0. We also had to check if the 
* cell was not empty and wasnt the start and wasnt the end then return a 0. And then if the end was reached return a 1.
* The we simply set the current cell as part of the PATH. Then simply check what the return value is when you call the solveMazeDFS
* from a cell up down and left and right of the current cell(To do this i would + or - to the row or colum parameter when calling the function).
*  If any of them return a 1 then we should also return a 1. If none of those 
* conditionals execute, then we should set our current cell to be VISITED and then return a zero.

*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    
    FILE *fp = fopen(fileName,"r"); 
    if(fp==NULL){
        printf("failed opening file");
        return NULL;
    }
    
    maze_t *Maze_PTR= (maze_t*)malloc(sizeof(maze_t));// dynamically assigned space for the maze
    if(Maze_PTR==NULL){
        printf("Failed to Allocate memory");
        return NULL;
    }
    
    
    int check = fscanf(fp,"%d%d", &(Maze_PTR->width) , &(Maze_PTR->height) );// check for scanf validity
    if (check!=2){
        printf("fopen failed");
        return NULL;
    }
    
    Maze_PTR->cells = (char**)malloc(sizeof(char*)*(Maze_PTR->height));// dynamically aloccates the array of pointers
    if(Maze_PTR->cells==NULL){
        printf("Failed to Allocate memory");
        return NULL;
    }
    for(int i=0; i<(Maze_PTR->height);i++){// for every element of the pointer array
        Maze_PTR->cells[i]=(char*)malloc(sizeof(char)*(Maze_PTR->width));// each element has size of the number of cols
        if(Maze_PTR->cells[i]==NULL){
            printf("Failed to Allocate memory");
            return NULL;
        }
    } 
    char temp;
    for(int j=0; j<Maze_PTR->height; j++){// for each row
        for (int k=0; k<Maze_PTR->width; k++){// for each element of the row
            
             int check_two = fscanf(fp,"%c", &temp);// copies the file contents to temp , check for fscanf validity
             if(check_two!=1){
                printf("fopen failed");
                return NULL;
             }
             if(temp=='\n'){// new line is hit when we already incremented j, must dec k by 1 to keep in sync with fscanf
                k--;
                continue;;
              } 
            
              Maze_PTR->cells[j][k]=temp;// temp goes into the cells
            
            if(temp == START){
                Maze_PTR->startRow=j;
                Maze_PTR->startColumn=k;
            }
            
            if(temp== END){
                Maze_PTR->endRow=j;
                Maze_PTR->endColumn=k;
            }
          
        }

    }
    fclose(fp);
    
        

    return Maze_PTR;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    if(maze == NULL){
        exit(1);
    }
    // Your code here.
    // free the game itself
    // free double pointer
    // free the pointers
    for(int i=0; i<(maze->height);i++){// for every element of the pointer array
        free(maze->cells[i]);// frees what the single pointers are pointing to
    }
    free(maze->cells);// frees what the double pointer was pointing to 
    free(maze);// frees the entire maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    if(maze == NULL){
        exit(1);
    }
    // Your code here.
    for (int i=0; i<(maze->height); i++){
        
        for (int j=0; j<(maze->width); j++){
            //char temp = maze->cells[i][j];
            printf("%c", maze->cells[i][j]);// just prints the value
        }
        printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    
    // The provided gold files recursively visit neighbors in the order
    // left, up, right, down. It is okay to deviate from this if you'd 
    // like, but your outputs will be different.
    
    // Your code here. Make sure to replace following line with your own code.
    if(maze == NULL){
        return 0;
    }
    if(col>=maze->width || row>=maze->height ||col<0 || row<0){// Base case out of boinds
        return 0;
    }
    if (maze-> startRow == row && maze->startColumn == col){// only enter if we are on the start, this is the base case for circling back
        // we want to check if any of the cells around it are *, if they are then we know that we are not on the first move
        // thus we want to consider it an invalid move
        if(col>0 && maze->cells[row][col-1]=='*'){// checks if the left cell is a star
            
            return 0;
        }
        
        if(col<(maze->width) && maze->cells[row][col+1]=='*'){// checks if the right cells is a star
            
            return 0;
        }

        if(row>0 && maze->cells[row-1][col] == '*'){// checks if the up cell is a star
            
            return 0; 
        }

        if(row<(maze->height) && maze->cells[row+1][col] == '*'){// checks if the cell below is a star
            
            return 0; 
        }

    }
    
    
    if (maze->cells[row][col]!= EMPTY && maze->cells[row][col]!= START && maze->cells[row][col]!= END ){// base case for not empty cell
        return 0;
    }
    
    if (row==maze->endRow && col==maze->endColumn){ // base case end reached
        return 1;
    }
    
    if(maze->cells[row][col] != START){
        maze->cells[row][col]= PATH;
    } // set as path
    
    if(row==maze->startRow && col==maze->startColumn){// we do this just incase we accidently over wrote the start
        maze->cells[row][col]= START; 
    }
    
    if(solveMazeDFS(maze, col, row-1)){// all of these cases are simply checking if making a next move will be valid or not
        return 1;
    }
    if (solveMazeDFS(maze, col, row+1)){
        return 1;
    }
    if (solveMazeDFS(maze, col+1, row)){
        return 1;
    }
    if (solveMazeDFS(maze, col-1, row)){
        return 1;
    }
    // back track if none of those are right thus marking it as visited
    if(maze->cells[row][col] != START){
        maze->cells[row][col]= VISITED;
    }
    
    
   
    return 0;
}