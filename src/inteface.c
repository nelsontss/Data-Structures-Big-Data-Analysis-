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
	GList* questions_list;

	long total_questions;
	long total_answers;

}TCD_community;

void destroy_key(char* key){
	free(key);
}

int load_users(TAD_community com, char *dump_path){
	char id[1000] ,name[1000];char dump[100],reputation[1000];
	memset(dump, '\0', sizeof(dump));
	memset(id, '\0', sizeof(id));
	memset(name, '\0', sizeof(name));
	memset(reputation, '\0', sizeof(reputation));
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
		
		get_prop(cur,"Reputation",reputation);
		get_prop(cur,"Id",id);
		get_prop(cur,"DisplayName",name);
		
		user = create_myuser(id,name,atoi(reputation));
		id_=mystrdup(id);
		g_hash_table_insert(com->users,id_,user);
		
		
		cur = cur->next->next;
		
		
	}
	free(doc);
	free(cur);
	return 0;
}



USER toUSER (MyUser user) {
	long post_history[10];
	GList* l = get_user_lastposts(user);
	int i = 0;
	while(i<10){
		if(g_list_nth_data(l,i)!=NULL)
			post_history[i]=strtol(get_fst_str(g_list_nth_data(l,i)),NULL,10);
		else
			post_history[i]=-1;
		i++;
	}
	char *bio = (char *)malloc(sizeof(char));
	sprintf(bio,"Nome: %s \nId: %s\n",get_user_name(user),get_user_id(user));

	return create_user(bio,post_history);
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

void insere_post_user(TAD_community com, char * userID, char * postID, int data){
	MyUser user = get_user(com,userID);
	set_lastpost(user,postID,data);
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

int load_posts(TAD_community com, char* dump_path){
	char tags[1000], comments[1000], score[1000], parentID[1000], answercount[1000], id[1000],  title[1000], ownerUser[1000], dump[1000], post_type[100], creationdate[20];
	Date d;
	int data;
	memset(dump, '\0', sizeof(dump));
	memset(id, '\0', sizeof(id));
	memset(title, '\0', sizeof(title));
	memset(ownerUser, '\0', sizeof(ownerUser));
	memset(creationdate, '\0', sizeof(creationdate));
	memset(post_type, '\0', sizeof(post_type));
	memset(tags,'\0',sizeof(tags));
	memset(answercount,'\0',sizeof(answercount));
	memset(parentID,'\0',sizeof(parentID));
	memset(score,'\0',sizeof(score));
	memset(comments,'\0',sizeof(comments));
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
			get_prop(cur, "OwnerUserId", ownerUser);
			get_prop(cur, "CreationDate", creationdate);
			get_prop(cur, "AnswerCount", answercount);
			

			d = get_data(creationdate);
			data=date_to_int (d);
			post = create_mypost(id,"",ownerUser, data,0,atoi(answercount));
			char* id_= mystrdup(id);
			g_hash_table_insert(com->posts, id_, post);
			
			insere_post_user(com,ownerUser,id,data);

			
			if (get_prop(cur,"Tags",tags)==0)
				insert_tags(post,tags);
			if (get_prop(cur,"Title",title)==0)
				set_post_title(post,title);
			if (get_prop(cur,"ParentId",parentID)==0)
				set_post_parentID(post,parentID);
			if(get_prop(cur,"Score",score)==0)
				set_post_score(post,atoi(score));
			if(get_prop(cur,"CommentCount",comments)==0)
				set_post_comments(post,atoi(comments));

			if(strcmp(post_type,"1")==0){
				com->total_questions++;
				aumenta_questions(com->users, ownerUser);
				set_post_type(post,1);
			}

			if(strcmp(post_type,"2")==0){
				com->total_answers++;
				aumenta_answers(com->users, ownerUser);
				set_post_type(post,2);
				set_post_resp(get_post(com,parentID),post);
				calc_post_pont(post,get_user_reputation(get_user(com,ownerUser)));
			}
		}
		cur = cur->next->next;
	}
	free(doc);
	free(cur);
	return 0;
}


void imprime (gpointer data, gpointer user_data){
	MyPost post = (MyPost) data;
	printf("%d\n",get_post_data(post));
}

MyPost g_list_get_post(GList* g){
	return g->data;
}

void load_userslist(TAD_community com){
	com->users_list=g_hash_table_get_values(com->users);
	com->users_list = g_list_sort(com->users_list,(GCompareFunc)compare_users);
	
}

void load_postslist(TAD_community com){
	com->posts_list = g_hash_table_get_values(com->posts);
	com->posts_list = g_list_sort(com->posts_list,(GCompareFunc)compare_posts);
	//g_list_foreach(com->posts_list,imprime,NULL);
}

int load_votes(TAD_community com, char* dump_path){
	char postID[1000], vote[1000], dump[1000];
	memset(postID, '\0', sizeof(postID));
	memset(vote, '\0', sizeof(vote));
	memset(dump, '\0', sizeof(dump));
	xmlDocPtr doc;
	xmlNodePtr cur;
	strcpy(dump, dump_path);
	doc = open_doc(strcat(dump, "Votes.xml"));
	if (doc==NULL)
		return 1;
	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;	
	cur = cur->next;
	while(cur!=NULL) {		
		
		get_prop(cur,"PostId",postID);
		get_prop(cur,"VoteTypeId",vote);
		if(strcmp(vote,"2")==0)
			up_post_votes(get_post(com,postID));
		if(strcmp(vote,"3")==0)
			down_post_votes(get_post(com,postID));
			

		cur = cur->next->next;
	}
	free(doc);
	free(cur);
	return 0;

}


void remove_answers (GList * list){
	GList *l = list;
	while (l != NULL){
   		 GList *next = l->next;
    		if (get_post_type(g_list_get_post(l))==2){
        		list = g_list_delete_link (list, l);
      		}
    	l = next;
  	}
}

void load_questionslist (TAD_community com){
	com->questions_list = g_list_copy (com->posts_list);
	remove_answers(com->questions_list);

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
	load_votes(com,dump_path);
	load_postslist(com);
	load_userslist(com);
	load_questionslist(com);
	//g_list_foreach(com->questions_list,(GFunc)imprime,NULL);
	return com;
}


STR_pair info_from_post(TAD_community com, long id){
	char * id_=(char*)malloc(sizeof(char));
	sprintf(id_, "%ld", id);
	STR_pair pair;
	
	MyPost mypost = get_post(com, id_);
	if (mypost==NULL){
		return NULL;
	}

	if(get_post_type(mypost)==1){
		MyUser myuser = get_user (com, get_post_ownerUser(mypost));
		if (myuser==NULL)
			return NULL;
		pair = create_str_pair(get_post_title(mypost), get_user_name(myuser));	
	}
	else
		return info_from_post(com,strtol(get_post_parentID(mypost),NULL,10));
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
	LONG_list lista= create_list(com->total_questions);
	while (aux->next!=NULL){
		aux=aux->next;
	}
		
		

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
			if (get_post_type(g_list_get_post(aux))==1){
				if (post_contains_tag(g_list_get_post(aux), tag)==0){
					set_list(lista, i, strtol(get_post_id(g_list_get_post(aux)), NULL, 10));
					i++;
				}
			}
		aux=aux->prev;
		}
		return lista;
	}
	else{
		if (begin==NULL){
			while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end)))
				aux=aux->prev;
			while (aux!=NULL){
				if (get_post_type(g_list_get_post(aux))==1)
					if (post_contains_tag(g_list_get_post(aux), tag)==0){
						set_list(lista, i, strtol(get_post_id(g_list_get_post(aux)), NULL, 10));
						i++;
				}
			aux=aux->prev;
			}
		 return lista;
		 }
		else{
			if (end==NULL){
				while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (begin))){
					if (get_post_type(g_list_get_post(aux))==1){
						if (post_contains_tag(g_list_get_post(aux), tag)==0){
							set_list(lista, i, strtol(get_post_id(g_list_get_post(aux)), NULL, 10));
							i++;
						}
					}
				aux=aux->prev;
				}
			return lista;
			}
		}
	}
	while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end))){
			aux=aux->prev;
		}
	while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (begin))){
			if (get_post_type(g_list_get_post(aux))==1){
				if (post_contains_tag(g_list_get_post(aux), tag)==0){
					set_list(lista, i, strtol(get_post_id(g_list_get_post(aux)), NULL, 10));
					
					i++;
				}
			}
	aux=aux->prev;
	}
	return lista;
}

USER get_user_info(TAD_community com, long id){
	char *id_=(char*)malloc(sizeof(char));
	sprintf(id_,"%ld", id);
	MyUser user = get_user(com,id_);
	USER r = toUSER(user);

	return r;
}

LONG_list contains_word(TAD_community com, char* word, int N){
	LONG_list l = create_list(N);
	int i = 0;
	GList *aux = com->posts_list;
	while(aux->next!=NULL){
		aux=aux->next;
	}
	while(aux!=NULL && i<N){	
		if(strstr(get_post_title(g_list_get_post(aux)),word)!=NULL){
			set_list(l,i,strtol(get_post_id(g_list_get_post(aux)),NULL,10));
			i++;
		}
		aux=aux->prev;
	}
	
	if(i<N)
		while(i<N){
			set_list(l,i,-1);
			i++;
		}
	return l;
}


int both_participated_aux(MyPost post, long id1, long id2){
	GList *l = post_get_resp(post);
	int flag = 0, id = 0;
	if(strtol(get_post_ownerUser(post),NULL,10)==id1 || strtol(get_post_ownerUser(post),NULL,10)==id2){
		
		flag = 1;
		if(strtol(get_post_ownerUser(post),NULL,10)==id1)
			id=1;
		else
			id=2;
	}
	if(id != 0)
	while(l!=NULL && flag != 2){
			if(strtol(get_post_ownerUser(g_list_get_post(l)),NULL,10)==id1){
				if(id == 2)
					flag = 2;
				else {
				id=1;
				flag=1;
				}
			}
			if(strtol(get_post_ownerUser(g_list_get_post(l)),NULL,10)==id2){
				if(id==1)
					flag = 2;
				else {
				id=2;
				flag=1;
				}
			}
			
		l=l->next;
	}

	if (flag == 2)
		return 0;

	return 1;
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	GList* aux = com->posts_list;
	LONG_list l = create_list(N);
	while (aux->next!=NULL){
		aux=aux->next;
	}
	int i = 0;
	while(aux!=NULL && i<N){
		if(both_participated_aux(g_list_get_post(aux), id1, id2) == 0){
			set_list(l,i,strtol(get_post_id(g_list_get_post(aux)),NULL,10));
			i++;
		}
		aux=aux->prev;
	}

	if(i<N)
		while(i<N){
			set_list(l,i,-1);
			i++;
		}
	return l;
}

long better_answer(TAD_community com, long id){
	char *id_str = (char*)malloc(sizeof(char));
	sprintf(id_str,"%ld",id);
	MyPost post = get_post(com,id_str);
	return (long)get_best_answer(post);
}


TAD_community clean(TAD_community com){
	g_hash_table_destroy(com->users);
	g_hash_table_destroy(com->posts);
	return com;
}
