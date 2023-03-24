/**
 * @file media_elementi_array.c
 * @author Elia Renzoni (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-24
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problem : Dato un array di interi, restituire la media degli interi rimanenti dopo aver rimosso dal piu' piccolo il 50% e 
 * dal piu' grande il 50%. 
 * 
 */


#include <stdio.h>
#include <stdlib.h>

#define ARR_LENGHT_LIMIT_F     3
#define ARR_LENGHT_LIMIT_S     10
#define PERCENT_TOGLIERE       0.5

void selectsort(int array[], int num_element);
void media_elementi_array(int array[], int num_elementi, int *media);

int main(void) {

    int *d_array,
         num_elementi,
         index,
         acquisizione_errata;
    
    int  media_valori;
        
    do {
        printf("Inserisci il numero degli elementi > \n");
        scanf("%d", &num_elementi);
        d_array = (int *)calloc(num_elementi, sizeof(int));

        printf("Inserisci le chiavi > \n");
        index = 0;
        while (index < num_elementi) {
            scanf("%d", &d_array[index]);
            index++;
        }

        acquisizione_errata = num_elementi < ARR_LENGHT_LIMIT_F || num_elementi > ARR_LENGHT_LIMIT_S;

        if (acquisizione_errata) {
            printf("Errore ! \n");
            free(d_array);
        }
        
        while (getchar() != '\n');

    } while (acquisizione_errata);

    selectsort(d_array, num_elementi);

    media_elementi_array(d_array, num_elementi, &media_valori);
    printf("La media dei valori dell'array e' > %d \n", media_valori);


    return (0);

}

void selectsort(int array[], int elememti) {

    int valore_min, indice_val_minimo, i, j;

    for (i = 0; (i < elememti - 1); i++) {
        for (valore_min = array[i], j = i + 1; (j < elememti); j++) 
            if (array[j] < valore_min) {
                indice_val_minimo = j;
                valore_min = array[j];
            }
        
        if (indice_val_minimo != i) {
            array[indice_val_minimo] = array[i];
            array[i] = valore_min;
        }
    }
}


void media_elementi_array(int array[], int num_elementi, int *media) {

    int i, somma = 0;

    /* tolgo il 5% dal primo elemento (il piu' piccolo) e dall'ultimo elemento (il piu' grande) */
    for (i = 0; (i < num_elementi); i++) 

        if (i == num_elementi || i == 0)
            array[i] *= PERCENT_TOGLIERE;

    /* sommo i valori degli array*/
    for (i = 0; (i < num_elementi); i++) 
        somma += array[i];


    printf("somma : %d \n", somma);
    *media = somma / 2;

}
