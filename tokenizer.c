/*Nathaniel Lovin, Josh Oettinger, Tenzin Dolphen
Methods to break input into tokens and assign types
*/

#include <stdio.h>
#include "value.h"
#include "talloc.h"
#include "linkedlist.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool canStartSymbol(char c){
  if(isalpha(c)){
    return true;
  }
  switch(c){
    case '!':
      return true;
    case '$':
      return true;
    case '%':
      return true;
    case '&':
      return true;
    case '*':
      return true;
    case '/':
      return true;
    case ':':
      return true;
    case '<':
      return true;
    case '=':
      return true;
    case '>':
      return true;
    case '?':
      return true;
    case '~':
      return true;
    case '_':
      return true;
    case '^':
      return true;
    default:
      return false;
  }
}

bool canFinishSymbol(char c){
  if(canStartSymbol(c)){
    return true;
  }
  if(isdigit(c)){
    return true;
  }
  switch(c){
    case '.':
      return true;
    case '+':
      return true;
    case '-':
      return true;
    default:
      return false;
  }
}

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

  while (charRead != EOF) {
    Value *val = talloc(sizeof(Value));
    val->type = NULL_TYPE;
    if (charRead == '(' ) {
      //Open parentheses
      val->type = OPEN_TYPE;
      val->s = "(";
    } else if (charRead == ')') {
      //Close parentheses
      val->type = CLOSE_TYPE;
      val->s = ")";
    } else if (charRead == '#') {
      charRead = fgetc(stdin);
      if (charRead == 't'){
        val->type = BOOL_TYPE;
        val->s = "#t";
        list = cons(val, list);
      }
      else if (charRead == 'f'){
        val->type = BOOL_TYPE;
        val->s = "#f";
        list = cons(val, list);
      }
      else {
        printf("invalid\n");
        texit(1);
      }
    } else if (charRead == '"') {
      //Strings
      char str[256] = "\"";
      int strLen = 1;
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
        charRead = fgetc(stdin);
      }
      str[strLen] = '"';
      val->type = STR_TYPE;
      val->s = str;
    } else if(charRead == '+' || charRead == '-') {
      char str[256] = "";
      int strLen = 0;
      str[strLen] = charRead;
      strLen++;
      charRead = fgetc(stdin);
      if(charRead == ' '){
        val->type = SYMBOL_TYPE;
        val->s = str;
      } else{
        bool noDot = true;
        while(isdigit(charRead) || (charRead == '.' && noDot == true)){
          str[strLen] = charRead;
          strLen++;
          if(charRead == '.'){
            noDot = false;
          }
          charRead = fgetc(stdin);
        }
        if (charRead==' '){
          if(noDot){
            int x = atoi(str);
            val->type = INT_TYPE;
            val->i = x;
          }
          else {
            float x = atof(str);
            val->type = DOUBLE_TYPE;
            val->d = x;
          }
        }
        else {
          printf("invalid\n");
          texit(1);
        }
      }
    } else if(charRead == '.'){
      char str[256] = "";
      int strLen = 0;
      str[strLen] = charRead;
      strLen++;
      charRead = fgetc(stdin);
      if(!isdigit(charRead)){
        printf("invalid\n");
        texit(1);
      }
      while(isdigit(charRead)){
        str[strLen] = charRead;
        strLen++;
        charRead = fgetc(stdin);
      }
      if(charRead == ' '){
        float x = atof(str);
        val->type = DOUBLE_TYPE;
        val->d = x;
      }
      else {
        printf("invalid\n");
        texit(1);
      }
    } else if(isdigit(charRead)){
      char str[256] = "";
      int strLen = 0;
      bool noDot = true;
      while(isdigit(charRead) || (charRead == '.' && noDot == true)){
        str[strLen] = charRead;
        strLen++;
        if(charRead == '.'){
          noDot = false;
        }
        charRead = fgetc(stdin);
      }
      if (charRead == ' '){
        if(noDot){
          int x = atoi(str);
          val->type = INT_TYPE;
          val->i = x;
        }
        else {
          float x = atof(str);
          val->type = DOUBLE_TYPE;
          val->d = x;
        }
      } else if(charRead == ')'){
        if(noDot){
          int x = atoi(str);
          val->type = INT_TYPE;
          val->i = x;
          ungetc(charRead, stdin);
        } else {
          float x = atof(str);
          val->type = DOUBLE_TYPE;
          val->d = x;
          ungetc(charRead, stdin);
        }
      } else {
        printf("invalid\n");
        texit(1);
      }
    } else if(charRead != ' '){
      char str[256] = "";
      int strLen = 0;
      if(canStartSymbol(charRead)){
        while(canFinishSymbol(charRead)){
          str[strLen] = charRead;
          strLen++;
          charRead = fgetc(stdin);
        }
        val->type = SYMBOL_TYPE;
        val->s = str;
      }
    }

    if(val->type != NULL_TYPE){
      list = cons(val, list);
    }
    charRead = fgetc(stdin);
    /*There's probably a better way to do this*/
    if(charRead == ';'){
      charRead = EOF;
    }
  }
  printf("");
  printf("");
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
        printf("%s:open\n", current->c.car->s);
      break;
      case CLOSE_TYPE:
        printf("%s:close\n", current->c.car->s);
      break;
      default:
        printf("invalid token type");
    }
    current = current->c.cdr;
  }
}
