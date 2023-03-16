/*
 *
 *  @author Elia Renzoni
 *  @date 16/03/2023
 *
 *  Problem : Insertion sort Array algorithm
 *
 *
 *
 *
 */



#include <stdio.h>

void insertsort(int array[], int numero_elementi);

int main(void) {

    int array[] = {42, 38, 11, 75, 99, 23, 84, 67};
    int num_element = 8;
    int cont;

    insertsort(array, num_element);

    //stampa array ord.
    for (cont = 0; (cont < num_element); cont++)
            printf("%d\n", array[cont]);


    return (0);
}


void insertsort(int array[], int numero_elementi) {

    int value_ins,
        f_index,
        s_index;
    
    for (f_index = 1; (f_index < numero_elementi); f_index++) {

        for (value_ins = array[f_index], s_index = f_index - 1;
                ((s_index >= 0) && (array[s_index] > value_ins));
            s_index--)
            array[s_index + 1] = array[s_index];
        
        if (s_index + 1 != f_index)
            array[s_index + 1] = value_ins;
    }
}