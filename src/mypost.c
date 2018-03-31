#include <mypost.h>
#include <common.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pair.h>

struct mypost
{
	char* id;
	char* title;
	char* ownerUser;
	char* parentID;
	int data;
	int type;
	GList *tags;
	GList *resp;
	int votes;
	int answerCount;
	int score;
	int comments;
	float pont;
};

MyPost create_mypost(char* id, char* title, char* ownerUser, int data, int type, int answerCount){
	MyPost post= (MyPost) malloc(sizeof(struct mypost));
	post->id = mystrdup(id);
	post->title= mystrdup(title);
	post->ownerUser= mystrdup(ownerUser);
	post->data = data;
	post->type = type;
	post->tags = NULL;
	post->resp = NULL;
	post->votes = 0;
	post->score = 0;
	post->comments = 0;
	post->pont = 0;
	post->answerCount = answerCount;
	post->parentID = mystrdup(" ");
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

char * get_post_parentID(MyPost post){
	return post ? mystrdup(post->parentID) : NULL;
}

int get_post_data (MyPost post){
	return post ? post->data : -1;
}

float get_post_pont (MyPost post){
	return post ? post->pont : -1;
}

int get_post_comments (MyPost post){
	return post ? post->comments : -1;
}

int get_post_score (MyPost post){
	return post ? post->score : -1;
}

int get_post_type (MyPost post){
	return post ? post->type : -1;
}

int get_post_votes (MyPost post){
	return post ? post->votes : -1;
}

int get_post_answerCount (MyPost post){
	return post ? post->answerCount : -1;
}

GList* post_get_tags(MyPost post){
	return post->tags;
}

GList* post_get_resp(MyPost post){
	return post->resp;
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

void set_post_parentID(MyPost post, char* parentID){
	free(post->parentID);
	post->parentID=mystrdup(parentID);
}

void set_post_score (MyPost post, int score){
	post->score = score;
}

void set_post_comments (MyPost post, int comments){
	post->comments = comments;
}

void set_post_data (MyPost post, int data){
	post->data = data;
}

void set_post_type (MyPost post, int type){
	post->type = type;
}


void set_post_tag (MyPost post, char *tag){
	post->tags = g_list_append(post->tags,mystrdup(tag));
}

void set_post_resp (MyPost post, MyPost resp){
	if(post!=NULL)
	post->resp = g_list_append(post->resp,resp);
}


void calc_post_pont (MyPost post, int reputation){
	post->pont = (post->score*0.45)+(reputation*0.25)+(post->votes*0.2)+(post->comments*0.1);
}


void insert_tags(MyPost post,char *tags) {
	int i = 1;
	int a  = 1;	
	char *aux=mystrdup(tags) ;
	while(tags[i]!='\0'){
		if(tags[i]=='<')
			a=i+1;
		if(tags[i]=='>'){
			aux[i]='\0';
			set_post_tag(post,aux+a);
		}
		i++;
	}
}

int post_contains_tag(MyPost post,char* tag) {
	if(g_list_find_custom(post->tags,tag,(GCompareFunc)strcmp)==NULL)
		return 1;
	return 0;
}

int compare_posts (MyPost p1, MyPost p2){
	if(p1->data<p2->data)
		return -1;
	if(p1->data==p2->data)
		return 0;

	return 1;
}

void best(MyPost data, LONG_pair pair){
	if(data->pont>get_fst_long(pair)){
		set_fst_long(pair,(long)data->pont);
		set_snd_long(pair,strtol(data->id,NULL,10));
	}
}

int get_best_answer(MyPost post){
	LONG_pair pair = create_long_pair(0,0);

	g_list_foreach(post->resp,(GFunc)best,pair);
	return get_snd_long(pair);
}

void up_post_votes(MyPost post){
	if(post!=NULL)
	post->votes+=1;
}

void down_post_votes(MyPost post){
	if(post!=NULL)
	post->votes+=1;
}

void destroy_mypost (MyPost post){
	free(post->id);
	free(post->title);
	free(post->ownerUser);
	free(post->parentID);
	g_list_free(post->tags);
	free(post);
}

