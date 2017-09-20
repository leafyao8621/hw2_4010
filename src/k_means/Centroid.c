#include <stdio.h>
#include <stdlib.h>
#include "Centroid.h"

Centroid* new_Centroid(int dim) {
    Centroid* opt = malloc(sizeof(Centroid));
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

int add_Centroid(Centroid* c, double val) {
    if (c->ind < c->dim) {
        c->vals[c->ind++] = val;
        return 0;
    } else {
        puts("Index out of bound");
        return 1;
    }
}

double get_Centroid(Centroid* c, int i) {
    if (i > -1 && i < c->dim) {
        return c->vals[i];
    } else {
        puts("Index out of bound");
        return 0;
    }
}

void print_Centroid(Centroid* c) {
    for (int i = 0; i < c->dim - 1; i++) {
        printf("%lf ", c->vals[i]);
    }
    printf("%lf\n", c->vals[c->dim - 1]);
}

void free_Centroid(Centroid* c) {
    free(c->vals);
    free(c);
}
