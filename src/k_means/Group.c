#include <stdio.h>
#include <stdlib.h>
#include "Group.h"

Group* new_Group(Centroid* centroid) {
    Group* opt = malloc(sizeof(Group));
    if (opt == NULL) {
        puts("Out of Memory");
        return NULL;
    }
    opt->cnt = 1;
    opt->total_dist_sq = 0;
    opt->centroid = centroid;
    if (centroid == NULL) {
        puts("Invalid");
        return NULL;
    }
    return opt;
}

int calc_dist_sq(Centroid* c, Entry* e, double* out) {
    if (c != NULL && e != NULL) {
        double temp = 0;
        for (int i = 0; i < c->dim; i++) {
            double a;
            double b;
            if (get_Centroid(c, i, &a)) {
                return 1;
            }
            if (get_Entry(e, i, &b)) {
                return 1;
            }
            temp += (a - b) *
                    (a - b);
        }
        *out = temp;
        return 0;
    } else {
        return 1;
    }
}

int free_Group(Group* g) {
    free_Centroid(g->centroid);
    free(g);
}
