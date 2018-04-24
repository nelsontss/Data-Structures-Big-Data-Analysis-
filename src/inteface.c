#include "interface.h"
#include <glib-2.0/gmodule.h>
#include <string.h>
#include <myparser.h>
#include <myuser.h>
#include <mypost.h>
#include <loader.h>
#include <query1.h>
#include <query2.h>
#include <query3.h>
#include <query4.h>
#include <query5.h>
#include <query6.h>
#include <query7.h>
#include <query8.h>
#include <query9.h>
#include <query10.h>
#include <query11.h>


struct TCD_community
{
	GHashTable* posts;
	GHashTable* users;
	GHashTable* tags;
	GList* posts_list;
	GList* users_list;
	GList* questions_list;
	GList* users_list_rep;

	long total_questions;
	long total_answers;

};




MyPost g_list_get_post(GList* g){
	if (g==NULL)
		return NULL;
	return g->data;
}


TAD_community init() {
	TAD_community com =(TAD_community)malloc(sizeof(struct TCD_community));
	com->users = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)destroy_myuser);
	com->posts = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)destroy_mypost);
	com->tags = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)free);
	com->questions_list = NULL;
	com->posts_list = NULL;
	com->users_list = NULL;
	com->users_list_rep = NULL;
	com->total_answers = 0;
	com->total_questions = 0;
	return com;
}

TAD_community load(TAD_community com, char* dump_path){
	
	load_users(com->users,&(com->users_list),&(com->users_list_rep),dump_path);
	load_posts(com->users,com->posts,&(com->posts_list),&(com->questions_list),&com->total_questions,&com->total_answers,dump_path);
	com->users_list = g_list_sort (com->users_list,(GCompareFunc)compare_users);
	load_tags(com->tags,dump_path);
	return com;
}


STR_pair info_from_post(TAD_community com, long id){
	return info_from_post_aux(com->users, com->posts, id);
}


LONG_list top_most_active(TAD_community com, int N){
	return top_most_active_aux(com->users_list,N);
}

LONG_pair total_posts(TAD_community com, Date begin, Date end){
	return total_posts_aux(com->posts_list, &(com->total_questions), &(com->total_answers) , begin, end);

}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	return questions_with_tag_aux(com->questions_list, tag, begin, end,com->total_questions);
}

USER get_user_info(TAD_community com, long id){
	return get_user_info_aux(com->users, id);
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	return most_voted_answers_aux(com->posts_list,N,begin,end);
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	return most_answered_questions_aux(com->questions_list,N,begin,end);
}

LONG_list contains_word(TAD_community com, char* word, int N){
	return contains_word_aux(com->questions_list,word,N);
}


LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	return both_participated_aux(com->questions_list,id1,id2,N);
}

long better_answer(TAD_community com, long id){
	return better_answer_aux(com->posts,id);
}


LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	return most_used_best_rep_aux(com->posts_list,com->users_list_rep,com->tags,N,begin,end);
}


TAD_community clean(TAD_community com){
	g_hash_table_destroy(com->users);
	g_hash_table_destroy(com->posts);
	g_hash_table_destroy(com->tags);
	g_list_free(com->users_list_rep);
	g_list_free(com->posts_list);
	g_list_free(com->questions_list);
	g_list_free(com->users_list);	
	return com;
}
