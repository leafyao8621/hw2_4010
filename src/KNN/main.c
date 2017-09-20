#include <stdio.h>
#include <stdlib.h>

double** readKMeans(FILE* in_file,int num_items,int num_attrs);
double** readKMeans(FILE* in_file,int num_items,int num_attrs) {
    //allocate memory for array
    double **mat = NULL;       // pointer to the matrix
    //allocate memory for rows
    mat = (double **) malloc(num_items*sizeof(double *));
    int i;
    for ( i = 0 ; i < num_items ; ++i ) {
        //allocate memory for cols in row
        mat[i] = (double *) malloc((num_attrs + 2)* sizeof(double));
    }
    //loop and assign rows
    int j;
    for (i = 0; i<num_items; i++) {
        for (j = 1; j<num_attrs + 2; j++) {
            double temp;
            fscanf(in_file, "%lf", &temp);
            mat[i][j] = temp;
        }
        //printf("%f %f %f\n", mat[i][1],mat[i][2],mat[i][3]);
    }


    return mat;
}

double** readKNN(FILE* in_file,int num_items,int num_attrs) {
    //allocate memory for array
    double **mat = NULL;       // pointer to the matrix
    //allocate memory for rows
    mat = (double **) malloc(num_items*sizeof(double *));
    int i;
    for ( i = 0 ; i < num_items ; ++i ) {
        //allocate memory for cols in row
        mat[i] = (double *) malloc((num_attrs+1)* sizeof(double));
    }
    //loop and assign rows
    int j;
    for (i = 0; i<num_items; i++) {
        for (j = 1; j<num_attrs + 1; j++) {
            double temp;
            fscanf(in_file, "%lf", &temp);
            mat[i][j] = temp;
        }
        //printf("%f %f %f\n", mat[i][1],mat[i][2],mat[i][3]);
    }
    return mat;
}

void print_matrix(int n1, int n2, double **a) {

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
    if (n1<=0 || n2<=0) {
        return;
    }
    int i;
    int j;
    for (i = 0; i<n1; i++){
        for (j = 0; j<n2; j++){
            printf("%-9.2f",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char** argv) {
    const char* in_file_name = argv[1];
    const char* in_file_name2 = argv[2];

    FILE* in_file = fopen(in_file_name, "r");
    int num_items, num_attrs;
    fscanf(in_file, "%d %d", &num_items, &num_attrs);

    double** a = readKMeans(in_file, num_items,num_attrs);
    print_matrix(num_items,num_attrs+2,a);

    FILE* in_file2 = fopen(in_file_name2, "r");
    int num_items2, num_attrs2;
    fscanf(in_file2, "%d %d", &num_items2, &num_attrs2);

    double** KNN = readKNN(in_file2, num_items2,num_attrs2);
    print_matrix(num_items,num_attrs,KNN);


}

