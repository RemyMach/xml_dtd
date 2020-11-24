#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "../christophe.h"

int main() {

    int valid;

    LinkedListTag* head = intialisation("");
    valid = validateSecondPart(head2, "xml_test/valid_1.xml");
    if(strcmp(head2->name, "") != 0) 
        //freeLinkedListTag(head2);
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 2\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }

    LinkedListDtd* head_dtd = intialisationDtd("");
    int valid_dtd;
    valid_dtd = getDtdTag(head_dtd, "DTD_test/valid_13.dtd");
    if(valid_dtd == 0)
        return 0; 
    
    if( verifymatchXmlDtd(head, head_dtd) != 1 ) {
        printf("\n**********************************\n");
        printf("le XML ne correspond pas à la DTD\n");
    }else {
        printf("\n**********************************\n");
        printf("le XML correspond bien à la DTD\n");
    }
    printf("**********************************\n");
    printTagsDtd(head_dtd);
    printf("**********************************\n");
    printf("**********************************\n");
    printTags(head);

    return 0;
}