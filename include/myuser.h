#ifndef __MYUSER_H__
#define __MYUSER_H__
typedef struct myuser* MyUser;

MyUser create_myuser(char *id, char *name);
char * get_user_id(MyUser user);
char * get_user_name(MyUser user);
void set_user_id(MyUser user, char* name);
void set_user_name(MyUser user, char* id);
void destroy_myuser (MyUser user);

#endif