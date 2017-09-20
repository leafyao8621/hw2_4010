typedef struct Entry {
    int dim;
    int ind;
    int assignment;
    double dist_sq;
    double* vals;
} Entry;

Entry* new_Entry(int dim);
void add_Entry(Entry* e, double val);
double get_Entry(Entry* e, int i);
void print_Entry(Entry* e);
void fprint_Entry(Entry* e, FILE* f);
void free_Entry(Entry* e);
