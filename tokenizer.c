/*Nathaniel Lovin, Josh Oettinger, Tenzin Dolphen
Methods to break input into tokens and assign types
*/

#include <stdio.h>
#include "value.h"
#include "talloc.h"
#include "linkedlist.h"

/*There's probably going to be a bunch of helper methods here
*/

/*This is just the code Jed said to use as a starter right now.
*/
Value *tokenize(){
   char charRead;
   Value *list = makeNull();
   charRead = fgetc(stdin);
   while (charRead != EOF) {
      if (charRead == ) {
         ...
      } else if (charRead == ...) {
         ...
      } else {
         ...
      }
      charRead = fgetc(stdin);
   }
   return reverse(list);
}

/*displayTokens, based in part on the linkedlist display
*/
void displayTokens(Value *list) {
	Value *current = list;
	while(!isNull(current)){
		switch(current->c.car->type){
			case BOOL_TYPE:
				printf("%s:boolean\n", current->c.car->s);
			case INT_TYPE:
        printf("%i:integer\n", current->c.car->i);
        break;
      case DOUBLE_TYPE:
       	printf("%f:float\n", current->c.car->d);
        break;
      case STR_TYPE:
      	printf("%s:string\n", current->c.car->s);
				break;
			case SYMBOL_TYPE:
				printf("%s:symbol\n", current->c.car->s);
				break;
			case OPEN_TYPE:
				printf("(:open\n");
				break;
			case CLOSE_TYPE:
				printf("):close\n");
				break;
			default:
				printf("invalid token type");
		}
		current = current->c.cdr;
	}
}
