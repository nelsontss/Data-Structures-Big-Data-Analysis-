#include <myuser.h>
#include <stdlib.h>
#include <common.h>
#include <string.h>
#include <pair.h>
#include <stdio.h>
struct myuser
{
	char * id;
	char * name;
	char * aboutme;
	int questions;
	int answers;
	int total_posts;
	int reputation;
	GList* last_posts;
};

MyUser create_myuser(char *id, char *name, int reputation, char* aboutme){
	MyUser user = (MyUser)malloc(sizeof(struct myuser));
	user->id = mystrdup(id);
	user->name = mystrdup(name);
	user->aboutme = mystrdup(aboutme);
	user->reputation = reputation;
	user->questions = 0;
	user->answers = 0;
	user->total_posts = 0;
	user->last_posts = NULL;
	return user;
}

char * get_user_id(MyUser user){
	return user ? mystrdup(user->id) : NULL;
}

char * get_user_name(MyUser user){
	return user ? mystrdup(user->name) : NULL;
}

char * get_user_aboutme(MyUser user){
	return user ? mystrdup(user->aboutme) : NULL;
}

int get_user_questions(MyUser user){
	return user ? user->questions : -1;
}

int get_user_reputation(MyUser user){
	return user ? user->reputation : -1;
}

int get_user_answers(MyUser user){
	return user ? user->answers : -1;
}

int get_user_totalposts(MyUser user){
	return user ? user->total_posts : -1;
}

GList * get_user_lastposts (MyUser user){
	return user->last_posts;
}


void set_user_id(MyUser user, char* id){
	free(user->id);
	user->id=mystrdup(id);
}

void set_user_name(MyUser user, char* name){
	free(user->name);
	user->name=mystrdup(name);
}

void set_user_aboutme(MyUser user, char* aboutme){
	free(user->aboutme);
	user->aboutme=mystrdup(aboutme);
}

void set_user_reputation(MyUser user, int reputation){
	user->reputation=reputation;
}

void set_user_questions(MyUser user, int questions){
	user->questions=questions;
}
void set_user_answers(MyUser user, int answers){
	user->answers=answers;
}

void set_user_totalposts(MyUser user, int total_posts){
	user->total_posts=total_posts;	
}



int inv_strcmp (STR_pair pair1, STR_pair pair2){
		int x = strcmp(get_snd_str(pair1),get_snd_str(pair2));

		return -x;
}

void set_lastpost (MyUser user, char * id, int data){
	char data_str[10];
	sprintf(data_str,"%d",data);
	STR_pair pair = create_str_pair(id,data_str);
	if(g_list_length (user->last_posts)<10)
		user->last_posts = g_list_insert_sorted_with_data(user->last_posts,pair,(GCompareDataFunc)inv_strcmp,NULL);
	else{
		if(atoi(get_snd_str(g_list_nth_data(user->last_posts,9)))<data){
			user->last_posts = g_list_remove(user->last_posts,g_list_nth_data(user->last_posts,9));
			user->last_posts = g_list_insert_sorted_with_data(user->last_posts,pair,(GCompareDataFunc)inv_strcmp,NULL);
		}
	}
	

}

void aumenta_questions_user(MyUser user){
	user->questions++;
	user->total_posts++;	
}

void aumenta_answers_user(MyUser user){
	user->questions++;
	user->total_posts++;	
}

int compare_users_rep (MyUser u1, MyUser u2){
	if(u1->reputation<u2->reputation)
		return 1;
	if(u1->reputation==u2->reputation)
		return 0;
	
	return -1;
}

int compare_users (MyUser u1, MyUser u2){
	if(u1->total_posts<u2->total_posts)
		return 1;
	if(u1->total_posts==u2->total_posts)
		return 0;
	
	return -1;
}

void destroy_myuser(MyUser user){
	free(user->id);
	free(user->name);
	free(user->aboutme);
	g_list_free_full(user->last_posts,(GDestroyNotify)free_str_pair);
	free(user);
}