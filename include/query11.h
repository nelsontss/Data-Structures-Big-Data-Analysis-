#include <glib-2.0/gmodule.h>
#include <list.h>
#include <date.h>

#ifndef QUERY11_H
#define QUERY11_H

LONG_list most_used_best_rep_aux(GList* posts_list, GList* users_list_rep, GHashTable *tags , int N, Date begin, Date end);
#endif