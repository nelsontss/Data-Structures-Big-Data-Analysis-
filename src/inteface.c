#include "../include/interface.h"
#include "../include/myparser.h"
#include <common.h>
#include <pair.h>
#include <myuser.h>
#include <mypost.h>
#include <glib-2.0/gmodule.h>
#include <string.h>


typedef struct TCD_community
{
	GHashTable* posts;
	GHashTable* users;
	GList* posts_list;
	GList* users_list;

	long total_questions;
	long total_answers;

}TCD_community;

void destroy_key(char* key){
	free(key);
}

int load_users(TAD_community com, char *dump_path){
	char id[1000] ,name[1000];char dump[100];
	memset(dump, '\0', sizeof(dump));
	memset(id, '\0', sizeof(id));
	memset(name, '\0', sizeof(name));
	char *id_;
	MyUser user; 
	xmlDocPtr doc;
	xmlNodePtr cur;
	strcpy(dump,dump_path);
	doc = open_doc(strcat(dump,"Users.xml"));
		if(doc==NULL){
			return 1;
		}

	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;	
	cur = cur->next;
	while(cur!=NULL) {		
		

		get_prop(cur,"Id",id);
		get_prop(cur,"DisplayName",name);
		
		user = create_myuser(id,name);
		id_=mystrdup(id);
		g_hash_table_insert(com->users,id_,user);
		
		
		cur = cur->next->next;
		
		
	}
	free(doc);
	free(cur);
	return 0;
}

USER toUSER (MyUser user) {
	long post_history;
	USER res = create_user(strcat(get_user_id(user),get_user_name(user)),&post_history);
	return res;
}

MyUser get_user(TAD_community com, char* id){
	if(g_hash_table_contains(com->users, id)==FALSE){
		return NULL;
	}
	MyUser myuser = g_hash_table_lookup(com->users,id);
	if(myuser==NULL)
		return NULL;
	return myuser;
}

void aumenta_answers(GHashTable* users, char *id){
	MyUser user = g_hash_table_lookup(users,id);
	aumenta_answers_user(user);

}

void aumenta_questions(GHashTable* users, char *id){
	MyUser user = g_hash_table_lookup(users,id);
	aumenta_questions_user(user);

}

Date get_data (char* creationdate){
	int i=0, day, month, year;
	while (creationdate[i]!='T'){
		if(creationdate[i]=='-')
			creationdate[i]='\0';
		i++;
	}
	creationdate[i]='\0';
	
	day= atoi(creationdate+8);
	month= atoi(creationdate+5);
	year= atoi(creationdate);
	
	return createDate (day,month,year);
}

int date_to_int(Date a){
	return (get_year(a)-2000)*365+get_month(a)*30+get_day(a);
}

int load_posts(TAD_community com, char* dump_path){
	char id[1000],  title[1000], ownerUser[1000], dump[1000], post_type[100], creationdate[20];
	Date d;
	int data;
	memset(dump, '\0', sizeof(dump));
	memset(id, '\0', sizeof(id));
	memset(title, '\0', sizeof(title));
	memset(ownerUser, '\0', sizeof(ownerUser));
	memset(creationdate, '\0', sizeof(creationdate));
	memset(post_type, '\0', sizeof(post_type));
	MyPost post;
	xmlDocPtr doc;
	xmlNodePtr cur;
	strcpy(dump, dump_path);
	doc = open_doc(strcat(dump, "Posts.xml"));
	if (doc==NULL)
		return 1;
	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;	
	cur = cur->next;
	while(cur!=NULL) {		
		
		get_prop(cur,"PostTypeId",post_type);
		if(strcmp(post_type,"1") == 0 || strcmp(post_type,"2")==0){

			get_prop(cur,"Id",id);
			get_prop(cur,"Title",title);
			get_prop(cur, "OwnerUserId", ownerUser);
			get_prop(cur, "CreationDate", creationdate);
			
			d = get_data(creationdate);
			data=date_to_int (d);
			post = create_mypost(id,title,ownerUser, data,0);
			char* id_= mystrdup(id);

			g_hash_table_insert(com->posts, id_, post);
			
			if(strcmp(post_type,"1")==0){
				com->total_questions++;
				aumenta_questions(com->users, ownerUser);
				set_post_type(post,1);
			}

			if(strcmp(post_type,"2")==0){
				com->total_answers++;
				aumenta_answers(com->users, ownerUser);
				set_post_type(post,2);
			}
		}
		cur = cur->next->next;
	}
	free(doc);
	free(cur);
	return 0;
}


MyPost get_post (TAD_community com, char* id){
	if(g_hash_table_contains(com->posts, id)==FALSE){
		return NULL;
	}
	MyPost mypost = g_hash_table_lookup(com->posts,id);
	if(mypost==NULL)
		return NULL;
	return mypost;	
}

/*void imprime (gpointer data, gpointer user_data){
	MyUser user = (MyUser) data;
	printf("%d\n",get_user_totalposts(user));
}
*/
MyPost g_list_get_post(GList* g){
	return g->data;
}

void load_userslist(TAD_community com){
	com->users_list=g_hash_table_get_values(com->users);
	com->users_list = g_list_sort(com->users_list,(GCompareFunc)compare_users);
	//g_list_foreach(com->users_list,imprime,NULL);
}

void load_postslist(TAD_community com){
	com->posts_list = g_hash_table_get_values(com->posts);
	com->posts_list = g_list_sort(com->posts_list,(GCompareFunc)compare_posts);
}

TAD_community init() {
	TAD_community com =(TAD_community)malloc(sizeof(struct TCD_community));
	com->users = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)destroy_key,(GDestroyNotify)destroy_myuser);
	com->posts = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)destroy_key,(GDestroyNotify)destroy_mypost);
	com->total_answers = 0;
	com->total_questions = 0;
	return com;
}

TAD_community load(TAD_community com, char* dump_path){
	
	load_users(com,dump_path);
	load_posts(com,dump_path);
	load_postslist(com);
	load_userslist(com);
	return com;
}


STR_pair info_from_post(TAD_community com, int id){
	char * id_=(char*)malloc(sizeof(char));
	sprintf(id_, "%d", id);
	
	MyPost mypost = get_post(com, id_);
	if (mypost==NULL){
		return NULL;
	}
	MyUser myuser = get_user (com, get_post_ownerUser(mypost));
	if (myuser==NULL)
		return NULL;
	STR_pair pair = create_str_pair(get_post_title(mypost), get_user_name(myuser));	
	return pair;
}



LONG_list top_most_active(TAD_community com, int N){
	LONG_list r = create_list(N);
	for (int i=0; i<N; i++) {
		MyUser user = g_list_nth_data(com->users_list,i);	
		set_list(r, i, (strtol(get_user_id(user),NULL,10)));
	}
	return r;
}

LONG_pair total_posts(TAD_community com, Date begin, Date end){
	
	long answers=0, questions=0;
	GList* aux= com->posts_list;
	if (begin == NULL && end == NULL)
		return (create_long_pair (com->total_questions, com->total_answers));
	else{
		if (begin == NULL){
			while (aux != NULL && get_post_data(g_list_get_post(aux)) < (date_to_int (end))){
				if(get_post_type(g_list_get_post(aux))==1)
					questions++;
				else
					answers++;
				aux=aux->next;
			}
			return (create_long_pair (questions, answers));
		}
		else{
			if (end == NULL){
				while (aux != NULL && get_post_data(g_list_get_post(aux)) < (date_to_int (begin)))
					aux=aux->next;
				while (aux !=NULL){
					if(get_post_type(g_list_get_post(aux))==1)
						questions++;
					else
						answers++;
					aux=aux->next;
				}
			return (create_long_pair (questions, answers));
			}
		}
	}
	while (aux != NULL && get_post_data(g_list_get_post(aux)) < (date_to_int (begin)))
		aux=aux->next;
	while (aux != NULL && get_post_data(g_list_get_post(aux)) < (date_to_int (end))){
				if(get_post_type(g_list_get_post(aux))==1)
					questions++;
				else
					answers++;
				aux=aux->next;
	}
	return (create_long_pair (questions, answers));
}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	GList* aux = com->posts_list;
	int i=0;
	LONG_list lista= create_list(0);
	g_list_last(aux);
	if (begin==NULL && end==NULL){
		if (begin==NULL){
			while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end)))
				aux=aux->prev;
		}
		while (aux!=NULL){
			if (get_post_type(g_list_get_post(aux))==2)
				if (strcmp(tag, get_post_tag(g_list_get_post(aux))) == 0){
					lista->list[i++]=get_post_id(g_list_get_post(aux));
					lista->size++;
					aux=aux->prev;
			}
		}
		return lista;
	}
	if (end==NULL){
		while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (begin))){
			if (get_post_type(g_list_get_post(aux))==2)
				if (strcmp(tag, get_post_tag(g_list_get_post(aux))) == 0){
					lista->list[i++]=get_post_id(g_list_get_post(aux));
					lista->size++;
					aux=aux->prev;
				}
		}
		return lista;
	}
	while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end))){
			aux=aux->prev;
		}
	while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (begin)))
			if (get_post_type(g_list_get_post(aux))==2)
				if (strcmp(tag, get_post_tag(g_list_get_post(aux))) == 0){
					lista->list[i++]=get_post_id(g_list_get_post(aux));
					lista->size++;
					aux=aux->prev;
	}
	return lista;
}

TAD_community clean(TAD_community com){
	g_hash_table_destroy(com->users);
	g_hash_table_destroy(com->posts);
	return com;
}