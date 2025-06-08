#include "game.h"
/*
In this MP we were tasked to make the game 2048

We had to implement make_game, get_cell, remake_game, move_w, move_a, move_s, move_d, legal_move_check

In make game I simply set the number of the rows for mygame, then I set the number of columns, intitialized
the score to be 0, and then lastly I iterated through the cells of mygame to set all the cells to -1 to indicate
that every cell was free. And then simply returned mygame which was a pointer to the game.

remake_game was very simmilar to make_game. Except this function passed in a double pointer. Thus for all
the operations on the double pointer I had to dereferance and then I had to use the arrow opperator. All I 
had to do was once again set the newgames row and columns and then set the score to zero again. Also
I iterated through the cells for the remade game and set them all to -1.

get_cell simply passed in a row and colum, we had to return a pointer to the correspondng cell. 
If the row or colum that we passed in was out of bounds we had to return a NULL. To do this
I simply checked if the arguements being passed in were in bounds, if it was then I used the row
and colum to find the spot in the array. I made a pointer and assigned the value of the adress of the spot 
in the array to the pointer and then simply returned the pointer.

move_w passed in a pointer to our game. First make a deep copy of the cells.
 So first I merged like tiles. To merge like tiles, I started at 
at the top row and saw if there were any tiles which were directly below which could merge. I ignored
blank spots because tiles could merge even if there is blanks. If they could merge, I summed the tiles together
and set the lower tile to -1 and added the sum of the tile to the over score. I did this for everyrow.
Then I had to shift everything up. To do this first I found the smallest non blank row and then found the smallest
filled row, if the blank row was higher than the filled row then I would move the filled entries where the 
empty entries used to be. And then set the orgiginal spot where the non blank entries were to -1. 
 At the very end see if the deep copy is equal to the new cells. If it
is then its an invalid move and return a 0. If things did change return a 1.

move_s passed in a pointer.First I had to make a deep copy of the cells
 Once again I merged like tiles. To do this I started at the bottom row and worked up. 
 I started looking for equal tiles above. I would ignore blank tiles. If they were equal then I would merge them 
sumnming them together and the setting the higher tile to -1.  I did this for every row. Then to shift it was the 
same as move_w except instead of starting at the top row I started at the bottom row. And then checked if 
the blank row was lower then the filled row. if it was then shift the filled row to the blank row
and then make the old filled row -1. At the very end see if the deep copy is equal to the new cells. If it
is then its an invalid move and return a 0. If things did change return a 1.

move_a also paseed in a pointer. First I made a deep copy of the cells. Then I wanted to merge in the 
leftward direction. Starting from the left most row, I started seeing if there were any adjcacent tiles 
we could merge with in the other cols ignoring blanks. If they could merge add the tile together
and then set the tile that is more to the left to -1. Then to shift left, starting at the left most colum
we try to find the first non zero col. Then we find the first blank col. if the blank col is more to the
left than the filled col then shift left. Do this for every col.  At the very end see if the deep copy is equal to the new cells. If it
is then its an invalid move and return a 0. If things did change return a 1.

move_d also passed in a pointer. First I made a deep copy of the cells. Then I wanted to merge in the right
direction. Starting from the rightmost row  I started seeing if there were any adjcacent tiles 
we could merge with in the other cols ignoring blanks. If the tiles were equal I wouls sum them together and 
set the left tile to -1. Then to shift, starting from the right I checked to find the first non blank
col. After than starting from the right I wanted to find the first blank col. If the blank col was to the 
right of the filled col. Then I would shift the tiles to the and then do this for every colum.
At the very end see if the deep copy is equal to the new cells. If it
is then its an invalid move and return a 0. If things did change return a 1.

The last function was legal_move_check. This function passed in a pointer to our game. First I had
to make a deep copy of the game it self using the make_game function. After doing that I had to copy the 
current games cells into the copied game. Then I had to check the return value for move_w, move_s, move_a,
and move_d. To do this I called all the functions by passing in the deepcopy of the game into the functions
if any of them returned a 1 then I should destroy the copy and return a 1. If none of them returned a 1 
then return a 0.


*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows=rows; // the reason we use -> instead of . is because mygame is actaully a pointer
    mygame->cols=cols;
    mygame->score=0;// this intialized the rows cols and the score
    // now we have to intialize the cells to all be -1
    // the name of the array holding the cell data is cells and the data type of it is user defined data
    //type cell
    for(int i = 0; i < (rows*cols); i++){
        mygame->cells[i]=-1;
        // we are going into mygame via arrow because it is a pointer
        // access the memeber cells, then we make them all =-1
        // we have to specifiy that its within mygame because we only want to initialize that
    }


    return mygame;// returns the pointer to the game
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows;// we derefernce the double pointer to convert to a single pointer
    (*_cur_game_ptr)->cols = new_cols;// then we use -> to access a memeber of the struct that pointer is pointing to
    (*_cur_game_ptr)->score = 0;// we set the rows cols and score
    // now we set all the cells to -1
    for(int i = 0; i < (new_rows*new_cols); i++){
    (*_cur_game_ptr)->cells[i]=-1;
    //cells it self if a pointer/array within the struct so we must loop through
    // the array to set all of the values to -1
    }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    // lets make an if statement which checks if we are out of bounds in rows or cols. If not
    //out of bounds we should return a pointer which points to the correspodnng cell
    
    if((row>-1) && (col>-1) && (row<(cur_game->rows)) && (col<(cur_game->cols))){// makes sure cell is inbounds
       // recall that cells is organized in row major
        
        cell *cellptr=&(cur_game->cells[row*((cur_game->cols))+col]);//might cause math error
        return cellptr;
    }
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
  
    // we will use the copy pointer as the past referance
    // we will edit the cur_game
    cell deepcopy[(cur_game->rows)*(cur_game->cols)];
    for(int i=0; i<((cur_game->rows)*(cur_game->cols)); i++){// causing seg fault
       deepcopy[i]= cur_game->cells[i];
    }// this loops copied all the cells over
    // write a new merge
    for(int i=0; i<cur_game->cols; i++){// for every colum

        for(int j=0; j<cur_game->rows;j++){ //for every row, startin at row 0
            // find the top most non zero row
            if(cur_game->cells[j*(cur_game->cols)+i]==-1){
                continue;
            }
            for(int k=j+1; k<cur_game->rows;k++){// based of the non zero row found go one below it
                if(cur_game->cells[k*(cur_game->cols)+i]==-1){// allows us to skip past blanks
                    continue;
                }
                if(cur_game->cells[j*(cur_game->cols)+i]== cur_game->cells[k*(cur_game->cols)+i]){// if equal add then make a blank in lower row
                    cur_game->cells[j*(cur_game->cols)+i]= (cur_game->cells[j*(cur_game->cols)+i])*2;
                    cur_game->score += cur_game->cells[j*(cur_game->cols)+i];
                    cur_game->cells[k*(cur_game->cols)+i]=-1;
                    break;
                }
                else{
                    break;
                }

            }

        }
    }





    // implement the lab shifting algo
    int target_row=cur_game->rows; // this makes sure our target row isnt too small off the jump
    int current_row=cur_game->rows;

    for(int N=0; N<(cur_game->cols);N++){// for each of the N colums
        for(int M=0; M<(cur_game->rows); M++){// for each of the M rows
            current_row=M;
            if(cur_game->cells[M*(cur_game->cols)+N]!=-1){// if the current row is not empty
                for(int F=0; F<(cur_game->rows); F++){//finding target row
                    if(cur_game->cells[F*(cur_game->cols)+N]==-1 && F<current_row){
                        target_row=F;
                        cur_game->cells[target_row*(cur_game->cols)+N]=cur_game->cells[current_row*(cur_game->cols)+N];
                        cur_game->cells[current_row*(cur_game->cols)+N]=-1;// empty cells are -1
                        
                    } 

                }
            
            }

        }
   
    }
    
    int flag=0;// we we will choose to see if we made a valid move or not
    //now lets check for a valid move
    for(int v=0; v<(cur_game->cols)*(cur_game->rows); v++){// looping over the entire array
        if(deepcopy[v]!= cur_game->cells[v]){
            flag=1;// flag gets set to 1 becasue a difference was detected
        }
    }
       


    
    

    //printf("%d",flag);
    return flag;// we can return flag because it is 1 if there is a valid move and 0 if not a valid move
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    cell deepcopy[(cur_game->rows)*(cur_game->cols)];
    for(int i=0; i<((cur_game->rows)*(cur_game->cols)); i++){// causing seg fault
       deepcopy[i]= cur_game->cells[i];
    }// this loops copied all the cells over
    
    for(int i=0; i<cur_game->cols; i++){// for every colum

        for(int j=(cur_game->rows)-1; j>-1;j--){ //for every row, startin at row max row
            // find the bottom most non zero row
            if(cur_game->cells[j*(cur_game->cols)+i]==-1){
                continue;
            }
            for(int k=j-1; k>-1;k--){// based of previous loop index
                if(cur_game->cells[k*(cur_game->cols)+i]==-1){// allows us to skip past blanks
                    continue;
                }
                if(cur_game->cells[j*(cur_game->cols)+i]== cur_game->cells[k*(cur_game->cols)+i]){
                    cur_game->cells[j*(cur_game->cols)+i]= (cur_game->cells[j*(cur_game->cols)+i])*2;
                    cur_game->score += cur_game->cells[j*(cur_game->cols)+i];
                    cur_game->cells[k*(cur_game->cols)+i]=-1;
                }
                else{
                    break;
                }

            }

        }
    }

    //below is the shifting algo
    int target_row = 0; // this makes sure our target row isnt too small off the jump
    int current_row = 0;
    for(int N=0; N<(cur_game->cols);N++){// for each of the N colums
        for(int M=(cur_game->rows)-1; M>-1; M--){// for each of the M rows
            current_row=M;
            if(cur_game->cells[M*(cur_game->cols)+N]!=-1){// if the current row is not empty
                for(int F=(cur_game->rows)-1; F>-1; F--){//finding target row
                    if(cur_game->cells[F*(cur_game->cols)+N]==-1 && F>current_row){
                        target_row=F;
                        cur_game->cells[target_row*(cur_game->cols)+N]=cur_game->cells[current_row*(cur_game->cols)+N];
                        cur_game->cells[current_row*(cur_game->cols)+N]=-1;// empty cells are -1
                    } 

                }
            
            }

            
        }
    
       
        
    }
    
    // check for change
    int flag=0;// we we will choose to see if we made a valid move or not
    //now lets check for a valid move
    for(int v=0; v<(cur_game->cols)*(cur_game->rows); v++){// looping over the entire array
        if(deepcopy[v]!= cur_game->cells[v]){
            flag=1;// flag gets set to 1 becasue a difference was detected
        }
    }



    return flag;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    cell deepcopy[(cur_game->rows)*(cur_game->cols)];
    for(int i=0; i<((cur_game->rows)*(cur_game->cols)); i++){
       deepcopy[i]= cur_game->cells[i];
    }// this loops copied all the cells over thus making a deep copy
    //a means everything is goin to be shifting left
    
    //here is the merge
    for (int i=0; i<cur_game->rows;i++){// for every row i

        for (int j=0; j<cur_game->cols;j++ ){// for every elemnt of  the row j
            if(cur_game->cells[i*(cur_game->cols)+j]==-1){// trying ot find the smallest colum index with non zero entry
                continue;
            }
            for(int k=j+1;k<cur_game->cols;k++){// finding the second non blank entry in a given row
                if(cur_game->cells[i*(cur_game->cols)+k]==-1){// trying ot find the smallest colum index with non zero entry
                    continue;
                }
                if(cur_game->cells[i*(cur_game->cols)+j]==cur_game->cells[i*(cur_game->cols)+k]){// if theyre equal ie merge
                  cur_game->cells[i*(cur_game->cols)+j]=(cur_game->cells[i*(cur_game->cols)+j])*2;
                  cur_game->score+= cur_game->cells[i*(cur_game->cols)+j];
                  cur_game->cells[i*(cur_game->cols)+k]=-1;
                  break;
                }
                else{
                    break;
                }

            }

        }
    }
    
    //shifting algorithm
    int target_col = cur_game->cols; // this makes sure our target row isnt too small off the jump
    int current_col = cur_game->cols;
    for(int M=0; M<cur_game->rows; M++){// for each of the M rows

        for(int N=0; N<cur_game->cols; N++){// for the N elements of each row
            current_col=N;
            if(cur_game->cells[M*(cur_game->cols)+N]!=-1){// if current col not empty
                
                for(int F=0; F<(cur_game->cols); F++){
                    if(cur_game->cells[M*(cur_game->cols)+ F]==-1 && F<current_col){
                        target_col=F;
                        // puts the line below from current col to target col
                        cur_game->cells[M*(cur_game->cols)+target_col]= cur_game->cells[M*(cur_game->cols)+current_col];
                        cur_game->cells[M*(cur_game->cols)+current_col]=-1;
                    }

                }

            }



        }

    }
    
    int flag=0;// we we will choose to see if we made a valid move or not
    //now lets check for a valid move
    for(int v=0; v<(cur_game->cols)*(cur_game->rows); v++){// looping over the entire array
        if(deepcopy[v]!= cur_game->cells[v]){
            flag=1;// flag gets set to 1 becasue a difference was detected
        }
    }
    return flag;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    cell deepcopy[(cur_game->rows)*(cur_game->cols)];
    for(int i=0; i<((cur_game->rows)*(cur_game->cols)); i++){
       deepcopy[i]= cur_game->cells[i];
    }// this loops copied all the cells over thus making a deep copy
    //d means everything shifts to the right
    
    //merge algo
    for (int i=0; i<cur_game->rows;i++){// for every row i

        for (int j=(cur_game->cols)-1; j>-1;j-- ){// for every elemnt of  the row j
            if(cur_game->cells[i*(cur_game->cols)+j]==-1){// trying ot find the largest colum index with non zero entry
                continue;
            }
            for(int k=j-1;k>-1;k--){// finding the second largest index that is non blank entry in a given row
                if(cur_game->cells[i*(cur_game->cols)+k]==-1){// trying ot find the smallest colum index with non zero entry
                    continue;
                }
                if(cur_game->cells[i*(cur_game->cols)+j]==cur_game->cells[i*(cur_game->cols)+k]){// if theyre equal ie merge
                  cur_game->cells[i*(cur_game->cols)+j]=(cur_game->cells[i*(cur_game->cols)+j])*2;
                  cur_game->score+= cur_game->cells[i*(cur_game->cols)+j];
                  cur_game->cells[i*(cur_game->cols)+k]=-1;
                  break;
                }
                else{
                    break;
                }

            }

        }
    }

    //shifting algorithm
    int target_col = 0; // this makes sure our target row isnt too big off the jump
    int current_col = 0;
    for(int M=0; M<cur_game->rows; M++){// for each of the M rows 

        for(int N=(cur_game->cols)-1; N>-1; N--){// for the N elements of each row except now iterate from other side
            current_col=N;
            if(cur_game->cells[M*(cur_game->cols)+N]!=-1){// if current col not empty
                
                for(int F=(cur_game->cols)-1; F>-1; F--){
                    if(cur_game->cells[M*(cur_game->cols)+ F]==-1 && F>current_col){
                        target_col=F;
                        // puts the line below from current col to target col
                        cur_game->cells[M*(cur_game->cols)+target_col]= cur_game->cells[M*(cur_game->cols)+current_col];
                        cur_game->cells[M*(cur_game->cols)+current_col]=-1;
                    }

                }

            }



        }

    }
    
    int flag=0;// we we will choose to see if we made a valid move or not
    //now lets check for a valid move
    for(int v=0; v<(cur_game->cols)*(cur_game->rows); v++){// looping over the entire array
        if(deepcopy[v]!= cur_game->cells[v]){
            flag=1;// flag gets set to 1 becasue a difference was detected
        }
    }
    return flag;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.

 */
{
    //YOUR CODE STARTS HERE
   
   game *game_deepcopy;// initialize a deep copy ptr
   game_deepcopy= (make_game(cur_game->rows,cur_game->cols));
   for(int i=0; i<(cur_game->rows)*(cur_game->cols); i++){
    game_deepcopy->cells[i]=cur_game->cells[i];
   }
   if(move_a(game_deepcopy)||move_d(game_deepcopy)||move_s(game_deepcopy)|| move_w(game_deepcopy)){
    destroy_game(game_deepcopy);
    return 1;
    }
    destroy_game(game_deepcopy);
    
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}