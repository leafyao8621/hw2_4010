#include <stdio.h>
#include <stdlib.h>
#include "DataSet.h"

DataSet* new_DataSet(int k, int num_attrs, int num_items) {
    DataSet* opt = malloc(sizeof(DataSet));
    if (opt == NULL) {
        puts("Out of Memory");
        return NULL;
    }
    opt->k = k;
    opt->num_attrs = num_attrs;
    opt->num_items = num_items;
    opt->gind = 0;
    opt->eind = 0;
    opt->dist_sqs = malloc(sizeof(double) * k);
    if (opt->dist_sqs == NULL) {
        puts("Out of Memory");
        return NULL;
    }
    opt->groups = malloc(sizeof(Group*) * k);
    if (opt->groups == NULL) {
        puts("Out of Memory");
        return NULL;
    }
    opt->entries = malloc(sizeof(Entry*) * num_items);
    if (opt->entries == NULL) {
        puts("Out of Memory");
        return NULL;
    }
    return opt;
}

int add_Group_DataSet(DataSet* d, Group* g) {
    if (d->gind < d->k) {
        d->groups[d->gind++] = g;
        return 0;
    } else {
        puts("Index out of bound");
        return 1;
    }
}

int add_Entry_DataSet(DataSet* d, Entry* e) {
    if (d->eind < d->num_items) {
        d->entries[d->eind++] = e;
        return 0;
    } else {
        puts("Index out of bound");
        return 1;
    }
}

int set_dist_sqs(DataSet* d) {
    if (d != NULL) {
        for (int i = 0; i < d->k; i++) {
            d->dist_sqs[i] = d->groups[i]->total_dist_sq;
        }
        return 0;
    } else {
        return 1;
    }
}
int check_stable(DataSet* d) {
    for (int i = 0; i < d->k; i++) {
        if (d->groups[i]->total_dist_sq != d->dist_sqs[i]) {
            return 0;
        }
    }
    return 1;
}

int update_Groups(DataSet* d) {
    if (d != NULL) {
        for (int i = 0; i < d->k; i++) {
            for (int j = 0; j < d->num_attrs; j++) {
                d->groups[i]->centroid->vals[j] = 0;
            }
        }
        for (int i = 0; i < d->num_items; i++) {
            for (int j = 0; j < d->num_attrs; j++) {
                d->groups[d->entries[i]->assignment]->centroid->vals[j] +=
                d->entries[i]->vals[j];
            }
        }
        for (int i = 0; i < d->k; i++) {
            for (int j = 0; j < d->num_attrs; j++) {
                d->groups[i]->centroid->vals[j] /= d->groups[i]->cnt;
            }
        }
        for (int i = 0; i < d->k; i++) {
            d->groups[i]->cnt = 0;
            d->groups[i]->total_dist_sq = 0;
        }
        return 0;
    } else {
        return 1;
    }
}

int print_Groups(DataSet* d) {
    if (d == NULL) {
        return 1;
    }
    for (int i = 0; i < d->k; i++) {
        printf("%d\n", d->groups[i]->cnt);
        printf("%lf\n", d->groups[i]->total_dist_sq);
        print_Centroid(d->groups[i]->centroid);
    }
    return 0;
}
int print_DataSet(DataSet* d) {
    if (d == NULL) {
        return 1;
    }
    for (int i = 0; i < d->num_items; i++) {
        print_Entry(d->entries[i]);
    }
    return 0;
}

int fprint_DataSet(DataSet*d, FILE* f) {
    if (f == NULL || d == NULL) {
        return 1;
    }
    for (int i = 0; i < d->num_items; i++) {
        if (fprint_Entry(d->entries[i], f)) {
            return 1;
        }
    }
    return 0;
}

int free_DataSet(DataSet* d) {
    if (d != NULL) {
        int out = 0;
        if (d->groups != NULL) {
            for (int i = 0; i < d->k; i++) {
                free_Group(d->groups[i]);
            }
            free(d->groups);
        } else {
            out = 1;
        }
        if (d->dist_sqs != NULL) {
            free(d->dist_sqs);
        } else {
            out = 1;
        }
        if (d->entries != NULL) {
            free(d->entries);
        } else {
            out = 1;
        }
        return out;
    } else {
        return 1;
    }
}
