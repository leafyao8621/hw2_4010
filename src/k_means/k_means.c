#include <stdio.h>
#include <stdlib.h>
#include "DataSet.h"

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
    DataSet* d = new_DataSet(k, num_attrs, num_items);
    if (d != NULL) {
        for (int i = 0; i < k; i++) {
            Centroid* c = new_Centroid(num_attrs);
            Entry* e = new_Entry(num_attrs);
            if (c!= NULL && e != NULL) {
                for (int j = 0; j < num_attrs; j++) {
                    double temp;
                    fscanf(in_file, "%lf", &temp);
                    if (add_Entry(e, temp)) {
                        free_DataSet(d);
                        fclose(in_file);
                        return 1;
                    }
                    if (add_Centroid(c, temp)) {
                        free_DataSet(d);
                        fclose(in_file);
                        return 1;
                    }

                }

                e->assignment = i;
                Group* g = new_Group(c);
                if (add_Group_DataSet(d, g)) {
                    free_DataSet(d);
                    fclose(in_file);
                    return 1;
                }
                if (add_Entry_DataSet(d, e)) {
                    free_DataSet(d);
                    fclose(in_file);
                    return 1;
                }
            } else {
                free_DataSet(d);
                fclose(in_file);
                return 1;
            }
        }
        for (int i = k; i < num_items; i++) {
            Entry* e = new_Entry(num_attrs);
            if (e == NULL) {
                free_DataSet(d);
                fclose(in_file);
                return 1;
            }
            for (int j = 0; j < num_attrs; j++) {
                double temp;
                fscanf(in_file, "%lf", &temp);
                if (add_Entry(e, temp)) {
                    free_DataSet(d);
                    fclose(in_file);
                    return 1;
                }
            }
            double minval;
            if (calc_dist_sq(d->groups[0]->centroid, e, &minval)) {
                free_DataSet(d);
                fclose(in_file);
                return 1;
            }
            int chosen = 0;
            for (int j = 0; j < k; j++) {
                double val;
                if (calc_dist_sq(d->groups[j]->centroid, e, &val)) {
                    free_DataSet(d);
                    fclose(in_file);
                    return 1;
                }
                if (val < minval) {
                    chosen = j;
                    minval = val;
                }
            }
            e->assignment = chosen;
            d->groups[chosen]->total_dist_sq += minval;
            d->groups[chosen]->cnt++;
            if (add_Entry_DataSet(d, e)) {
                free_DataSet(d);
                fclose(in_file);
                return 1;
            }
        }
        if (set_dist_sqs(d)) {
            free_DataSet(d);
            fclose(in_file);
            return 1;
        }
        if (print_Groups(d)) {
            free_DataSet(d);
            fclose(in_file);
            return 1;
        }
        if (print_DataSet(d)) {
            free_DataSet(d);
            fclose(in_file);
            return 1;
        }
        int cond = 0;
        do {
            if (update_Groups(d)) {
                free_DataSet(d);
                fclose(in_file);
                return 1;
            }
            for (int i = 0; i < d->num_items; i++) {
                Entry* e = d->entries[i];
                double minval;
                if (calc_dist_sq(d->groups[0]->centroid, e, &minval)) {
                    free_DataSet(d);
                    fclose(in_file);
                    return 1;
                }
                int chosen = 0;
                for (int j = 0; j < d->k; j++) {
                    double val;
                    if (calc_dist_sq(d->groups[j]->centroid, e, &val)) {
                        free_DataSet(d);
                        fclose(in_file);
                        return 1;
                    }
                    if (val < minval) {
                        chosen = j;
                        minval = val;
                    }
                }
                d->groups[chosen]->total_dist_sq += minval;
                d->groups[chosen]->cnt++;
                e->assignment = chosen;
            }
            if (print_Groups(d)) {
                free_DataSet(d);
                fclose(in_file);
                return 1;
            }
            cond = check_stable(d);
            if (set_dist_sqs(d)) {
                free_DataSet(d);
                fclose(in_file);
                return 1;
            }
            if (print_DataSet(d)) {
                free_DataSet(d);
                fclose(in_file);
                return 1;
            }
        } while (!cond);
        puts("\nFinal Result:");
        if (print_DataSet(d)) {
            free_DataSet(d);
            fclose(in_file);
            return 1;
        }
        const char* out_file_name = argv[3];
        FILE* out_file = fopen(out_file_name, "w");
        if (out_file == NULL) {
            free_DataSet(d);
            fclose(in_file);
            return 1;
        }
        if (fprintf(out_file, "%d %d %d\n", num_items, num_attrs, k)) {
            free_DataSet(d);
            fclose(in_file);
            fclose(out_file);
            return 1;
        }
        if (fprint_DataSet(d, out_file)) {
            free_DataSet(d);
            fclose(in_file);
            fclose(out_file);
            return 1;
        }
        free_DataSet(d);
        fclose(out_file);
    }
    fclose(in_file);
}
