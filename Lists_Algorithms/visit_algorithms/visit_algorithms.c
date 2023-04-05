/**
 * @file visit_algorithms.c
 * @author Elia Renzoni (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : Implementazione di un semplice algortimo di visita per liste concatenate
 * 
 */


#include <stdio.h>
#include <stdlib.h>

#define  SENTINELLA -1

typedef struct lista_nodo {
    int                numeri_acq;
    struct lista_nodo *successivo;
} numeri_t;

numeri_t *riempimento_lista(void);
void      visita_lista(numeri_t *);


int main(void) {

    numeri_t *testa;

    printf("Inserisci dei numeri interi, quando vuoi finire digita -1 > \n");
    testa = riempimento_lista();
    visita_lista(testa);


    return (0);

}

numeri_t *riempimento_lista(void) {

    numeri_t *elemento,
             *testa_lista;
    int       numero;

    printf("Inserisci i numeri > \n");
    scanf("%d", &numero);

    if (numero == SENTINELLA) {
        elemento = NULL;
    } 
    else {
        testa_lista = elemento = (numeri_t *)malloc(sizeof(numeri_t));
        elemento->numeri_acq = numero;

        for (scanf("%d", &numero); (numero != SENTINELLA); scanf("%d", &numero)) {
             elemento = elemento->successivo = (numeri_t *)malloc(sizeof(numeri_t));
             elemento->numeri_acq = numero;
        }

        elemento = elemento->successivo = (numeri_t *)malloc(sizeof(numeri_t));
        elemento->successivo = NULL;
    }

    return (testa_lista);

}

void visita_lista(numeri_t *testa) {

    numeri_t *elemento;

    for (elemento = testa; (elemento != NULL); elemento = elemento->successivo)
            printf("%d\n", elemento->numeri_acq);

}