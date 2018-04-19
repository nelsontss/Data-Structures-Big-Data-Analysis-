#include "loader.h"
#include <myparser.h>
#include <string.h>
#include <date_to_int.h>
#include <common.h>

int load_users(GHashTable* users, char *dump_path){
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
		
		g_hash_table_insert(users,mystrdup(id),user);
		
		
		cur = cur->next->next;
		
		
	}
	xmlFreeDoc(doc);
	return 0;
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

void insere_post_user(GHashTable* users, char * userID, char * postID, int data){
	MyUser user = get_user(users,userID);
	set_lastpost(user,postID,data);
}

int load_posts(GHashTable* users, GHashTable* posts, long* total_questions, long* total_answers, char* dump_path){
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
			
			MyUser user = get_user(users,ownerUser);
			
			d = get_data(creationdate);
			data=date_to_int (d);
			free(d);
			post = create_mypost(id,"",ownerUser, data,0,atoi(answercount));
			g_hash_table_insert(posts, mystrdup(id), post);
			
			insere_post_user(users,ownerUser,id,data);

			
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
				*(total_questions)+=1;
				aumenta_questions(users, ownerUser);
				set_post_type(post,1);
			}

			if(strcmp(post_type,"2")==0){
				*(total_answers)+=1;
				aumenta_answers(users, ownerUser);
				set_post_type(post,2);
				set_post_resp(get_post(posts,parentID),post);
				calc_post_pont(post,get_user_reputation(user));
			}
		}
		cur = cur->next->next;
	}
	xmlFreeDoc(doc);
	
	return 0;
}

int load_tags(GHashTable* tags, char* dump_path){
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
		
		g_hash_table_insert(tags, mystrdup(TagName), mystrdup(id));

		cur = cur->next->next;
	}
	xmlFreeDoc(doc);
	return 0;

}

void copy_questions (MyPost data, GList** userdata) {
	
	if(get_post_type(data)==1){
		*userdata = g_list_append(*userdata,data);

	}
}

GList* load_questionslist (GList* posts_list){
	GList* questions_list;
	g_list_foreach(posts_list,(GFunc)copy_questions,&(questions_list));
	return questions_list;
}

GList* load_userslist_rep (GList* users_list) {
	GList* users_list_rep = g_list_copy(users_list);
	users_list_rep = g_list_sort(users_list_rep,(GCompareFunc)compare_users_rep);
	return users_list;
}

GList* load_userslist(GHashTable* users){
	GList* users_list=g_hash_table_get_values(users);
	users_list = g_list_sort(users_list,(GCompareFunc)compare_users);
	return users_list;
}

GList* load_postslist(GHashTable* posts){
	GList* posts_list = g_hash_table_get_values(posts);
	posts_list = g_list_sort(posts_list,(GCompareFunc)compare_posts);
	return posts_list;
}

MyPost get_post (GHashTable* posts, char* id){
	if(g_hash_table_contains(posts, id)==FALSE){
		return NULL;
	}
	MyPost mypost = g_hash_table_lookup(posts,id);
	if(mypost==NULL)
		return NULL;
	return mypost;	
}



MyUser get_user(GHashTable* users, char* id){
	if(g_hash_table_contains(users, id)==FALSE){
		return NULL;
	}
	MyUser myuser = g_hash_table_lookup(users,id);
	if(myuser==NULL)
		return NULL;
	return myuser;
}
