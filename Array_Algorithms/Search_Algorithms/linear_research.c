/*
 *
 *
 * 
 *  @author Elia Renzoni
 *  @date 23/03/2023
 * 
 *  Problem : Linear Research Algorithms - Arrays Algorithms
 * 
 * 
 * 
 * 
 */



#include <stdio.h>

#define NOT_FOUND -1


int linear_research(int array[], int number_of_element, int value_s);

int main(void) {

    int array[] = {1, 2, 10, 4, 5, 6, 9, 8, 7, 3};
    int value_search;
    int number_of_element = 10;
    int result;

    printf("Insert a value search > \n");
    scanf("%d", &value_search);
    while (value_search < 1) {
        while (getchar() != '\n');
        printf("The value must be maj of 1 \n");
        scanf("%d", &value_search);
    }

    result = linear_research(array, number_of_element, value_search);

    if (result != NOT_FOUND)
        printf("The values is present in the %d element !", result);
    else
        printf("Element not found ! ");

    return (0);
}

int linear_research(int array[], int num_element, int value) {

    int index_loop;

    for (index_loop = 0; 
            (index_loop < num_element && array[index_loop] != value);
         index_loop++) {}

    return ((index_loop < num_element)? 
                        index_loop : NOT_FOUND);

}