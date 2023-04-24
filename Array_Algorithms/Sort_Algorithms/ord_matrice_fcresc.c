/**
 * @file ord_matrice_fcresc.c
 * @author Elia Renzoni
 * @brief 
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : Ordina matriche in ordine crescente o decrescente se contiene duplicati o meno, rispettivamente.
 * RESTRIZIONI => La ricerca di duplicati non puo' essere fatta su array ordinati. 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define  MAX_ELEMENTS  20
#define  TRUE          1
#define  FALSE         0

void bubblesort_crescente(int array[], int numero_elementi);
void bubblesort_decrescente(int array[], int numero_elementi);
int  controlla_duplicati(int array[], int numero_elementi);

int main(void) {

    int *array, 
         index, 
         acquisizione_errata, 
         numero_elementi,
         duplicati;

    do {
        printf("Inserisci il numero degli elementi dell'array > \n");
        scanf("%d", &numero_elementi);
        array = (int *)calloc(numero_elementi, sizeof(int));
        printf("Inserisci gli elementi > \n");
        
        index = 0;
        while (index < numero_elementi) {
            scanf("%d", &array[index]);
            index++;
        }

        acquisizione_errata = numero_elementi < 0 || numero_elementi > MAX_ELEMENTS;
        if (acquisizione_errata) {
            printf("Errore !\n");
            free(array);
        }
        while (getchar() != '\n');

    } while (acquisizione_errata);

    duplicati = controlla_duplicati(array, numero_elementi);

    switch(duplicati) {
        case TRUE:
            bubblesort_decrescente(array, numero_elementi);
            break;
        case FALSE:
            bubblesort_crescente(array, numero_elementi);
            break;
    }

    index = 0;
    printf("Array ordinato \n");
    while(index < numero_elementi) {
        printf("%d\t", array[index]);
        index++;
    }
    
    free(array);

    return (0);
}

/**
 * @brief controlla se gli elementi dell'array hanno duplicati o meno.
 * 
 */
int controlla_duplicati(int array[], int numero_elementi) {

    int duplicati = 0;
    int indice_i, indice_j;
    
    /* visita degli elementi */
    for (indice_i = 0; (indice_i < numero_elementi); indice_i++) {
        /* confronto con elementi */
        for (indice_j = 0; (indice_j < numero_elementi); indice_j++) {
            if (indice_j != indice_i)
                if (array[indice_j] == array[indice_i])
                    ++duplicati;
        }
    } 

    return ((duplicati > 0)? TRUE : FALSE);

}

/**
 * @brief bubblesort con relazione di ordinamento totale sul dominio delle chiavi pari a < 
 * 
 */
void bubblesort_crescente(int array[], int numero_elementi) {

    int tmp, i, j;

    for (i = 0; (i < numero_elementi); i++) {
        for (j = numero_elementi - 1; (j >= i); j--) {
            if (array[j] < array[j - 1]) {
                tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }
        }
    }

}

/**
 * @brief bubblesort con relazione di ordinamento totale sul dominio delle chiavi pari a > 
 * 
 */
void bubblesort_decrescente(int array[], int numero_elementi) {

    int tmp, j, i;

    for (i = 0; (i < numero_elementi); i++) {
        for (j = numero_elementi - 1; (j >= i); j--) {
            if (array[j] > array[j - 1]) {
                tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }
        }
    }

}
