#include <glib-2.0/gmodule.h>
#include <date.h>
#ifndef __MYPOST_H__
#define __MYPOST_H__
typedef struct mypost* MyPost;

MyPost create_mypost(char *id, char *title, char *ownerUser, Date data, int type, int answerCount);
char * get_post_id(MyPost post);
char * get_post_title(MyPost post);
char * get_post_ownerUser(MyPost post);
char * get_post_parentID(MyPost post);
Date get_post_data(MyPost post);
int get_post_type (MyPost post);
int get_post_comments (MyPost post);
int get_post_score (MyPost post);
int get_post_answerCount (MyPost post);
float get_post_pont(MyPost post);
GList* post_get_tags(MyPost post);
GList* post_get_resp(MyPost post);
GHashTable* post_get_resp_hash(MyPost post);
void set_post_id(MyPost post, char* id);
void set_post_title(MyPost post, char* title);
void set_post_ownerUser(MyPost post, char* ownerUser);
void set_post_parentID(MyPost post, char* parentID);
void set_post_score (MyPost post, int score);
void set_post_data(MyPost post, int data);
void set_post_type (MyPost post, int type);
void set_post_comments (MyPost post, int comments);
void set_post_tag (MyPost post, char *tag);
void set_post_resp (MyPost post, MyPost resp);
int post_contains_tag(MyPost post,char* tag);
void calc_post_pont (MyPost post, int reputation);
int get_best_answer(MyPost post);
int compare_posts (MyPost p1, MyPost p2);
int compare_votes (MyPost p1, MyPost p2);
int compare_answerCount(MyPost p1, MyPost p2);
MyPost post_clone(MyPost post);
void destroy_mypost (MyPost post);

#endif