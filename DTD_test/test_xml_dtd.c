#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "../christophe.h"

int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, "xml_test/valid_14.xml");
    if(strcmp(head->name, "") != 0) 
        //freeLinkedListTag(head);
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 3 et 4\n");
        return 0;
    }else {
        printf("le fichier xml est valide\n");
    }

    LinkedListDtd* head_dtd1 = intialisationDtd("");
    int valid_dtd;
    valid_dtd = getDtdTag(head_dtd1, "DTD_test/valid_14.dtd");
    if(valid_dtd == 0)
        return 0; 

    if( verifymatchXmlDtd(head, head_dtd1) != 1 ) {
        printf("\n**********************************\n");
        printf("le XML ne correspond pas à la DTD\n");
    }else {
        printf("\n**********************************\n");
        printf("le XML correspond bien à la DTD\n");
    }
    printf("**********************************\n");
    printTagsDtd(head_dtd1);
    printf("**********************************\n");
    printf("**********************************\n");
    printTags(head);
    if(strcmp(head->name, "") != 0) 
        //freeLinkedListTag(head);
    return 0;
}