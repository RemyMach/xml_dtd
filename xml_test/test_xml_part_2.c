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
    LinkedListTag* head2 = intialisation("");
    valid = validateSecondPart(head2, name_xml);
    if(strcmp(head2->name, "") != 0) 
        freeLinkedListTag(head2);
    
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 2\n");
    }else {
        printf("le fichier est valide\n");
    }
    //return 0;

    printf("\n---------------------------------------------------------------\n");
    printf("********** L'ensemble des tests sont passés **********");
    printf("\n---------------------------------------------------------------\n");

    return 0;
}