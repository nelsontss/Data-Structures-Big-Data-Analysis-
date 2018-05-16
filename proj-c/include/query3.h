#include <interface.h>
#include <glib-2.0/gmodule.h>
#include <pair.h>
#include <date.h>

#ifndef QUERY3_H
#define QUERY3_H

LONG_pair total_posts_aux(GList* posts_list, long * total_questions, long * total_answers , Date begin, Date end);

#endif