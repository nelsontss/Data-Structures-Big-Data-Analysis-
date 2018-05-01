#include "../include/myparser.h"
#include <string.h>

/**
\ brief Função que abre os ficheiros xml
@param dump_path Caminho para a pasta que contém os ficheiros xml
*/
xmlDocPtr open_doc(char *dump_path){
	xmlDocPtr doc = xmlParseFile(dump_path);
	xmlNodePtr cur;
	if(!doc){
		printf("Document not parser successfully\n");
		xmlFreeDoc(doc);
		return NULL;
	}
	
	cur = xmlDocGetRootElement(doc);

	if(!cur){
		printf("Empty document\n");
		xmlFreeDoc(doc);
	}
	return doc;
}

/**
\ brief Função que 
@param cur Apontador para uma zona do ficheiro
@param prop String que contém informação para algo
@param res Local onde poderá ser colocado o id
@returns 1 se o id não existe e 0 se existe
*/
int get_prop(xmlNodePtr cur, char * prop, char * res){

	
	xmlChar *id;
	id = xmlGetProp(cur,(xmlChar*)prop);
	if(id==NULL)
		return 1;
	strcpy(res,(const char *)id);
	
	xmlFree(id);
return 0;
}


