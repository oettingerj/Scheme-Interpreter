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


//Prints a Value
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
        case PRIMITIVE_TYPE:
            printf("[procedure]");
            break;
        case CONS_TYPE:
            printCons(v);
            break;
        case NULL_TYPE:
            printf("()");
            break;
        default:
            break;
    }
}

//Prints a cons list
void printCons(Value *v){
    printf("(");
    Value *cur = v;
    while(!isNull(cur)){
        if(cur->type != CONS_TYPE){
            printf(". ");
            printValue(cur);
            cur = makeNull();
        }
        else{
            printValue(car(cur));
            if(!isNull(cdr(cur))){
                printf(" ");
            }
            cur = cdr(cur);
        }
    }
    printf(")");
}

/*Bind a primitive function */
void bind(char *name, Value *(*function)(Value *), Frame *frame){
    Value *value = talloc(sizeof(Value));
    value->type = PRIMITIVE_TYPE;
    value->pf = function;
    Value *variable = talloc(sizeof(Value));
    variable->type = SYMBOL_TYPE;
    variable->s = name;
    Value *bound = cons(variable, cons(value, makeNull()));
    frame->bindings = cons(bound, frame->bindings);
}
/*primitive div function*/
Value *primitiveDiv(Value *args){
    if(length(args) != 2){
        printf("Division takes exactly two arguments\n");
        texit(1);
    }
    else if(args->type == CONS_TYPE){
        Value *val = car(args);
        Value *ret = car(cdr(args));
        if (ret->i == 0 || ret->d == 0.0000000){
            printf("zero not allowed as a denominator\n");
            texit(1);
        }

        else if(val->type == INT_TYPE){
            if(ret->type == INT_TYPE){
                if (val->i / ret->i == 0){
                    ret->type = DOUBLE_TYPE;
                    ret->d = (float)val->i / (float)ret->i;;
                }
                else if (val->i % ret->i != 0){
                    ret->type = DOUBLE_TYPE;
                    ret->d = (float)((val->i / ret->i) + (float)((float)(val->i % ret->i) / ret->i ));
                }
                else{
                ret->i = val->i / ret->i;
                }
            }
            else {
                ret->d = val->d / ret->i;
            }

        }
        else if(val->type == DOUBLE_TYPE){
            if(ret->type == INT_TYPE){
                ret->type = DOUBLE_TYPE;
                ret->d = val->d / ret->i;
            }
            else{
                ret->d = val->d / ret->d;
            }
        }
        else{
            printf("Invalid argument type\n");
            texit(1);
        }
        return ret;
    }
    else{
        printf("Invalid argument type\n");
        texit(1);
    }
    return makeNull();
}
/*primitive multpilication function*/
Value * primitiveMult(Value *args){
    if(args->type == NULL_TYPE){
        Value *ret = talloc(sizeof(Value));
        ret->type = INT_TYPE;
        ret->i = 1;
        return ret;
    }
    if(args->type == CONS_TYPE){
        Value *val = car(args);
        Value *ret = primitiveMult(cdr(args));
        if(val->type == INT_TYPE){
            if(ret->type == INT_TYPE){
                ret->i = ret->i * val->i;
            }
            else{
                ret->d = ret->d * val->i;
            }
        }
        else if(val->type == DOUBLE_TYPE){
            if(ret->type == INT_TYPE){
                ret->type = DOUBLE_TYPE;
                ret->d = ret->i * val->d;
            }
            else{
                ret->d = ret->d * val->d;
            }
        }
        else{
            printf("Invalid argument type\n");
            texit(1);
        }
        return ret;
    }
    else{
        printf("Invalid argument type\n");
        texit(1);
    }
    return makeNull();
}

Value * primitiveSub(Value *args){
    if(length(args) != 2){
        printf("Substraction takes exactly two arguments\n");
        texit(1);
    }
    if(args->type == NULL_TYPE){
        Value *ret = talloc(sizeof(Value));
        ret->type = INT_TYPE;
        ret->d = 0;
        return ret;
    }
    if(args->type == CONS_TYPE){
        Value *val = car(args);
        Value *ret = car(cdr(args));
        if(val->type == INT_TYPE){
            if(ret->type == INT_TYPE){
                ret->i = val->i - ret->i;
            }
            else{
                ret->d = val->i - ret->d;
            }
        }
        else if(val->type == DOUBLE_TYPE){
            if(ret->type == INT_TYPE){
                ret->type = DOUBLE_TYPE;
                ret->d = val->d - ret->i;
            }
            else{
                ret->d = val->d - ret->d;
            }
        }
        else{
            printf("Invalid argument type\n");
            texit(1);
        }
        return ret;
    }
    else{
        printf("Invalid argument type\n");
        texit(1);
    }
    return makeNull();
}

/*Add
 For right now, everything's a float*/
Value * primitiveAdd(Value *args){
    if(args->type == NULL_TYPE){
        Value *ret = talloc(sizeof(Value));
        ret->type = INT_TYPE;
        ret->d = 0;
        return ret;
    }
    if(args->type == CONS_TYPE){
        Value *val = car(args);
        Value *ret = primitiveAdd(cdr(args));
        if(val->type == INT_TYPE){
            if(ret->type == INT_TYPE){
                ret->i = ret->i + val->i;
            }
            else{
                ret->d = ret->d + val->i;
            }
        }
        else if(val->type == DOUBLE_TYPE){
            if(ret->type == INT_TYPE){
                ret->type = DOUBLE_TYPE;
                ret->d = ret->i + val->d;
            }
            else{
                ret->d = ret->d + val->d;
            }
        }
        else{
            printf("Invalid argument type\n");
            texit(1);
        }
        return ret;
    }
    else{
        printf("Invalid argument type\n");
        texit(1);
    }
    return makeNull();
}

/*null?*/
Value *primitiveIsNull(Value *args){
    Value *val = talloc(sizeof(Value));
    val->type = BOOL_TYPE;
    if(length(args) != 1){
        printf("null? takes exactly one argument\n");
        texit(1);
    }
    else{
        if(isNull(car(args))){
            val->s = "#t";
        }
        else{
            val->s = "#f";
        }
    }
    return val;
}

/*car*/
Value *primitiveCar(Value *args){
    if(length(args) != 1){
        printf("car takes exactly one argument\n");
        texit(1);
    }
    else{
        return car(car(args));
    }
    return makeNull();
}

/*cdr*/
Value *primitiveCdr(Value *args){
    if(length(args) != 1){
        printf("cdr takes exactly one argument\n");
        texit(1);
    }
    else{
        return cdr(car(args));
    }
    return makeNull();
}

/*cons*/
Value *primitiveCons(Value *args){
    if(length(args) != 2){
        printf("cons takes exactly two arguments\n");
        texit(1);
    }
    else{
        return cons(car(args), car(cdr(args)));
    }
    return cons(makeNull(), makeNull());
}


//Takes a list of s-expressions, calls eval on them, and prints results
void interpret(Value *tree){
    Frame *parent = talloc(sizeof(Frame));
    parent->bindings = makeNull();
    parent->hasParent = 0;
    bind("+", primitiveAdd, parent);
    bind("null?", primitiveIsNull, parent);
    bind("car", primitiveCar, parent);
    bind("cdr", primitiveCdr, parent);
    bind("cons", primitiveCons, parent);
    bind("*", primitiveMult, parent);
    bind("/", primitiveDiv, parent);
    bind("-", primitiveSub, parent);
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

//Applies a function to its args
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
                printf("Incorrect number of params in function");
                texit(1);
            } else{
                Value *binding = cons(car(formal), cons(car(actual),
                                                        makeNull()));
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
    } else if(function->type == PRIMITIVE_TYPE){
        return (function->pf)(args);
    } else{
        return makeNull();
    }
}

/*
 Evaluates a list of expressions and returns a list of
 those evaluated expressions
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

//Evaluates a symbol and returns its value
Value *eval_symbol(Value *expr, Frame *frame){
    //Loop through bindings, then parent, error if not in bindings
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
    printf("Error: symbol '%s' not defined\n", expr->s);
    texit(1);
    return makeNull();
}

//Evaluates a quote expression and returns its value
Value *eval_quote(Value *expr, Frame *frame){
    if(!isNull(cdr(expr))){
        return car(cdr(expr));
    }
    printf("Incorrect number of args in 'quote'\n");
    texit(1);
    return makeNull();
}

//Evaluates an if statement and returns its value
Value *eval_if(Value *expr, Frame *frame){
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
    }
    printf("Incorrect number of args in 'if'\n");
    texit(1);
    return makeNull();
}

//Evaluates a let expression and returns its value
Value *eval_let(Value *expr, Frame *frame){
    if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
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
                    printf("Duplicate identifier in 'let': %s\n",car(val)->s);
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
    printf("Incorrect number of args in 'let'\n");
    texit(1);
    return makeNull();
}

//Evaluates a define expression and returns a VOID_TYPE
Value *eval_define(Value *expr, Frame *frame){
    if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
        Value *variable = cdr(expr);
        frame->bindings = cons(variable, frame->bindings);
        Value *v = talloc(sizeof(Value));
        v->type = VOID_TYPE;
        return v;
    }
    printf("Incorrect number of args in 'define'\n");
    texit(1);
    return makeNull();
}

//Evaluates a lambda expression and returns a closure
Value *eval_lambda(Value *expr, Frame *frame){
    if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
        Value *closure = talloc(sizeof(Value));
        closure->type = CLOSURE_TYPE;
        closure->clo.params = car(cdr(expr));
        closure->clo.body = cdr(cdr(expr));
        closure->clo.frame = frame;
        return closure;
    }
    printf("Incorrect number of args in 'lambda'\n");
    texit(1);
    return makeNull();
}

//Evaluates a set! expression
//TODO: Make it search in parent frame if binding not changed
Value *eval_set(Value *expr, Frame *frame){
    if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
        Value *newBinding = cdr(expr);
        Value *newBindings = makeNull();
        Value *cur = frame->bindings;
        int bindingFound = 0;
        while(!isNull(cur)){
            if(strcmp(car(car(cur))->s, car(newBinding)->s) == 0){
                newBindings = cons(newBinding, newBindings);
                bindingFound = 1;
            } else{
                newBindings = cons(cur, newBindings);
            }
            cur = cdr(cur);
        }
        frame->bindings = newBindings;
        Value *v = talloc(sizeof(Value));
        v->type = VOID_TYPE;
        return v;
    }
    printf("Incorrect number of args in 'set!'\n");
    texit(1);
    return makeNull();
}

//Evaluates an and expression
Value *eval_and(Value * expr, Frame *frame){
    Value *boolean = talloc(sizeof(Value));
    boolean->type = BOOL_TYPE;
    if(!isNull(cdr(expr))){
        Value *cur = cdr(expr);
        while(!isNull(cur)){
            Value *val = eval(car(cur), frame);
            if(val->type == BOOL_TYPE && strcmp(val->s, "#f") == 0){
                boolean->s = "#f";
                return boolean;
            }
            if(isNull(cdr(cur))){
                return eval(car(cur), frame);
            }
            cur = cdr(cur);
        }
    } else{
        printf("Incorrect number of args in 'and'");
        texit(1);
    }
    boolean->s = "#t";
    return boolean;
}

//Evaluates an or expression
Value *eval_or(Value * expr, Frame *frame){
    Value *boolean = talloc(sizeof(Value));
    boolean->type = BOOL_TYPE;
    if(!isNull(cdr(expr))){
        Value *cur = cdr(expr);
        while(!isNull(cur)){
            Value *val = eval(car(cur), frame);
            if(!(val->type == BOOL_TYPE && strcmp(val->s, "#f") == 0)){
                return val;
            }
            cur = cdr(cur);
        }
    } else{
        printf("Incorrect number of args in 'and'");
        texit(1);
    }
    boolean->s = "#f";
    return boolean;
}

//Evaluates an expression
Value *eval(Value *expr, Frame *frame){
    if(expr->type == INT_TYPE || expr->type == DOUBLE_TYPE ||
       expr->type == STR_TYPE || expr->type == BOOL_TYPE ||
       expr->type == PRIMITIVE_TYPE || expr->type == NULL_TYPE){
        return expr;
    }
    if(expr->type == SYMBOL_TYPE){
        return eval_symbol(expr, frame);
    }
    if(expr->type == CONS_TYPE){
        if(car(expr)->type == SYMBOL_TYPE){
            if(strcmp(car(expr)->s, "quote") == 0){
                return eval_quote(expr, frame);
            }
            if(strcmp(car(expr)->s, "if") == 0){
                return eval_if(expr, frame);
            }
            if(strcmp(car(expr)->s, "let") == 0){
                return eval_let(expr, frame);
            }
            if(strcmp(car(expr)->s, "define") == 0){
                return eval_define(expr, frame);
            }
            if(strcmp(car(expr)->s, "lambda") == 0){
                return eval_lambda(expr, frame);
            }
            if(strcmp(car(expr)->s, "set!") == 0){
                return eval_set(expr, frame);
            }
            if(strcmp(car(expr)->s, "and") == 0){
                return eval_and(expr, frame);
            }
            if(strcmp(car(expr)->s, "or") == 0){
                return eval_or(expr, frame);
            }
            Value *values = eval_combination(expr, frame);
            return apply(car(values), cdr(values));
        } else{
            return car(expr);
        }
    }
    printf("Error: invalid expression\n");
    texit(1);
    return makeNull();
}
