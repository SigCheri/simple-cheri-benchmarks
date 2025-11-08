#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int add_pointer(int** p1, int** p2, int** p3, int** p4, int len){
    int sum = 0;
    for(int i=0;i < len; i++){
        sum += (*p1)[i] + (*p2)[i] + (*p3)[i] + (*p4)[i];
    }
    return sum;
}

void sum_matrix(int* a[4]){
    for(int i = 0;i < 10;i ++){
        a[0][i] = i;
        a[1][i] = i;
        a[2][i] = i;
        a[3][i] = i;
    }
    int* p[4] = {a[0], a[1], a[2], a[3]};
    int** q[4] = {&p[0], &p[1], &p[2], &p[3]};
    int sum = add_pointer(q[0], q[1], q[2], q[3], 10);
    printf("sum = %d, sum's address = %lx\n", sum, (uint64_t)&sum);
    return;
}

int global_array[4][10];
int* global_matrix[4] = {global_array[0], global_array[1], global_array[2], global_array[3]};

int main(int argc, const char* argv[]){
    int local_array[4][10];
    int* local_matrix[4] = {local_array[0], local_array[1], local_array[2], local_array[3]};
    
    int** heap_matrix = (int**)malloc(sizeof(int*) * 4);
    heap_matrix[0] = (int*)malloc(sizeof(int) * 10);
    heap_matrix[1] = (int*)malloc(sizeof(int) * 10);
    heap_matrix[2] = (int*)malloc(sizeof(int) * 10);
    heap_matrix[3] = (int*)malloc(sizeof(int) * 10);
    sum_matrix(global_matrix);
    sum_matrix(local_matrix);
    sum_matrix(heap_matrix);
    return 0;
}
