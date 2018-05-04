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

/**
@file interface.c
Definição da estrutura de dados e chamada das funções gerais.
*/

struct TCD_community
{
	GHashTable* posts; /**<Tabela de hash que contém os posts */ 
	GHashTable* users; /**<Tabela de hash que contém os utilizadores */
	GHashTable* tags; /**<Tabela de hash que contém as tags */
	GList* posts_list; /**<Lista que contém os posts */
	GList* users_list; /**<Lista que contém os utilizadores */
	GList* questions_list; /**<Lista que contém as questões */
	GList* users_list_rep; /**<Lista que contém as respostas de cada utilizador */

	long total_questions; /**<Valor que representa o número total de questões */
	long total_answers; /**<Valor que representa o número total de respostas */

};



/**
\brief Esta função devolve a informação de um post numa glist.
@param g Apontador para uma lista ligada do tipo GList.
@returns NULL se não estiver a apontar para um post ou g->data se estiver a apontar para um post.
*/
MyPost g_list_get_post(GList* g){
	if (g==NULL)
		return NULL;
	return g->data;
}

/**
\brief Inicia os parâmetros da estrutura de dados.
@returns Estrutura de dados.
*/
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

/**
\brief Carrega as listas e as tabelas de hash com a informação dos ficheiros xml.
@param com Estrutura de dados.
@param dump_path Caminho para o dump.
@returns Estrutura de dados.
*/
TAD_community load(TAD_community com, char* dump_path){
	
	load_users(com->users,&(com->users_list),&(com->users_list_rep),dump_path);
	load_posts(com->users,com->posts,&(com->posts_list),&(com->questions_list),&com->total_questions,&com->total_answers,dump_path);
	com->users_list = g_list_sort (com->users_list,(GCompareFunc)compare_users);
	load_tags(com->tags,dump_path);
	return com;
}

/**
\brief .
@param com Estrutura de dados.
@param id ID do post.
@returns Se for uma pergunta retorna o título e o ID do user, se for uma resposta retorna o títula da pergunta ao qual foi feita a resposta e o ID da pergunta.
*/
STR_pair info_from_post(TAD_community com, long id){
	return info_from_post_aux(com->users, com->posts, id);
}

/**
\brief Esta função encontra o top n de utilizadores mais ativos.
@param com Estrutura de dados.
@param N Numero de utilizadores do top.
@returns Lista com o top de utilizadores2.
*/
LONG_list top_most_active(TAD_community com, int N){
	return top_most_active_aux(com->users_list,N);
}

/**
\brief Esta função calcula o número de perguntas e respostas durante um intervalo de tempo.
@param com Estrutura de dados.
@param begin Início do intervalo.
@param end Fim do intervalo.
@returns Um par com o número de perguntas e respostas.
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end){
	return total_posts_aux(com->posts_list, &(com->total_questions), &(com->total_answers) , begin, end);

}

/**
\brief Esta função procura dentro de um intervalo de tempo, as perguntas com uma determinada tag.
@param com Estrutura de dados.
@param tag Apontador para a tag.
@param begin Início do intervalo de tempo.
@param end Fim do intervalo de tempo.
@returns Lista de perguntas com tag.
*/
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	return questions_with_tag_aux(com->questions_list, tag, begin, end,com->total_questions);
}

/**
\brief Dado um id retorna os últimos 10 posts do user e a short bio.
@param com Estrutura de dados.
@param id ID do utilizador.
@returns Últimos 10 posts do user e short bio.
*/
USER get_user_info(TAD_community com, long id){
	return get_user_info_aux(com->users, id);
}

/**
\brief Encontra o top N de respostas com mais votos dentro de um intervalo de tempo.
@param com Estrutura de dados.
@param N Numero de utilizadores do top.
@param begin Início do intervalo.
@param end Fim do intervalo.
@returns Lista com o top de utilizadores mais votados.
*/
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	return most_voted_answers_aux(com->posts_list,N,begin,end);
}

/**
\brief Encontra o top N de preguntas com mais respostas dentro de um intervalo de tempo.
@param com Estrutura de dados.
@param N Numero de utilizadores do top.
@param begin Início do intervalo.
@param end Fim do intervalo.
@returns Lista com o top de perguntas mais respondidas.
*/
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	return most_answered_questions_aux(com->questions_list,N,begin,end);
}

/**
\brief Procura os N posts mais recentes que contêm a palavra dada.
@param com Estrutura de dados.
@param word Palavra procurada.
@param N Número de posts a procurar.
@returns Lista com os ids dos posts que contêm a palavra.
*/
LONG_list contains_word(TAD_community com, char* word, int N){
	return contains_word_aux(com->questions_list,word,N);
}

/**
\brief Dados os IDs de dois utilizadores, devolver as últimas N perguntas em que participaram dois utilizadores específicos.
@param com Estrutura de dados.
@param id1 ID do utiliazdor 1.
@param id2 ID do utilizador 2.
@param N Número de perguntas.
@returns 0 se ambos participam ou 1 se não.
*/
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	return both_participated_aux(com->questions_list,id1,id2,N);
}

/**
\brief Dado um id de uma pergunta retorna a resposta mais votada por utilizadores com melhor reputação.
@param com Estrutura de dados.
@param id ID da pergunta.
@returns Resposta mais votada.
*/
long better_answer(TAD_community com, long id){
	return better_answer_aux(com->posts,id);
}

/**
\brief Dado um intervalo arbitrário de tempo,devolve as N tags mais usadas pelos N utilizadores com melhor reputação. Em ordem decrescente do número de vezes em que a tag foi usada.
@param posts_list Lista de posts.
@param users_list_rep Lista de users ordenados por reputação.
@param tags Tabela de hash de tags.
@param N Número de tags.
@param begin Data inicial.
@param end Data final.
@returns Lista final das tags.
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	return most_used_best_rep_aux(com->questions_list,com->users_list_rep,com->tags,N,begin,end);
}

/**
\brief Função que limpa as estruturas de armazenamento de dados.
@param com Estrutura de dados.
@returns Estutura de dados final.
*/
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
