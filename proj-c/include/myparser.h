#include <libxml2/libxml/parser.h>

#ifndef MYPARSER_H
#define MYPARSER_H

xmlDocPtr open_doc(char *dump_path);
int get_prop(xmlNodePtr cur, char * prop, char * res);

#endif