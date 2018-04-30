#include <myuser.h>
#include <stdlib.h>
#include <common.h>
#include <string.h>
#include <pair.h>
#include <stdio.h>
#include <compare_date.h>

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



int inv_cmp (STR_pair pair1, STR_pair pair2){
		char *a = get_snd_str(pair1);
		char *b = get_snd_str(pair2);
		Date c = string_toDate(a);
		Date d = string_toDate(b);
		int x = compare_date(c,d);
		free (a);
		free (b);
		free_date(c);
		free_date(d);
		return -x;
}

void set_lastpost (MyUser user, char * id, Date data){
	char *x = get_snd_str(g_list_nth_data(user->last_posts,9));
	char* date = date_toString(data);
	
	if(g_list_length (user->last_posts)<10)
		user->last_posts = g_list_insert_sorted_with_data(user->last_posts,create_str_pair(id,date),(GCompareDataFunc)inv_cmp,NULL);
	else{
		Date x_ = string_toDate(x);
		if(compare_date(x_,data)<0){
			GList* l=g_list_nth(user->last_posts,9);
			user->last_posts = g_list_remove_link(user->last_posts,l);
			free_str_pair(l->data);
			g_list_free(l);
			user->last_posts = g_list_insert_sorted_with_data(user->last_posts,create_str_pair(id,date),(GCompareDataFunc)inv_cmp,NULL);
		}
		free_date(x_);
	}
	
	free(date);
	free(x);

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

void destroy_myuser(MyUser user){
	free(user->id);
	free(user->name);
	free(user->aboutme);
	if(user->last_posts!=NULL)
		g_list_free_full(user->last_posts,(GDestroyNotify)free_str_pair);
	free(user);
}