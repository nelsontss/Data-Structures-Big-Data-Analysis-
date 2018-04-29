#include "query7.h"
#include <stdlib.h>
#include <mypost.h>
#include <compare_date.h>
#include <pair.h>
#include <stdio.h>

int compare_answerCount(LONG_pair p1, LONG_pair p2){
	long lng1 = get_snd_long(p1);
	long lng2 = get_snd_long(p2);
	if (lng1<lng2)
		return 1;
	if (lng1==lng2)
		return 0;
	return -1;
}


int count_answers (MyPost p, Date begin, Date end){
	GList* resp = post_get_resp(p);
	GList* aux = resp;
	int r = 0;

	while(aux!=NULL){
		if(compare_date(get_post_data(aux->data), begin)>=0 && compare_date(get_post_data(aux->data), end)<=0){
			r++;
		}
		aux=aux->next;
	}

	return r;
}

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
	LONG_pair pair;

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
			if (get_post_type(aux->data)==1){
				postID = get_post_id(aux->data);
				pair = create_long_pair(strtol(postID, NULL, 10),count_answers(aux->data,begin,end));
				l = g_list_insert_sorted(l,pair,(GCompareFunc)compare_answerCount);
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
					pair = create_long_pair(strtol(postID, NULL, 10),count_answers(aux->data,begin,end));
					l = g_list_insert_sorted(l,pair,(GCompareFunc)compare_answerCount);
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
						pair = create_long_pair(strtol(postID, NULL, 10),count_answers(aux->data,begin,end));
						l = g_list_insert_sorted(l,pair,(GCompareFunc)compare_answerCount);
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
			pair = create_long_pair(strtol(postID, NULL, 10),count_answers(aux->data,begin,end));
			l = g_list_insert_sorted(l,pair,(GCompareFunc)compare_answerCount);
			free(postID);
		}
		aux=aux->next;
	}
	LONG_list lista = create_list(N);
	aux = l;
	while (i<N){
		set_list(lista, i, get_fst_long(aux->data));
		printf("--%d\n",get_snd_long(aux->data) );
		aux=aux->next;
		i++;
	}
	g_list_free_full(l,(GDestroyNotify)free_long_pair);
	return lista;
}