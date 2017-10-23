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

/*TODO:
1. Comments should end line, not file
2. Increase string character limit
3. Test files*/
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
      }
      else if (charRead == 'f'){
        val->type = BOOL_TYPE;
        val->s = "#f";
      }
      else {
        printf("invalid\n");
        texit(1);
      }
    } else if (charRead == '"') {
      //Strings
      char *str = talloc(sizeof(char)*256);
      str[0] = '"';
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
      strLen++;
      str[strLen] = 0;
      val->type = STR_TYPE;
      val->s = str;
    } else if(charRead == '+' || charRead == '-') {
      char *nstr = talloc(sizeof(char)*256);
      int nstrLen = 0;
      nstr[nstrLen] = charRead;
      nstrLen++;
      charRead = fgetc(stdin);
      if(charRead == ' '){
        nstr[nstrLen] = 0;
        val->type = SYMBOL_TYPE;
        val->s = nstr;
      } else{
        bool noDot = true;
        while(isdigit(charRead) || (charRead == '.' && noDot == true)){
          nstr[nstrLen] = charRead;
          nstrLen++;
          if(charRead == '.'){
            noDot = false;
          }
          charRead = fgetc(stdin);
        }
        if (charRead==' '){
          if(noDot){
            int x = atoi(nstr);
            val->type = INT_TYPE;
            val->i = x;
          }
          else {
            float x = atof(nstr);
            val->type = DOUBLE_TYPE;
            val->d = x;
          }
        } else if(charRead == ')'){
          if(noDot){
            int x = atoi(nstr);
            val->type = INT_TYPE;
            val->i = x;
            ungetc(charRead, stdin);
          } else {
            float x = atof(nstr);
            val->type = DOUBLE_TYPE;
            val->d = x;
            ungetc(charRead, stdin);
          }
        } else {
          printf("invalid\n");
          texit(1);
        }
      }
    } else if(charRead == '.'){
      char *dstr = talloc(sizeof(char)*256);
      int dstrLen = 0;
      dstr[dstrLen] = charRead;
      dstrLen++;
      charRead = fgetc(stdin);
      if(!isdigit(charRead)){
        printf("invalid\n");
        texit(1);
      }
      while(isdigit(charRead)){
        dstr[dstrLen] = charRead;
        dstrLen++;
        charRead = fgetc(stdin);
      }
      if(charRead == ' '){
        float x = atof(dstr);
        val->type = DOUBLE_TYPE;
        val->d = x;
      } else if(charRead == ')'){
        float x = atof(dstr);
        val->type = DOUBLE_TYPE;
        val->d = x;
        ungetc(charRead, stdin);
      } else {
        printf("invalid\n");
        texit(1);
      }
    } else if(isdigit(charRead)){
      char *istr = talloc(sizeof(char)*256);
      int istrLen = 0;
      bool noDot = true;
      while(isdigit(charRead) || (charRead == '.' && noDot == true)){
        istr[istrLen] = charRead;
        istrLen++;
        if(charRead == '.'){
          noDot = false;
        }
        charRead = fgetc(stdin);
      }
      if (charRead == ' '){
        if(noDot){
          int x = atoi(istr);
          val->type = INT_TYPE;
          val->i = x;
        }
        else {
          float x = atof(istr);
          val->type = DOUBLE_TYPE;
          val->d = x;
        }
      } else if(charRead == ')'){
        if(noDot){
          int x = atoi(istr);
          val->type = INT_TYPE;
          val->i = x;
          ungetc(charRead, stdin);
        } else {
          float x = atof(istr);
          val->type = DOUBLE_TYPE;
          val->d = x;
          ungetc(charRead, stdin);
        }
      } else {
        printf("invalid\n");
        texit(1);
      }
    } else if(charRead != ' '){
      char *sstr = talloc(sizeof(char)*256);
      int sstrLen = 0;
      if(canStartSymbol(charRead)){
        while(canFinishSymbol(charRead)){
          sstr[sstrLen] = charRead;
          sstrLen++;
          charRead = fgetc(stdin);
        }
        sstr[sstrLen] = 0;
        val->type = SYMBOL_TYPE;
        val->s = sstr;
        ungetc(charRead, stdin);
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
        break;
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
