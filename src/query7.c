#include "query7.h"
#include <stdlib.h>
#include <mypost.h>
#include <compare_date.h>
#include <pair.h>
#include <stdio.h>






/**
\brief Encontra o top N de preguntas com mais respostas dentro de um intervalo de tempo.
@param com Estrutura de dados.
@param N Numero de utilizadores do top.
@param begin Início do intervalo.
@param end Fim do intervalo.
@returns Lista com o top de perguntas mais respondidas.
*/
LONG_list most_answered_questions_aux(GList* posts_list, int N, Date begin, Date end){
	GList* aux = posts_list;
	int i=0;
	GList* l= NULL;
	char * postID = "";

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
			if (get_post_type(aux->data)==1){
				postID = get_post_id(aux->data);
				l= g_list_prepend(l, aux->data);
				free(postID);
			}
			aux=aux->next;
		}
	}
	else{
		if (end==NULL){
			while (aux != NULL && compare_date(get_post_data(aux->data), begin)>=0){
				if (get_post_type(aux->data)==1){
					postID = get_post_id(aux->data);
					l= g_list_prepend(l, aux->data);
					free(postID);
				}
				aux=aux->next;
			}
		}
		else{
			if (begin==NULL){
				while (aux != NULL && compare_date(get_post_data(aux->data), end)>0)
					aux=aux->next;
				while (aux!=NULL){
					if (get_post_type(aux->data)==1){
						postID = get_post_id(aux->data);
						l= g_list_prepend(l, aux->data);
						free(postID);			
					}
					aux=aux->next;
				}			
			}
		}
	}
	while (aux != NULL && compare_date(get_post_data(aux->data), end)>0){
			aux=aux->next;
	}
	while (aux != NULL && compare_date(get_post_data(aux->data), begin)>=0){
		if (get_post_type(aux->data)==1){
			postID = get_post_id(aux->data);
			l= g_list_prepend(l, aux->data);
			free(postID);
		}
		aux=aux->next;
	}

	l = g_list_sort(l,(GCompareFunc)compare_answerCount);
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