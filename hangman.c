#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int random_numbers(int i);
void man(int mistakes, char* body);
void printWord(char* guess, int len);
void trimTrailing(char * str);

typedef struct text{
	char texts[40];
}t;

int main() {

	printf("\n\t - 7 mistakes and you will be hanged.");
	printf("\n\t - Enter all characters in lower case.");

        FILE *fp1;
	int o;
	t shuffled[847];
	fp1 = fopen("text.txt","r");
	while(!feof(fp1)){
		for(o=0;o<847;o++)
		{
			fgets(shuffled[o].texts,40,fp1);
		}
	}
	//extracting words from file text.txt which contains 847 random words
	
	char *body = malloc(7);
	//malloc allocates a block of memory of 7 bytes and stores address in body pointer

       	int word_no = random_numbers(847);
	//choosing a random word from the list using the function radom_numbers
	
	char *word = (shuffled[word_no].texts);
	trimTrailing(word);
        int len = strlen(word);	
        char *guessed = malloc(len);
	//guessed pointer stores memory location equal to the length of the word
	char falsechar[7];
        //Falsechar stores all the mistaken characters.

	memset(body, ' ', 7);
	// memset fuction replaces the first mistakes+1 characters of body by space/s
	
	memset(guessed, '_', len);
	// memset fuction replaces the first mistakes+1 characters of guessed by space/s
  
	char guess;
	bool found ;
	char* win;

	int mistakes = 0;

	do {
    found = false;
		printf("\n\n");
		man(mistakes, body);
		printf("\n\n");
		printf("\tFalse Letters : ");

		if(mistakes == 0) printf("None for now\n");
		for (int i = 0; i < mistakes; ++i)
		{
			printf("%c", falsechar[i]);
		}
		
		printf("\n\n");
		printWord(guessed, len);//prints the characters as the user guesses "-" for the characters not guessed 
		printf("\tEnter a character in lower case : ");
		
		do {
			scanf("%c",&guess);
		} while ( getchar() != '\n' );
		
		for (int i = 0; i < len; ++i)
		{
			if(word[i] == guess) {
				found = true;
				guessed[i] = guess;
			}	
		}

		if(!found) {
			falsechar[mistakes] = guess;
			mistakes += 1;
		}
		win = strchr(guessed, '_'); 
		//searches for the first appearance of space in guessed.
	}while(mistakes < 7 && win != NULL);
        //runs until number of mistakes increases to 7

	if(win == NULL) {
		printf("\n");
		printWord(guessed, len);
		printf("\nHurrah! You have won , the word was : %s\n\n", word);
		//if there is no blank space remaining in the word the user wins.
	}
	else {
		printf("\n");
		man(mistakes, body);
		printf("\n\n\tBetter try next time. The word was %s\n\n", word);
		//if there is a blank space remaining in the word the user is totally hanged and he/she loses.
	}


	return 0;
}

bool srand_called = false;
//This function returns an remainder of an random number. srand here is used to seed rand() such tah it returns a different number on every execution
int random_numbers(int i){
	srand(time(0));
  return rand() % i;
}

// man function is used to draw body parts of the man according to the mistake's number

void man(int mistakes, char* body) {
	printf("\tMistakes :%d\n", mistakes);
	switch(mistakes) {

		case 6: body[6] = '\\'; break;//for sixth mistake
		case 5: body[5] = '/'; break;//for fifth mistake
		case 4: body[4] = '\\'; break;//for fourth mistake
		case 3: body[3] = '|'; break;//for third mistake
		case 2: body[2] = '/'; break;//for second mistake
		case 1: body[1] = ')', body[0] = '('; break;//for first mistake
		default: break;

	}

	printf("\t _________\n"
	       "\t|         |\n"
	       "\t|        %c %c\n"
	       "\t|        %c%c%c\n"
	       "\t|        %c %c\n"
	       "\t|             \n"
	       "\t|             ", body[0], body[1], body[2],
	       body[3], body[4], body[5], body[6]);
}

//this function is used to print the word as per the user's guesses.
void printWord(char* guess, int len) {
	printf("\t");
	for (int i = 0; i < len; ++i)
	{
		printf("%c ", guess[i]);
	}
	printf("\n\n");
}

//This function trims the trailing white spaces we get in the strings after reading from the file

void trimTrailing(char * str)
{
    int index, i;

    index = -1;

    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    str[index + 1] = '\0';
}
