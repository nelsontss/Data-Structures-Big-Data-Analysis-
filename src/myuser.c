#include <myuser.h>
#include <stdlib.h>
#include <common.h>
struct myuser
{
	char * id;
	char * name;
	int questions;
	int answers;
	int total_posts;
};

MyUser create_myuser(char *id, char *name){
	MyUser user = (MyUser)malloc(sizeof(struct myuser));
	user->id = mystrdup(id);
	user->name = mystrdup(name);
	user->questions = 0;
	user->answers = 0;
	user->total_posts = 0;
	return user;
}

char * get_user_id(MyUser user){
	return user ? mystrdup(user->id) : NULL;
}

char * get_user_name(MyUser user){
	return user ? mystrdup(user->name) : NULL;
}

int get_user_questions(MyUser user){
	return user ? user->questions : -1;
}

int get_user_answers(MyUser user){
	return user ? user->answers : -1;
}

int get_user_totalposts(MyUser user){
	return user ? user->total_posts : -1;
}

void set_user_id(MyUser user, char* id){
	free(user->id);
	user->id=mystrdup(id);
}

void set_user_name(MyUser user, char* name){
	free(user->name);
	user->name=mystrdup(name);
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

void aumenta_questions_user(MyUser user){
	user->questions++;
	user->total_posts++;	
}

void aumenta_answers_user(MyUser user){
	user->questions++;
	user->total_posts++;	
}

int compare_users (MyUser u1, MyUser u2){
	if(u1->total_posts<u2->total_posts)
		return -1;
	if(u1->total_posts==u2->total_posts)
		return 0;
	if(u1->total_posts>u2->total_posts)
		return 1;
}

void destroy_myuser(MyUser user){
	free(user->id);
	free(user->name);
	free(user);
}