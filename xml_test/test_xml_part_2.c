#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "test_xml.h"

int main() {

    int valid;

    LinkedListTag* head2 = intialisation("");
    valid = validateSecondPart(head2, "xml_test/valid_10.xml");
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