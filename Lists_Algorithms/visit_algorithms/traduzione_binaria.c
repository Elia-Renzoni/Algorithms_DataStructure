/**
 * @file traduzione_binaria.c
 * @author Elia Renzoni elia.renzoni03@gmail.com
 * @brief 
 * @version 0.1
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : Convertire in decimale i numeri binari contenuti in una lista concatenata.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SENTINELLA -1

typedef struct numeri_binari {
    int                   numero_binario;
    struct numeri_binari *successivo;
} binario_t;

binario_t *creazione_lista(void);
void       ricerca_e_traduzione(binario_t *);

int main(void) {

    binario_t *testa_lista_sing_concat;


    printf("Inserisci dei numeri binari (1 e 0) e quando vuoi terminare inserisci -1 > \n");
    testa_lista_sing_concat = creazione_lista();
    ricerca_e_traduzione(testa_lista_sing_concat);

    free(testa_lista_sing_concat);

    return (0);
}


/**
 * @brief creazione di una lista singolarmente concatenata, contenente cifre binarie.
 * 
 */
binario_t *creazione_lista(void) {

    binario_t   *testa_lista,
                *oggetto_lista;
    int          valore_bin;

    scanf("%d", &valore_bin);
    if (valore_bin != SENTINELLA) {

        testa_lista = oggetto_lista = (binario_t *)malloc(sizeof(binario_t));
        oggetto_lista->numero_binario = valore_bin;
    }

    
    for (scanf("%d", &valore_bin); (valore_bin != SENTINELLA); scanf("%d", &valore_bin)) {
        oggetto_lista = oggetto_lista->successivo = (binario_t *)malloc(sizeof(binario_t));
        oggetto_lista->numero_binario = valore_bin;
    }

    oggetto_lista->successivo = NULL;

    return (testa_lista);
        
}

/**
 * @brief definizione della funzione per tradurre i numeri binari in base 10.
 * 
 */
void ricerca_e_traduzione(binario_t *testa_lista) {

    binario_t *oggetto_lista;
    int        valori_dominanti = 0;
    int        sum = 0;

    for (oggetto_lista = testa_lista; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo) {

        if (oggetto_lista->numero_binario == 1) 
            sum += pow(2, valori_dominanti);
        
        ++valori_dominanti;
        
    }

    printf("Il numero Convertito é > %d", sum);

}