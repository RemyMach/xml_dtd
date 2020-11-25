#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"

int main(int argc, char *argv[]) {

    if(argc != 2) {
        displayArgXML();
        return 0;
    }
    char xml_prev[] = "xml_test/";
    char name_xml[strlen(xml_prev) + strlen(argv[1]) +1];
    sprintf(name_xml,"%s%s",xml_prev, argv[1]);

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, name_xml);
    if(strcmp(head->name, "") != 0) 
        freeLinkedListTag(head);
    
    
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 3 et 4\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }

    printf("\n---------------------------------------------------------------\n");
    printf("********** L'ensemble des tests sont passés **********");
    printf("\n---------------------------------------------------------------\n");

    return 0;
}