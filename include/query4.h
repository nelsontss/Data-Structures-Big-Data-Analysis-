#include <glib-2.0/gmodule.h>
#include <date.h>
#include <list.h>

#ifndef QUERY4_H
#define QUERY4_H

LONG_list questions_with_tag_aux(GList* posts_list, char* tag, Date begin, Date end, long total_questions);

#endif