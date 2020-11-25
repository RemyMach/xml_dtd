#ifndef CHRISTOPHE_H
#define CHRISTOPHE_H

#include "structure.h"
#include "validate_read.h"

int calcLignes(char*);
int calcCarL(char*,int);
void filterOne(char*,int,int);
int getDtdTag(LinkedListDtd* head_dtd, char* pathfile);

#endif