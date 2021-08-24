#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int random_numbers(int i);
void man(int mistakes, char* body);
void printWord(char* guess, int len);


#define WORDS 10
#define WORDLEN 40
#define MISTAKES 6


int main() {

	printf("\n\t - Maximum 6 mistakes are allowed.");
	printf("\n\t - Enter all characters in lower case.");

	char texts[WORDS][WORDLEN] = {"able","about","account","acid","across","act","addition","adjustment","advertisement","after"};
	
	char *body = malloc(MISTAKES+1);
	//malloc allocates a block of memory of 7 bytes and stores address in body pointer

	int word_no = random_numbers(WORDS);
	char *word = (texts[word_no]);
	int len = strlen(word);
	char *guessed = malloc(len);
	//guessed pointer stores memory location equal to the length of th word
	char falseWord[MISTAKES];
  //Falseword stores all the mistaken words.

	memset(body, ' ', MISTAKES+1);
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
			printf("%c", falseWord[i]);
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
			falseWord[mistakes] = guess;
			mistakes += 1;
		}
		win = strchr(guessed, '_'); //searches for the first appearance of space in guessed.
	}while(mistakes < MISTAKES && win != NULL);

	if(win == NULL) {
		printf("\n");
		printWord(guessed, len);
		printf("\nHurrah! You have won , the word was : %s\n\n", word);
	} else {
		printf("\n");
		man(mistakes, body);
		printf("\n\n\tBetter try next time. The word was %s\n\n", word);
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

//this functio is used to print the word as per the user's guesses.
void printWord(char* guess, int len) {
	printf("\t");
	for (int i = 0; i < len; ++i)
	{
		printf("%c ", guess[i]);
	}
	printf("\n\n");
}
