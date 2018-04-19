#include "query9.h"
#include <stdlib.h>
#include <mypost.h>

int both_participated_aux_aux(MyPost post, long id1, long id2){
	GList *l = post_get_resp(post);
	int flag = 0, id = 0;
	char *ownerUserId = get_post_ownerUser(post);
	if(strtol(ownerUserId,NULL,10)==id1 || strtol(ownerUserId,NULL,10)==id2){
		
		flag = 1;
		if(strtol(ownerUserId,NULL,10)==id1)
			id=1;
		else
			id=2;
	}
	free(ownerUserId);
	while(l!=NULL && flag != 2){
			ownerUserId = get_post_ownerUser(l->data);
			if(strtol(ownerUserId,NULL,10)==id1){
				if(id == 2)
					flag = 2;
				else {
				id=1;
				flag=1;
				}
			}
			if(strtol(ownerUserId,NULL,10)==id2){
				if(id==1)
					flag = 2;
				else {
				id=2;
				flag=1;
				}
			}
			free(ownerUserId);
		l=l->next;
	}

	if (flag == 2)
		return 0;

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