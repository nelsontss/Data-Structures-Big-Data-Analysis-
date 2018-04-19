#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <pair.h>
#include <user.h>
#include <stdlib.h>

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
  char * str1 = get_fst_str(pair1);
  char * str2 = get_snd_str(pair1);
  printf("%s--%s\n", str1, str2);
  free(str1);
  free(str2);


  LONG_list list = top_most_active(com,10);
    printf("Top_most_active:\n");
    for(i = 0;i<9;i++){
      printf("%ld\n", get_list(list,i));
      
    }
  LONG_pair pair2 =total_posts(com,b,NULL);
  printf("Total_posts:\n");
  printf("%ld--%ld\n", get_fst_long(pair2), get_snd_long(pair2));
  
  LONG_list x = questions_with_tag(com, "twrp",b , NULL);
  printf("Questions_with_tag:\n");
  for(i=0;get_list(x,i)!=-1;i++){
    printf("%ld\n",get_list(x,i));
  }
  
  USER user = get_user_info(com,241593);
  printf("Get_user_info:\n");
  printf("bio: %s\n",get_bio(user));
  long *post_history;
  post_history = get_10_latest_posts(user);
  printf("10_latest_posts:\n");
  for(i=0;i<10;i++){
   printf("%ld\n", post_history[i]);
  }
  free(post_history);
  free_user(user);

  LONG_list z = most_voted_answers(com, 5, a, b);
  printf("Most_voted_answers:\n");
  for(i=0;i<5;i++){
    printf("%ld\n",get_list(z,i));
  }


  LONG_list k= most_answered_questions(com, 10, a, b);
  printf("Most answerd questions:\n");
  for(i=0;i<10;i++){
    printf("%ld\n",get_list(k,i));
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
	
  com = clean(com);
  free_date(a);
  free_list(x);
  free_date(b);
  free_list(z);
  free_list(k);
  free_list(l);
  free_list(y);
  free_list(j);
  free_list(list);
  free(com);
  free_str_pair(pair1);
  free_long_pair(pair2);
  return 0;
} 

