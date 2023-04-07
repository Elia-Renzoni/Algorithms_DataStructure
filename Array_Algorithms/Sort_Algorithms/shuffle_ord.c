/**
 * @file shuffle_ord.c
 * @author Elia Renzoni
 * @brief 
 * @version 0.1
 * @date 2023-03-24
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : Alice ha un certo numero di carte e vuole riorganizzare le carte in gruppi, in modo che ogni gruppo sia di dimensione groupsize e 
 * sia composto da groupsize carte consecutive. Dato un array di interi, dove il generico elemento i-esimo e' il valore delle carte, determinare
 * se si puo' ordinare o meno (true or false).
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define  TRUE               1
#define  FALSE              0
#define  ARR_LENGHT_MIN     1
#define  ARR_LENGHT_MAX     20

int  controlla_miscuglio(int numero_elementi, int dimensione_mazzo);
void selectsort(int array[], int numero_elementi);

int main(void) {

    int *carte,
         numero_elementi,
         index,
         acquisizione_errata,
         risultato,
         dimesione_mazzo;

    do {
        printf("Inserisci il numero degli elementi > \n");
        scanf("%d", &numero_elementi);

        carte = (int *)calloc(numero_elementi, sizeof(int));

        printf("Inserisci i valori delle carte > \n");
        index = 0;
        while (index < numero_elementi) {
            scanf("%d", &carte[index]);
            index++;
        }

        printf("Inserisci la dimensione di ogni mazzo > \n");
        scanf("%d", &dimesione_mazzo);

        acquisizione_errata = numero_elementi < ARR_LENGHT_MIN || numero_elementi > ARR_LENGHT_MAX || dimesione_mazzo < 1;

        if (acquisizione_errata) {
            printf("Errore ! \n");
            free(carte);
        }

        while (getchar() != '\n');

    } while (acquisizione_errata);

    selectsort(carte, numero_elementi);
    risultato = controlla_miscuglio(numero_elementi, dimesione_mazzo);

    if (risultato)
        printf("Miscuglio fatto ! \n");
    else 
        printf("Miscuglio Impossibile ! \n");


    free(carte);
    
    return (0);

}

/**
 * @brief ordinamento per selezione
 * 
 * @param carte 
 * @param numero_elementi 
 */
void selectsort(int carte[], int numero_elementi) {

    int i, j, valore_min, indice_valore_minimo;

    for (i = 0; (i < numero_elementi - 1); i++) {
        for (valore_min = carte[i], j = i + 1, indice_valore_minimo = i; (j < numero_elementi); j++) {
            if (carte[j] < valore_min) {
                indice_valore_minimo = j;
                valore_min = carte[j];
            }
        }
        if (indice_valore_minimo != i) {
            carte[indice_valore_minimo] = carte[i];
            carte[i] = valore_min;
        }
    }
}

/**
 * @brief controlla se é possibile dividere il mazzo in n carte. 
 * 
 * @param numero_elementi 
 * @param miscuglio 
 * @return int 
 */

int controlla_miscuglio(int numero_elementi, int miscuglio) {

    return ((numero_elementi % miscuglio == 0)? TRUE : FALSE);

}

