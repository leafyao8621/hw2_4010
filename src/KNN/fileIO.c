double readKMeans(char in_file_name) {
    FILE* in_file = fopen(in_file_name, "r");
    int num_items, num_attrs;
    fscanf(in_file, "%d %d", &num_items, &num_attrs);

    //allocate memory for array
    double **mat = NULL;       // pointer to the matrix
    //allocate memory for rows
    mat = (double **) malloc(num_items*sizeof(double *));
    int i;
    for ( i = 0 ; i < n1 ; ++i ) {
        //allocate memory for cols in row
        mat[i] = (double *) malloc((num_attrsn2 + 2)* sizeof(double));
    }
    //loop and assign rows
}