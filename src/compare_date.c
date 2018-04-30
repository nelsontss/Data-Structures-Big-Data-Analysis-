#include "compare_date.h"
#include <stdlib.h>
#include <stdio.h>
#include <common.h>

int compare_date(Date d1, Date d2){
	if(get_year(d1)<get_year(d2))
		return -1;
	else if(get_year(d1)>get_year(d2))
			return 1;
		 else if(get_month(d1)<get_month(d2))
		 		return -1;
		 	  else if(get_month(d1)>get_month(d2))
		 	  		return 1;
		 	  	   else if(get_day(d1)<get_day(d2))
		 	  	   		return -1;
		 	  	   		else if(get_day(d1)>get_day(d2))
		 	  	   				return 1;
		 	  	   			 else return 0;
}


char* date_toString (Date a){
	char r[11];
	sprintf(r,"%.2d-%.2d-%.4d",get_day(a),get_month(a),get_year(a));

	return mystrdup(r);
}

Date string_toDate (char* s){
	char *aux=mystrdup(s);
	int i=0, day, month, year;
	while (aux[i]!='\0'){
		if(aux[i]=='-')
			aux[i]='\0';
		i++;
	}
	
	
	year= atoi(aux+6);
	month= atoi(aux+3);
	day= atoi(aux);
	
	free(aux);
	return createDate (day,month,year);
}