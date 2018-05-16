#include <glib-2.0/gmodule.h>
#include <interface.h>
#include <myuser.h>
#include <mypost.h>


#ifndef LOADER_H
#define LOADER_H

int load_users(GHashTable* users, GList** users_list, GList** users_list_rep, char *dump_path);
int load_posts(GHashTable* users, GHashTable* posts, GList** posts_list, GList** questions_list, long* total_questions, long* total_answers, char* dump_path);
int load_tags(GHashTable* tags, char* dump_path);
GList* load_userslist_rep (GList* users_list);
MyPost get_post (GHashTable* posts, char* id);
MyUser get_user(GHashTable* users, char* id);



#endif