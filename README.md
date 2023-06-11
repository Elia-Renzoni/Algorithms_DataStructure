# Algorithms and Data Structure 
> * Exercises of Algorithms and Data Structure Teaching. University of Urbino - Bachelor's Degree in Applied Computer Science
> * Sequentail and Deterministic Algorithms. 

## Array Algorithms > 
| Search Algorithms | Sort Algorithms |
|-------------------|-----------------|
| Linear Search     | Insert Sort     |
| Binary Search     | Select Sort     |
|                   | Bubble Sort     |
|                   | Merge Sort      |
|                   | Quick Sort      |
|                   | Heap Sort       |

* Linear Search : 
```C
int linear_research(int array[], int num_element, int value) {

    int index_loop;

    for (index_loop = 0; 
            (index_loop < num_element && array[index_loop] != value);
         index_loop++) {}

    return ((index_loop < num_element)? 
                        index_loop : NOT_FOUND);

}
```
* Binary Search : 
```C
int binary_research(int array[], int num_element, int value_s) {

    int index_sx,
        index_dx,
        index_mx;

    for (index_sx = 0, index_dx = num_element - 1, index_mx = (index_sx + index_dx) / 2;
            ((index_sx < index_dx) && (array[index_mx] != value_s));
         index_mx = (index_sx + index_mx) / 2)

         if (array[index_mx] > value_s)
            index_dx = index_mx - 1;
         else
            index_sx = index_mx + 1;

    return ((index_sx < index_dx)? 
                    index_mx : NOT_FOUND);
    
}
```
* Insert Sort : 
```C
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
```
* Select Sort : 
```C
void selectsort(int array[], int num_of_element) {

    int min_value,
        index_min_value,
        ex_index,
        in_index;

    for (ex_index = 0; (ex_index < num_of_element - 1); ex_index++) {

        for (min_value = array[ex_index], index_min_value = ex_index, in_index = ex_index + 1;
                (in_index < num_of_element);
             in_index++)

            if (array[in_index] < min_value) {
                min_value = array[in_index];
                index_min_value = in_index;
            }

        if (index_min_value != ex_index) {
            array[index_min_value] = array[ex_index];
            array[ex_index] = min_value;
        }
    }

}
```
* Bubble Sort : 
```C
/**
 * @brief bubblesort algorithm => T(n) = O(n^2)
 * 
 */
void bubblesort(int array[], int num_elements) {

    int tmp, i, j;

    for (i = 1; (i < num_elements); i++) {

        for (j = num_elements - 1; (j >= i); j--)
        
            if (array[j] < array[j - 1]) {
                tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }

    }

}
```
* Merge Sort : 
```C
/**
 * @brief implementazione dell'algoritmo di ordinamento merge sort
 * 
 */
void merge_sort(int numeri[], int sx, int dx) {

    int mx;

    if (sx < dx) {
        mx = (sx + dx) / 2;
        merge_sort(numeri, sx, mx);
        merge_sort(numeri, mx + 1, dx);
        merge(numeri, sx, mx, dx);
    }

}

/**
 * @brief implementazione della funzione di fusione ordinata
 * 
 */
void merge(int numeri[], int sx, int mx, int dx) {

    int *appoggio, i, j, k;

    appoggio = (int *)calloc(dx + 1, sizeof(int));

    for (i = sx, j = mx + 1, k = 0; ((i <= mx) && (j <= dx)); k++) {

        if (numeri[i] <= numeri[j]) {
            appoggio[k] = numeri[i];
            i++;
        }
        else {
            appoggio[k] = numeri[j];
            j++;
        }
    }

    while (i <= mx) {
        appoggio[k] = numeri[i];
        i++;
        k++;
    }

    while (j <= dx) {
        appoggio[k] = numeri[j];
        j++;
        k++;
    }

    for (k = sx; (k <= dx); k++) 
        numeri[k] = appoggio[k - sx];

    free(appoggio);

}
```
* Heap Sort : 
```C
/**
 * @brief heap-sort
 * 
 */
void heap_sort(int numeri[], int numero_elementi) {

    int index_sx,
        index_dx,
        tmp;

    /* prima fase : creazione max-heap */
    for (index_sx = numero_elementi / 2; (index_sx >= 1); index_sx--)
        crea_heap(numeri, index_sx, numero_elementi);

    /* seconda fase : ordinamento dell'array */
    for (index_dx = numero_elementi; (index_dx > 1); index_dx--) {
        tmp = numeri[1];
        numeri[1] = numeri[index_dx];
        numeri[index_dx] = tmp;

        crea_heap(numeri, 1, index_dx - 1);
    }


}

/**
 * @brief funzione che fa rispettare le prop. del Max - Heap
 * 
 */
void crea_heap(int numeri[], int sx, int dx) {

    int valore_max, i, j;

    for (valore_max = numeri[sx], i = sx, j = 2 * i; 
            (j <= dx);) {

                if ((j < dx) && (numeri[j + 1] > numeri[j]))  /* determino il maggiore tra i figli */
                    j++;

                if (valore_max < numeri[j]) {      /* confronto il maggiore tra i figli con il nodo gen. */

                    numeri[i] = numeri[j];
                    i = j;
                    j = 2 * i;
                }
                else 
                    j = dx + 1;    /* la condizione diventa falsa */

    }

    if (i != sx)
        numeri[i] = valore_max;
}

```

## List Algorithms > 

* Visit Algorithm : 
```C
void visita_lista(numeri_t *testa) {

    numeri_t *elemento;

    for (elemento = testa; (elemento != NULL); elemento = elemento->successivo)
            printf("%d\n", elemento->numeri_acq);

}
```
* Search Algorithm : 
```C
elem_t *ricerca_inlista(elem_t *testa_lista, int valore_ricercare) {

	elem_t *oggetto_lista;

	for (oggetto_lista = testa_lista; 
		 (oggetto_lista != NULL && oggetto_lista->numeri != valore_ricercare); 
		  oggetto_lista = oggetto_lista->successore);

	return (oggetto_lista);
}
```
* Insert Algorithm : 
```C
int inserimento_lista_ordinata(nodi_ord_t **testa_lista, int valore_inserire) {

    int         esito_inserimento;
    nodi_ord_t *oggetto_nuovo, *oggetto_lista, *oggetto_lista_prec;

    for (oggetto_lista_prec, oggetto_lista = *testa_lista; 
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
```
* Delete Algorithm : 
```C
int rimozione_elementi(elementi_t **testa_lista, int valore_da_rimuovere) {

	elementi_t *oggetto_lista, *oggetto_precedente;
	int         esito_rimozione;

	for (oggetto_precedente = oggetto_lista = *testa_lista; 
						((oggetto_lista != NULL) && (oggetto_lista->valore != valore_da_rimuovere)); 
								oggetto_precedente = oggetto_lista, oggetto_lista = oggetto_lista->successivo);

	if (oggetto_lista == NULL || oggetto_lista->valore != valore_da_rimuovere)
		esito_rimozione = 0;
	else {

		esito_rimozione = 1;
		if (oggetto_lista == *testa_lista) 
			*testa_lista = oggetto_lista->successivo;
		else 
			oggetto_precedente->successivo = oggetto_lista->successivo;

		free(oggetto_lista);
	}

	return (esito_rimozione);

}
```
* Queue Insert Algorithm : 
```C
void creazione_coda(coda_t **uscita, coda_t **ingresso, int valore_inserire) {

	coda_t *oggetto_nuovo = (coda_t *)malloc(sizeof(coda_t));
	oggetto_nuovo->valore = valore_inserire;
	oggetto_nuovo->successivo = NULL;

	if (*ingresso != NULL)
		(*ingresso)->successivo = oggetto_nuovo;
	else
		*uscita = oggetto_nuovo;
	*ingresso = oggetto_nuovo;


}
```
* Queue Remove Algorithm : 
```C
coda_t *eliminazione_elem_coda(coda_t **uscita, coda_t **ingresso) {

	coda_t *oggetto_lista = *uscita;

	if (*uscita != NULL) {
		*uscita = (*uscita)->successivo;
		if (*uscita == NULL)
			*ingresso = NULL;
	}

	return (oggetto_lista);
}
```
* Stack Insert Algorithm : 
```C
void creazione_stack(stack_t **cima, char parentesi) {

  stack_t *nuovo_oggetto = (stack_t *)malloc(sizeof(stack_t));
  nuovo_oggetto->parentesi = parentesi;
  nuovo_oggetto->successivo = *cima;
  *cima = nuovo_oggetto;

}
```
* Stack Remove Algorithm : 
```C
stack_t *elminazione_elem_stack(stack_t **cima) {

	stack_t *oggetto_elimi = *cima;
	if (*cima != NULL)
		*cima = (*cima)->successivo;

	return (oggetto_elimi);

}
```

## Tree Algorithms > 



## Graph Algorithms > 


## Hash Algorithms >
