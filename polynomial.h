#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#ifndef POLY_H
#define POLY_H

struct term{
    int coeff;
    int exp;
    struct term* next;
};

typedef struct term polynomial; 

struct term *make_term( int coeff, int exp);
void poly_free( polynomial * eqn);
void poly_print(polynomial *eqn);
char *poly_to_string(polynomial *p);
void append_poly(polynomial *a, polynomial *b);
polynomial *add_poly(polynomial *a, polynomial *b);
polynomial *addOrSub_poly(polynomial *a, polynomial *b, bool add);
polynomial *sub_poly(polynomial *a, polynomial *b);
bool is_equal(polynomial *a, polynomial *b);
void apply_to_each_term(polynomial *p, void (*transform)(struct term *));
double eval_poly(polynomial *p, double x);
polynomial *multiply_poly(polynomial *a, polynomial *b);


#endif /* POLY_H */
