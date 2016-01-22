#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#ifndef POLY_H
#define POLY_H

struct term{
    int coeff;
    int exp;
    struct term* next;
};

typedef struct term polynomial; 

#endif /* POLY_H */
