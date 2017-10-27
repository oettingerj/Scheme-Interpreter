/*
	parser.c
	Nathaniel Lovin, Josh Oettinger, Tenzin Dolphen
*/

#include <stdio.h>
#include "value.h"
#include "talloc.h"
#include "linkedlist.h"
#include "tokenizer.h"
#include <stdbool.h>

/*
Parses a list of Scheme tokens
Returns a parse tree
*/
Value *parse(Value *tokens) {
	Value *parse = makeNull();
	int count = 0;
	while(!isNull(tokens)){
		Value *val = car(tokens);
		tokens = cdr(tokens);
		if(val->type == CLOSE_TYPE){
			count-=1;
			Value *expr = makeNull();
			Value *cur = car(parse);
			parse = cdr(parse);
			while(!(isNull(parse)) && cur->type != OPEN_TYPE){
				expr = cons(cur, expr);
				cur = car(parse);
				parse = cdr(parse);
			}
			if (count < 0){
				printf("Syntax error: too many close parentheses\n");
				texit(1);
			}
			parse = cons(expr, parse);
		}
		else{
			parse = cons(val, parse);
		}
		if(val->type == OPEN_TYPE){
			count+=1;
		}
	}
	if(count != 0){
		printf("Syntax error: not enough close parentheses\n");
		texit(1);
	}
	parse = reverse(parse);
	return parse;
}

/*
Prints out parse tree
*/
void printTree(Value *tree){
	bool first = true;
	while(!isNull(tree)){
		if(!first){
			printf(" ");
		} else {
			first = false;
		}
		Value *cur = car(tree);
		tree = cdr(tree);
		switch(cur->type){
			case BOOL_TYPE:
				printf("%s", cur->s);
				break;
			case INT_TYPE:
        		printf("%i", cur->i);
        		break;
      		case DOUBLE_TYPE:
       			printf("%f", cur->d);
        		break;
      		case STR_TYPE:
      			printf("%s", cur->s);
				break;
			case SYMBOL_TYPE:
				printf("%s", cur->s);
				break;
			case CONS_TYPE:
				printf("(");
				printTree(cur);
				printf(")");
				break;
			case NULL_TYPE:
				printf("()");
				break;
			default:
				break;
		}
	}
}
