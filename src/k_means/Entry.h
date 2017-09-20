typedef struct Entry {
    int dim;
    int ind;
    int assignment;
    double dist_sq;
    double* vals;
} Entry;

Entry* new_Entry(int dim);
int add_Entry(Entry* e, double val);
int get_Entry(Entry* e, int i, double* a);
int print_Entry(Entry* e);
int fprint_Entry(Entry* e, FILE* f);
int free_Entry(Entry* e);
