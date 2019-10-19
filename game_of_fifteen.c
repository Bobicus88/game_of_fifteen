#include <stdio.h>
#include <math.h>

// must include stdlib.h to use atoi()
#include <stdlib.h> 

// must include this to use bool
#include <stdbool.h>

/****************
GLOBAL VARIABLES
****************/
//functions defined later in the program
void init(void);
void draw(void); 
void move(void);
bool won(void); 


// dimension constant
#define DIM_MAX 9
#define DIM_MIN 3

// The number of rows/columns
int row_col = 4; 

// Keeps track of the coordinates of the space and the tile that the user wants to switch
int space_row;
int space_col; 
int num_row; 
int num_col; 

//board
int board[DIM_MAX][DIM_MAX];

// variable to store number to switch
char number[2]; 


int main(void) {
  // initializes board array
  init();
  while (won() != true)
  {
    // draws board according to initialized board array 
    draw();
    // prompts user for number to switch
    move(); 
  }

}

// initializes values in board array
void init(void)
{
  // variable that keeps track of number being printed onto initial board
  int board_num = (row_col * row_col) - 1;
  
  // populates board array with initial board values
  for (int row = 0; row < row_col; row ++)
  {
    for (int col = 0; col < row_col; col ++)
    {
      board[row][col] = board_num--;
    }
  } 
}

// draws board
void draw(void)
{
  for (int row = 0; row < row_col; row++)
  {
    for (int col = 0; col < row_col; col++)
    {
      // prints space instead of 0 
      if ((board[row][col]) == 0)
      {
        printf("  _ "); 
        space_row = row; 
        space_col = col; 
      }
      // prints column 3 characters wide for each number 
      else
      {
        printf("%3i", board[row][col]); 
      }
    }
    printf("\n"); 
  }
}

void move(void)
{
  printf("Please enter a number to switch. ");
  scanf("%s", number);
  int num_int = atoi(number);
  // printf("%i\n", num_int); 
  for (int row = 0; row < row_col; row++)
  {
    for (int col = 0; col < row_col; col++)
    {
      if (board[row][col] == num_int)
      {
        // keeps track of the row and col of the tile that the user wants to switch
        num_row = row;
        num_col = col; 
      }

      else if (board[row][col] == 0)
      // keeps track of the row and col of the space
      {
        space_row = row; 
        space_col = col; 
      }
    }
  }

  // checks if the move is legal (if the tile is right next to the blank space), and if so, switches the blank and tile 
  if (abs((num_row - space_row) + (num_col - space_col)) == 1)
  {
    int blank = board[space_row][space_col];

    board[space_row][space_col] = board[num_row][num_col]; 
    
    board[num_row][num_col] = blank; 
  }
  else
  {
    printf("Invalid move.\n"); 
  }
}

// game is won if tiles are in increasing order - left to right, top to bottom
bool won(void)
{
  // keeps track of the number of correct tiles
  int counter = 0; 

  for (int row = 0; row < row_col; row ++)
  {
    for (int col = 0; col < row_col; col ++)
    {
      if (board[row][col] == row_col * row + col + 1)
      {
        counter++; 
      }
    }
  }

  if (counter == row_col * row_col - 1)
  {
    return true;   
  }
  else
  {
    return false; 
  }
}
