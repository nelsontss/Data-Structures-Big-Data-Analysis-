#include "date_to_int.h"

int date_to_int(Date a){
	int y = get_year(a);
	int m = get_month(a);
	int d = get_day(a);
	int aux = 30;
	if(m % 2 != 0 || m == 8)
		aux = 31;
	if(m == 2)
		aux = 28;

	return (y-2000)*365+m*aux+d;
}