/*
 *
 *
 *  @author Elia Renzoni
 *  @date 23/03/2023
 *
 *
 *  Problem : Binary research Array Algorithm
 *
 *
 *
 */


#include <stdio.h>

#define NOT_FOUND -1

int binary_research(int array[], int num_of_element, int value);

int main(void) {

    int array[] = {10, 15, 20, 24, 32, 50};
    int num_element = 6;
    int value_search;
    int result;

    printf("Insert a Value > \n");
    scanf("%d", &value_search);


    result = binary_research(array, num_element, value_search);
   
    if (result != NOT_FOUND)
        printf("The value is in the %d element !", result);
    else
        printf("The value is not present !");


    return (0);
}

int binary_research(int array[], int num_element, int value_s) {

    int index_sx,
        index_dx,
        index_mx;

    for (index_sx = 0, index_dx = num_element - 1, index_mx = (index_sx + index_dx) / 2;
            ((index_sx < index_dx) && (array[index_mx] != value_s));
         index_mx = (index_sx + index_mx) / 2)

         if (index_mx > value_s)
            index_dx = index_mx - 1;
         else
            index_sx = index_mx + 1;

    return ((index_sx < index_dx)? 
                    index_mx : NOT_FOUND);
    
}
