#include "sudoku.h"
/*
In this MP we had to solve a 9 by 9 sudoku. To this I implemented is_val_in_row, is_val_in_col, and is_val 3x3 
then is val_valid and solve_sudoku

In is_val_in_row I had to check if the value passed into the funcion was already in the row. If it
was found on the row return a 1 if not return 0. We ran a loop which icremented in the horizontal direction
and kept checking if the value passed into the function was found in the row i. 

In the is_val_in_col I had to check if the value number I passed into the function could be found in the colum
which I also passed into the function. To check I incremented the rows over and over and cheked if the val was
found. If it was found then I would return a 1. If not return a 0.

In the is_val 3x3 function I had to check if the value was valid in the 3x3 area around it. To do this
I had to check the 3x3 matrix in which the row and colum were found in. In this function I had to loop
over rows and colums. The lower and upper bounds were computed using a formula. UPPERBOUND=index+3-(index mod3)
and for lower bound it was index=index-(index mod 3). We would then just check if the value passed into the function
was foud. If it was return a 1 if it wasnt return a 0. 

In the is_val_valid function we pass in the row, colum, value, and the board. we would then feed these values
into their corresponding functions. In this function I was checking the return values of 3 is_val functions above
if any of them returne a one, then is_val_valid would return a 0. If not it would return a 1.  

Lastly I had to implement the solve_sudoku function. In this function first I had to search the board for an open 
cell. If no open cells were found we had solved the game and return a 1. If not save the value of the row and colum 
of the open cell. Then start trying differnt values for the open cell. First we check if the value was valid, then 
checked if the value we picked will eventually lead to a solution. If a solution can eventally be reached return a 1. If not then we just try puttingthe next number
in the cell. Once we exhaust all of our possible choices to put in the cell and still a solution cannot be found
we must back track. TO back track  we zero out the open cell and then we return a 0.
*/






//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int h=0; h<9; h++){// increments horizonatlly
    if(sudoku[i][h]==val){// check if it is in the same row
      return 1;// we found the val in the same row

    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int v=0; v<9; v++){// increments horizonatlly
    if(sudoku[v][j]==val){// check if it is in the same colum
      return 1;// we found the val in the same colum
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int R_ROW=i%3;
  int R_COLUM=j%3;// this will give us a reletive postion inside the 3 by 3 sqaure
  
  // lets set the bounds the loops
  for(int R_INDEX=i-R_ROW;R_INDEX<i+(3-R_ROW); R_INDEX++){
    for(int C_INDEX=j-R_COLUM;C_INDEX<j+(3-R_COLUM); C_INDEX++){
      if(sudoku[R_INDEX][C_INDEX]==val){// check if it is in the same colum
        return 1;// we found the val in the same colum
      }
    }
  }
  
  
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if((is_val_in_col(val,j,sudoku))||(is_val_in_row(val,i,sudoku))||((is_val_in_3x3_zone(val,i,j,sudoku)))){
    return 0;
  }
  
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
int done=1;
int openr=0;
int openc=0;
  // BEG TODO.
  for(int r=0; r<9;r++){
    for(int c=0;c<9;c++){
      if(sudoku[r][c]==0){
        openr=r;//indicates free spot
        openc=c;
        done=0;
        
      }
    }
  
  }// this all is checking if we have an empty spot
  if(done==1){
    return 1;// this tells us the sudoku is solved
  }
  else{//not done
    for(int num=1;num<10;num++){
      if (is_val_valid(num,openr,openc,sudoku)){
        sudoku[openr][openc]=num;
        if(solve_sudoku(sudoku)){
          return 1;
        }
        sudoku[openr][openc]=0;
      }
      
      

    }
    
  }
  
  
  return 0;
  
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}