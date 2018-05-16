#include "query2.h"
#include <myuser.h>
#include <stdlib.h>

/**
@file query2.c
Implementação da query 2.
*/

/**
\brief Esta função encontra o top n de utilizadores mais ativos.
@param com Estrutura de dados.
@param N Numero de utilizadores do top.
@returns Lista com o top de utilizadores2.
*/
LONG_list top_most_active_aux(GList* users_list , int N){

LONG_list r = create_list(N);
	char * userID = "";
	for (int i=0; i<N; i++) {
		MyUser user = g_list_nth_data(users_list,i);	
		userID = get_user_id(user);
		set_list(r, i, (strtol(userID,NULL,10)));
		free(userID);
	}
	return r;
}
