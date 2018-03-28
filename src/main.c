#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <pair.h>
#include <user.h>

int main(){
  Date a = createDate(14,9,2010);
  Date b = createDate(10,9,2010);
  TAD_community com;
  STR_pair pair;
  com=init();
  int i = 0;
  load(com,"xml/");
  //pair = info_from_post(com,1);
  //printf("%s--%s\n", get_fst_str(pair), get_snd_str(pair));
 
 	//LONG_list list = top_most_active(com,10);
  	//for(int i = 0;i<9;i++){
  		//printf("%ld\n", get_list(list,i));
  		
	//}
  //LONG_pair pair =total_posts(com,a,NULL);
  //printf("%ld--%ld\n", get_fst_long(pair), get_snd_long(pair));
  
  //LONG_list l = questions_with_tag(com, "sms",b , a);
  //for(int i=0;get_list(l,i)!=0;i++)
   // printf("%ld\n",get_list(l,i));
  USER user = get_user_info(com,241679);
  printf("%s\n",get_bio(user));
  long *post_history;
  post_history = get_10_latest_posts(user);
  while(i<10){
    printf("%ld\n", post_history[i]);
    i++;
  }
  return 0;
} 
