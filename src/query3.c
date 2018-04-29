#include "query3.h"
#include <mypost.h>
#include <loader.h>
#include <compare_date.h>
#include <stdio.h>

/**
\brief Esta função calcula o número de perguntas e respostas durante um intervalo de tempo.
@param com Estrutura de dados.
@param begin Início do intervalo.
@param end Fim do intervalo.
@returns Um par com o número de perguntas e respostas.
*/
LONG_pair total_posts_aux(GList* posts_list, long * total_questions, long * total_answers , Date begin, Date end){
	long answers=0, questions=0;
	GList* aux= posts_list;

	if (begin == NULL && end == NULL)
		return (create_long_pair (*total_questions, *total_answers));
	else{
		if (end == NULL){
			while (aux != NULL && compare_date(get_post_data(aux->data), begin)>=0){
				if(get_post_type(aux->data)==1)
					questions++;
				else
					answers++;
				aux=aux->next;
			}
			return (create_long_pair (questions, answers));
		}
		else{
			if (begin == NULL){
				while (aux != NULL && compare_date(get_post_data(aux->data), end)>0)
					aux=aux->next;
				while (aux !=NULL){
					if(get_post_type(aux->data)==1)
						questions++;
					else
						answers++;
					aux=aux->next;
				}
			return (create_long_pair (questions, answers));
			}
		}
	}

	while (aux != NULL && compare_date(get_post_data(aux->data), end)>0)
		aux=aux->next;
	
	while (aux != NULL && compare_date(get_post_data(aux->data), begin)>=0){
				if(get_post_type(aux->data)==1)
					questions++;
				else
					answers++;
				aux=aux->next;
	}
	return (create_long_pair (questions, answers));
}
