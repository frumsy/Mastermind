//masterminds game 
#include <stdio.h>
#include <stdlib.h>

#define SLOT 0
#define WHITE_PEG -1
#define BLACK_PEG -2

#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define BACK_C_BLUE "\x1b[44m"
#define BACK_C_BLACK "\x1b[40m"
#define C_CYAN    "\x1b[36m"
#define C_RESET   "\x1b[0m"

const int number_pegs = 4;
const int number_rows = 12;
const int colors = 6;
int turn = 0;
int goalRow[number_pegs];

struct row
{
	int pegs[number_pegs];
	int *cluePegs;
};

struct row board[number_rows + 1];

bool won(int* cluePegs)
{
	for(int i =0; i < number_pegs; i++)
	{
		if(cluePegs[i] != BLACK_PEG)
		{
			return false;
		}
	}
	//take this out if you want to use it in an if or for something else.
	printf("%s\n", "YOU WIN!!!!!!");
	exit(0);
	//
	return true;
}

void printRow(int * row)
{
	printf(BACK_C_BLUE C_MAGENTA "# ");
	for(int i = 0; i <= 3; i++) {
    	printf("%d ", row[i]);
    }
    printf("#");
    printf("%s\n", BACK_C_BLACK);
}

int* guessPegs()
{
	static int guess[number_pegs];
	printf("%s\n", "try to guess the code!.");
	for(int i = 0; i < number_pegs; i++)
	{
		printf("Enter peg number %d: ", i+1);
		scanf("%d", &guess[i]);
		if(guess[i] >= colors || guess[i] < 0)
		{
			printf("%s\n", "OUT OF RANGE");
			guess[0] = -1;
			return guess;
		}
	}
	return guess;
}

//returns a another row with white or black spaces filled in according to the game rules.
int * getClues(int * row)
{
	static int clues[4] = {SLOT, SLOT, SLOT, SLOT};	
	//add black to clues if row has the correct color
	for (int i = 0; i <= 3; i++)
	{
	   	if(goalRow[i] == row[i])
		{
			clues[i] = BLACK_PEG;
		}
	}
	for (int i = 0; i <= 3; i++)
	{
		if(clues[i] == SLOT)
		{
			//check for white
			for (int j = 0; j <= 3; j++)
			{
				if(goalRow[j] == row[i] && clues[j] != BLACK_PEG)	
				{
					clues[i] = WHITE_PEG;
				}
			}
		}
	}
return clues;
}

bool setGoalPeg()
{
	printf("%s\n", "please set goal row.");
	for(int i = 0; i < number_pegs; i++)
	{
		printf("Enter peg number %d: ", i+1);
		scanf("%d", &goalRow[i]);
		if(goalRow[i] >= colors || goalRow[i] < 0)
		{
			return false;
		}
	}
	return true;
}

void run()
{
	while(turn < number_rows){
		//make guess
		int* guess = guessPegs();
		while(guess[0] == -1)
		{
			printf("There was an error. The pegs in your guess must be ints in range [0-%d]\nTry again.\n", colors-1);
			guess = guessPegs();
		}

		//print current row
		printRow(guess);
		//print clues
		board[turn].cluePegs = getClues(guess);
		printRow(board[turn].cluePegs);

		//check to see if the player has won.
		won(board[turn].cluePegs);
		turn++;
	}
	printf("%s\n", "You are out of tries! YOU LOSE! Try again?");
}

int main()
{
	while(!setGoalPeg())
	{
		printf("There was an error. The pegs must be integers in the range [0-%d]\nTry again.\n", colors-1);
	}
	printRow(goalRow);
	run();	
}