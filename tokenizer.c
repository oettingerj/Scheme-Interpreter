/*Nathaniel Lovin, Josh Oettinger, Tenzin Dolphen
Methods to break input into tokens and assign types
*/

#include <stdio.h>
#include "value.h"
#include "talloc.h"
#include "linkedlist.h"
#include <ctype.h>

/*There's probably going to be a bunch of helper methods here
*/

/*This is just the code Jed said to use as a starter right now.
*/
Value *tokenize(){
  char charRead;
  Value *list = makeNull();
  charRead = fgetc(stdin);
  /*Ignore rest of line if comment*/
  if(charRead == ';'){
    charRead = EOF;
  }

  Value *val = talloc(sizeof(Value));

  while (charRead != EOF) {
    if (charRead == '(' ) {
      //Open parentheses
      val->type = OPEN_TYPE;
      val->s = "(";
      list = cons(val, list);
    } else if (charRead == ')') {
      //Close parentheses
      val->type = CLOSE_TYPE;
      val->s = ")";
      list = cons(val, list);
    } else if (charRead == '#') {
      /*create a string, add to it until space
      which is also what we'll do for strings and
      symbols*/
    } else if (charRead == '"') {
      //Strings
      char str[256] = "";
      int strLen = 0;
      charRead = fgetc(stdin);
      while(charRead != '"'){
        if(charRead == '\\'){
          charRead = fgetc(stdin);
          switch(charRead){
            case 'n':
              str[strLen] = '\n';
              strLen++;
              break;
            case 't':
              str[strLen] = '\t';
              strLen++;
              break;
            case '\\':
              str[strLen] = '\\';
              strLen++;
              break;
            case '\'':
              str[strLen] = '\'';
              strLen++;
              break;
            case '"':
              str[strLen] = '"';
              strLen++;
              break;
            default:
              break;
          }
        } else{
          str[strLen] = charRead;
          strLen++;
        }
      }
      val->type = STR_TYPE;
      val->s = str;
      list = cons(val, list);
    } else if(charRead == '+') {
      charRead = fgetc(stdin);
      if(charRead == ' '){
        val->type = SYMBOL_TYPE;
        val->s = "+";
        list = cons(val, list);
      }
      else if (isdigit(charRead)){
        //Number
      }
      else {
        printf("invalid");
        texit(1);
      }
    } else {
      printf(".");
    }
    charRead = fgetc(stdin);
    /*There's probably a better way to do this*/
    if(charRead == ';'){
      charRead = EOF;
    }
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
