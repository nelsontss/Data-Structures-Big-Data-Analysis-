#include "query1.h"
#include <stdlib.h>
#include <myuser.h>
#include <mypost.h>
#include <loader.h>
#include <stdio.h>

/**
\brief .
@param com Estrutura de dados.
@param id ID do post.
@returns Se for uma pergunta retorna o título e o ID do user, se for uma resposta retorna o títula da pergunta ao qual foi feita a resposta e o ID da pergunta.
*/
STR_pair info_from_post_aux(GHashTable* users, GHashTable* posts, long id){
	char id_[10];
	sprintf(id_, "%ld", id);
	STR_pair pair;
	MyPost mypost = get_post(posts, id_);
	char * ownerUserId = get_post_ownerUser(mypost);
	MyUser myuser = get_user (users, ownerUserId);
	char * title = get_post_title(mypost);
	char * username =  get_user_name(myuser);
	char * parentID = get_post_parentID(mypost);
	
	if (mypost==NULL){
		return NULL;
	}

	if(get_post_type(mypost)==1){
		if (myuser==NULL)
			return NULL;
		pair = create_str_pair(title,username);
	}
	else{
		pair = info_from_post_aux(users,posts,strtol(parentID,NULL,10));
	}
	free(ownerUserId);
	free(title);
	free(username);
	free(parentID);
	return pair;
}