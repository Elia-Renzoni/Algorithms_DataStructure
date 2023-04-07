/*
*
*
*   @author Elia Renzoni
*   @date 12/03/2023
*
*   Problem : delete the duplicated element of an array of intergers
*   from leetcode.com
*
*
*
* */



#include <stdio.h>
#include <stdlib.h>


#define MAX_VALUE_ARR     100          
#define MIN_VALUE_ARR    -100
#define TRUE               1
#define FALSE              0

void search_duplicate_values(char *darray, int num_da_element);

int main(void) {

    int  array_num_element;                             // input -> number of arr. elements
    char *dynamic_array;                                // input -> dynamic array
    
    int  loop_index,                                    // support vars 
         check_scanf,
         n_scanf,
         not_correct_input;
    int  check_validation_value_arr = 0;
    
    // input validation
    do {

        printf("Insert the number of values > \n");
        check_scanf = scanf("%d", &array_num_element);
        printf("Insert the value of the element > \n");
        if (array_num_element >= 1) {

                dynamic_array = (char *)calloc(array_num_element, sizeof(char));
                loop_index = 0;
                while (loop_index < array_num_element) {
                    n_scanf = scanf(" %c ", &dynamic_array[loop_index]);
                    if (dynamic_array[loop_index] < MIN_VALUE_ARR || dynamic_array[loop_index] > MAX_VALUE_ARR)
                            check_validation_value_arr = 1;

                    loop_index++;
                }
        }
        else 
            printf("ERROR ARRAY \n");
        
        not_correct_input = check_scanf < 1 || check_scanf > 3 * 104 || check_validation_value_arr == TRUE || dynamic_array == NULL;

        if (not_correct_input == TRUE)
            printf("Error ! \n");

        while (getchar() != '\n');

    } while (not_correct_input == TRUE);

    search_duplicate_values(dynamic_array, array_num_element);

    free(dynamic_array);
    
    return (0);
}


void search_duplicate_values(char *dynamic_array, int number_of_element) {

    int loop_index,                     // support vars
        backup_loop_index;
    
    int number_of_right_element;        // output var.

    backup_loop_index = number_of_element;

    for (loop_index = 0; (loop_index < number_of_element); loop_index++) {

        if (dynamic_array[loop_index] == dynamic_array[loop_index + 1]) {           // substitution of the non corretc element
            dynamic_array[loop_index] = '_';
            dynamic_array[backup_loop_index] = dynamic_array[loop_index];
            --backup_loop_index;
        } 
    }

    loop_index = 0;
    while (dynamic_array[loop_index] != '_' && loop_index < number_of_element) {    // determination of K
        number_of_right_element++;
        loop_index++;
    } 

    printf("Number of right element > %d \n", number_of_right_element);       

}
