#include <stdio.h>
#include <stdlib.h>

int fill_matrix(int row, int col, double** matrix, FILE* stream){
    if(row<=0|| col<=0){
    	return 1;
    }
    for(int i=0; i<row; i++){
    	for(int j=1; j<col; j++){
    		double currentdata;
    		fscanf(stream, "%lf", &currentdata);
    		matrix[i][j] = currentdata;
    	}
    }
    return 0;
}

double**  malloc_matrix(int row, int col){
	double** matrix = NULL;
//	if(row<=0|| col<=0){
//		return NULL;
//	}
	matrix = malloc(sizeof(double*)*row);
    for (int i=0; i<row; i++){
    	matrix[i] = malloc(sizeof(double)*col);
    }
    return matrix;
}

void free_matrix(int row, int col, double** matrix){
	if(row>0 && col>0){
		for(int i=0; i<row; i++){
			free(matrix[i]);
		}
		free(matrix);
	}
}

int Calculate_Distance(double** data, double* point, int num_items, int num_attrs){
    if (num_items<=0 || num_attrs<=0|| data==NULL|| point==NULL){
    	return 1;
    }
    for(int i = 0; i<num_items; i++){
    	double distance = 0;
    	for (int j=0; j<num_attrs; j++){
            distance += (data[i][j+2] - point[j+1])*(data[i][j+2] - point[j+1]);
    	}
        data[i][0] = distance;
    }
    return 0;
}

int Compare(double* a, double* b){
	if (a == NULL|| b==NULL){
		exit(1);
	}
	if(a[0] > b[0]){
		return 1;
	} else {
        return 0;
	}
}

int Sort_by_Distance(double** data, int num_items, int num_attrs){
	if (num_items<=0 || num_attrs<=0|| data==NULL){
	    	return 1;
	    }
	for(int ed=0; ed<num_items - 1; ed++){
		for (int i=0; i<num_items - ed - 1; i++){
			if (Compare(data[i],data[i+1])){
				double* swap = data[i+1];
				data[i+1] = data[i];
				data[i] = swap;
			}
		}
	}
    return 0;
}

int Get_GroupNum(int num_groups, int k, double** data, int* groupFreq){
	if (num_groups<=0|| k<=0|| data==NULL){
		exit(1);
	}
    for(int j=0; j<num_groups; j++){
    	groupFreq[j] = 0;
    }
    for (int i=0; i<k; i++){
    	int groupnum = (int)data[i][1];
    	groupFreq[groupnum] += 1;
    }
    int group_number = 0;
    for (int h=0; h<num_groups; h++){
    	if(groupFreq[group_number] < groupFreq[h]){
    		group_number = h;
    	}
    }
    return group_number;
}
//free(groupFreq);

int main(int argc, char** argv){
    if(argc < 5){
    	return 1;
    }
    const char* data_file = argv[1]; //non_target grouped data from Kmeans
    const char* points_file = argv[2]; //target data to be classified
    const char* output_file = argv[3];
    int k = atoi(argv[4]); //The number of closest points to pick in KNN


    FILE* data_stream = fopen(data_file, "r");
    int num_items, num_attrs, num_groups;
    fscanf(data_stream, "%d", &num_items);
    fscanf(data_stream, "%d", &num_attrs);
    fscanf(data_stream, "%d", &num_groups);
    double** data = malloc_matrix(num_items, num_attrs+2);
    if (fill_matrix(num_items, num_attrs+2, data, data_stream)){
    	return 1;
    }
    fclose(data_stream); //write non-target grouped data to double** data
//    for (int i = 0; i < num_items; i++) {
//    	for (int j = 0; j < num_attrs + 1; j++) {
//    		printf("%lf ", data[i][j]);
//    	}
//    	printf("%lf\n", data[i][num_attrs + 1]);
//    }
    FILE* points_stream = fopen(points_file, "r");
    int num_items_p, num_attrs_p;
    fscanf(data_stream, "%d", &num_items_p);
    fscanf(data_stream, "%d", &num_attrs_p);
    if(num_attrs != num_attrs_p){
    	return 1;
    }
    double** points = malloc_matrix(num_items_p, num_attrs_p + 1);
    if(fill_matrix(num_items_p, num_attrs_p + 1, points, points_stream)){
        return 1;
    }
    fclose(points_stream); //write target data to double** points
//	for (int i = 0; i < num_items_p; i++) {
//		for (int j = 0; j < num_attrs_p; j++) {
//			printf("%lf ", points[i][j]);
//		}
//		printf("%lf\n", points[i][num_attrs]);
//	}
    int groupFreq[num_groups]; //= malloc(sizeof(int)*num_groups);
    //generate a 1-d array to record the frequency for each group/label

    for (int i=0; i<num_items_p; i++){
    	double* point = points[i];
    	if(Calculate_Distance(data, point, num_items, num_attrs)){
    		return 1;
    	}
    	if(Sort_by_Distance(data, num_items, num_attrs)){
    		return 1;
    	}
    	int groupnum = Get_GroupNum(num_groups, k, data, groupFreq);
        points[i][0] = groupnum;
        printf("Data Point: %d, Group Num: %d\n", i+1, groupnum);
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < num_attrs + 1; j++) {
				printf("%lf ", data[i][j]);
			}
			printf("%lf\n", data[i][num_attrs + 1]);
        }
        printf("\n");
    }

    FILE* out = fopen(output_file, "w");
    for(int i=0; i<num_items_p; i++){
    	fprintf(out, "%.0lf ", points[i][0]);
    	for(int j=1; j<num_attrs_p+1; j++){
            fprintf(out, "%lf ", points[i][j]);
    	}
    	fprintf(out, "\n");
    }
    fclose(out);
    free_matrix(num_items, num_attrs+2, data);
    free_matrix(num_items_p, num_attrs_p+1, points);
    return 0;
}


