#include <stdio.h>
#include <stdlib.h>

/*

In this MP we were tasked to print out rows in Pascal's triangle
To do this we were given an equation which was able to compute the coeffecients of the terms in the triangle
To implement this MP, I came to the realization that the first term in every row of the triangle was 1.
Therefore I hard coded the first output. Secondly I realized that I should only enter the for loop if 
i<=row to avoid an incorrect output for row=0
The loop is self just uses the formula and prints the output of the formula
the loop is i<=row to maintain the correct output for row 1

*/


int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);
 
  // Write your code here
 
  
  unsigned long int VALUE = 1 ;
  printf("%lu ", VALUE); // The triangle's first term is always a one thus print this
   
      for(unsigned long int i = 1; i<=row; i++ ){ // due to already printing the first term we want to ignore the loop if row =0
        
        VALUE = VALUE * (row - i + 1) / i;// formula from mp which uses previous product to compute next output
        
        printf("%lu ", VALUE); // prints output every itteration of the for loop

      }

      

  
  
  
  
  return 0;
}