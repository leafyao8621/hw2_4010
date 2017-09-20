#include <stdio.h>
#include <stdlib.h>
#include "Group.h"

Group* new_Group(Centroid* centroid) {
    Group* opt = malloc(sizeof(Group));
    // if (opt == NULL) {
    //     puts("Out of Memory");
    //     return NULL;
    // }
    opt->cnt = 1;
    opt->total_dist_sq = 0;
    opt->centroid = centroid;
    return opt;
}

double calc_dist_sq(Centroid* c, Entry* e) {
    double temp = 0;
    for (int i = 0; i < c->dim; i++) {
        temp += (get_Centroid(c, i) - get_Entry(e, i)) *
                (get_Centroid(c, i) - get_Entry(e, i));
    }
    return temp;
}

void free_Group(Group* g) {
    free_Centroid(g->centroid);
    free(g);
}
