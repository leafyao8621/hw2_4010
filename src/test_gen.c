#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    srand(time(NULL));
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("%d %d\n", a, b);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b - 1; j++) {
            printf("%.lf ", ((double)rand()/RAND_MAX) * a);
        }
        printf("%.lf\n", ((double)rand()/RAND_MAX) * a);
    }
    return 0;
}
