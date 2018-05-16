#include <glib-2.0/gmodule.h>
#include <list.h>
#include <date.h>

#ifndef QUERY7_H
#define QUERY7_H

LONG_list most_answered_questions_aux(GList* posts_list, int N, Date begin, Date end);
	
#endif