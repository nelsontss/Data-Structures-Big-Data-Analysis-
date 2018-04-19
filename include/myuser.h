#include <glib-2.0/gmodule.h>
#include <user.h>
#ifndef __MYUSER_H__
#define __MYUSER_H__
typedef struct myuser* MyUser;

MyUser create_myuser(char *id, char *name, int reputation, char	* aboutme);
char * get_user_id(MyUser user);
char * get_user_name(MyUser user);
char * get_user_aboutme(MyUser user);
int get_user_reputation(MyUser user);
int get_user_questions(MyUser user);
int get_user_answers(MyUser user);
int get_user_totalposts(MyUser user);
GList * get_user_lastposts (MyUser user);
void set_user_id(MyUser user, char* name);
void set_user_name(MyUser user, char* id);
void set_user_aboutme(MyUser user, char* aboutme);
void set_user_reputation(MyUser user, int reputation);
void set_user_questions(MyUser user, int questions);
void set_user_answers(MyUser user, int answers);
void set_user_totalposts(MyUser user, int totalposts);
void set_lastpost (MyUser user, char * id, int data);
void aumenta_questions_user(MyUser user);
void aumenta_answers_user(MyUser user);
int compare_users (MyUser u1, MyUser u2);
int compare_users_rep (MyUser u1, MyUser u2);
USER toUSER (MyUser user);
void destroy_myuser (MyUser user);

#endif