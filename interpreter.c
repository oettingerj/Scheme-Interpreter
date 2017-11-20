/*
 interpreter.c
 Nathaniel Lovin, Josh Oettinger, Tenzin Dolphen
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"
#include "tokenizer.h"
#include "parser.h"


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

Value *lowerCaseWord(Value *a){
    for (int i = 0; i < strlen(a->s); i++){
        a->s[i] = tolower(a->s[i]);
    }
    return a;
}
/*quote problems with comb of num and . eg (pair? (quote 3 . 3))*/
Value *primitivePair(Value *args){
    Value *ret = talloc(sizeof(Value));
    ret->type = BOOL_TYPE;
    if((car(args))->type == CONS_TYPE){
        ret->s = "#t";
    }
    else {
        ret->s = "#f";
    }
    return ret;
}
/*primitive eq? function*/
Value *primitiveEq(Value *args){
    if(length(args) != 2){
        printf("eq? takes exactly two arguments\n");
        texit(1);
    }
    if(args->type == CONS_TYPE){
        Value *val = car(args);
        Value *ret = car(cdr(args));
        while (val->type == CONS_TYPE && ret->type == CONS_TYPE){
            val = car(val);
            ret = car(ret);
        }
        if(val->type == INT_TYPE){
            if(ret->type == INT_TYPE){
                ret->type = BOOL_TYPE;
                if (val->i == ret->i){
                    ret->s = "#t";
                }
                else{
                    ret->s = "#f";
                }
            }
            else {
                ret->type = BOOL_TYPE;
                ret->s = "#t";
                }
        }
        else if(val->type == DOUBLE_TYPE){
            if(ret->type == DOUBLE_TYPE){
                ret->type = BOOL_TYPE;
                    ret->s = "#t";
            }
            else{
                ret->type = BOOL_TYPE;
                ret->s = "#f";
            }
        }
        else if(val->type == SYMBOL_TYPE){
            if(ret->type == SYMBOL_TYPE){
                ret->type = BOOL_TYPE;
                if (strlen(val->s) != strlen(ret->s)){
                    ret->s = "#f";
                }
                else if (strcmp(lowerCaseWord(val)->s,lowerCaseWord(ret)->s) == 0){
                    ret->s = "#t";
                }
                else{
                    ret->s = "#f";
                }
            }
            else{
                ret->type = BOOL_TYPE;
                ret->s = "#f";
            }
        }
        else if(val->type == BOOL_TYPE){
            if(ret->type == BOOL_TYPE){
                ret->type = BOOL_TYPE;
                if (val->s == ret->s){
                    ret->s = "#t";
                }
                else{
                    ret->s = "#f";
                }
            }
            else{
                ret->type = BOOL_TYPE;
                ret->s = "#f";
            }
        }
        else if(val->type == NULL_TYPE){
            if(ret->type == NULL_TYPE){
                ret->type = BOOL_TYPE;
                    ret->s = "#t";
            }
            else{
                ret->type = BOOL_TYPE;
                ret->s = "#f";
            }
        }
        else if(val->type == PRIMITIVE_TYPE){
            if(ret->type == PRIMITIVE_TYPE){
                ret->type = BOOL_TYPE;
                if (ret->s == val->s){
                    ret->s = "#t";
            }
                else{
                    ret->s = "#f";
            }
        }
        else{
            ret->type = BOOL_TYPE;
            ret->s = "#f";
            }
        }
        else if(val->type == CLOSURE_TYPE){
            if(ret->type == CLOSURE_TYPE){
                ret->type = BOOL_TYPE;
                if (ret->s == val->s){
                    ret->s = "#t";
                }
                else{
                    ret->s = "#f";
                }
            }
            else{
                ret->type = BOOL_TYPE;
                ret->s = "#f";
            }
        }
        return ret;
    }
    else{
        printf("Invalid argument type\n");
        texit(1);
    }
    return makeNull();
}
<<<<<<< HEAD

Value *primitiveLeq(Value *args){
=======
/*primitive less than equal function*/
Value * primitiveLeq(Value *args){
>>>>>>> primitives
    if(length(args) != 2){
        printf("<= takes exactly two arguments\n");
        texit(1);
    }
    if(args->type == CONS_TYPE){
        Value *val = car(args);
        Value *ret = car(cdr(args));
        if(val->type == INT_TYPE){
            if(ret->type == INT_TYPE){
                ret->type = BOOL_TYPE;
                if (val->i <= ret->i){
                    ret->s = "#t";
                }
                else{
                    ret->s = "#f";
                }
            }
            else if (ret->type == DOUBLE_TYPE){
                ret->type = BOOL_TYPE;
                if (val->i <= ret->d){
                    ret->s = "#t";
                }
                else{
                    ret->s = "#f";
                }
            }
            else{
                printf("Invalid argument type\n");
                texit(1);
            }
        }
        else if(val->type == DOUBLE_TYPE){
            if(ret->type == INT_TYPE){
                ret->type = BOOL_TYPE;
                if (val->d <= ret->i){
                    ret->s = "#t";
                }
                else{
                    ret->s = "#f";
                }
            }
            else if (ret->type == DOUBLE_TYPE){
                ret->type = BOOL_TYPE;
                if (val->d <= ret->d){
                    ret->s = "#t";
                }
                else{
                    ret->s = "#f";
                }
            }
            else{
                printf("Invalid argument type\n");
                texit(1);
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
/*primitive div function*/
Value *primitiveDiv(Value *args){
    if(length(args) != 2){
        printf("Division takes exactly two arguments\n");
        texit(1);
    }
    else if(args->type == CONS_TYPE){
        Value *val = car(args);
        Value *ret = car(cdr(args));
        if(val->type == INT_TYPE){
            if(ret->type == INT_TYPE){
                if (ret->i == 0 ){
                    printf("zero not allowed as a denominator\n");
                    texit(1);
                }
                else if (val->i / ret->i == 0){
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
                if (ret->d == 0.0000000){
                    printf("zero not allowed as a denominator\n");
                    texit(1);
                }
                ret->d = val->i / ret->d;
            }

        }
        else if(val->type == DOUBLE_TYPE){
            if(ret->type == INT_TYPE){
                if (ret->i == 0 ){
                    printf("zero not allowed as a denominator\n");
                    texit(1);
                }
                ret->type = DOUBLE_TYPE;
                ret->d = val->d / ret->i;
            }
            else{
                if (ret->d == 0.0000000){
                    printf("zero not allowed as a denominator\n");
                    texit(1);
                }
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
Value *primitiveMult(Value *args){
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
<<<<<<< HEAD

Value *primitiveSub(Value *args){
=======
/*primitive substraction function*/
Value * primitiveSub(Value *args){
    if(length(args) != 2){
        printf("Substraction takes exactly two arguments\n");
        texit(1);
    }
>>>>>>> primitives
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
        if(isNull(cdr(cdr(args)))){
            return ret;
        }
        else{
            return primitiveSub(cons(ret, cdr(cdr(args))));
        }
    }
    else{
        printf("Invalid argument type\n");
        texit(1);
    }
    return makeNull();
}

/*Add
 For right now, everything's a float*/
Value *primitiveAdd(Value *args){
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
    if(car(args)->type != CONS_TYPE){
        printf("Error: car takes a list of elements\n");
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
    if(car(args)->type != CONS_TYPE){
        printf("Error: cdr takes a list of elements\n");
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

/*truncate*/
Value *primitiveTrunc(Value *args){
    if(length(args) != 1){
        printf("truncate takes exactly one arguement\n");
        texit(1);
    }
    else{
        if(car(args)->type != INT_TYPE && car(args)->type != DOUBLE_TYPE){
            printf("Error: truncate takes a number\n");
        }
        if(car(args)->type == INT_TYPE){
            return car(args);
        }
        else{
            car(args)->d = ((int) car(args)->d);
            return car(args);
        }
    }
    return makeNull();
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
    bind("<=", primitiveLeq, parent);
    bind("eq?", primitiveEq, parent);
    bind("pair?", primitivePair, parent);
    bind("truncate", primitiveTrunc, parent);
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
        if(formal->type == CONS_TYPE){
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
        } else{
            Value *binding = cons(formal, cons(actual, makeNull()));
            child->bindings = cons(binding, child->bindings);
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
        Value *binding = car(current);
        current = cdr(current);
        if(strcmp(car(binding)->s, expr->s) == 0){
            return car(cdr(binding));
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
            if(isNull(car(formals))){
                printf("Error: empty pair in let expression\n");
                texit(1);
            }
            Value *variable = car(car(formals));
            Value *value = eval(car(cdr(car(formals))), frame);
            Value *binding = cons(variable, cons(value, makeNull()));

            formals = cdr(formals);
            Value *current = child->bindings;
            while(!isNull(current)){
                Value *val = car(current);
                current = cdr(current);
                if(strcmp(car(binding)->s,car(val)->s) == 0){
                    printf("Duplicate identifier in 'let': %s\n",car(val)->s);
                    texit(1);
                }
            }
            child->bindings = cons(binding, child->bindings);
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

//Evaluates a letrec expression and returns its value
Value *eval_letrec(Value *expr, Frame *frame){
    if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
        /*bind variables*/
        Frame *child = talloc(sizeof(Frame));
        child->parent = frame;
        child->hasParent = 1;
        child->bindings = makeNull();
        Value *formals = car(cdr(expr));
        while(!isNull(formals)){
            if(isNull(car(formals))){
                printf("Error: empty pair in let expression\n");
                texit(1);
            }
            Value *variable = car(car(formals));
            Value *value = car(cdr(car(formals)));
            Value *binding = cons(variable, cons(value, makeNull()));

            formals = cdr(formals);
            Value *current = child->bindings;
            while(!isNull(current)){
                Value *val = car(current);
                current = cdr(current);
                if(strcmp(car(binding)->s,car(val)->s) == 0){
                    printf("Duplicate identifier in 'let': %s\n",car(val)->s);
                    texit(1);
                }
            }
            child->bindings = cons(binding, child->bindings);
        }
        //Evaluate expressions after binding
        Value *cur = child->bindings;
        Value *evalBindings = makeNull();
        while(!isNull(cur)){
            Value *var = car(car(cur));
            Value *val = car(cdr(car(cur)));
            val = eval(val, child);
            Value *binding = cons(var, cons(val, makeNull()));
            evalBindings = cons(binding, evalBindings);
            cur = cdr(cur);
        }
        child->bindings = evalBindings;

        //Evaluate multiple body expressions in let
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

//Evaluates a let* expression and returns its value
Value *eval_let_star(Value *expr, Frame *frame){
    if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
        /*bind variables*/
        Frame *child = talloc(sizeof(Frame));
        child->parent = frame;
        child->hasParent = 1;
        child->bindings = makeNull();
        Value *formals = car(cdr(expr));
        while(!isNull(formals)){
            if(isNull(car(formals))){
                printf("Error: empty pair in let expression\n");
                texit(1);
            }
            Value *variable = car(car(formals));
            Value *value = eval(car(cdr(car(formals))), child);
            Value *binding = cons(variable, cons(value, makeNull()));

            formals = cdr(formals);
            Value *current = child->bindings;
            while(!isNull(current)){
                Value *val = car(current);
                current = cdr(current);
                if(strcmp(car(binding)->s,car(val)->s) == 0){
                    printf("Duplicate identifier in 'let': %s\n",car(val)->s);
                    texit(1);
                }
            }
            child->bindings = cons(binding, child->bindings);
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
//TODO: Check for already defined variables
Value *eval_define(Value *expr, Frame *frame){
    if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
        Value *variable = car(cdr(expr));
        Value *value = eval(car(cdr(cdr(expr))), frame);
        Value *binding = cons(variable, cons(value, makeNull()));
        frame->bindings = cons(binding, frame->bindings);
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
Value *eval_set(Value *expr, Frame *frame){
    if(!isNull(cdr(expr)) && !isNull(cdr(cdr(expr)))){
        Value *variable = car(cdr(expr));
        Value *value = eval(car(cdr(cdr(expr))), frame);
        Value *newBinding = cons(variable, cons(value, makeNull()));
        Value *newBindings = makeNull();
        Value *cur = frame->bindings;
        Frame *curFrame = frame;
        int bindingFound = 0;
        while(!isNull(cur)){
            if(strcmp(car(car(cur))->s, car(newBinding)->s) == 0){
                newBindings = cons(newBinding, newBindings);
                bindingFound = 1;
            } else{
                newBindings = cons(car(cur), newBindings);
            }
            cur = cdr(cur);
            if(isNull(cur) && bindingFound == 0){
                if(frame->hasParent){
                    curFrame = frame->parent;
                    cur = curFrame->bindings;
                } else{
                    printf("No binding for '%s'\n", car(newBinding)->s);
                    texit(1);
                }
            }
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
        printf("Incorrect number of args in 'and'\n");
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
        printf("Incorrect number of args in 'and'\n");
        texit(1);
    }
    boolean->s = "#f";
    return boolean;
}

//Evaluates cond expressions
Value *eval_cond(Value *expr, Frame *frame){
    if(!isNull(cdr(expr))){
        Value *cur = cdr(expr);
        while(!isNull(cur)){
            Value *testExpr = car(cur);
            if(testExpr->type == CONS_TYPE && !isNull(cdr(testExpr))){
                Value *test = eval(car(testExpr), frame);
                if(test->type == SYMBOL_TYPE && strcmp(test->s, "else") == 0){
                    if(isNull(cdr(cur))){
                        return eval(car(cdr(testExpr)), frame);
                    } else{
                        printf("Error: else must be in last test-expr pair in cond expression\n");
                        texit(1);
                    }
                }
                if(!(test->type == BOOL_TYPE && strcmp(test->s, "#f") == 0)){
                    return eval(car(cdr(testExpr)), frame);
                }
            } else{
                printf("Invalid test-expr pair\n");
                texit(1);
            }
            cur = cdr(cur);
        }
    } else{
        printf("Incorrect number of args in 'cond'\n");
        texit(1);
    }
    Value *voidReturn = talloc(sizeof(Value));
    voidReturn->type = VOID_TYPE;
    return voidReturn;
}

//Evaluates a begin expression
Value *eval_begin(Value *expr, Frame *frame){
    if(!isNull(cdr(expr))){
        Value *cur = cdr(expr);
        while(!isNull(cur)){
            if(isNull(cdr(cur))){
                return eval(car(cur), frame);
            } else{
                eval(car(cur), frame);
            }
            cur = cdr(cur);
        }
    } else{
        printf("Incorrect number of args in 'begin'\n");
        texit(1);
    }
    return makeNull();
}

Value *eval_load(Value *expr){
    if(length(expr) == 2 && !isNull(car(cdr(expr)))){
        Value *filename = car(cdr(expr));
        if(filename->type == STR_TYPE){
            char *file = filename->s;
            memmove(file, file+1, strlen(file));
            file[strlen(file) - 1] = '\0';
            freopen(file, "r", stdin);
            Value *tokens = tokenize();
            Value *tree = parse(tokens);
            interpret(tree);
        } else{
            printf("Error: argument to 'load' must be a string\n");
            texit(1);
        }
    } else{
        printf("Error: incorrect number of args in 'load'\n");
        texit(1);
    }
    Value *val = talloc(sizeof(Value));
    val->type = VOID_TYPE;
    return val;
}

//Evaluates an expression
//TODO: Figure out how to make lists evaluate to lists but have (+) not print as (0)
Value *eval(Value *expr, Frame *frame){
    if(expr->type == INT_TYPE || expr->type == DOUBLE_TYPE ||
       expr->type == STR_TYPE || expr->type == BOOL_TYPE ||
       expr->type == PRIMITIVE_TYPE || expr->type == NULL_TYPE){
        return expr;
    }
    if(expr->type == SYMBOL_TYPE){
        if(strcmp(expr->s, "else") == 0){
            return expr;
        }
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
            if(strcmp(car(expr)->s, "letrec") == 0){
                return eval_letrec(expr, frame);
            }
            if(strcmp(car(expr)->s, "let*") == 0){
                return eval_let_star(expr, frame);
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
            if(strcmp(car(expr)->s, "cond") == 0){
                return eval_cond(expr, frame);
            }
            if(strcmp(car(expr)->s, "begin") == 0){
                return eval_begin(expr, frame);
            }
            if(strcmp(car(expr)->s, "load") == 0){
                return eval_load(expr);
            }
            Value *values = eval_combination(expr, frame);
            return apply(car(values), cdr(values));
        } else if(car(expr)->type != CONS_TYPE){
            printf("Error: ");
            printValue(car(expr));
            printf(" is not a procedure\n");
            texit(1);
        } else{
            Value *values = eval_combination(expr, frame);
            return apply(car(values), cdr(values));
        }
    }
    printf("Error: invalid expression\n");
    texit(1);
    return makeNull();
}
