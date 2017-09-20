#include "Group.h"

typedef struct DataSet {
    int k;
    int num_attrs;
    int num_items;
    int gind;
    int eind;
    double* dist_sqs;
    Group** groups;
    Entry** entries;
} DataSet;

DataSet* new_DataSet(int k, int num_attrs, int num_items);
void add_Group_DataSet(DataSet* d, Group* g);
void add_Entry_DataSet(DataSet* d, Entry* e);
void set_dist_sqs(DataSet* d);
int check_stable(DataSet* d);
void update_Groups(DataSet* d);
void print_Groups(DataSet* d);
void print_DataSet(DataSet* d);
void fprint_DataSet(DataSet* d, FILE* f);
void free_DataSet(DataSet* d);
