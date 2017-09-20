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
int add_Group_DataSet(DataSet* d, Group* g);
int add_Entry_DataSet(DataSet* d, Entry* e);
int set_dist_sqs(DataSet* d);
int check_stable(DataSet* d);
int update_Groups(DataSet* d);
int print_Groups(DataSet* d);
int print_DataSet(DataSet* d);
int fprint_DataSet(DataSet* d, FILE* f);
int free_DataSet(DataSet* d);
