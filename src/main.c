#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <pair.h>

int main(){
  Date a = createDate(3,12,2017);
  Date b = createDate(14,9,2010);
  TAD_community com;
 //STR_pair pair;
  com=init();
  load(com,"xml/");
  //pair = info_from_post(com,1210);
  //printf("%s--%s\n", get_fst_str(pair), get_snd_str(pair));
 
 	//LONG_list list = top_most_active(com,10);
  	//for(int i = 0;i<9;i++){
  		//printf("%ld\n", get_list(list,i));
  		
	//}
  LONG_pair pair =total_posts(com,a,NULL);
  printf("%ld--%ld\n", get_fst_long(pair), get_snd_long(pair));
  return 0;
} 
