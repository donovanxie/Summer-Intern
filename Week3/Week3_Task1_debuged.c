#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int *array = (int *)malloc(5 * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        array[i] = i + 1;
    }

    printf("Original array: ");
    print_array(array, 5);

    //int *ptr = array + 5; comment out, this is where the problem occurs

    int *ptr = array + 4; /*
                            same as int *ptr = &array[4],  
                            since the array only have 5 elements, from array[0] to array[4],
                            the orginal *ptr = array + 5 is pointing to array[5], which is out of bound,
                            the fix here is simply make the ptr pointer points to array[4], which is the last element in the array,
                            so there is no out of bound issue.
                            
                            */ 
    *ptr = 10; // now the pointer will change array[4] to 10

    printf("Modified array: ");
    print_array(array, 5);

    free(array);
    return 0;
}
