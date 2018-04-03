#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <pair.h>
#include <user.h>

int main(){
  Date a = createDate(1,12,2017);
  Date b = createDate(3,12,2017);
  TAD_community com;
  STR_pair pair;
  com=init();
  int i = 0;
  load(com,"xml/");
   
  //pair = info_from_post(com,187246);
  //printf("%s--%s\n", get_fst_str(pair), get_snd_str(pair));
 
 	//LONG_list list = top_most_active(com,10);
  	//for(int i = 0;i<9;i++){
  		//printf("%ld\n", get_list(list,i));
  		
	//}
  //LONG_pair pair =total_posts(com,a,NULL);
  //printf("%ld--%ld\n", get_fst_long(pair), get_snd_long(pair));
  
  /*LONG_list x = questions_with_tag(com, "sms",b , a);
  for(int i=0;get_list(x,i)!=0;i++)
    printf("%ld\n",get_list(x,i));
  */
  //USER user = get_user_info(com,241679);
  //printf("%s\n",get_bio(user));
  //long *post_history;
  //post_history = get_10_latest_posts(user);
  //while(i<10){
   // printf("%ld\n", post_history[i]);
    //i++;
  //}
  /*LONG_list l = contains_word(com, "Nexus", 2);
  while(i<2){
    printf("%ld\n",get_list(l,i));
    i++;
  }*/

  //printf("%ld",better_answer(com,2342));
  /*LONG_list y = both_participated(com,241679,23340 , 2);
  while(i<2){
    printf("%ld\n",get_list(y,i));
    i++;
  }*/

  /*LONG_list z = most_voted_answers(com, 5, a, b);
  while(i<5){
    printf("%ld\n",get_list(z,i));
    i++;
  }*/
  LONG_list j = most_used_best_rep(com, 3, NULL, NULL);
  while(i<3){
    printf("%ld\n",get_list(j,i));
    i++;
  }
  return 0;
} 
