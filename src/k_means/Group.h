#include "Entry.h"
#include "Centroid.h"

typedef struct Group {
    int cnt;
    double total_dist_sq;
    Centroid* centroid;
} Group;

Group* new_Group(Centroid* centroid);
int calc_dist_sq(Centroid* c, Entry* e, double* out);
int free_Group(Group* g);
