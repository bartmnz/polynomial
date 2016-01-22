#include "polynomial.h"

/*mallocs a new term of a polynomial with coeff and exp as the parameters
 *returns malloc'd struct term
 * code provided as part of assignment
 */
struct term *make_term( int coeff, int exp){
    struct term *node = malloc(sizeof(*node));
    if(node){
        node->coeff = coeff;
        node->exp = exp;
        node->next = NULL;
    }
    return node;
}

/*free all terms of a polynomial. Does not error check for circular linked lists
 *code provided as part of assignment
 */
void poly_free( polynomial * eqn){
    while(eqn){
        struct term *tmp = eqn->next;
        free(eqn);
        eqn=tmp;
    }
}

/*prints the terms of a given polynomial -- does not check for circular linked lists.
 *code provided as part of assignment
 */
void poly_print(polynomial *eqn){
    if (!eqn){
        return;
    }
    if (eqn->coeff){
        printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
        if(eqn->exp > 1 ){
            printf("x^%d", eqn->exp);
        } else if(eqn->exp == 1){
            printf("x");
        }
        printf(" ");
    }
    poly_print(eqn->next);
}

/*Code needs to be implemented
 * Returns a newly-malloced string that displays the given polynomial
 */
char *poly_to_string(polynomial *p){
    if(!p){
        // invalid polynomial
    }
    char *string = "need to implement";
    return string;
}

/*Code needs to be implemented
 *Returns a newly-malloced polynomial that is the sum of the two arguments
 */
polynomial *add_poly(polynomial *a, polynomial *b){
    if (!a || !b){
        // invalid polynomial
    }
    return a;
}

/*Code needs to be implemented
 *Returns a newly-malloced polynomial that is the sum of the two arguments
 */
polynomial *sub_poly(polynomial *a, polynomial *b){
        if (!a || !b){
        // invalid polynomial
    }
    return a;
}

/*Code needs to be implemented
 *returns true if the two arguments have the same terms; false otherwise
 */
bool is_eual(polynomial *a, polynomial *b){
     if (!a || !b){
        // invalid polynomial
    }
    return true;
}

/*Code needs to be implemented
 *Calls the function transform on each term of the polynomial
 */
void apply_to_each_term(polynomial *p, void (*transform)(struct term *)){
    if( !p || !transform){
        // invalid polynomial
    }
    
}

/*Code needs to be implemented
 *Evaluates the polynomial by substituting x in the variable of the polynomial
 */
double eval_poly(polynomial *p, double x){
    if(!p || !x){
        // invalid polynomial
    }
    return 0;
}

//here for compile
int main (void){
    return 1;
}