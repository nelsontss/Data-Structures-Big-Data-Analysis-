#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <pair.h>
#include <user.h>

int main(){
  Date a = createDate(1,12,2017);
  Date b = createDate(3,12,2017);
  TAD_community com;
  STR_pair pair1;
  com=init();
  int i = 0;
  load(com,"xml/");
   
  pair1 = info_from_post(com,187246);
  printf("Info_from_post:\n");
  printf("%s--%s\n", get_fst_str(pair1), get_snd_str(pair1));
 
 	LONG_list list = top_most_active(com,10);
  	printf("Top_most_active:\n");
    for(i = 0;i<9;i++){
  		printf("%ld\n", get_list(list,i));
  		
	  }
  LONG_pair pair2 =total_posts(com,a,NULL);
  printf("Total_posts:\n");
  printf("%ld--%ld\n", get_fst_long(pair2), get_snd_long(pair2));
  
  LONG_list x = questions_with_tag(com, "sms",NULL , NULL);
  printf("Questions_with_tag:\n");
  for(i=0;get_list(x,i)!=0;i++){
    printf("%ld\n",get_list(x,i));
  }
  
  USER user = get_user_info(com,241679);
  printf("Get_user_info:\n");

  printf("bio: %s\n",get_bio(user));
  long *post_history;
  post_history = get_10_latest_posts(user);
  printf("10_latest_posts:\n");
  for(i=0;i<10;i++){
   printf("%ld\n", post_history[i]);
  }


  LONG_list z = most_voted_answers(com, 5, a, b);
  printf("Most_voted_answers:\n");
  for(i=0;i<5;i++){
    printf("%ld\n",get_list(z,i));
  }

  LONG_list l = contains_word(com, "Nexus", 2);
  printf("Contains_word:\n");
  for(i=0;i<2;i++){
    printf("%ld\n",get_list(l,i));
  }

  LONG_list y = both_participated(com,241679,23340 , 2);
  printf("Both_participated:\n");
  for(i=0;i<2;i++){
    printf("%ld\n",get_list(y,i));
  }

  printf("Better_answer: %ld\n",better_answer(com,2342));
  

  
  LONG_list j = most_used_best_rep(com, 3, NULL, NULL);
  printf("Most_used_best_rep:\n");
  for(i=0;i<3;i++){
    printf("%ld\n",get_list(j,i));
  }
  return 0;
} 
