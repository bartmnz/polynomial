#include "polynomial.h"
#include "tester.h"

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
 * Creates (or over-wrights) and deletes a tempory file poly_to_string_tmp.txt 
 */
char *poly_to_string(polynomial *p){
    if(!p){
        return NULL;
    }
    FILE *file;
    const char filename[] = "poly_to_string_tmp.txt";
    file = fopen(filename, "w");
    while(p && file){
        if (p->coeff){
        fprintf(file, "%s%d", p->coeff > 0 ? "+" : "", p->coeff);
        }
        if(p->exp > 1 ){
            fprintf(file, "x^%d", p->exp);
        } else if(p->exp == 1){
            fprintf(file, "x");
        }
        fprintf(file," ");
        p = p->next;
    }
    fclose(file);
    file = fopen(filename, "r"); // re-open the file to read it.
    if (!file){
        fprintf(stderr, "ERROR: unable to open temporary file. %s\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END); 
    char *string = malloc(ftell(file)); // allocate enough memory to store the string
    if( ! string){
        fprintf(stderr, "ERROR: unable to allocate memory");
        return NULL;
    }
    fseek(file, 0, SEEK_SET);
    char tmp;
    int count = 0;
    while( (tmp = fgetc(file)) != EOF){
            string[count] = tmp;
            count++;
    }
    string[count] = '\0';
    // clean up after ourselves
    int check; 
    check = remove(filename);
    if ( check != 0){
        fprintf(stderr, "ERROR: unable to delete temporary file. %s\n", filename);
        return NULL;
    }
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
    test();
    return 1;
}