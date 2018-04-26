#include "query11.h"
#include <stdlib.h>
#include <date_to_int.h>
#include <mypost.h>
#include <myuser.h>
#include <string.h>
#include <pair.h>
#include <stdio.h>
#include <common.h>

int cmp (int fst, int snd){
	if (fst<snd)
		return -1;
	if (fst==snd)
		return 0;
	return 1;
}

int ord_tags(STR_pair pair1, STR_pair pair2){
	char * str1 = get_snd_str(pair1);
	char * str2 = get_snd_str(pair2);
	char * str3 = get_fst_str(pair1);
	char * str4 = get_fst_str(pair2);
	if(atoi(str1)<atoi(str2)){
		free(str1);
		free(str2);
		return 1;
	}
	if(atoi(str1)==atoi(str2)){
		free(str1);
		free(str2);
		int r = cmp(atoi(str3),atoi(str4));
		free(str3);
		free(str4);
		return r;
	}
	free(str1);
	free(str2);
	return -1;
}

int compara_tags(STR_pair pair, char* tag) {
	char *str1 = get_fst_str(pair);
	int r = strcmp(str1,tag);
	free(str1);
	return r;
}

GList* insere_tag(char *tag,GList* tags){
	char *tagdup = mystrdup(tag);
	GList* l = g_list_find_custom(tags,tag,(GCompareFunc)compara_tags);
	char *str = "";
	char count[10];
	if(l!=NULL){
		str = get_snd_str(l->data);
		sprintf(count,"%d",atoi(str)+1);
		tags=g_list_remove_link(tags,l);
		free_str_pair(l->data);
		g_list_free(l);
		tags = g_list_insert_sorted(tags,create_str_pair(tagdup,count),(GCompareFunc)ord_tags);
		free(str);
	}else{
		tags = g_list_insert_sorted(tags,create_str_pair(tagdup,"1"),(GCompareFunc)ord_tags);
	}
	free(tagdup);
	return tags;

}

int is_in_top_N(char* userID, GList* users, int N){
	int i = 0;
	char* aux = "";
	while(users!=NULL && userID != NULL && i<N){
		aux = get_user_id(users->data);
		if(strcmp(aux,userID)==0){
			free(aux);
			return 0;
		}
		i++;
		free(aux);
		users=users->next;
	}
	return 1;
}

char * get_tag_id (GHashTable* tags, char* tag){
	if(g_hash_table_contains(tags, tag)==FALSE){
		return NULL;
	}
	char * id = g_hash_table_lookup(tags,tag);
	if(id==NULL)
		return NULL;
	return id;
}

LONG_list most_used_best_rep_aux(GList* posts_list, GList* users_list_rep, GHashTable* tags ,int N, Date begin, Date end){
	GList* tags_ = NULL;
	GList* aux = posts_list;
	GList* tags_aux = NULL;
	char * ownerUserId = "";
	char * str = "";

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
  			 ownerUserId = get_post_ownerUser(aux->data);
  			 if(is_in_top_N(ownerUserId,users_list_rep,N)==0){
  			 	tags_aux = post_get_tags(aux->data);
  					while(tags_aux!=NULL){
  						tags_ = insere_tag(tags_aux->data,tags_);
  						tags_aux=tags_aux->next;
  					}

  			 }
  			 free(ownerUserId);
  			 aux=aux->next;	
		}
	}
	else{
		if (begin==NULL){
			while (aux != NULL && get_post_data(aux->data) > (date_to_int (end)))
				aux=aux->next;
			while (aux!=NULL){
  				ownerUserId = get_post_ownerUser(aux->data);
  				if(is_in_top_N(ownerUserId,users_list_rep,N)==0){
  					tags_aux = post_get_tags(aux->data);
  					while(tags_aux!=NULL){
  						tags_ = insere_tag(tags_aux->data,tags_);
  						tags_aux=tags_aux->next;
  					}
  			 	}
  			 	free(ownerUserId);
  			 	aux=aux->next;		
			}
		 }
		else{
			if (end==NULL){
				while (aux != NULL && get_post_data(aux->data) >= (date_to_int (begin))){
					ownerUserId = get_post_ownerUser(aux->data);
					if(is_in_top_N(ownerUserId,users_list_rep,N)==0){
						tags_aux = post_get_tags(aux->data);
  						while(tags_aux!=NULL){
  							tags_ = insere_tag(tags_aux->data,tags_);
  							tags_aux=tags_aux->next;
  						}
  			 		}
  			 		free(ownerUserId);
  			 		aux=aux->next;	
				}
			}
		}
	}

	if(begin!=NULL && end!=NULL){
		while (aux != NULL && get_post_data(aux->data) > (date_to_int (end))){
			aux=aux->next;
		}
		while (aux != NULL && get_post_data(aux->data) >= (date_to_int (begin))){
  			ownerUserId = get_post_ownerUser(aux->data);
  			if(is_in_top_N(ownerUserId,users_list_rep,N)==0){
  				tags_aux = post_get_tags(aux->data);
  					while(tags_aux!=NULL){
  						tags_ = insere_tag(get_tag_id(tags,tags_aux->data),tags_);
  						tags_aux=tags_aux->next;
  					}	
  			 }
  			 free(ownerUserId);
  			 aux=aux->next;
		}
	}
    LONG_list lista = create_list(N);
    int i = 0;
	GList *x = tags_;
	while (i<N){
		str = get_fst_str(x->data);
		set_list(lista, i, atoi(str));
		x=x->next;
		i++;
		free(str);
	}
	
	g_list_free_full(tags_,(GDestroyNotify)free_str_pair);
	return lista;
}