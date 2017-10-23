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

/*
    Tokenizes boolean types
*/
void tokenizeBoolean(Value *val, char charRead){
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
}

/*
    Tokenizes string types
*/
void tokenizeString(Value *val, char charRead){
    char *str = talloc(sizeof(char)*32);
    str[0] = '"';
    int strLen = 1;
    int strSize = 32;
    charRead = fgetc(stdin);
    while(charRead != '"'){
        if(strSize - strLen <= 2){
            char *str2 = talloc(sizeof(char)*strSize);
            str2 = str;
            strSize += 32;
            str = talloc(sizeof(char) * strSize);
            str = str2;
        }
        if(charRead == '\\'){
            //Handle escape characters
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
}

/*
    Tokenizes operators + and -
*/
void tokenizeOperators(Value *val, char charRead){
    char *str = talloc(sizeof(char)*32);
    int strLen = 0;
    int strSize = 32;
    str[strLen] = charRead;
    strLen++;
    charRead = fgetc(stdin);
    if(charRead == ' '){
        //+/- is a symbol
        str[strLen] = 0;
        val->type = SYMBOL_TYPE;
        val->s = str;
    } else{
        //+/- at start of a number
        bool noDot = true;
        while(isdigit(charRead) || (charRead == '.' && noDot == true)){
            if(strSize - strLen <= 1){
                char *str2 = talloc(sizeof(char)*strSize);
                str2 = str;
                strSize += 32;
                str = talloc(sizeof(char) * strSize);
                str = str2;
            }
            str[strLen] = charRead;
            strLen++;
            if(charRead == '.'){
                noDot = false;
            }
            charRead = fgetc(stdin);
        }
        if (charRead == ' ' || charRead == ')' || charRead == ';'){
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
            ungetc(charRead,stdin);
        } else {
            printf("Invalid token\n");
            texit(1);
        }
    }
}

/*
    Tokenizes numbers that start with a decimal (e.g. .56)
*/
void tokenizeNumberStartingWithDecimal(Value *val, char charRead){
    char *str = talloc(sizeof(char)*32);
    int strLen = 0;
    int strSize = 32;
    str[strLen] = charRead;
    strLen++;
    charRead = fgetc(stdin);
    if(!isdigit(charRead)){
        printf("Invalid token\n");
        texit(1);
    }
    while(isdigit(charRead)){
        if(strSize - strLen <= 1){
            char *str2 = talloc(sizeof(char)*strSize);
            str2 = str;
            strSize += 32;
            str = talloc(sizeof(char) * strSize);
            str = str2;
        }
        str[strLen] = charRead;
        strLen++;
        charRead = fgetc(stdin);
    }
    if(charRead == ' ' || charRead == ')' || charRead== ';'){
        float x = atof(str);
        val->type = DOUBLE_TYPE;
        val->d = x;
        ungetc(charRead, stdin);
    } else {
        printf("Invalid token\n");
        texit(1);
    }
}

/*
    Tokenizes numbers that start with a digit
*/
void tokenizeNumber(Value *val, char charRead){
    char *str = talloc(sizeof(char)*32);
    int strLen = 0;
    int strSize = 32;
    bool noDot = true;
    while(isdigit(charRead) || (charRead == '.' && noDot == true)){
        if(strSize - strLen <= 1){
            char *str2 = talloc(sizeof(char)*strSize);
            str2 = str;
            strSize += 32;
            str = talloc(sizeof(char) * strSize);
            str = str2;
        }
        str[strLen] = charRead;
        strLen++;
        if(charRead == '.'){
            noDot = false;
        }
        charRead = fgetc(stdin);
    }
    if (charRead == ' ' || charRead == ';' || charRead == ')'){
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
        ungetc(charRead, stdin);
    } else {
        printf("Invalid token\n");
        texit(1);
    }
}

/*
    Checks if a character is a valid start to a symbol
*/
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

/*
    Checks if a character is a valid non-starting char in a symbol
*/
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

/*
    Tokenizes symbols
*/
void tokenizeSymbol(Value *val, char charRead){
    char *str = talloc(sizeof(char)*32);
    int strLen = 0;
    int strSize = 32;
    if(canStartSymbol(charRead)){
        while(canFinishSymbol(charRead)){
            if(strSize - strLen <= 1){
                char *str2 = talloc(sizeof(char)*strSize);
                str2 = str;
                strSize += 32;
                str = talloc(sizeof(char) * strSize);
                str = str2;
            }
            str[strLen] = charRead;
            strLen++;
            charRead = fgetc(stdin);
        }
        str[strLen] = 0;
        val->type = SYMBOL_TYPE;
        val->s = str;
        ungetc(charRead, stdin);
    }
}

/*TODO:
1. Increase string character limit
2. 2 more test files
*/

/*
    Tokenizes scheme files, adding each token in order to a linkedlist
*/
Value *tokenize(){
    char charRead;
    Value *list = makeNull();
    charRead = fgetc(stdin);

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
        }else if (charRead == '#') {
            tokenizeBoolean(val, charRead);
        }else if (charRead == '"') {
            tokenizeString(val, charRead);
        } else if(charRead == '+' || charRead == '-') {
            tokenizeOperators(val, charRead);
        } else if(charRead == '.'){
            tokenizeNumberStartingWithDecimal(val, charRead);
        } else if(isdigit(charRead)){
            tokenizeNumber(val, charRead);
        } else if(charRead == ';'){
            while(charRead != '\n' && charRead != EOF){
                charRead = fgetc(stdin);
            }
        } else if(charRead != ' '){
            tokenizeSymbol(val, charRead);
        }

        if(val->type != NULL_TYPE){
            list = cons(val, list);
        }
        charRead = fgetc(stdin);
    }
    return reverse(list);
}

/*
    Displays all tokens and their types
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
            printf("Invalid token type");
        }
        current = current->c.cdr;
    }
}
