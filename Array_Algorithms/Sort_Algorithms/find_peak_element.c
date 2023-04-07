/*
 *
 *
 *  @author Elia Renzoni
 *  @date 16/03/2023
 *
 *
 *  Problem : find peak element of non order array
 *
 *
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define MAX_ELEMENT     1000
#define MIN_ELEMENT     1
#define NOT_FOUND      -1

void insertsort(int n_ord_array[], int num_of_element, int *search_value);
int  binary_search(int ord_array[], int num_of_element, int *value_s);

int main(void) {

    int *sequence_of_integers;
    int  num_of_element;
    int  check_errors;
    int  index;
    int  element_max;
    int  index_find;
    int *search_value;

    do {

        printf("Insert the number of element > \n");
        scanf("%d", &num_of_element);
        printf("Insert the elements > \n");

        sequence_of_integers = (int *)calloc(num_of_element, sizeof(int));

        for (index = 0; (index < num_of_element); index++) {

            scanf("%d", &sequence_of_integers[index]);
            if (sequence_of_integers[index] > (INT_MAX / 2)) 
                element_max++;
            else 
                element_max = 0;
        }

        check_errors = num_of_element > MAX_ELEMENT || num_of_element < MIN_ELEMENT || element_max != 0;

        if (check_errors) {
            printf("Error !\n");
            free(sequence_of_integers);
        }

        while (getchar() != '\n'); 

    } while (check_errors);


    insertsort(sequence_of_integers, num_of_element, search_value);

    index_find = binary_search(sequence_of_integers, num_of_element, search_value);

    if (!(index_find == NOT_FOUND))
        printf("Peak element find ! %d \n", index_find);
    else 
        printf("Peak element non find ! \n", index_find);
    
    free(sequence_of_integers);

    return (0);
}


void insertsort(int array_n_ord[], int number_elements, int *search_value) {

    int values_ins,
        f_index,
        s_index;

    for (f_index = 1; (f_index < number_elements); f_index++) {
        for (values_ins = array_n_ord[f_index], s_index = f_index - 1;
                ((s_index >= 0) && (array_n_ord[s_index] > values_ins));
             s_index--) 
                array_n_ord[s_index + 1] = array_n_ord[s_index];
        
        if (s_index + 1 != f_index)
            array_n_ord[s_index + 1] = values_ins;

    }

    *search_value = array_n_ord[number_elements - 1];

}


int binary_search(int ord_array[], int num_element, int *search_value) {

    int mx_index,
        sx_index,
        dx_index;



    for (sx_index = 0, dx_index = num_element - 1, mx_index = (sx_index + dx_index) / 2;
            ((sx_index <= dx_index) && (ord_array[mx_index] != *search_value));
        mx_index = (sx_index + dx_index) / 2)

        if (ord_array[mx_index] > *search_value)
            dx_index = mx_index - 1;
        else
            sx_index = mx_index + 1;

    

    return ((sx_index <= dx_index)? mx_index : NOT_FOUND);

}




