#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "../christophe.h"

int main(int argc, char *argv[]) {

    if(argc != 3) {
        displayArgDTD();
        return 0;
    }
    char xml_prev[] = "xml_test/";
    char name_xml[strlen(xml_prev) + strlen(argv[1]) +1];
    sprintf(name_xml,"%s%s",xml_prev, argv[1]);

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateSecondPart(head, name_xml);
    
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 2\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }

    char dtd_prev[] = "DTD_test/";
    char name_dtd[strlen(dtd_prev) + strlen(argv[2]) +1];
    sprintf(name_dtd,"%s%s",dtd_prev, argv[2]);

    LinkedListDtd* head_dtd = intialisationDtd("");
    int valid_dtd;
    valid_dtd = getDtdTag(head_dtd, name_dtd);
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
    /*printTagsDtd(head_dtd);
    printf("**********************************\n");
    printf("**********************************\n");
    printTags(head);*/
    if(strcmp(head->name, "") != 0) 
        freeLinkedListTag(head);

    return 0;
}