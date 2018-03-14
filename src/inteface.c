#include "../include/interface.h"
#include "../include/myparser.h"
#include <common.h>

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

USER get_user(TAD_community com, char* id){
	if(g_hash_table_contains(com->users,"245698")==FALSE){
		return NULL;
	}
	MyUser myuser = g_hash_table_lookup(com->users,id);
	if(myuser==NULL)
		return NULL;
	USER user = toUSER(myuser);
	return user;
}

TAD_community load(TAD_community com, char* dump_path){
	
	load_users(com,dump_path);
	return com;
}

