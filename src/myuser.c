#include <myuser.h>
#include <stdlib.h>
#include <common.h>
struct myuser
{
	char * id;
	char * name;
};

MyUser create_myuser(char *id, char *name){
	MyUser user = (MyUser)malloc(sizeof(struct myuser));
	user->id = mystrdup(id);
	user->name = mystrdup(name);

	return user;
}

char * get_user_id(MyUser user){
	return user ? mystrdup(user->id) : NULL;
}

char * get_user_name(MyUser user){
	return user ? mystrdup(user->name) : NULL;
}

void set_user_id(MyUser user, char* id){
	free(user->id);
	user->id=mystrdup(id);
}

void set_user_name(MyUser user, char* name){
	free(user->name);
	user->name=mystrdup(name);
}

void destroy_myuser(MyUser user){
	free(user->id);
	free(user->name);
	free(user);
}