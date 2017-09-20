#include "Entry.h"
#include "Centroid.h"

typedef struct Group {
    int cnt;
    double total_dist_sq;
    Centroid* centroid;
} Group;

Group* new_Group(Centroid* centroid);
double calc_dist_sq(Centroid* c, Entry* e);
void reset_Group(Group* g);
void free_Group(Group* g);
