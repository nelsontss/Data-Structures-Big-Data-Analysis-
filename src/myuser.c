#include <myuser.h>
#include <stdlib.h>
#include <common.h>
#include <string.h>
#include <pair.h>
#include <stdio.h>
#include <compare_date.h>

/**
 * Estrutura criada por nós que representa um utilizador
 */
struct myuser
{
	char * id; /**<Id do utilizador */
	char * name; /**<Nome do utilizador */
	char * aboutme; /**<Descrição do utilizador */
	int questions; /**<Número de questões do utilizador */
	int answers; /**<Número de respostas do utilizador */
	int total_posts; /**<Número de posts feitos pelo utilizador */
	int reputation; /**<Reputação do utilizador */
	GList* last_posts; /**<Lista com os ultimos posts feitos pelo utilizador */
};

/*
\ brief Função que cria um utilizador
@param id Id do utilizador
@param name Nome do utilizador
@param reputation Reputação do utilizador
@param aboutme Descrição do utilizador
@returns user Utilizador com os parâmetros dados
*/
MyUser create_myuser(char *id, char *name, int reputation, char* aboutme){
	MyUser user = (MyUser)malloc(sizeof(struct myuser));
	user->id = mystrdup(id);
	user->name = mystrdup(name);
	user->aboutme = mystrdup(aboutme);
	user->reputation = reputation;
	user->questions = 0;
	user->answers = 0;
	user->total_posts = 0;
	user->last_posts = NULL;
	return user;
}

/**
\ brief Função que dá o id do utilizador
@param user Utilizador recebido
@returns Id do utilizador se existir, NULL se não existir
*/
char * get_user_id(MyUser user){
	return user ? mystrdup(user->id) : NULL;
}

/**
\ brief Função que dá o nome do utilizador
@param user Utilizador recebido
@returns Nome do utilizador se existir, NULL se não existir
*/
char * get_user_name(MyUser user){
	return user ? mystrdup(user->name) : NULL;
}

/**
\ brief Função que dá a desrição do utilizador
@param user Utilizador recebido
@returns Descrição do utilizador se existir, NULL se não existir
*/
char * get_user_aboutme(MyUser user){
	return user ? mystrdup(user->aboutme) : NULL;
}

/**
\ brief Função que dá o número de questões do utilizador
@param user Utilizador recebido
@returns Número de questões do utilizador se existir, NULL se não existir
*/
int get_user_questions(MyUser user){
	return user ? user->questions : -1;
}

/**
\ brief Função que dá a reputação do utilizador
@param user Utilizador recebido
@returns Reputação do utilizador se existir, NULL se não existir
*/
int get_user_reputation(MyUser user){
	return user ? user->reputation : -1;
}

/**
\ brief Função que dá o número de respostas do utilizador
@param user Utilizador recebido
@returns Número de respostas do utilizador se existir, NULL se não existir
*/
int get_user_answers(MyUser user){
	return user ? user->answers : -1;
}

/**
\ brief Função que dá o número de posts do utilizador
@param user Utilizador recebido
@returns Numero de posts do utilizador se existir, NULL se não existir
*/
int get_user_totalposts(MyUser user){
	return user ? user->total_posts : -1;
}

/**
\ brief Função que dá a lista dos ultimos posts do utilizador
@param user Utilizador recebido
@returns Lista dos ultimos posts do utilizador se existir, NULL se não existir
*/
GList * get_user_lastposts (MyUser user){
	return user->last_posts;
}

/**
\ brief Função que define o id do utilizador
@param user Utilizador recebido
@param id Id do utilizador
*/
void set_user_id(MyUser user, char* id){
	free(user->id);
	user->id=mystrdup(id);
}

/**
\ brief Função que define o nome do utilizador
@param user Utilizador recebido
@param name Nome do utilizador
*/
void set_user_name(MyUser user, char* name){
	free(user->name);
	user->name=mystrdup(name);
}

/**
\ brief Função que define a descrição do utilizador
@param user Utilizador recebido
@param aboutme Descrição do utilizador
*/
void set_user_aboutme(MyUser user, char* aboutme){
	free(user->aboutme);
	user->aboutme=mystrdup(aboutme);
}

/**
\ brief Função que define a reputação do utilizador
@param user Utilizador recebido
@param reputation Reputação do utilizador
*/
void set_user_reputation(MyUser user, int reputation){
	user->reputation=reputation;
}

/**
\ brief Função que define as questões do utilizador
@param user Utilizador recebido
@param questions Questões do utilizador
*/
void set_user_questions(MyUser user, int questions){
	user->questions=questions;
}

/**
\ brief Função que define as respostas do utilizador
@param user Utilizador recebido
@param answers Respostas do utilizador
*/
void set_user_answers(MyUser user, int answers){
	user->answers=answers;
}

/**
\ brief Função que define o número total de posts do utilizador
@param user Utilizador recebido
@param total_posts Número total de posts do utilizador
*/
void set_user_totalposts(MyUser user, int total_posts){
	user->total_posts=total_posts;	
}

/**
\ brief Função que compara os segundos elementos dos pares, que são datas
@param pair1 1º par
@param pair2 2º par
@returns 1 se a data do par pair1 é menor que o do par pair2, 0 se as datas são iguais e -1 se a data do par pair1 é maior que o do par pair2
*/
int inv_strcmp (STR_pair pair1, STR_pair pair2){
	char *a = get_snd_str(pair1);
	char *b = get_snd_str(pair2);
	Date c = string_toDate(a);
	Date d = string_toDate(b);
	int x = compare_date(c,d);
	free (a);
	free (b);
	free_date(c);
	free_date(d);
	return -x;
}

/**
\ brief Função que define o último post feito pelo utilizador
@param user Utilizador recebido
@param id Id do post
@param data Data do post
*/
void set_lastpost (MyUser user, char * id, Date data){
	char *x = get_snd_str(g_list_nth_data(user->last_posts,9));
	char* date = date_toString(data);
	
	if(g_list_length (user->last_posts)<10)
		user->last_posts = g_list_insert_sorted_with_data(user->last_posts,create_str_pair(id,date),(GCompareDataFunc)inv_cmp,NULL);
	else{
		Date x_ = string_toDate(x);
		if(compare_date(x_,data)<0){
			GList* l=g_list_nth(user->last_posts,9);
			user->last_posts = g_list_remove_link(user->last_posts,l);
			free_str_pair(l->data);
			g_list_free(l);
			user->last_posts = g_list_insert_sorted_with_data(user->last_posts,create_str_pair(id,date),(GCompareDataFunc)inv_cmp,NULL);
		}
		free_date(x_);
	}
	
	free(date);
	free(x);
}

/**
\ brief Função que aumenta o número de perguntas feitas pelo utilizador
@param user Utilizador recebido
*/
void aumenta_questions_user(MyUser user){
	user->questions++;
	user->total_posts++;	
}

/**
\ brief Função que aumenta o número de respostas feitas pelo utilizador
@param user Utilizador recebido
*/
void aumenta_answers_user(MyUser user){
	user->questions++;
	user->total_posts++;	
}

/**
\ brief Função que compara a reputação de 2 utilizadores
@param u1 1º utilizador recebido
@param u2 2º utilizador recebido
@returns 1 se a reputação do utilizador u1 é menor que o do utilizador u2, 0 se as reputações são iguais e -1 se a reputação do utilizador u1 é maior que o do utilizador u2
*/
int compare_users_rep (MyUser u1, MyUser u2){
	if(u1->reputation<u2->reputation)
		return 1;
	if(u1->reputation==u2->reputation)
		return 0;
	
	return -1;
}

/**
\ brief Função que compara a reputação de 2 utilizadores
@param u1 1º utilizador recebido
@param u2 2º utilizador recebido
@returns 1 se o número total de posts do utilizador u1 é menor que o do utilizador u2, 0 se o número total de posts é igual e -1 se o número total de posts do utilizador u1 é maior que o do utilizador u2
*/
int compare_users (MyUser u1, MyUser u2){
	if(u1->total_posts<u2->total_posts)
		return 1;
	if(u1->total_posts==u2->total_posts)
		return 0;
	
	return -1;
}

/**
\ brief Função que transforma um myuser (estrutura do utilizador criada pelo grupo) num user (estrututa de um utilizador criada pelos docentes)
@param user Utilizador recebido
@returns Utilizador na estrutura "user"
*/
USER toUSER (MyUser user) {
	long post_history[10];
	GList* l = get_user_lastposts(user);
	int i = 0;
	char * str1 = "";
	char *aboutme = get_user_aboutme(user);
	while(i<10){
		if(g_list_nth_data(l,i)!=NULL){
			str1 = get_fst_str(g_list_nth_data(l,i));
			post_history[i]=strtol(str1,NULL,10);
			free(str1);
		}
		else
			post_history[i]=-1;
		i++;
	}
	USER r = create_user(aboutme,post_history);
	free(aboutme);
	return r;
}

/**
\ brief Função que liberta a memória ocupada pelo utilizador
@param user Utilizador recebido
*/
void destroy_myuser(MyUser user){
	free(user->id);
	free(user->name);
	free(user->aboutme);
	if(user->last_posts!=NULL)
		g_list_free_full(user->last_posts,(GDestroyNotify)free_str_pair);
	free(user);
}