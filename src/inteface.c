#include "../include/interface.h"
#include "../include/myparser.h"
#include <common.h>
#include <glib-2.0/gmodule.h>
#include <string.h>

typedef struct TCD_community
{
	GHashTable* posts;
	GHashTable* users;

}TCD_community;

typedef struct myuser
{
	char * id;
	char * name;
}*MyUser;

typedef struct mypost
{
	char* id;
	char* title;
	char* ownerUser;
}*MyPost;

TAD_community init() {
	TAD_community com =(TAD_community)malloc(sizeof(struct TCD_community));
	com->users = g_hash_table_new(g_str_hash,g_str_equal);
	com->posts = g_hash_table_new(g_str_hash,g_str_equal);
	return com;
}


MyUser create_myuser(char *id, char *name){
	MyUser user = (MyUser)malloc(sizeof(struct myuser));
	user->id = mystrdup(id);
	user->name = mystrdup(name);

	return user;
}

void destroy_myuser(MyUser user){
	free(user->id);
	free(user->name);
	free(user);
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
	USER res = create_user(strcat(user->id,user->name),&post_history);
	return res;
}



void imprime(gpointer key, gpointer user_, gpointer user_data){
	MyUser user = (MyUser) user_;
	printf("%s\n", user->name);
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

TAD_community load(TAD_community com, char* dump_path){
	
	load_users(com,dump_path);
	return com;
}

MyPost create_mypost(char* id, char* title, char* ownerUser){
	MyPost post= (MyPost) malloc(sizeof(struct mypost));
	post->id = mystrdup(id);
	post->title= mystrdup(title);
	post->ownerUser= mystrdup(ownerUser);
	return post;
}

void destroy_mypost (MyPost post){
	free(post->id);
	free(post->title);
	free(post->ownerUser);
	free(post);
}

int load_posts(TAD_community com, char* dump_path){
	char id[1000],  title[1000], ownerUser[1000], dump[1000];
	memset(dump, '\0', sizeof(dump));
	memset(id, '\0', sizeof(id));
	memset(title, '\0', sizeof(title));
	memset(ownerUser, '\0', sizeof(ownerUser));
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
		

		get_prop(cur,"Id",id);
		get_prop(cur,"Title",title);
		get_prop(cur, "OwnerUserId", ownerUser);
		
		post = create_mypost(id,title,ownerUser);
		char* id_= mystrdup(id);

		g_hash_table_insert(com->posts, id_, post);
		
		
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

STR_pair info_from_post(TAD_community com, int id){
	char c = (char) id;
	MyPost mypost = get_post(com, &c);
	if (mypost==NULL)
		return NULL;
	MyUser myuser = get_user (com, mypost->ownerUser);
	if (myuser==NULL)
		return NULL;
	STR_pair pair = create_str_pair(mypost->title, myuser->name);
	return pair;
}
