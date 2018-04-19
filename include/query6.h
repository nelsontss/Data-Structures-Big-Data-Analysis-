#include <glib-2.0/gmodule.h>
#include <list.h>
#include <date.h>

#ifndef QUERY6_H
#define QUERY6_H

LONG_list most_voted_answers_aux(GList* post_list, int N, Date begin, Date end);
	
#endif