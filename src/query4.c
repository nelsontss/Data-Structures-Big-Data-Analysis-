#include "query4.h"
#include <mypost.h>
#include <stdlib.h>
#include <loader.h>

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
			while (aux != NULL && get_post_data(aux->data) > (date_to_int (end)))
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
				while (aux != NULL && get_post_data(aux->data) >= (date_to_int (begin))){
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
		
					while (aux != NULL && get_post_data(aux->data) > (date_to_int (end))){
							aux=aux->next;
					}
					while (aux != NULL && get_post_data(aux->data) >= (date_to_int (begin))){
							if (get_post_type(aux->data)==1){
								if (post_contains_tag(aux->data, tag)==0){
									postID = get_post_id(aux->data);
									set_list(lista, i, strtol(postID, NULL, 10));
									i++;
									free(postID);
								}
							}
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