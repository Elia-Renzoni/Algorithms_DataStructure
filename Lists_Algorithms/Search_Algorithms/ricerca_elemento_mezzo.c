/**
 * @file ricerca_elemento_mezzo.c
 * @author Elia Renzoni (elia.renzoni03@gmail.cpm)
 * @brief 
 * @version 0.1
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : restituire l'indirizzo dell'elememento di mezzo di una lita concatenata, in caso di assenza di tale elemento restituire
 * l'indirizzo di memoria dell'elemento dopo la testa.
 * 
 */


#include <stdio.h>
#include <stdlib.h>

#define SENTINELLA '-'

typedef struct lista_char {
    char               valori;
    struct lista_char *successivo;
} caratteri_t;

caratteri_t *creazione_lista(int *);
caratteri_t *ricerca_sequenziale(caratteri_t *, int *);

int main(void) {


    caratteri_t *testa_lsita_sing_concat,
                *indirizzo_oggetto_lista;
    int          numero_oggetti = 1;

    testa_lsita_sing_concat = creazione_lista(&numero_oggetti);
    indirizzo_oggetto_lista = ricerca_sequenziale(testa_lsita_sing_concat, &numero_oggetti);

    printf("valore >  : %d", indirizzo_oggetto_lista);

    free(testa_lsita_sing_concat);

    return (0);
}

/**
 * @brief creazione lista concatenata
 * 
 */
caratteri_t *creazione_lista(int *numero_liste) {

    caratteri_t *testa_lista,
                *oggetto_lista;
    char         valore_inserire;


    scanf("%c", &valore_inserire);
    if (valore_inserire != SENTINELLA) {

        testa_lista = oggetto_lista = (caratteri_t *)malloc(sizeof(caratteri_t));
        oggetto_lista->valori = valore_inserire;

        for (scanf("%c", &valore_inserire); (valore_inserire != SENTINELLA); scanf("%c", &valore_inserire)) {
            ++numero_liste;
            oggetto_lista->successivo = (caratteri_t *)malloc(sizeof(caratteri_t));
            oggetto_lista->successivo->valori = valore_inserire;
        }

        oggetto_lista->successivo = NULL;
    }
    else
        testa_lista = NULL;


    return (testa_lista);

}

/**
 * @brief algoritmo di ricerca, restituisce l'elemento di mezzo della lista (indirizzo), altrimenti il secondo
 * 
 */
caratteri_t *ricerca_sequenziale(caratteri_t *testa_lista, int *numero_liste) {

    caratteri_t *oggetto_lista;
    int          media = *numero_liste / 2;
    int          contatore;

    if (media > 1) {
        for (oggetto_lista = testa_lista, contatore = 1; (contatore != media); oggetto_lista->successivo);
        return (oggetto_lista);
    }
    else {
        oggetto_lista = testa_lista;
        oggetto_lista = oggetto_lista->successivo;
        return (oggetto_lista);
    }

}