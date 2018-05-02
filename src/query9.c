#include "query9.h"
#include <stdlib.h>
#include <mypost.h>
#include <stdio.h>

/**
@file query9.c
Implementação da query 9.
*/

/**
\brief Dado um post e dois ids de utilizadores, diz se ambos participaram no post.
@param post Post onde se vai procurar.
@param id1 ID do utiliazdor 1.
@param id2 ID do utilizador 2.
@returns 0 se ambos participam ou 1 se não.
*/
int both_participated_aux_aux(MyPost post, long id1, long id2){
	GHashTable *l = post_get_resp_hash(post);
	char aux1[10];
	char aux2[10];
	sprintf(aux1,"%ld",id1);
	sprintf(aux2,"%ld",id2);
	char *ownerUserId = get_post_ownerUser(post);
	int flag = 0;
	if(atoi(ownerUserId) == id1)
		flag++;
	if(atoi(ownerUserId) == id2)
		flag++;
	if(atoi(ownerUserId)!= id1 && g_hash_table_lookup(l,aux1)!=NULL)
		flag++;
	if(atoi(ownerUserId)!= id2 && g_hash_table_lookup(l,aux2)!=NULL)
		flag++;


	free(ownerUserId);
	if (flag >= 2)
		return 0;
	else
		return 1;
}

LONG_list both_participated_aux(GList* questions_list, long id1, long id2, int N){
	GList* aux = questions_list;
	LONG_list l = create_list(N);
	char * postID = "";

	int i = 0;
	while(aux!=NULL && i<N){
		if(both_participated_aux_aux(aux->data, id1, id2) == 0){
			postID = get_post_id(aux->data);
			set_list(l,i,strtol(postID,NULL,10));
			i++;
			free(postID);
		}
		aux=aux->next;
	}

	if(i<N)
		while(i<N){
			set_list(l,i,-1);
			i++;
		}
	return l;
}
