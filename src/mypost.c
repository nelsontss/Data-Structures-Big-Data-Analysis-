#include <mypost.h>
#include <common.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pair.h>
#include <compare_date.h>


struct mypost
{
	char* id;
	char* title;
	char* ownerUser;
	char* parentID;
	Date data;
	int type;
	GList *tags;
	GList *resp;
	int answerCount;
	int score;
	int comments;
	float pont;
};

MyPost create_mypost(char* id, char* title, char* ownerUser, Date data, int type, int answerCount){
	MyPost post= (MyPost) malloc(sizeof(struct mypost));
	post->id = mystrdup(id);
	post->title= mystrdup(title);
	post->ownerUser= mystrdup(ownerUser);
	post->data = data;
	post->type = type;
	post->tags = NULL;
	post->resp = NULL;
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

Date get_post_data (MyPost post){
	return post ? post->data : NULL;
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
	post->pont = (post->score*0.65)+(reputation*0.25)+(post->comments*0.1);
}




int post_contains_tag(MyPost post,char* tag) {
	if(g_list_find_custom(post->tags,tag,(GCompareFunc)strcmp)==NULL)
		return 1;
	return 0;
}

int compare_posts (MyPost p1, MyPost p2){
	

	return -1*compare_date(p1->data,p2->data);
}

int compare_votes (MyPost p1, MyPost p2){
	if(p1->score<p2->score)
		return 1;
	if(p1->score==p2->score)
		return 0;

	return -1;
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
	int r = get_snd_long(pair);
	free_long_pair(pair);
	return r;
}


void destroy_mypost (MyPost post){
	free(post->id);
	free(post->title);
	free(post->ownerUser);
	free(post->parentID);
	free_date(post->data);
	g_list_free_full(post->tags,(GDestroyNotify)free);
	g_list_free(post->resp);
	free(post);
}

