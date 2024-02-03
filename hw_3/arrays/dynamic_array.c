#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;

    arrays[num_allocated] = da;
    num_allocated++;

    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    num_allocated--;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}


//Part for HW3

double DynamicArray_min ( const DynamicArray * da ){
    double result = INT_MAX;
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        double ele = DynamicArray_get(da,i);
        result = ele >= result ? result : ele;
    }

    return result;
}

double DynamicArray_max ( const DynamicArray * da ){
    double result = INT_MIN;
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        double ele = DynamicArray_get(da,i);
        result = ele >= result ? ele : result;
    }

    return result;
}

double DynamicArray_mean ( const DynamicArray * da ){
    double sum = 0;
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        sum += DynamicArray_get(da,i);
    }

    return sum / (double)DynamicArray_size(da);
}

int compare(const void *a, const void *b) {
    double ret = *(double*)a - *(double*)b;
    return ret <= 0 ? 0 : 1;
}

double DynamicArray_median ( const DynamicArray * da ){
    int size = DynamicArray_size(da);
    double *tmp = (double *) calloc (size, sizeof(double) );
    for ( int i=0; i<size; i++ ) {
        tmp[i] = DynamicArray_get(da,i);
    }

    qsort(tmp, size, sizeof(double), compare);
    // size is odd
    if (size % 2 != 0) {
        
        return tmp[size / 2];
    } 
    // size is even, return the average of mid two
    else {
        double mid1 = tmp[size / 2 - 1];
        double mid2 = tmp[size / 2];
        return (mid1 + mid2) / 2.0;
    }
}

double DynamicArray_sum ( const DynamicArray * da ){
    double sum = 0;
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        sum += DynamicArray_get(da,i);
    }

    return sum;
}

double DynamicArray_last ( const DynamicArray * da ){
    assert(DynamicArray_size(da) > 0);

    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    return value;
}

double DynamicArray_first ( const DynamicArray * da ){
    assert(DynamicArray_size(da) > 0);

    double value = DynamicArray_get(da, 0);
    return value;
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ){
    DynamicArray *result = (DynamicArray *) malloc(sizeof(DynamicArray));
    result->capacity = da->capacity;
    result->origin = da->origin;
    result->end = da->end;
    result->buffer = (double *) calloc ( da->capacity, sizeof(double) );

    for ( int i=0; i<DynamicArray_size(result); i++ ) {
        result->buffer[result->origin + i] = DynamicArray_get(da,i);
    }
    
    arrays[num_allocated] = result;
    num_allocated++;

    return result;
}

DynamicArray * DynamicArray_range ( double a, double b, double step){
    DynamicArray *result = DynamicArray_new();
    for(double i = a; i < b + step/10; i+=step){
        DynamicArray_push(result, i);
    }
    // double size = (b - a) / step + 1;
    // for(int i = 0; i < size; i++){
    //     DynamicArray_push(result, a + step * i);
    // }
    return result;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ){
    int size = DynamicArray_size(a) + DynamicArray_size(b);
    double *tmp = (double *) calloc (size, sizeof(double) );
    for ( int i=0; i<DynamicArray_size(a); i++ ) {
        tmp[i] = DynamicArray_get(a,i);
    }
    for ( int j=0; j<DynamicArray_size(b); j++ ) {
        tmp[j + DynamicArray_size(a)] = DynamicArray_get(b,j);
    }

    qsort(tmp, size, sizeof(double), compare);

    DynamicArray *result = DynamicArray_new();
    for(int k = 0; k < size; k++){
        DynamicArray_push(result, *(tmp + k));
    }

    free(tmp);

    return result;
}

DynamicArray * DynamicArray_take(const DynamicArray * da, int n){
    int size = DynamicArray_size(da);

    DynamicArray *result = DynamicArray_new();
    if(n > 0){
        for(int i = 0; i < n; i++){
            DynamicArray_push(result, DynamicArray_get(da, i));
        }
    }
    else{
        for(int i = size + n; i < size; i++){
            DynamicArray_push(result, DynamicArray_get(da, i));
        }
    }

    return result;
}

void DynamicArray_destroy_all(){
    for(int i = 0; i < 50; i++){
        if(arrays[i] == NULL) break;
        if(DynamicArray_is_valid(arrays[i]))
            DynamicArray_destroy(arrays[i]);
    }
    return;
}

int DynamicArray_is_valid(const DynamicArray * da){
    if(da->buffer != NULL)
        return 1;
    else
        return 0;
}

int DynamicArray_num_arrays(){
    return num_allocated;
}

