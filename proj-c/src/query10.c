#include "query10.h"
#include <mypost.h>
#include <stdio.h>
#include <loader.h>

/**
@file query10.c
Implementação da query 10.
*/

/**
\brief Dado um id de uma pergunta retorna a resposta mais votada por utilizadores com melhor reputação.
@param com Estrutura de dados.
@param id ID da pergunta.
@returns Resposta mais votada.
*/
long better_answer_aux(GHashTable* posts, long id){
	char id_str[10];
	sprintf(id_str,"%ld",id);
	MyPost post = get_post(posts,id_str);
	return (long)get_best_answer(post);
}
