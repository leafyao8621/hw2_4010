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

int get_Centroid(Centroid* c, int i, double* a) {
    if (i > -1 && i < c->dim) {
        *a = c->vals[i];
        return 0;
    } else {
        puts("Index out of bound");
        return 1;
    }
}

int print_Centroid(Centroid* c) {
    if (c != NULL) {
        for (int i = 0; i < c->dim - 1; i++) {
            printf("%lf ", c->vals[i]);
        }
        printf("%lf\n", c->vals[c->dim - 1]);
        return 0;
    } else {
        return 1;
    }
}

int free_Centroid(Centroid* c) {
    if (c != NULL) {
        if (c->vals != NULL) {
            free(c->vals);
            free(c);
            return 0;
        } else {
            free(c);
            return 1;
        }
    } else {
        return 1;
    }
}
