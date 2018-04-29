#include "query4.h"
#include <compare_date.h>
#include <mypost.h>
#include <stdlib.h>
#include <loader.h>
#include <stdio.h>

/**
\brief Esta função procura dentro de um intervalo de tempo, as perguntas com a tag dada.
@param com Estrutura de dados.
@param tag Apontador para a tag.
@param begin Início do intervalo de tempo.
@param end Fim do intervalo de tempo.
@returns Lista de perguntas com tag.
*/
LONG_list questions_with_tag_aux(GList* posts_list, char* tag, Date begin, Date end, long total_questions){
GList* aux = posts_list;
	int i=0;
	LONG_list lista= create_list(total_questions);
	char * postID = "";
		
		

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
			if (get_post_type(aux->data)==1){
				if (post_contains_tag(aux->data, tag)==0){
					postID = get_post_id(aux->data);
					set_list(lista, i, strtol(postID, NULL, 10));
					free(postID);
					i++;
				}
			}
			
		aux=aux->next;
		}
	}
	else{
		if (begin==NULL){
			while (aux != NULL && compare_date(get_post_data(aux->data), end)>0)
				aux=aux->next;
			while (aux!=NULL){
				if (get_post_type(aux->data)==1)
					if (post_contains_tag(aux->data, tag)==0){
						postID = get_post_id(aux->data);
						set_list(lista, i, strtol(postID, NULL, 10));
						i++;
						free(postID);
				}
			aux=aux->next;
			}
		 }
		else{
			if (end==NULL){
				while (aux != NULL && compare_date(get_post_data(aux->data), begin)>=0){
					if (get_post_type(aux->data)==1){
						if (post_contains_tag(aux->data, tag)==0){
							postID = get_post_id(aux->data);
							set_list(lista, i, strtol(postID, NULL, 10));
							i++;
							free(postID);
						}
					}
				aux=aux->next;
				}
			}
			else{
		
					while (aux != NULL && compare_date(get_post_data(aux->data), end)>0){
							aux=aux->next;
					}
					while (aux != NULL && compare_date(get_post_data(aux->data), begin)>=0){
							if (get_post_type(aux->data)==1){
								if (post_contains_tag(aux->data, tag)==0){
									postID = get_post_id(aux->data);
									set_list(lista, i, strtol(postID, NULL, 10));
									i++;
									free(postID);
								}
							}
							aux=aux->next;
					}
		   		}
		   	}			
	aux=aux->next;
	}
	LONG_list r = create_list(i+1);
	int a = 0;
	for(a = 0 ; a<i;a++){
		set_list(r,a,get_list(lista,a));
	}
	set_list(r,a,-1);
	free_list(lista);
	return r;
}