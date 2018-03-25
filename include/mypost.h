#ifndef __MYPOST_H__
#define __MYPOST_H__
typedef struct mypost* MyPost;

MyPost create_mypost(char *id, char *title, char *ownerUser, int data, char* post_type);
char * get_post_id(MyPost post);
char * get_post_title(MyPost post);
char * get_post_ownerUser(MyPost post);
int get_post_data(MyPost post);
char * get_post_type (MyPost post);
void set_post_id(MyPost post, char* id);
void set_post_title(MyPost post, char* title);
void set_post_ownerUser(MyPost post, char* ownerUser);
void set_post_data(MyPost post, int data);
void set_post_type (MyPost, char* post_type);
int compare_posts (MyPost p1, MyPost p2);
void destroy_mypost (MyPost post);

#endif