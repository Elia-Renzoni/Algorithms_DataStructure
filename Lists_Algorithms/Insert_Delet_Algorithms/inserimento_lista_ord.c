/**
 * @file inserimento_lista_ord.c
 * @author Elia Renzoni
 * @brief Algoritmo di Inserimento in lista ordinata
 * @version 0.1
 * @date 2023-04-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define SENTINELLA -1

typedef struct nodi_ord {
    int              valore;
    struct nodi_ord *successore;
} nodi_ord_t;

nodi_ord_t *creazione_lista_ordinata(void);
int         inserimento_lista_ordinata(nodi_ord_t **, int);


int main(void) {

    nodi_ord_t *testa_lista;
    int         valore_inserire, esito_inserimento;

    testa_lista = creazione_lista_ordinata();

    printf("Inserisci un valore da inserire nella lista > \n");
    scanf("%d", &valore_inserire);
    esito_inserimento = inserimento_lista_ordinata(&testa_lista, valore_inserire);

    if (esito_inserimento == 1)
        printf("valore inserito con successo ! \n");
    else
        printf("Valore non inserito !\n");
    
    free(testa_lista); 

    return (0);
}

/**
 * @brief creazione della lista ordinata
 * 
 */
nodi_ord_t *creazione_lista_ordinata(void) {

    int         valore_inserire, valore_precedente, acquisizione_errata;
    nodi_ord_t *oggetto_lista, *testa_lista;

    printf("Inserisci dei numeri interi - in ordine crescente - -1 per terminare \n");
    scanf("%d", &valore_inserire);
    if (valore_inserire != SENTINELLA) {
        testa_lista = oggetto_lista = (nodi_ord_t *)malloc(sizeof(nodi_ord_t));
        oggetto_lista->valore = valore_inserire;
        
        scanf("%d", &valore_inserire);
        valore_precedente = valore_inserire;
        while (valore_inserire != SENTINELLA) {
            acquisizione_errata = valore_precedente > valore_inserire;
            if (acquisizione_errata)
                do {
                    printf("Errore, il nuovo valore deve esseere minore del precedente !\n");
                    while (getchar() != '\n');
                    scanf("%d", &valore_inserire);
                    acquisizione_errata = valore_precedente > valore_inserire;
                } while (acquisizione_errata);
            
            oggetto_lista = oggetto_lista->successore = (nodi_ord_t *)malloc(sizeof(nodi_ord_t));
            oggetto_lista->valore = valore_inserire;

            valore_precedente = valore_inserire;
            scanf("%d", &valore_inserire);
        }

        oggetto_lista->successore = NULL;
    }
    else
        testa_lista = NULL;
    
    return (testa_lista);

}

/**
 * @brief inserimento di un valore in una lista ordinata
 * 
 */
int inserimento_lista_ordinata(nodi_ord_t **testa_lista, int valore_inserire) {

    int         esito_inserimento;
    nodi_ord_t *oggetto_nuovo, *oggetto_lista, *oggetto_lista_prec;

    for (oggetto_lista_prec = oggetto_lista = *testa_lista; 
              (oggetto_lista != NULL && oggetto_lista->valore < valore_inserire); 
        oggetto_lista_prec = oggetto_lista, oggetto_lista = oggetto_lista->successore);

    if (oggetto_lista == NULL && oggetto_lista->valore == valore_inserire)
        esito_inserimento = 0;
    else {
        esito_inserimento = 1;
        oggetto_nuovo = (nodi_ord_t *)malloc(sizeof(nodi_ord_t));
        oggetto_nuovo->valore = valore_inserire;
        oggetto_nuovo->successore = oggetto_lista;

        if (oggetto_lista == *testa_lista)
            *testa_lista = oggetto_nuovo;
        else
            oggetto_lista_prec->successore = oggetto_nuovo;
    }

    return (esito_inserimento);

}

