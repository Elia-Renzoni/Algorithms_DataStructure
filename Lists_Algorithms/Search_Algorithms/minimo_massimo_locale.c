/**
 * @file minimo_massimo_locale.c
 * @author Elia Renzoni (elia.renzoni03@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-09
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : Ricerca di un minimo o massimo locale
 * 
 * 
 **/

#include <stdio.h>
#include <stdlib.h>

#define  MAX_LENGHT   2
#define  SENTINELLA  -1

typedef struct min_max_l {
    int               valore;
    struct min_max_l *precedente, *successivo;
} valori_t;

valori_t *creazione_lista(void);
void      min_max_locale(valori_t *);

int main(void) {

    valori_t *testa_lista;

    testa_lista = creazione_lista();
    min_max_locale(testa_lista);

    free(testa_lista);
 
    return (0);
}

/**
 * @brief creazione lista doppiamente concatenata
 * 
 */
valori_t *creazione_lista(void) {

    valori_t *testa_lista, *oggetto_lista, *indirizzo_supporto;
    int       valore;

    scanf("%d", &valore);
    if (valore != SENTINELLA) {

        testa_lista = oggetto_lista = (valori_t *)malloc(sizeof(valori_t));
        oggetto_lista->precedente = NULL;
        oggetto_lista->valore = valore;

        for (scanf("%d", &valore); (valore != SENTINELLA); scanf("%d", &valore)) {
            indirizzo_supporto = oggetto_lista;
            oggetto_lista = oggetto_lista->successivo = (valori_t *)malloc(sizeof(valori_t));
            oggetto_lista->precedente = indirizzo_supporto;
            oggetto_lista->valore = valore;
        }

        oggetto_lista->precedente = indirizzo_supporto;
        oggetto_lista->successivo = NULL;
    }
    else 
        testa_lista = NULL;
    
    return (testa_lista);
 
}

/**
 * @brief ricerca del minimo e massimo locale
 * 
 */
void min_max_locale(valori_t *testa) {

    valori_t *oggetto_lista;
    int       tmp_valore_min, tmp_valore_max, tmp1, tmp2;


    oggetto_lista = testa;
    while (oggetto_lista != NULL) {

        if (oggetto_lista != testa) {

            oggetto_lista = oggetto_lista->precedente;
            tmp1 = oggetto_lista->valore;
            oggetto_lista = oggetto_lista->successivo;
            oggetto_lista = oggetto_lista->successivo;
            tmp2 = oggetto_lista->valore;
            oggetto_lista = oggetto_lista->precedente;

            if ((oggetto_lista->valore < tmp1) && (oggetto_lista->valore < tmp2)) 
                tmp_valore_min = oggetto_lista->valore;
            else if ((oggetto_lista->valore > tmp1) && (oggetto_lista->valore > tmp2)) 
                tmp_valore_max = oggetto_lista->valore;
            else 
                tmp_valore_max, tmp_valore_min = -1;

            oggetto_lista = oggetto_lista->successivo;
        }
        else 
            oggetto_lista = oggetto_lista->successivo;
    }

    printf("Minimo %d \n Massimo %d \n", tmp_valore_min, tmp_valore_max);

}