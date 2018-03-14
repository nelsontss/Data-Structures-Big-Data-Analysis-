#include "../include/myparser.h"
#include <string.h>

xmlDocPtr open_doc(char *dump_path){
	xmlDocPtr doc = xmlParseFile(dump_path);
	xmlNodePtr cur;
	if(!doc){
		printf("Document not parser successfully\n");
		return NULL;
	}
	
	cur = xmlDocGetRootElement(doc);

	if(!cur){
		printf("Empty document\n");
		xmlFreeDoc(doc);
	}
	return doc;
}



int get_prop(xmlNodePtr cur, char * prop, char * res){

	
	xmlChar *id;
	id = xmlGetProp(cur,(xmlChar*)prop);
	if(id==NULL)
		return 1;
	strcpy(res,(const char *)id);
	
	xmlFree(id);
return 0;
}


