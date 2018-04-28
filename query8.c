#include "query8.h"
#include <stdlib.h>
#include <mypost.h>
#include <string.h>

/**
\brief Procura os N posts mais recentes que contêm a palavra dada.
@param com Estrutura de dados.
@param word Palavra procurada.
@param N Número de posts a procurar.
@returns Lista com os ids dos posts que contêm a palavra.
*/
LONG_list contains_word_aux(GList* posts_list, char* word, int N){
	LONG_list l = create_list(N);
	int i = 0;
	GList *aux = posts_list;
	char* title = "";
	char* postID = "";
	while(aux!=NULL && i<N){
		title = get_post_title(aux->data);	
		if(strstr(title,word)!=NULL){
			postID = get_post_id(aux->data);
			set_list(l,i,strtol(postID,NULL,10));
			free(postID);
			i++;
		}
		free(title);
		aux=aux->next;
	}
	
	if(i<N)
		while(i<N){
			set_list(l,i,-1);
			i++;
		}
	return l;
}