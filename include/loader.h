#include <glib-2.0/gmodule.h>
#include <interface.h>
#include <myuser.h>
#include <mypost.h>


#ifndef LOADER_H
#define LOADER_H

int load_users(GHashTable* users, char *dump_path);
int load_posts(GHashTable* users, GHashTable* posts, long* total_questions, long* total_answers, char* dump_path);
GList* load_userslist(GHashTable* users);
GList* load_postslist(GHashTable* posts);
GList* load_questionslist (GList* posts_list);
GList* load_userslist_rep (GList* users_list);
int load_tags(GHashTable* tags, char* dump_path);
MyPost get_post (GHashTable* posts, char* id);
MyUser get_user(GHashTable* users, char* id);
int date_to_int(Date a);


#endif