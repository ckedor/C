#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


int main(){



    clock_t start, end;
    double cpu_time_used;
    int a=0;
    int i=0;
    int j=0;
    int k=0;

    start = clock();

    for (i=0; i < 10000; i++){
        for (j=0; j < 10000; j++){
            for (k=0; k < 10; k++){
                a++;
            }
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf ("%f",cpu_time_used);
    


    return 0;

}