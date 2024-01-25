#include <stdlib.h>
#include <stdio.h>
#include "solutions.h"

int running_total(int num){
    static int sum = 0;
    sum += num;
    return sum;
}


int* reverse(int* a, int length){
    int *res = (int*) calloc(length, sizeof(int));
    for(int i = 0; i < length; i++){
        res[i] = a[length - 1 - i];
    }
    return res;
}


void reverse_in_place(int* a, int length){
    int tmp = 0;
    for(int i = 0; i < length / 2; i++){
        tmp = a[i];
        a[i] = a[length - 1 - i];
        a[length - 1 - i]  = tmp;
    }
}


int num_occurences(int* a, int length, int value){
    int res = 0;
    for(int i = 0; i < length; i++){
        if(a[i] == value){
            res++;
        }
    }
    return res;
}