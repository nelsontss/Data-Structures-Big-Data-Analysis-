#include "query7.h"
#include <stdlib.h>
#include <mypost.h>
#include <date_to_int.h>

LONG_list most_answered_questions_aux(GList* posts_list, int N, Date begin, Date end){
	GList* aux = posts_list;
	int i=0;
	GList* l= NULL;
	char * postID = "";

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
			if (get_post_type(aux->data)==1)
				l= g_list_insert_sorted(l, aux->data, (GCompareFunc)compare_answerCount);
			aux=aux->next;
		}
	}
	else{
		if (end==NULL){
			while (aux != NULL && get_post_data(aux->data) >= (date_to_int (begin))){
				if (get_post_type(aux->data)==1)
					l= g_list_insert_sorted(l, aux->data, (GCompareFunc)compare_answerCount);
				aux=aux->next;
			}
		}
		else{
			if (begin==NULL){
				while (aux != NULL && get_post_data(aux->data) < (date_to_int (end)))
					aux=aux->next;
				while (aux!=NULL){
					if (get_post_type(aux->data)==1)
						l= g_list_insert_sorted(l, aux->data, (GCompareFunc)compare_answerCount);
					aux=aux->next;
				}			
			}
		}
	}
	while (aux != NULL && get_post_data(aux->data) > (date_to_int (end))){
			aux=aux->next;
	}
	while (aux != NULL && get_post_data(aux->data) >= (date_to_int (begin))){
		if (get_post_type(aux->data)==1)
			l= g_list_insert_sorted(l, aux->data, (GCompareFunc)compare_answerCount);
		aux=aux->next;
	}
	LONG_list lista = create_list(N);
	aux = l;
	while (i<N){
		postID = get_post_id(aux->data);
		set_list(lista, i, strtol(postID, NULL, 10));
		aux=aux->next;
		i++;
		free(postID);
	}
	g_list_free(l);
	return lista;
}