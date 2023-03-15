/*
*
*
*   @author Elia Renzoni
*   @date 14/03/2023
*
*   Text - Problem : Given two integer arrays nums1 and nums2, sorted in non-decreasing order, return the minimum integer common to both arrays. If there is no common integer amongst nums1 and nums2, return -1.
*   Note that an integer is said to be common to nums1 and nums2 if both arrays have at least one occurrence of that integer.
*
*
*
*/


#include <stdio.h>

#define NOT_FOUND      -1
#define ARR_MAX_ELEMENT 7

void visit_algorithms(int array[], int numb_element, int *search_value_check, int second_array[], int numb_element2);
int  binary_search_algorithm(int search_in_arr_element, int value_to_search[], int num_element2);

int main(void) {

    int fisrt_array[ARR_MAX_ELEMENT],
        second_array[ARR_MAX_ELEMENT];
    int numb_of_element_fa,
        num_of_element_sa;
    int index_array_init;
    int check_erro;
    int *search_value_check;

    do {

        printf("Insert the number of element - first array - \n");
        scanf("%d", &numb_of_element_fa);
        printf("Insert the values (ordered) > \n");

        if (numb_of_element_fa > 1)
            for (index_array_init = 0; (index_array_init < numb_of_element_fa); index_array_init++)
                scanf("%d", &fisrt_array[index_array_init]);
        else
            printf("Error ! \n");
        
        printf("Insert the number of - second array - \n");
        scanf("%d", &num_of_element_sa);
        printf("Insert the values (ordered) > \n");

        if (num_of_element_sa > 1)
            for (index_array_init = 0; (index_array_init < num_of_element_sa); index_array_init++)
                scanf("%d", &second_array[index_array_init]);
        else
            printf("Error ! \n");

        check_erro = num_of_element_sa < 1 || numb_of_element_fa < 1;

        if (check_erro)
            printf("Error, repeat ! \n");
        
        while (getchar() != '\n');
        
    }
    while (check_erro);


    visit_algorithms(fisrt_array, numb_of_element_fa, search_value_check, second_array, num_of_element_sa);
    return (0);
    
}


void visit_algorithms(int array[], int number_of_elem, int *search_value_check, int second_array[], int num_element2) {

    int index_visit_for_loop;
    int value_search;

    for (index_visit_for_loop = 0;
                (index_visit_for_loop < number_of_elem);
            index_visit_for_loop++) {

        value_search = array[index_visit_for_loop];        
        *search_value_check = binary_search_algorithm(value_search, second_array, num_element2);


        if (*search_value_check != NOT_FOUND)
            printf("Common element in %d index \n", *search_value_check);
        else 
            printf("No common element in %d index ! \n", *search_value_check);

    }


}

int binary_search_algorithm(int search_in_arr_element, int value_to_search[], int num_element2) {

    int sx_index,
        dx_index,
        mx_index;

    for (sx_index = 0, dx_index = num_element2 - 1, mx_index = (sx_index + dx_index) / 2;
                (sx_index <= dx_index && value_to_search[mx_index] != search_in_arr_element);
        mx_index = (sx_index + dx_index) / 2)

        if (value_to_search[mx_index] > search_in_arr_element)
            dx_index = mx_index - 1;
        else
            sx_index = mx_index + 1;

    
    return ((sx_index <= dx_index? mx_index : NOT_FOUND));

}