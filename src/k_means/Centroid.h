typedef struct Centroid {
    int dim;
    int ind;
    double* vals;
} Centroid;

Centroid* new_Centroid(int dim);
int add_Centroid(Centroid* c, double val);
int get_Centroid(Centroid* c, int i, double* a);
int print_Centroid(Centroid* c);
int free_Centroid(Centroid* c);
