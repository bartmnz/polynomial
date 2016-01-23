#include "polynomial.h"
#include "tester.h"

/*mallocs a new term of a polynomial with coeff and exp as the parameters
 *returns malloc'd struct term
 * code provided as part of assignment
 */
struct term *make_term( int coeff, int exp){
    struct term *node = malloc(sizeof(struct term));
    memset(node, 0, sizeof(struct term));
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
void poly_free( polynomial *eqn){
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

/*
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
    int size = ftell(file); 
    char *string = malloc(size+1); // allocate enough memory to store the string
    memset(string, 0, size+1);
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
    fclose(file);
 //   fprintf(stdout, "in set = %lu\n", (unsigned long) string );
    return string;
}

/*
 *helper function for add and subtract poly. places the first term of poly b 
 *at the end of poly a by mallocing new space. 
 */
void append_poly(polynomial *a, polynomial *b){
    if (!a || !b){
        return;
    }
    if(!a->coeff && !a->exp ){ // unitialized list
        a->coeff = b->coeff;
        a->exp = b->exp;
        return;
    }
    polynomial *temp = malloc(sizeof(polynomial));
    memset(temp, 0, sizeof(polynomial));
    temp->coeff = b->coeff;
    temp->exp = b->exp;
    temp->next = NULL;
    while( a->next ){
        a = a->next;
    }
    a->next = temp;
}

/*
 *Returns a newly-malloced polynomial that is the sum of the two arguments
 */
polynomial *add_poly(polynomial *a, polynomial *b){
    return addOrSub_poly(a,b,true);
}
/*
 *helper function for add and subract .. the code is the same for both with one dfference
 * boolean set to true for add and false for subtract
 */
polynomial *addOrSub_poly(polynomial *a, polynomial *b, bool add){
    if (!a || !b){
        return NULL;
    }
    polynomial *ret = malloc(sizeof(polynomial));
    memset(ret, 0, sizeof(polynomial));
    while ( a || b ){
        if (!a){
            append_poly(ret, b);
            b = b->next;
        }
        else if (!b){
            append_poly(ret, a);
            a = a->next;
        }
        else if (a->exp == b->exp){
            if( add){
                a->coeff += b->coeff;
            } else{
                a->coeff -= b->coeff;
            }
            append_poly(ret, a);
            a = a->next;
            b = b->next;
        }
        else if (a->exp > b->exp){
            append_poly(ret, a);
            a = a->next;
        }
        else{ // b > a
            append_poly(ret, b);
            b = b->next;
        }
    }
    return ret;    
}


/*
 *Returns a newly-malloced polynomial that is the sum of the two arguments
 */
polynomial *sub_poly(polynomial *a, polynomial *b){
    return addOrSub_poly(a,b,false);
}

/*
 *returns true if the two arguments have the same terms; false otherwise
 */
bool is_equal(polynomial *a, polynomial *b){
    if (!a || !b){
        // invalid polynomial
    }
    while( a && b){
        if ( a->exp == b->exp && a->coeff == b->coeff){
            a = a->next;
            b = b->next;
            continue;
        }
        return false;
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
    while (p){
        transform(p);
        p = p->next;
    }
}

/*
 *Evaluates the polynomial by substituting x in the variable of the polynomial
 *Return is double value of the returned polynomial
 */
double eval_poly(polynomial *p, double x){
    if(!p || !x){
        return 0;
    }
    double sum = 0;
    while (p){
        sum += p->coeff * pow(x, p->exp);
        p = p->next;
    }
    return sum;
}

/*Function multiplies polynomial a by polynomial b and  
 * Returns  the result as a newly malloc'd polynomial 
 *
 */
polynomial *multiply_poly(polynomial *a, polynomial *b){
     polynomial *b_start = b;
     // non malloc'd poly temp
     polynomial out_loop = {0};
     // non malloc'd poly intermediate 
     polynomial in_loop = {0};
     polynomial *temp = {0};
     // for each term in a multiply by b
     while( a ){
        while (b){
            // malloc a new poly to hold result and append to intermediate,
            polynomial *tmp = make_term(a->coeff * b->coeff, a->exp + b->exp );
            append_poly(&in_loop, tmp);
            free(tmp);
            b = b->next;
            
            // jus
        }
        // add temp and intermediate polynomial -- store in temp
        temp = add_poly(&out_loop, &in_loop);
        free(in_loop.next);
        in_loop.coeff = 0;
        in_loop.exp = 0;
        in_loop.next = NULL;
        poly_free(out_loop.next);
        out_loop.coeff = temp->coeff;
        out_loop.exp = temp->exp;
        out_loop.next = temp->next;
        free(temp);
        b = b_start;
        a = a->next;
     }
     // create malloc'd poly results 
     polynomial *results = make_term(out_loop.coeff, out_loop.exp);
     // assign temp to results;
     results->next = out_loop.next;
     return results;
 }

//here for compile
int main (void){
    test();
    return 1;
}