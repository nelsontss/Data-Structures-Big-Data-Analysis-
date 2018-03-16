#ifndef __MYPOST_H__
#define __MYPOST_H__
typedef struct mypost* MyPost;

MyPost create_mypost(char *id, char *title, char *ownerUser);
char * get_post_id(MyPost post);
char * get_post_title(MyPost post);
char * get_post_ownerUser(MyPost post);
void set_post_id(MyPost post, char* id);
void set_post_title(MyPost post, char* title);
void set_post_ownerUser(MyPost post, char* ownerUser);
void destroy_mypost (MyPost post);

#endif