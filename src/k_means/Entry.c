#include <stdio.h>
#include <stdlib.h>
#include "Entry.h"

Entry* new_Entry(int dim) {
    Entry* opt = malloc(sizeof(Entry));
    if (opt == NULL) {
        puts("Out of Memory");
        return NULL;
    }
    opt->dim = dim;
    opt->ind = 0;
    opt->vals = malloc(sizeof(double) * dim);
    if (opt->vals == NULL) {
        puts("Out of Memory");
        return NULL;
    }
    return opt;
}

int add_Entry(Entry* e, double val) {
    if (e->ind < e->dim) {
        e->vals[e->ind++] = val;
        return 0;
    } else {
        puts("Index out of bound");
        return 1;
    }
}

int get_Entry(Entry* e, int i, double* a) {
    if (i > -1 && i < e->dim) {
        *a = e->vals[i];
        return 0;
    } else {
        puts("Index out of bound");
        return 1;
    }
}

int print_Entry(Entry* e) {
    if (e != NULL) {
        for (int i = 0; i < e->dim; i++) {
            printf("%lf ", e->vals[i]);
        }
        printf("%d\n", e->assignment);
        return 1;
    } else {
        return 0;
    }
}

int fprint_Entry(Entry* e, FILE* f) {
    if (f != NULL) {
        fprintf(f, "%d ", e->assignment);
        for (int i = 0; i < e->dim - 1; i++) {
            fprintf(f, "%lf ", e->vals[i]);
        }
        fprintf(f, "%lf\n", e->vals[e->dim - 1]);
        return 1;
    } else {
        return 0;
    }
}

int free_Entry(Entry* e) {
    if (e != NULL) {
        if (e->vals != NULL) {
            free(e->vals);
            free(e);
            return 0;
        } else {
            free(e);
            return 1;
        }
    } else {
        return 1;
    }
}
