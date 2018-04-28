#include "date_to_int.h"

/**
\brief Esta função passa uma data para o número de dias dessa data depois do ano 2000.
@param a Data original.
@returns Data transformada.
*/
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