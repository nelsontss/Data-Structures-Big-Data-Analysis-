#include <mypost.h>
#include <common.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pair.h>
#include <compare_date.h>

/**
 * Estrutura criada por nós que representa um post
 */
struct mypost
{
	char* id; /**< Id do post */
	char* title; /**<Titulo do post */
	char* ownerUser; /**<Id do proprietário do post */
	char* parentID; /**< Caso o post seja uma resposta representa o id da pergunta */
	Date data; /**<Data em que o post foi escrito */
	int type; /**<Tipo do post, 1 se for pergunta e 2 se for resposta */
	GList *tags; /**<Lista das tags do post caso seja pergunta */
	GList *resp; /**<Lista das respostas caso o post seja uma pergunta */
	GHashTable *resp_hash; /**<Tabela de hash que contém as respostas caso o post seja uma pergunta */
	int answerCount; /**<Número de respostas caso o post seja uma pergunta */
	int score; /**<Score do post */
	int comments; /**<Número de comentários do post caso seja resposta */
	float pont; /**<Valor do calculo da média ponderada indicada na query 10 */
};

/**
\ brief Função que cria um post dados os parâmetros da estrutura
@param id Id do post
@param title Titulo do post
@param ownerUser Id do proprietário do post
@param data Data em que o post foi escrito
@param type Tipo do post
@param answerCount Número de respostas do post
@returns Post com os argumentos dados
*/
MyPost create_mypost(char* id, char* title, char* ownerUser, Date data, int type, int answerCount){
	MyPost post= (MyPost) malloc(sizeof(struct mypost));
	post->id = mystrdup(id);
	post->title= mystrdup(title);
	post->ownerUser= mystrdup(ownerUser);
	post->data = data;
	post->type = type;
	post->tags = NULL;
	post->resp_hash = g_hash_table_new_full(g_str_hash,g_str_equal,free,NULL);
	post->resp = NULL;
	post->score = 0;
	post->comments = 0;
	post->pont = 0;
	post->answerCount = answerCount;
	post->parentID = mystrdup(" ");
	return post;
}

/**
\ brief Função que dá o id do post
@param post Post recebido
@returns Id do post se o post existe, NULL se não existe
*/
char * get_post_id(MyPost post){
	return post ? mystrdup(post->id) : NULL;
}

/**
\ brief Função que dá o titulo do post
@param post Post recebido
@returns Titulo do post se o post existe, NULL se não existe
*/
char * get_post_title(MyPost post){
	return post ? mystrdup(post->title) : NULL;
}

/**
\ brief Função que dá o id do proprietário do post
@param post Post recebido
@returns Id do proprietário do post se o post existe, NULL se não existe
*/
char * get_post_ownerUser(MyPost post){
	return post ? mystrdup(post->ownerUser) : NULL;
}

/**
\ brief Função que dá o id da pergunta a que o post dá resposta
@param post Post recebido
@returns Id da pergunta a que o post dá resposta se o post existe, NULL se não existe
*/
char * get_post_parentID(MyPost post){
	return post ? mystrdup(post->parentID) : NULL;
}

/**
\ brief Função que dá a data do post
@param post Post recebido
@returns Data do post se o post existe, -1 se não existe
*/
Date get_post_data (MyPost post){
	return post ? post->data : NULL;
}

/**
\ brief Função que dá a média ponderada do post (indicado na query 10)
@param post Post recebido
@returns Média ponderada do post se o post existe, -1 se não existe
*/
float get_post_pont (MyPost post){
	return post ? post->pont : -1;
}
 /**
\ brief Função que dá o número de comentários do post
@param post Post recebido
@returns Número de comentários do post se o post existe, -1 se não existe
*/
int get_post_comments (MyPost post){
	return post ? post->comments : -1;
}

/**
\ brief Função que dá o score do post
@param post Post recebido
@returns Score do post se o post existe, -1 se não existe
*/
int get_post_score (MyPost post){
	return post ? post->score : -1;
}

/**
\ brief Função que dá o tipo do post
@param post Post recebido
@returns Tipo do post se o post existe, -1 se não existe
*/
int get_post_type (MyPost post){
	return post ? post->type : -1;
}

/**
\ brief Função que dá o número de respostas do post
@param post Post recebido
@returns Número de respostas do post se o post existe, NULL se não existe
*/
int get_post_answerCount (MyPost post){
	return post ? post->answerCount : -1;
}

/**
\ brief Função que dá a lista de tags do post
@param post Post recebido
@returns Lista de tags do post
*/
GList* post_get_tags(MyPost post){
	return post->tags;
}

/**
\ brief Função que dá lista das respostas do post
@param post Post recebido
@returns Lista das respostas do post
*/
GList* post_get_resp(MyPost post){
	return post->resp;
}

/**
\ brief Função que dá a tabela de hash das respostas do post
@param post Post recebido
@returns Tabela de hash das respostas do post
*/
GHashTable* post_get_resp_hash(MyPost post){
	return post->resp_hash;
}

/**
\ brief Função que define o id do post
@param post Post recebido
@param id Id do post
*/
void set_post_id(MyPost post, char* id){
	free(post->id);
	post->id=mystrdup(id);
}

/**
\ brief Função que define o titulo do post
@param post Post recebido
@param title Titulo do post
*/
void set_post_title(MyPost post, char* title){
	free(post->title);
	post->title=mystrdup(title);
}

/**
\ brief Função que define o id do proprietário do post
@param post Post recebido
@param ownerUser Id do proprietário post
*/
void set_post_ownerUser(MyPost post, char* ownerUser){
	free(post->ownerUser);
	post->ownerUser=mystrdup(ownerUser);
}

/**
\ brief Função que define o id da pergunta a que o post dá resposta
@param post Post recebido
@param parentID Id da pergunta a que o post dá resposta
*/
void set_post_parentID(MyPost post, char* parentID){
	free(post->parentID);
	post->parentID=mystrdup(parentID);
}

/**
\ brief Função que define o score do post
@param post Post recebido
@param score Score do post
*/
void set_post_score (MyPost post, int score){
	post->score = score;
}

/**
\ brief Função que define o número de comentários do post
@param post Post recebido
@param comments Número de comentários do post
*/
void set_post_comments (MyPost post, int comments){
	post->comments = comments;
}

/**
\ brief Função que define o tipo do post
@param post Post recebido
@param type Tipo do post
*/
void set_post_type (MyPost post, int type){
	post->type = type;
}

/**
\ brief Função que adiciona à lista de tags do post uma nova tag
@param post Post recebido
@param tag Tag do post
*/
void set_post_tag (MyPost post, char *tag){
	post->tags = g_list_append(post->tags,mystrdup(tag));
}

/**
\ brief Função que adiciona uma resposta à lista de respostas do post
@param post Post recebido
@param resp Resposta do post 
*/
void set_post_resp (MyPost post, MyPost resp){
	if(post!=NULL){
	post->resp = g_list_append(post->resp,resp);
	g_hash_table_insert(post->resp_hash,get_post_ownerUser(resp),resp);
	}
}

/**
\ brief Função que calcula a média ponderada do post (indicado na query 10)
@param post Post recebido
@param reputation Reputação do post
*/
void calc_post_pont (MyPost post, int reputation){
	post->pont = (post->score*0.65)+(reputation*0.25)+(post->comments*0.1);
}

/**
\ brief Função que indica se o post contém a tag dada no parametro
@param post Post recebido
@param tag Tag do post
@returns 1 se o post não contém a tag do parametro, 0 se existe
*/
int post_contains_tag(MyPost post, char* tag) {
	if(g_list_find_custom(post->tags,tag,(GCompareFunc)strcmp)==NULL)
		return 1;
	return 0;
}

/**
\ brief Função que compara dois posts relativamente às suas datas
@param p1 Post 1 recebido
@param p2 Post 2 recebido
@returns 1 se a data do post p1 é menor que a do post p2, 0 se forem iguais e -1 se a data do post p1 é maior que a do post p2
*/
int compare_posts (MyPost p1, MyPost p2){
	return -1*compare_date(p1->data,p2->data);
}

/**
\ brief Função que compara os votos de 2 posts
@param p1 Post 1 recebido
@param p2 Post 2 recebido
@returns 1 se o score do post p1 é menor que o do p2, 0 se os scores são iguais e -1 se o score do post p1 é maior que o do post p2
*/
int compare_votes (MyPost p1, MyPost p2){
	if(p1->score<p2->score)
		return 1;
	if(p1->score==p2->score){
		if (atoi(p1->id) < atoi(p2->id))
			return 1;
		else
			if (atoi(p1->id) < atoi(p2->id))
				return -1;
			else
				return 0;
	}

	return -1;
}

/**
\ brief Função que compara o número de respostas do post
@param p1 Post 1 recebido
@param p2 Post 2 recebido
@returns 1 se o número de respostas do post p1 é menor que o do post p2, 0 se forem iguais e -1 se o número de respostas do post p1 for maior que o do post p2
*/
int compare_answerCount(MyPost p1, MyPost p2){
	if (p1->answerCount<p2->answerCount)
		return 1;
	if (p1->answerCount==p2->answerCount){
		if (atoi(p1->id) < atoi(p2->id))
			return 1;
		else
			if (atoi(p1->id) < atoi(p2->id))
				return -1;
			else
				return 0;
	}
	return -1;
}

/**
\ brief Função que compara o valor pont de data com o primeiro elemento do par e caso seja maior coloca-o no primeiro elemento do par e o id desse post no segundo elemento do par
@param data Post recebido
@param pair Par de longs recebido
*/
void best(MyPost data, LONG_pair pair){
	if(data->pont>get_fst_long(pair)){
		set_fst_long(pair,(long)data->pont);
		set_snd_long(pair,strtol(data->id,NULL,10));
	}
}

/**
\ brief Função que recebe o id da melhor resposta
@param post Post recebido
@returns Id da melhor resposta
*/
int get_best_answer(MyPost post){
	LONG_pair pair = create_long_pair(0,0);

	g_list_foreach(post->resp,(GFunc)best,pair);
	int r = get_snd_long(pair);
	free_long_pair(pair);
	return r;
}

/**
\ brief Função que dá free de um post e os seus componentes
@param post Post recebido
*/
void destroy_mypost (MyPost post){
	free(post->id);
	free(post->title);
	free(post->ownerUser);
	free(post->parentID);
	g_list_free_full(post->tags,(GDestroyNotify)free);
	g_hash_table_destroy(post->resp_hash);
	g_list_free(post->resp);
	free(post);
}

