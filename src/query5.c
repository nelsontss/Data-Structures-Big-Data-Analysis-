#include "query5.h"
#include <stdio.h>
#include <myuser.h>
#include <loader.h>

/**
@file query5.c
Implementação da query 5.
*/

/**
\brief Dado um id retorna os últimos 10 posts do user e a short bio.
@param com Estrutura de dados.
@param id ID do utilizador.
@returns Últimos 10 posts do user e short bio.
*/
USER get_user_info_aux(GHashTable* users, long id){
	char id_[10];
	sprintf(id_,"%ld", id);
	MyUser user = get_user(users,id_);
	USER r = toUSER(user);
	return r;
}
