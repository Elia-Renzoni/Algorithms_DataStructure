/*
 *	@author Elia Renzoni
 *	@date 31/05/2023
 *	@brief data una playlist di n canzoni, ordinare i brani in ordine crscente di aggiunta del brano,
 *	inserirlo in un albero BST e in una coda, cercare un brano da eliminare dalla playlist (albero BST)
 *      cercare un brano da riprodurre nella coda delle riproduzioni
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct {
	int id_brano, data_ins;
} info_playlist_t;

typedef struct playlist_tree {
	info_playlist_t chiave;
	struct playlist_tree *sx, *dx;
} playlist_tree_t;

typedef struct coda_riproduzioni {
	info_playlist_t valore;
	struct coda_riproduzioni *succ;
} coda_riproduzioni_t;

void crea_albero_playlist(playlist_tree_t **, int, int);
void crea_coda_riproduzioni(coda_riproduzioni_t **, coda_riproduzioni_t **, int, int);
void heapsort(info_playlist_t *, int);
void setaccia_heap(info_playlist_t *, int, int);
coda_riproduzioni_t *riproduci_brano(coda_riproduzioni_t **, coda_riproduzioni_t **);
int rimozione_brano_playlist(playlist_tree_t **, int);

int main(void) {

	playlist_tree_t *radice = NULL;
	coda_riproduzioni_t *uscita = NULL, *ingresso = NULL, *brano;
	int numero_elementi, contatore, esito_lettura, acq_err, brano_eliminare;
	info_playlist_t dati_brani, *elenco_brani;

	do {
		printf("Inserisci il numero dei brani da aggiungere > \n");
		esito_lettura = scanf("%d", &numero_elementi);
		printf("Inserisci il brano da eliminare > \n");
		esito_lettura = scanf("%d", &brano_eliminare);
		acq_err = esito_lettura != 1 || numero_elementi < 1 || numero_elementi >= (INT_MAX / 2) || brano_eliminare < 1 || brano_eliminare >= INT_MAX;
		if (acq_err)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (acq_err);
	
	elenco_brani = (info_playlist_t *)calloc(numero_elementi + 1, sizeof(info_playlist_t));
	if (elenco_brani != NULL) {
		srand(time(NULL));
		for (contatore = 1; (contatore <= numero_elementi); contatore++) {
			dati_brani.id_brano = rand() % (numero_elementi * numero_elementi);
			dati_brani.data_ins = rand() % numero_elementi;
			elenco_brani[contatore] = dati_brani;
		}
		heapsort(elenco_brani, numero_elementi);
		for (contatore = 1; (contatore <= numero_elementi); contatore++) {
			crea_albero_playlist(&radice, elenco_brani[contatore].id_brano, elenco_brani[contatore].data_ins);
			crea_coda_riproduzioni(&uscita, &ingresso, elenco_brani[contatore].id_brano, elenco_brani[contatore].data_ins);
		}
		printf("%d\n", rimozione_brano_playlist(&radice, brano_eliminare));
		brano = riproduci_brano(&uscita, &ingresso);
		printf("stai ascoltando il brano %d \n", brano->valore.id_brano);
		free(brano);
	}	
	else 
		printf("Errore : Puntatore a NULL \n");

	return (0);

}

void crea_albero_playlist(playlist_tree_t **radice, int id_nuovo_brano, int data_nuovo_brano) {

	playlist_tree_t *nodo, *nodo_padre, *nuovo_nodo;

	for (nodo_padre = nodo = *radice; 
			(nodo != NULL); 
			nodo_padre = nodo, nodo = (id_nuovo_brano < nodo->chiave.id_brano)? nodo->sx : nodo->dx);

	if (nodo == NULL) {
		nuovo_nodo = (playlist_tree_t *)malloc(sizeof(playlist_tree_t));
		nuovo_nodo->chiave.id_brano = id_nuovo_brano;
		nuovo_nodo->chiave.data_ins = data_nuovo_brano;
		nuovo_nodo->sx = nuovo_nodo->dx = NULL;
		if (nodo == *radice)
			*radice = nuovo_nodo;
		else
			if (id_nuovo_brano < nodo_padre->chiave.id_brano)
				nodo_padre->sx = nuovo_nodo;
			else 
				nodo_padre->dx = nuovo_nodo;
	}

}

void crea_coda_riproduzioni(coda_riproduzioni_t **uscita, coda_riproduzioni_t **ingresso, int id_brano, int data_brano) {

	coda_riproduzioni_t *nuovo_elem = (coda_riproduzioni_t *)malloc(sizeof(coda_riproduzioni_t));
	nuovo_elem->valore.id_brano = id_brano;
	nuovo_elem->valore.data_ins = data_brano;
	nuovo_elem->succ = NULL;
	if (*ingresso != NULL)
		(*ingresso)->succ = nuovo_elem;
	else
		*uscita = nuovo_elem;
	*ingresso = nuovo_elem;

}

void heapsort(info_playlist_t *brani_playlist, int numero_elementi) {
	
	int sx, dx, tmp;

	for (sx = numero_elementi / 2; (sx >= 1); sx--)
		setaccia_heap(brani_playlist, sx, numero_elementi);
	for (dx = numero_elementi; (dx > 1); dx--) {
		tmp = brani_playlist[1].id_brano;
		brani_playlist[1].id_brano = brani_playlist[dx].id_brano;
		brani_playlist[dx].id_brano = tmp;
		setaccia_heap(brani_playlist, 1, dx - 1);
	}
}

void setaccia_heap(info_playlist_t *brani_playlist, int sx, int dx) {

	int nuovo_valore, i, j;

	for (nuovo_valore = brani_playlist[sx].id_brano, i = sx, j = 2 * i; (j <= dx);) {
		if ((j < dx) && (brani_playlist[j + 1].id_brano > brani_playlist[j].id_brano)) {
			j++;
		}
		if (nuovo_valore < brani_playlist[j].id_brano) {
			brani_playlist[i].id_brano = brani_playlist[j].id_brano;
			i = j;
			j = 2 * i;
		}
		else 
			j = dx + 1;
	}
	if (i != sx)
		brani_playlist[i].id_brano = nuovo_valore;


}

coda_riproduzioni_t *riproduci_brano(coda_riproduzioni_t **uscita, coda_riproduzioni_t **ingresso) {

	coda_riproduzioni_t *brano = *uscita;
	if (*uscita != NULL) {
		*uscita = (*uscita)->succ;
		if (*uscita == NULL)
			*ingresso = NULL;
	}

	return (brano);
}

int rimozione_brano_playlist(playlist_tree_t **radice, int id_brano_r) {

	playlist_tree_t *nodo, *nodo_padre, *nodo_sost;
	int esito_rimozione;

	for (nodo_padre = nodo = *radice; 
			((nodo != NULL) && (nodo->chiave.id_brano != id_brano_r));
	    nodo_padre = nodo, nodo = (id_brano_r < nodo->chiave.id_brano)? nodo->sx : nodo->dx);

	if (nodo == NULL)
		esito_rimozione = 0;
	else {
		esito_rimozione = 1;
		if (nodo->sx == NULL) {
			if (nodo == *radice)
				*radice = nodo->dx;
			else 
				if (id_brano_r < nodo->chiave.id_brano)
					nodo_padre->sx = nodo->dx;
				else
					nodo_padre->dx = nodo->dx;
		}
		else {
			if (nodo->dx == NULL) {
				if (nodo == *radice)
					*radice = nodo->sx;
				else
					if (id_brano_r < nodo->chiave.id_brano)
						nodo_padre->sx = nodo->sx;
					else
						nodo_padre->dx = nodo->sx;
			}
			else {
				nodo_sost = nodo;
				for (nodo_padre = nodo_sost, nodo = nodo_sost->sx; 
						(nodo->dx != NULL); 
				    nodo_padre = nodo, nodo = nodo->dx);
				nodo_sost->chiave.id_brano = nodo->chiave.id_brano;
				if (nodo_padre == nodo_sost)
					nodo_padre->sx = nodo->sx;
				else 
					nodo_padre->dx = nodo->sx;
			
			}
		}
		free(nodo);
	}

	return (esito_rimozione);

}
