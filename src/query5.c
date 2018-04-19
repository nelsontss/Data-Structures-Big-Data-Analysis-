#include "query5.h"
#include <stdio.h>
#include <myuser.h>
#include <loader.h>

USER get_user_info_aux(GHashTable* users, long id){
	char id_[10];
	sprintf(id_,"%ld", id);
	MyUser user = get_user(users,id_);
	USER r = toUSER(user);
	return r;
}
