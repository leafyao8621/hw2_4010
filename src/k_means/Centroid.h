typedef struct Centroid {
    int dim;
    int ind;
    double* vals;
} Centroid;

Centroid* new_Centroid(int dim);
int add_Centroid(Centroid* c, double val);
double get_Centroid(Centroid* c, int i);
void print_Centroid(Centroid* c);
void free_Centroid(Centroid* c);
