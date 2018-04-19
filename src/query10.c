#include "query10.h"
#include <mypost.h>
#include <stdio.h>
#include <loader.h>

long better_answer_aux(GHashTable* users, long id){
	char id_str[10];
	sprintf(id_str,"%ld",id);
	MyPost post = get_post(users,id_str);
	return (long)get_best_answer(post);
}