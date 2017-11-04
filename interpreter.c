/*
    interpreter.c
    Nathaniel Lovin, Josh Oettinger, Tenzin Dolphen
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "interpreter.h"

/*
    Prints a Value
*/
void printValue(Value *v){
    switch (v->type) {
        case INT_TYPE:
            printf("%i", v->i);
            break;
        case DOUBLE_TYPE:
            printf("%f", v->d);
            break;
        case STR_TYPE:
        case BOOL_TYPE:
        case SYMBOL_TYPE:
            printf("%s", v->s);
            break;
        case CONS_TYPE:
            printf("(");
            while(!isNull(v)){
                Value *cur = car(v);
                printValue(cur);
                if(!isNull(cdr(v))){
                    printf(" ");
                }
                v = cdr(v);
            }
            printf(")");
        default:
            break;
    }
}

/*
    Takes a list of s-expressions, calls eval on them, and prints results
*/
void interpret(Value *tree){
	Frame *parent = talloc(sizeof(Frame));
	parent->bindings = makeNull();
    parent->hasParent = 0;
	while(!isNull(tree)){
		Value *cur = car(tree);
        Value *result = eval(cur, parent);
		printValue(result);
		tree = cdr(tree);
        printf("\n");
	}
}
/*
    Applies a function to its args
*/
Value *apply(Value *function, Value *args){
    if(function->type == CLOSURE_TYPE){
        Frame *child = talloc(sizeof(Frame));
        child->bindings = makeNull();
        child->parent = function->clo.frame;
        Value *actual = args;
        Value *formal = function->clo.params;
        while(!isNull(formal)){
            if(isNull(actual)){
                printf("Incorrect number of params");
                texit(1);
            } else{
                Value *binding = cons(formal, actual);
                child->bindings = cons(binding, child->bindings);
                actual = cdr(actual);
                formal = cdr(formal);
            }
        }

        Value *body = function->clo.body;
        Value *result = eval(car(body), child);
        body = cdr(body);
        while(!isNull(body)){
            result = eval(car(body), child);
            body = cdr(body);
        }
        return result;
    } else{
        return makeNull();
    }
}

/*
    Evaluates expressions
*/
Value *eval(Value *expr, Frame *frame){
	if(expr->type == INT_TYPE || expr->type == DOUBLE_TYPE
	   || expr->type == STR_TYPE || expr->type == BOOL_TYPE){
		return expr;
	}
    if(expr->type == SYMBOL_TYPE){
        if(isNull(frame->bindings)){
            printf("Evaluation error: \"%s\" is not a valid symbol\n", expr->s);
            texit(1);
        }
        else{
            /*loop through bindings, then parent, error if not in bindings*/
            Value *current = frame->bindings;
            while(!isNull(current)){
                Value *val = car(current);
                current = cdr(current);
                if(strcmp(car(val)->s,expr->s) == 0){
                    return eval(car(cdr(val)),frame);
                }
                if(isNull(current) && frame->hasParent){
                    frame = frame->parent;
                    current = frame->bindings;
                }
            }
        }

    }
	if(expr->type == CONS_TYPE){
		if(strcmp(car(expr)->s, "quote") == 0){
			return car(cdr(expr));
		}
		if(strcmp(car(expr)->s, "if") == 0){
			if(strcmp(eval(car(cdr(expr)), frame)->s, "#f") == 0){
				return eval(car(cdr(cdr(cdr(expr)))), frame);
			}
			else{
				return eval(car(cdr(cdr(expr))), frame);
			}
		}
        if(strcmp(car(expr)->s, "let") == 0){
            /*bind variables*/
            Frame *child = talloc(sizeof(Frame));
            child->parent = frame;
            child->bindings = makeNull();
            Value *formals = car(cdr(expr));
            while(!isNull(formals)){
                Value *variable = car(formals);
                formals = cdr(formals);
                Value *current = child->bindings;
                while(!isNull(current)){
                    Value *val = car(current);
                    current = cdr(current);
                    if(strcmp(car(variable)->s,car(val)->s) == 0){
                        printf("let: duplicate identifier in: %s\n",car(val)->s);
                        texit(1);
                    }
                }
                child->bindings = cons(variable, child->bindings);
            }
            /*evaluate multiple body expressions in let*/
            Value *body = cdr(cdr(expr));
            Value *result = eval(car(body), child);
            body = cdr(body);
            while(!isNull(body)){
                result = eval(car(body), child);
                body = cdr(body);
            }
            return result;
        }
        if(strcmp(car(expr)->s, "define") == 0){
            Value *variable = cdr(expr);
            frame->bindings = cons(variable, frame->bindings);
            Value *v = talloc(sizeof(Value));
            v->type = VOID_TYPE;
            return v;
        }
        if(strcmp(car(expr)->s, "lambda") == 0){
            Value *closure = talloc(sizeof(Value));
            closure->type = CLOSURE_TYPE;
            closure->clo.params = car(cdr(expr));
            closure->clo.body = car(cdr(cdr(expr)));
            closure->clo.frame = frame;
            return closure;
        }
        Value *values = makeNull();
        Value *current = expr;
        while(!isNull(current)){
            values = cons(eval(car(current), frame), values);
            current = cdr(current);
        }
        values = reverse(values);
        return apply(car(values), cdr(values));
	}
	return makeNull();
}
