/*
 *
 *  @author Elia Renzoni
 *  @date 12/03/2023
 *
 *  Problem : Simple Visit Algorithm of a static array
 *
 *
 *
 *
*/


#include <stdio.h>

#define ARR_LNGHT 7

void visit_array(int array[], int number_of_element);

int main(void) {

    int array[ARR_LNGHT];
    int number_of_element = 7;
    int cnt_loop;

    printf("Insert %d values > \n", number_of_element);
    cnt_loop = 0;
    while (cnt_loop < 7) {
        scanf("%d", &array[cnt_loop]);
        cnt_loop++;
    }

    //pre
    if (cnt_loop <= 7)
            visit_array(array, number_of_element);
    else
        printf("Something Wrong ! \n");



    return (0);
}

void visit_array(int array[], int number_of_elem) {

    int index;

    for (index = 0; (index < number_of_elem); index++)
            printf("%d \n", array[index]);

}
