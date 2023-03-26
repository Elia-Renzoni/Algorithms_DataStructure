/**
 * @file selectsort.c
 * @author Elia Renzoni
 * @brief 
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * Problem : Selecsort example
 * 
 */

#include <stdio.h>
#define ARR_ELEM 8

void selectsort(int array[], int num_of_element);

int main(void) {

    int array[] = {42, 38, 11, 75, 99, 23, 84, 67};
    int num_elemnts = ARR_ELEM;
    int index;

    selectsort(array, num_elemnts);

    index = 0;
    while (index < num_elemnts) {
        printf("%d\n", array[index]);
        index++;
    }


    return (0);
}

void selectsort(int array[], int num_of_element) {

    int min_value,
        index_min_value,
        ex_index,
        in_index;

    for (ex_index = 0; (ex_index < num_of_element - 1); ex_index++) {

        for (min_value = array[ex_index], index_min_value = ex_index, in_index = ex_index + 1;
                (in_index < num_of_element);
             in_index++)

            if (array[in_index] < min_value) {
                min_value = array[in_index];
                index_min_value = in_index;
            }

        if (index_min_value != ex_index) {
            array[index_min_value] = array[ex_index];
            array[ex_index] = min_value;
        }
    }

}



