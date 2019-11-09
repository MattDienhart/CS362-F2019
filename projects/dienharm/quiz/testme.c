// Random Testing Quiz
// inputChar() and inputString() written by Matt Dienhart
// Date: 11/9/2019

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    int category;
    char returnChar;
    char* category0 = "[]{}()";
    char* category2 = "!\"#$%&'*+,-./:;<>=?`~_^@\\";

    // select a category of character types
    category = rand() % 6;

    switch(category) {
       // Category 0: brackets & parentheses
       case(0):
          // get a random bracket or parentheses character
          returnChar = category0[rand() % strlen(category0)];
          break;
       // Category 1: lower case letters
       case(1):
          // get a random lower case letter (ASCII 97 - 122)
          returnChar = (char) (97 + (rand() % 26));
          break;
       // Category 2: symbols
       case(2):
          // get a random symbol character
          returnChar = category2[rand() % strlen(category2)];
          break;
       // Category 3: upper case letters
       case(3):
          // get a random upper chase letter (ASCII 65 - 90)
          returnChar = (char) (65 + (rand() % 26));
          break;
       // Category 4: numbers
       case(4):
          // get a random number character (ASCII 48 - 57)
          returnChar = (char) (48 + (rand() % 10));
          break;
       // Category 5: empty space
       default:
          returnChar = ' ';
    }

    return returnChar;
}

char *inputString()
{
    // TODO: rewrite this function
    int category;
    char c;
    int i;
    char* returnString;
    char* category1[] = {"reset", "RESET", "Reset", "exit", "quit", "abort",
                          "stop", "terminate", "desist", "cease", "abate", "give up"};
    char* category2[] = {"apple", "bark", "leaf", "character", "valid", "loop",
                          "boat", "summer", "whiskey", "foxtrot", "adventure", "koala"};

    char* category3[] = {"APPLE", "BARK", "LEAF", "CHARACTER", "VALID", "LOOP",
                          "BOAT", "SUMMER", "WHISKEY", "FOXTROT", "ADVENTURE", "KOALA"};
    char category4[11];
    memset(category4, '\0', 11); // clear category 4 string with all null terminators

    // select a category of string types
    category = rand() % 6;

    switch(category) { 
       // Category 0: single character from inputChar()
       case(0):
          // get a single character from inputChar() to be the returnString
          c = inputChar();
          returnString = &c;
          break;
       // Category 1: valid exit keyword "reset" and other similar but invalid keywords
       case(1):
          // choose a random word from category1 array (12 elements)
          returnString = category1[rand() % 12];
          break;
       // Category 2: random real words of varying lengths, lower case
       case(2):
          // choose a random word from category2 array (12 elements)
          returnString = category2[rand() % 12];
          break;
       // Category 3: random real words of varying lengths, upper case
       case(3):
          // choose a random word from category3 array (12 elements)
          returnString = category3[rand() % 12];
          break;
       // Category 4: a word made up of 10 random characters from inpuChar()
       case(4):
          // loop and call inputChar() until category4 string has 10 random characters
          for (i=0; i<10; i++) {
             c = inputChar();
             category4[i] = c;
          }
          returnString = category4;
          break;
       // Category 5: empty string
       default:
          returnString = "";
    }

    return returnString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
