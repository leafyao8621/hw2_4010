#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 4) {
        puts("Requires at least 3 arguments");
        return 1;
    }
    const char* in_file_name = argv[1];
    int k = atoi(argv[2]);
    if (k < 1) {
        puts("Invalid k value");
        return 1;
    }
    FILE* in_file = fopen(in_file_name, "r");
    if (in_file == NULL) {
        puts("Invalid input file name");
        return 1;
    }
    int num_items, num_attrs;
    fscanf(in_file, "%d %d", &num_items, &num_attrs);
    if (num_items < k) {
        puts("Invalid k value(greater than total number of items)");
        return 1;
    }
    int cnt = 0;
    double centroids[k][num_attrs];
    double entries[num_items][num_attrs];
    int assignments[num_items];
    int cnts[k];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < num_attrs; j++) {
            double temp;
            fscanf(in_file, "%lf", &temp);
            centroids[cnt][j] = temp;
            entries[cnt][j] = temp;
        }
        cnts[i] = 1;
        assignments[cnt++] = i;
    }
    for (int i = 0; i < num_items - k; i++) {
        double min_val = 0;
        int chosen = 0;
        for (int j = 0; j < num_attrs; j++) {
            double temp;
            fscanf(in_file, "%lf", &temp);
            entries[cnt][j] = temp;
            min_val += (temp - centroids[0][j]) * (temp - centroids[0][j]);
        }
        for (int j = 1; j < k; j++) {
            double val = 0;
            for (int l = 0; l < num_attrs; l++) {
                val += (entries[cnt][l] - centroids[j][l]) *
                       (entries[cnt][l] - centroids[j][l]);
            }
            if (val < min_val) {
                min_val = val;
                chosen = j;
            }
        }
        for (int j = 0; j < num_attrs; j++) {
            centroids[chosen][j] *= cnts[chosen];
            centroids[chosen][j] += entries[cnt][j];
            centroids[chosen][j] /= (cnts[chosen] + 1);
        }
        cnts[chosen]++;
        assignments[cnt++] = chosen;
    }
    FILE* out_file = fopen(argv[3], "w");
    puts("Centroids:\n\n");
    for (int i = 0; i < k; i++) {
        printf("%d. ", i);
        for (int j = 0; j < num_attrs - 1; j++) {
            printf("%lf ", centroids[i][j]);
        }
        printf("%lf\n", centroids[i][num_attrs - 1]);
    }
    puts("\nData Points:\n\n");
    for (int i = 0; i < num_items; i++) {
        printf("%d. ", i);
        for (int j = 0; j < num_attrs; j++) {
            printf("%lf ", entries[i][j]);
            fprintf(out_file, "%lf ", entries[i][j]);
        }
        printf("%d\n", assignments[i]);
        fprintf(out_file, "%d\n", assignments[i]);
    }
    fclose(in_file);
    fclose(out_file);
    return 0;
}
