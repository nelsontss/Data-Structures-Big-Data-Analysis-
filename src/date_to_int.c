#include "date_to_int.h"

int date_to_int(Date a){
	return (get_year(a)-2000)*365+get_month(a)*30+get_day(a);
}