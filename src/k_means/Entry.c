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
    if (opt->vals = NULL) {
        puts("Out of Memory");
        return NULL;
    }
    return opt;
}

void add_Entry(Entry* e, double val) {
    if (e->ind < e->dim) {
        e->vals[e->ind++] = val;
    } else {
        puts("Index out of bound");
        exit(1);
    }
}

double get_Entry(Entry* e, int i) {
    if (i > -1 && i < e->dim) {
        return e->vals[i];
    } else {
        puts("Index out of bound");
        exit(1);
    }
}

void print_Entry(Entry* e) {
    for (int i = 0; i < e->dim; i++) {
        printf("%lf ", e->vals[i]);
    }
    printf("%d\n", e->assignment);
}

void fprint_Entry(Entry* e, FILE* f) {
    if (f == NULL) {
        exit(1);
    }
    fprintf(f, "%d ", e->assignment);
    for (int i = 0; i < e->dim - 1; i++) {
        fprintf(f, "%lf ", e->vals[i]);
    }
    fprintf(f, "%lf\n", e->vals[e->dim - 1]);
}

void free_Entry(Entry* e) {
    free(e->vals);
    free(e);
}
