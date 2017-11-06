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
#include <assert.h>

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
            printf("%s", v->s);
            break;
        case BOOL_TYPE:
            printf("%s", v->s);
            break;
        case SYMBOL_TYPE:
            printf("%s", v->s);
            break;
        case CLOSURE_TYPE:
            printf("[procedure]");
            break;
        case CONS_TYPE:
            printf("(");
            Value *cur = v;
            while(!isNull(cur)){
                printValue(car(cur));
                if(!isNull(cdr(cur))){
                    printf(" ");
                }
                cur = cdr(cur);
            }
            printf(")");
            break;
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
        if(result->type != VOID_TYPE){
            printf("\n");
        }
		tree = cdr(tree);
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
        child->hasParent = 1;
        Value *actual = args;
        Value *formal = function->clo.params;
        while(!isNull(formal)){
            if(isNull(actual)){
                printf("Incorrect number of params");
                texit(1);
            } else{
                Value *binding = cons(car(formal), cons(car(actual),
                                                        makeNull()));
                //printValue(binding);
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
    Evaluates a list of expressions and returns a list of those evaluated exprs
*/
Value *eval_combination(Value *expr, Frame *frame){
    Value *values = makeNull();
    while(!isNull(expr)){
        values = cons(eval(car(expr), frame), values);
        expr = cdr(expr);
    }
    values = reverse(values);
    return values;
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
                    return eval(car(cdr(val)), frame);
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
            if(!isNull(car(cdr(expr)))){
                return car(cdr(expr));
            } else{
                printf("Incorrect number of args in 'quote'\n");
                texit(1);
            }
		}
		if(strcmp(car(expr)->s, "if") == 0){
            if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
                Value *cond = eval(car(cdr(expr)), frame);
                if(cond->type == BOOL_TYPE){
                    if(strcmp(eval(car(cdr(expr)), frame)->s, "#t") != 0){
                        if(!isNull(cdr(cdr(cdr(expr))))){
                            return eval(car(cdr(cdr(cdr(expr)))), frame);
                        } else{
                            printf("No false case found in if statement\n");
                            texit(1);
                        }
        			}
                }
    			return eval(car(cdr(cdr(expr))), frame);
            } else{
                printf("Incorrect number of args in 'if'\n");
                texit(1);
            }
		}
        if(strcmp(car(expr)->s, "let") == 0){
            if(!isNull(cdr(cdr(expr)))){
                /*bind variables*/
                Frame *child = talloc(sizeof(Frame));
                child->parent = frame;
                child->hasParent = 1;
                child->bindings = makeNull();
                Value *formals = car(cdr(expr));
                while(!isNull(formals)){
                    Value *variable = car(formals);
                    if(isNull(variable)){
                        printf("Error: empty pair in let expression\n");
                        texit(1);
                    }
                    formals = cdr(formals);
                    Value *current = child->bindings;
                    while(!isNull(current)){
                        Value *val = car(current);
                        current = cdr(current);
                        if(strcmp(car(variable)->s,car(val)->s) == 0){
                            printf("let: duplicate identifier: %s\n",car(val)->s);
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
            } else{
                printf("Incorrect number of args in 'let'\n");
                texit(1);
            }
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
            closure->clo.body = cdr(cdr(expr));
            closure->clo.frame = frame;
            return closure;
        }
        Value *values = eval_combination(expr, frame);
        return apply(car(values), cdr(values));
	}
    printf("Error: invalid expression");
    texit(1);
    return makeNull();
}
