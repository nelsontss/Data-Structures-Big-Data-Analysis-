#include <glib-2.0/gmodule.h>
#ifndef __MYUSER_H__
#define __MYUSER_H__
typedef struct myuser* MyUser;

MyUser create_myuser(char *id, char *name);
char * get_user_id(MyUser user);
char * get_user_name(MyUser user);
int get_user_questions(MyUser user);
int get_user_answers(MyUser user);
int get_user_totalposts(MyUser user);
GList * get_user_lastposts (MyUser user);
void set_user_id(MyUser user, char* name);
void set_user_name(MyUser user, char* id);
void set_user_questions(MyUser user, int questions);
void set_user_answers(MyUser user, int answers);
void set_user_totalposts(MyUser user, int totalposts);
void set_lastpost (MyUser user, char * id, int data);
void aumenta_questions_user(MyUser user);
void aumenta_answers_user(MyUser user);
int compare_users (MyUser u1, MyUser u2);
void destroy_myuser (MyUser user);

#endif