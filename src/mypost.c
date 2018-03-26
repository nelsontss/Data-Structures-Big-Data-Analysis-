#include <mypost.h>
#include <common.h>
#include <stdlib.h>


struct mypost
{
	char* id;
	char* title;
	char* ownerUser;
	int data;
	int type;
};

MyPost create_mypost(char* id, char* title, char* ownerUser, int data, int type){
	MyPost post= (MyPost) malloc(sizeof(struct mypost));
	post->id = mystrdup(id);
	post->title= mystrdup(title);
	post->ownerUser= mystrdup(ownerUser);
	post->data= data;
	post->type= type;
	return post;
}

char * get_post_id(MyPost post){
	return post ? mystrdup(post->id) : NULL;
}

char * get_post_title(MyPost post){
	return post ? mystrdup(post->title) : NULL;
}

char * get_post_ownerUser(MyPost post){
	return post ? mystrdup(post->ownerUser) : NULL;
}

int get_post_data (MyPost post){
	return post ? post->data : -1;
}

int get_post_type (MyPost post){
	return post ? post->type : -1;
}

void set_post_id(MyPost post, char* id){
	free(post->id);
	post->id=mystrdup(id);
}

void set_post_title(MyPost post, char* title){
	free(post->title);
	post->title=mystrdup(title);
}

void set_post_ownerUser(MyPost post, char* ownerUser){
	free(post->ownerUser);
	post->ownerUser=mystrdup(ownerUser);
}

void set_post_data (MyPost post, int data){
	post->data = data;
}

void set_post_type (MyPost post, int type){
	post->type = type;
}

int compare_posts (MyPost p1, MyPost p2){
	if(p1->data<p2->data)
		return -1;
	if(p1->data==p2->data)
		return 0;

	return 1;
}

void destroy_mypost (MyPost post){
	free(post->id);
	free(post->title);
	free(post->ownerUser);
	free(post);
}

