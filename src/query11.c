#include "query11.h"
#include <stdlib.h>
#include <compare_date.h>
#include <mypost.h>
#include <myuser.h>
#include <string.h>
#include <pair.h>
#include <stdio.h>
#include <common.h>

/**
\brief Função que compara 2 inteiros.
@param fst Primeiro inteiro a comparar.
@param snd Segundo inteiro a comparar.
@returns 0 se forem iguais, -1 se o segundo for maior, ou 1 se o primeiro for maior.
*/
int cmp (int fst, int snd){
	if (fst<snd)
		return -1;
	if (fst==snd)
		return 0;
	return 1;
}

/**
\brief Função que compara 2 pares (tag,ocorrencias) pelo número de ocorrências.
@param pair1 Primeiro par a comparar.
@param pair2 Segundo par a comparar.
@returns 0 se forem iguais, 1 se o segundo for maior, ou -1 se o primeiro for maior.
*/
int ord_tags(STR_pair pair1, STR_pair pair2){
	char * str1 = get_snd_str(pair1);
	char * str2 = get_snd_str(pair2);
	char * str3 = get_fst_str(pair1);
	char * str4 = get_fst_str(pair2);
	if(atoi(str1)<atoi(str2)){
		free(str1);
		free(str2);
		free(str3);
		free(str4);
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
	free(str3);
	free(str4);
	return -1;
}

/**
\brief Função que compara a tag de um par (tag,ocorrencias) com outra tag dada.
@param pair Par a comparar.
@param tag Tag a comparar.
@returns Resultado lógico da comparação.
*/
int compara_tags(STR_pair pair, char* tag) {
	char *str1 = get_fst_str(pair);
	int r = strcmp(str1,tag);
	free(str1);
	return r;
}

/**
\brief Função que insere uma tag na glist de tags.
@param tag Tag a inserir.
@param tags Lista de tags.
@returns Lista de tags com aquela tag acrescentada.
*/
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

/**
\brief Dado um id de user e uma lista de users, vê se ele está contido na lista.
@param userID Id do user.
@param *users Apontador para lista de users.
@param N Número de elementos da lista.
@returns 1 se não está contido, ou 0 se está contido.
*/
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

/**
\brief Função que obtém o id de uma tag na tabela de hash de tags a partir da tag.
@param tags Tabela de hash de tags.
@param tag Tag a procurar.
@returns Id da tag.
*/
char * get_tag_id (GHashTable* tags, char* tag){
	if(g_hash_table_contains(tags, tag)==FALSE){
		return NULL;
	}
	char * id = g_hash_table_lookup(tags,tag);
	if(id==NULL)
		return NULL;
	return id;
}

/**
\brief Dado um intervalo arbitrário de tempo,devolve as N tags mais usadas pelos N utilizadores com melhor reputação. Em ordem decrescente do número de vezes em que a tag foi usada.
@param posts_list Lista de posts.
@param users_list_rep Lista de users ordenados por reputação.
@param tags Tabela de hash de tags.
@param N Número de tags.
@param begin Data inicial.
@param end Data final.
@returns Lista final das tags.
*/
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
			while (aux != NULL && compare_date(get_post_data(aux->data), end)>0)
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
				while (aux != NULL && compare_date(get_post_data(aux->data), begin)>=0){
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
		while (aux != NULL && compare_date(get_post_data(aux->data), end)>0){
			aux=aux->next;
		}
		while (aux != NULL && compare_date(get_post_data(aux->data), begin)>=0){
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