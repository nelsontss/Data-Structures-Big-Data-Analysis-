#include "../include/interface.h"
#include "../include/myparser.h"
#include <common.h>
#include <pair.h>
#include <myuser.h>
#include <mypost.h>
#include <glib-2.0/gmodule.h>
#include <string.h>


struct TCD_community
{
	GHashTable* posts;
	GHashTable* users;
	GHashTable* tags;
	GList* posts_list;
	GList* users_list;
	GList* questions_list;
	GList* users_list_rep;

	long total_questions;
	long total_answers;

};



int load_users(TAD_community com, char *dump_path){
	char id[100000], aboutme[1000] ,name[1000];char dump[100],reputation[1000];
	memset(dump, '\0', sizeof(dump));
	memset(id, '\0', sizeof(id));
	memset(name, '\0', sizeof(name));
	memset(reputation, '\0', sizeof(reputation));
	memset(aboutme, '\0', sizeof(aboutme));
	
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
	cur = cur->next->next;
	while(cur!=NULL) {		
		
		get_prop(cur,"AboutMe",aboutme);
		get_prop(cur,"Reputation",reputation);
		get_prop(cur,"Id",id);
		get_prop(cur,"DisplayName",name);
		
		user = create_myuser(id,name,atoi(reputation),aboutme);
		
		g_hash_table_insert(com->users,mystrdup(id),user);
		
		
		cur = cur->next->next;
		
		
	}
	xmlFreeDoc(doc);
	return 0;
}



USER toUSER (MyUser user) {
	long post_history[10];
	GList* l = get_user_lastposts(user);
	int i = 0;
	char * str1 = "";
	char *aboutme = get_user_aboutme(user);
	while(i<10){
		if(g_list_nth_data(l,i)!=NULL){
			str1 = get_fst_str(g_list_nth_data(l,i));
			post_history[i]=strtol(str1,NULL,10);
			free(str1);
		}
		else
			post_history[i]=-1;
		i++;
	}
	USER r = create_user(aboutme,post_history);
	free(aboutme);
	return r;
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

void insert_tags(MyPost post, char *tags) {
	int i = 1;
	int a  = 1;	
	char *aux=mystrdup(tags) ;
	while(tags[i]!='\0'){
		if(tags[i]=='<')
			a=i+1;
		if(tags[i]=='>'){
			aux[i]='\0';
			set_post_tag(post,aux+a);
		}
		i++;
	}
	free(aux);
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
			
			MyUser user = get_user(com,ownerUser);
			
			d = get_data(creationdate);
			data=date_to_int (d);
			free(d);
			post = create_mypost(id,"",ownerUser, data,0,atoi(answercount));
			g_hash_table_insert(com->posts, mystrdup(id), post);
			
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
				calc_post_pont(post,get_user_reputation(user));
			}
		}
		cur = cur->next->next;
	}
	xmlFreeDoc(doc);
	
	return 0;
}


void imprime (gpointer data, gpointer user_data){
	MyPost post = (MyPost) data;
	printf("%d\n",get_post_type(post));
}

MyPost g_list_get_post(GList* g){
	if (g==NULL)
		return NULL;
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



/*
GList* remove_answers (GList * list){
	GList *l = list;
	while (l != NULL){
   		 GList *next = l->next;
    		if (get_post_type(g_list_get_post(l))==2){
        		list = g_list_remove_link(list, l);
      		}
    	l = next;
  	}
  	return list;
}*/

void copy_questions (MyPost data, GList** userdata) {
	
	if(get_post_type(data)==1){
		*userdata = g_list_append(*userdata,data);

	}
}

void load_questionslist (TAD_community com){
	g_list_foreach(com->posts_list,(GFunc)copy_questions,&(com->questions_list));
}

void load_userslist_rep (TAD_community com) {
	com->users_list_rep = g_list_copy(com->users_list);
	com->users_list_rep = g_list_sort(com->users_list_rep,(GCompareFunc)compare_users_rep);
}

int load_tags(TAD_community com, char* dump_path){
	char TagName[1000], id[1000], dump[1000];
	memset(TagName, '\0', sizeof(TagName));
	memset(id, '\0', sizeof(id));
	memset(dump, '\0', sizeof(dump));
	xmlDocPtr doc;
	xmlNodePtr cur;
	strcpy(dump, dump_path);
	doc = open_doc(strcat(dump, "Tags.xml"));
	if (doc==NULL)
		return 1;
	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;	
	cur = cur->next;
	while(cur!=NULL) {		
		
		get_prop(cur,"Id",id);
		get_prop(cur,"TagName",TagName);
		
		g_hash_table_insert(com->tags, mystrdup(TagName), mystrdup(id));

		cur = cur->next->next;
	}
	xmlFreeDoc(doc);
	return 0;

}

TAD_community init() {
	TAD_community com =(TAD_community)malloc(sizeof(struct TCD_community));
	com->users = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)destroy_myuser);
	com->posts = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)destroy_mypost);
	com->tags = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)free);
	com->questions_list = NULL;
	com->total_answers = 0;
	com->total_questions = 0;
	return com;
}

TAD_community load(TAD_community com, char* dump_path){
	
	load_users(com,dump_path);
	load_posts(com,dump_path);
	load_tags(com,dump_path);
	load_postslist(com);
	load_userslist(com);
	load_questionslist(com);
	load_userslist_rep(com);
	return com;
}


STR_pair info_from_post(TAD_community com, long id){
	char id_[10];
	sprintf(id_, "%ld", id);
	STR_pair pair;
	MyPost mypost = get_post(com, id_);
	char * ownerUserId = get_post_ownerUser(mypost);
	MyUser myuser = get_user (com, ownerUserId);
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
		pair = info_from_post(com,strtol(parentID,NULL,10));
	}
	free(ownerUserId);
	free(title);
	free(username);
	free(parentID);
	return pair;
}



LONG_list top_most_active(TAD_community com, int N){
	LONG_list r = create_list(N);
	char * userID = "";
	for (int i=0; i<N; i++) {
		MyUser user = g_list_nth_data(com->users_list,i);	
		userID = get_user_id(user);
		set_list(r, i, (strtol(userID,NULL,10)));
		free(userID);
	}
	return r;
}

LONG_pair total_posts(TAD_community com, Date begin, Date end){
	
	long answers=0, questions=0;
	GList* aux= com->posts_list;

	if (begin == NULL && end == NULL)
		return (create_long_pair (com->total_questions, com->total_answers));
	else{
		if (end == NULL){
			while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
				if(get_post_type(g_list_get_post(aux))==1)
					questions++;
				else
					answers++;
				aux=aux->next;
			}
			return (create_long_pair (questions, answers));
		}
		else{
			if (begin == NULL){
				while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end)))
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
	while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end)))
		aux=aux->next;
	while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
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
	char * postID = "";
		
		

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
			if (get_post_type(g_list_get_post(aux))==1){
				if (post_contains_tag(g_list_get_post(aux), tag)==0){
					postID = get_post_id(g_list_get_post(aux));
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
			while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end)))
				aux=aux->next;
			while (aux!=NULL){
				if (get_post_type(g_list_get_post(aux))==1)
					if (post_contains_tag(g_list_get_post(aux), tag)==0){
						postID = get_post_id(g_list_get_post(aux));
						set_list(lista, i, strtol(postID, NULL, 10));
						i++;
						free(postID);
				}
			aux=aux->next;
			}
		 }
		else{
			if (end==NULL){
				while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
					if (get_post_type(g_list_get_post(aux))==1){
						if (post_contains_tag(g_list_get_post(aux), tag)==0){
							postID = get_post_id(g_list_get_post(aux));
							set_list(lista, i, strtol(postID, NULL, 10));
							i++;
							free(postID);
						}
					}
				aux=aux->next;
				}
			}
			else{
		
					while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end))){
							aux=aux->next;
					}
					while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
							if (get_post_type(g_list_get_post(aux))==1){
								if (post_contains_tag(g_list_get_post(aux), tag)==0){
									postID = get_post_id(g_list_get_post(aux));
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

USER get_user_info(TAD_community com, long id){
	char id_[10];
	sprintf(id_,"%ld", id);
	MyUser user = get_user(com,id_);
	USER r = toUSER(user);
	return r;
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	GList* aux = com->posts_list;
    GList* l=NULL;  
	int i=0;
	char* postID = "";

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
  			if(get_post_type(g_list_get_post(aux))==2)	
  				l = g_list_insert_sorted (l,g_list_get_post(aux),(GCompareFunc)compare_votes);
			aux=aux->next;
		}
	}
	else{
		if (begin==NULL){
			while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end)))
				aux=aux->next;
			while (aux!=NULL){
  				if(get_post_type(g_list_get_post(aux))==2)
  					l = g_list_insert_sorted (l,g_list_get_post(aux),(GCompareFunc)compare_votes);
				aux=aux->next;
			}
		 }
		else{
			if (end==NULL){
				while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
					if(get_post_type(g_list_get_post(aux))==2)	
						l = g_list_insert_sorted (l,g_list_get_post(aux),(GCompareFunc)compare_votes);
					aux=aux->next;
				}
			}
		}
	}

	if(begin!=NULL && end!=NULL){
		while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end))){
			aux=aux->next;
		}
		while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
  			if(get_post_type(g_list_get_post(aux))==2){
  				
  				l = g_list_insert_sorted (l,g_list_get_post(aux),(GCompareFunc)compare_votes);
			}
			aux=aux->next;
		}
	}

    LONG_list lista = create_list(N);
	aux = l;
	while (i<N){
		postID = get_post_id(g_list_get_post(aux));
		set_list(lista, i, strtol(postID, NULL, 10));
		aux=aux->next;
		i++;
		free(postID);
	}
	g_list_free(l);
	return lista;
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	GList* aux = com->posts_list;
	int i=0;
	GList* l= NULL;
	char * postID = "";

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
			if (get_post_type(g_list_get_post(aux))==1)
				l= g_list_insert_sorted(l, g_list_get_post(aux), (GCompareFunc)compare_answerCount);
			aux=aux->next;
		}
	}
	else{
		if (end==NULL){
			while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
				if (get_post_type(g_list_get_post(aux))==1)
					l= g_list_insert_sorted(l, g_list_get_post(aux), (GCompareFunc)compare_answerCount);
				aux=aux->next;
			}
		}
		else{
			if (begin==NULL){
				while (aux != NULL && get_post_data(g_list_get_post(aux)) < (date_to_int (end)))
					aux=aux->next;
				while (aux!=NULL){
					if (get_post_type(g_list_get_post(aux))==1)
						l= g_list_insert_sorted(l, g_list_get_post(aux), (GCompareFunc)compare_answerCount);
					aux=aux->next;
				}			
			}
		}
	}
	while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end))){
			aux=aux->next;
	}
	while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
		if (get_post_type(g_list_get_post(aux))==1)
			l= g_list_insert_sorted(l, g_list_get_post(aux), (GCompareFunc)compare_answerCount);
		aux=aux->next;
	}
	LONG_list lista = create_list(N);
	aux = l;
	while (i<N){
		postID = get_post_id(g_list_get_post(aux));
		set_list(lista, i, strtol(postID, NULL, 10));
		aux=aux->next;
		i++;
		free(postID);
	}
	g_list_free(l);
	return lista;
}

LONG_list contains_word(TAD_community com, char* word, int N){
	LONG_list l = create_list(N);
	int i = 0;
	GList *aux = com->posts_list;
	char* title = "";
	char* postID = "";
	while(aux!=NULL && i<N){
		title = get_post_title(g_list_get_post(aux));	
		if(strstr(title,word)!=NULL){
			postID = get_post_id(g_list_get_post(aux));
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


int both_participated_aux(MyPost post, long id1, long id2){
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
			ownerUserId = get_post_ownerUser(g_list_get_post(l));
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

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	GList* aux = com->questions_list;
	LONG_list l = create_list(N);
	char * postID = "";

	int i = 0;
	while(aux!=NULL && i<N){
		if(both_participated_aux(g_list_get_post(aux), id1, id2) == 0){
			postID = get_post_id(g_list_get_post(aux));
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

long better_answer(TAD_community com, long id){
	char id_str[10];
	sprintf(id_str,"%ld",id);
	MyPost post = get_post(com,id_str);
	return (long)get_best_answer(post);
}

int ord_tags(STR_pair pair1, STR_pair pair2){
	char * str1 = get_snd_str(pair1);
	char * str2 = get_snd_str(pair2);
	if(atoi(str1)<atoi(str2)){
		free(str1);
		free(str2);
		return 1;
	}
	if(atoi(str1)==atoi(str2)){
		free(str1);
		free(str2);
		return 0;
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

char * get_tag_id (TAD_community com, char* tag){
	if(g_hash_table_contains(com->tags, tag)==FALSE){
		return NULL;
	}
	char * id = g_hash_table_lookup(com->tags,tag);
	if(id==NULL)
		return NULL;
	return id;
}

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	GList* tags = NULL;
	GList* aux = com->posts_list;
	GList* tags_aux = NULL;
	char * ownerUserId = "";
	char * str = "";

	if (begin==NULL && end==NULL){
		while (aux!=NULL){
  			 ownerUserId = get_post_ownerUser(g_list_get_post(aux));
  			 if(is_in_top_N(ownerUserId,com->users_list_rep,N)==0){
  			 	tags_aux = post_get_tags(g_list_get_post(aux));
  					while(tags_aux!=NULL){
  						tags = insere_tag(tags_aux->data,tags);
  						tags_aux=tags_aux->next;
  					}

  			 }
  			 free(ownerUserId);
  			 aux=aux->next;	
		}
	}
	else{
		if (begin==NULL){
			while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end)))
				aux=aux->next;
			while (aux!=NULL){
  				ownerUserId = get_post_ownerUser(g_list_get_post(aux));
  				if(is_in_top_N(ownerUserId,com->users_list_rep,N)==0){
  					tags_aux = post_get_tags(g_list_get_post(aux));
  					while(tags_aux!=NULL){
  						insere_tag(tags_aux->data,tags);
  						tags_aux=tags_aux->next;
  					}
  			 	}
  			 	free(ownerUserId);
  			 	aux=aux->next;		
			}
		 }
		else{
			if (end==NULL){
				while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
					ownerUserId = get_post_ownerUser(g_list_get_post(aux));
					if(is_in_top_N(ownerUserId,com->users_list_rep,N)==0){
						tags_aux = post_get_tags(g_list_get_post(aux));
  						while(tags_aux!=NULL){
  							insere_tag(tags_aux->data,tags);
  							tags_aux=tags->next;
  						}
  			 		}
  			 		free(ownerUserId);
  			 		aux=aux->next;	
				}
			}
		}
	}

	if(begin!=NULL && end!=NULL){
		while (aux != NULL && get_post_data(g_list_get_post(aux)) > (date_to_int (end))){
			aux=aux->next;
		}
		while (aux != NULL && get_post_data(g_list_get_post(aux)) >= (date_to_int (begin))){
  			ownerUserId = get_post_ownerUser(g_list_get_post(aux));
  			if(is_in_top_N(ownerUserId,com->users_list_rep,N)==0){
  				tags_aux = post_get_tags(g_list_get_post(aux));
  					while(tags_aux!=NULL){
  						insere_tag(tags_aux->data,tags);
  						tags_aux=tags_aux->next;
  					}	
  			 }
  			 free(ownerUserId);
  			 aux=aux->next;
		}
	}
    LONG_list lista = create_list(N);
    int i = 0;
	GList *x = tags;
	while (i<N){
		str = get_fst_str(x->data);
		set_list(lista, i, strtol(get_tag_id(com,str), NULL, 10));
		x=x->next;
		i++;
		free(str);
	}
	
	g_list_free_full(tags,(GDestroyNotify)free_str_pair);
	return lista;
}


TAD_community clean(TAD_community com){
	g_hash_table_destroy(com->users);
	g_hash_table_destroy(com->posts);
	g_hash_table_destroy(com->tags);
	g_list_free(com->users_list);
	g_list_free(com->users_list_rep);
	g_list_free(com->posts_list);
	g_list_free(com->questions_list);
	return com;
}
