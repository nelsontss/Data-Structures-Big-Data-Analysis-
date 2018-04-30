#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <pair.h>
#include <time.h>
#include <user.h>
#include <stdlib.h>

int main(){
  Date a = createDate(1,1,2014);
  Date b = createDate(31,1,2014);
  Date c = createDate(1,1,2014);
  Date d = createDate(31,12,2014);
  Date e = createDate(1,5,2013);
  Date f = createDate(6,5,2013);
  Date g = createDate(1,1,2012);
  Date h = createDate(31,12,2012);
  Date i2 = createDate(1,1,2014);
  Date j2 = createDate(31,12,2014);
  TAD_community com;
  STR_pair pair1;
  com=init();
  int i = 0;
  
  clock_t begin2 = clock();
  load(com,"xml/");
  clock_t end2 = clock();
  printf("Tempo '0 - load' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);


  begin2 = clock();
  pair1 = info_from_post(com,796430);
  end2 = clock();
  printf("Tempo '1 - info_from_post' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Info_from_post:\n");
  char * str1 = get_fst_str(pair1);
  char * str2 = get_snd_str(pair1);
  printf("%s--%s\n", str1, str2);
  free(str1);
  free(str2);

  begin2 = clock();
  LONG_list list = top_most_active(com,100);
  end2 = clock();
  printf("Tempo '2 - top_most_active' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Top_most_active:\n");
  for(i = 0;i<100;i++){
      printf("%ld\n", get_list(list,i));
      
  }
  free_list(list);
  
  begin2 = clock();
  LONG_pair pair2 =total_posts(com,c,d);
  end2 = clock();
  printf("Tempo '3 - total_posts' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Total_posts:\n");
  printf("%ld--%ld\n", get_fst_long(pair2), get_snd_long(pair2));


  begin2 = clock();
  LONG_list x = questions_with_tag(com, "nautilus",a , b);
  end2 = clock();
  printf("Tempo '4 - questions_with_tag' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Questions_with_tag:\n");
  for(i=0;get_list(x,i)!=-1;i++){
    printf("%ld\n",get_list(x,i));
  }
  
  begin2 = clock();
  USER user = get_user_info(com,449);
  end2 = clock();
  printf("Tempo '5 - get_user_info' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
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
  

  begin2 = clock();
  LONG_list z = most_voted_answers(com, 50, e, f);
  end2 = clock();
  printf("Tempo '6 - most_voted_answers' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Most_voted_answers:\n");
  for(i=0;i<50;i++){
    printf("%ld\n",get_list(z,i));
  }
  

  begin2 = clock();
  LONG_list k= most_answered_questions(com, 100, g, h);
  end2 = clock();
  printf("Tempo '7 - most_answered_questions' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Most answerd questions:\n");
  for(i=0;i<100;i++){
    printf("%ld\n",get_list(k,i));
  }

  begin2 = clock();
  LONG_list l = contains_word(com, "glib", 10);
  end2 = clock();
  printf("Tempo '8 - contains_word' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Contains_word:\n");
  for(i=0;i<10;i++){
    printf("%ld\n",get_list(l,i));
  }

  begin2 = clock();
  LONG_list y = both_participated(com,253,455,5);
  end2 = clock();
  printf("Tempo '9 - both_participated' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Both_participated:\n");
  for(i=0;i<5;i++){
    printf("%ld\n",get_list(y,i));
  }


  begin2 = clock();
  long better = better_answer(com,5942);
  end2 = clock();
  printf("Tempo '10 - better_answer' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  printf("Better_answer: %ld\n",better);
  
  

  begin2 = clock();
  LONG_list j = most_used_best_rep(com, 10, i2, j2);
  end2 = clock();
  printf("Most_used_best_rep:\n");
  printf("Tempo '11 - most_used_best_rep' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
  for(i=0;i<10;i++){
    printf("%ld\n",get_list(j,i));
  }
    
  free_date(a);
  free_date(b);
  free_date(c);
  free_date(d);
  free_date(e);
  free_date(f);
  free_date(g);
  free_date(h);
  free_date(i2);
  free_date(j2);
  free_list(x);
  free_list(z);
  free_list(k);
  free_list(l);
  free_list(y);
  free_list(j);
  
  free_str_pair(pair1);
  free_long_pair(pair2);
  
  
  com = clean(com);
  free(com);
  return 0;
} 
