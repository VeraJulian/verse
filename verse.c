/*                                                                              
 * (c) 2015 Julian Vera                                                         
 * verse.c                                                                      
 * This program reverses the input. With -c, it reverses the characters on each
 * line. If you switch -l, it just reverses the order of lines of the input.    
 * With both switches, it does both; with neither, it assumes -c.               
 */

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

//These global variables represent the switches                                 
static int l;
static int c;

/*                                                                                                   
 * readline returns a char* that will contain an entire line of input read from                      
 * stdin held as characters. Since a line is ended with a \n character we know we                    
 * only need to read characters of a line until we hit the \n character.                             
 */
char* readline()
{
  int size = 32;
  int c;
  int i = 0;
  int done = 1;
  static char* text = 0;

  //if text is 0, which it is initially, then allocate some memory for text                          
  if(!text)
    {
      text = malloc(size*sizeof(char));
    }

  //Account for all inputs                                                                           
  while(EOF != (c = fgetc(stdin)))
    {
      done = 0;
      //If we hit a newline character then we've read all then characters in the                     
      //line                                                                                         
      if(c == '\n') break;
      if(i+1 == size) text = realloc(text,sizeof(char)*(size*=2));
      //Store all characters in text array and increment index                                       
      text[i] = c;
      i++;
    }
  //last character in a string is 0                                                                  
  text[i]=0;

  //if c hit eof and done=1 return 0, else cut return new pointer                                    
  return(c == EOF && done) ? 0 : strdup(text);
}

/*                                                                                                   
 * This method swaps letters in an array of chars. We have two pointers, one to the begging          
 * of the char array and the other at the end. All we do is exchange letters pointed to by l and r.  
 * Ex. HI THERE => EI THERH ...                                                                      
 */
void swapletter(char* l, char* r){
  char temp = *l;
  *l = *r;
  *r = temp;
}

/*                                                                                                   
 * This method reverses a string                                                                     
 */
void swapline(char* l){
  char* r = l + strlen(l) - 1;
  while(l < r){
    swapletter(l++,r--);
  }
}

/*                                                                                                   
 * This method swaps the lines input by printing the string array starting from the                  
 * end. The l is the left end of the string array and the r is the right end.                        
 * We simply switch them                                                                             
 */
void swaplines(char** l, char** r){
  char* temp = *l;
  *l = *r;
  *r = temp;
}

/*                                                                                                   
 * We've kept track of how many lines were input and have those lines stored in                      
 * a string array so to swap lines we just need to traverse the string array                         
 * and call the swaplines method above                                                               
 */
void swaplineorder(char** l, int numLines){
  char** r = l + numLines - 1;
  while(l < r){
    swaplines(l++,r--);
  }
}

/*                                                                                                   
 * parseArgs sets the switches, determined by the command line text. A switch                        
 * activation will be represented by a 1. If no switches are entered, then                           
 * the default switch -c will be activated                                                           
 */
void parseArgs(int argc,char** argv){
  //stores the switches that were thrown                                                             
  int switches;
  //determines which switches were thrown, max 2                                                     
  int nums;
  if(argc > 1){
    for(nums = 1; nums < 3; nums++){
      switches = argv[1][nums];
      switch(switches){
      case 'c':
        c = 1;
        break;
      case 'l':
        l = 1;
        break;
      }
    }
  }
  //This is the case if no switches have been thrown                                                 
  if(!(c || l)) c = 1;
}

int main(int argc, char** argv)
{
  //Determine which switches are activated early on                                                  
  parseArgs(argc,argv);

  //this int will be used to print lines held in char**                                              
  int i;

  //arbitrary sizes that will be used to allocate memory for char* and char**                        
  int size = 32;
  int size2 = 32;

  //arr_str will hold the strings of each line                                                       
  char ** arr_str = malloc(size * sizeof(char*));

  //will be used to read each character of line                                                      
  char * str = malloc(size2 * sizeof(char));

  //num_sentences is really number of lines                                                          
  int num_sentences = 0;

   /*                                                                                                 
   * This while loop places all of the characters of the stdin into the str array                    
   * of characters and ensures the arr_str is large enough to hold all the                           
   * character arrays                                                                                
   */
  while( (str = readline()) ){
    if(num_sentences == size)
      arr_str = realloc(arr_str, sizeof(char)*(size*=2));
    /*                                                                                               
     * To make life easier, swap the characters in a line before they're placed                      
     * into the arr_str since they will always be switched (-c is assumed)                           
     */
    if(c) swapline(str);
    //Place character arrays into arr_str                                                            
    arr_str[num_sentences++] = str;
  }
  /*                                                                                                 
   * Call the swaplineorder function that takes an array of "strings" and the number                 
   * of lines to be switched                                                                         
   */
  if(l) swaplineorder(arr_str, num_sentences);

  //Once the switches have been accounted for, print the desired product                             
  for(i = 0; i < num_sentences; i++){
    puts(arr_str[i]);
  }
  return 0;
}
