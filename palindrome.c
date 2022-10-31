#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "queue.h"
#include "stack.h"

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
  printf("\nEnter a string, and we'll check whether it's a palindrome:\n");
  if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
    /*
     * If a string was successfully read from the user, remove any trailing
     * line ending characters.  Here's some documentation on strcspn() to help
     * understand how this works:
     *
     * https://en.cppreference.com/w/c/string/byte/strcspn
     */
    
    dest[strcspn(dest, "\r\n")] = '\0';
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char const *argv[]) {
  char* in = malloc(MAX_STR_LEN * sizeof(char));
  char* in2;
  struct queue* qu;
  struct stack* stack;
  

  while (get_user_str(in, MAX_STR_LEN)) {
    /*
     * Inside this loop body, you'll have an input string from the user in `in`.
     * You should use your stack and your queue to test whether that string is
     * a palindrome (i.e. a string that reads the same backward as forward, e.g.
     * "ABCBA" or "Madam, I'm Adam").  For each string input by the user,
     * print a message letting the user know whether or not their string is
     * is a palindrome.
     *
     * When you test whether the user's string is a palindrome, you should
     * ignore any non-letter characters (e.g. spaces, numbers, punctuation,
     * etc.), and you should ignore the case of letters (e.g. the characters
     * 'a' and 'A' should be considered as equal).  The C functions isalpha()
     * and tolower() from ctype.h might help with this.
     * https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/
     */
    in2 = in;
    qu = queue_create();
    stack = stack_create();
    for (int i = 0; in2[i] != '\0'; i++)
    {
      
        // check for non letters and spaces
      if (isalpha(in2[i]) == 0){
        // for(int j = i; in2[j] != '\0'; j++){
        //   in2[j] = in2[j+1];
        // }
        // i--;
        continue;
      }
      //check for uppercase
      in2[i] = tolower(in2[i]);

      //insert vals into the queue and stack      
      queue_enqueue(qu, &in2[i]);
      // printf("insert: %s\n", queue_front(qu));
      // printf("insert qu: %c\n", *(char*)queue_front(qu));
      stack_push(stack, &in2[i]);
      // printf("Insert: %s\n", stack_top(stack));
      // printf("insert stacl: %c\n", *(char*)stack_top(stack));
    }
    

    // for (int i = 0; in2[i] != '\0'; i++)
    while(stack_isempty(stack) == 0 && queue_isempty(qu) == 0)
    {
      char* dq = queue_dequeue(qu);
      // printf("qu: %c\n", dq[0]);
      char* st = stack_pop(stack);
      // printf("stack: %c\n", st[0]);
      if(dq[0] != st[0]){
        printf("Not a palendrome:(\n");
        queue_free(qu);
        stack_free(stack);
        free(in);
        return 0;
      }
    }

    // if(isalpha(in)){
      printf("%s is a palendrome!\n", in);
      queue_free(qu);
      stack_free(stack);
      free(in);
      return 0;
      // break;
    // }
    
  }
  
  
  
  
  
  

  return 0;
}
