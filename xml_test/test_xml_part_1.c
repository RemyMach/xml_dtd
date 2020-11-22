#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "test_xml.h"

int main() {

    int valid;

    LinkedListTag* head1 = intialisation("");
    valid = validateFirstPart(head1, "xml_test/valid_10.xml");
    if(strcmp(head1->name, "") != 0) 
        freeLinkedListTag(head1);
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 1\n");
    }else {
        printf("le fichier est valide\n");
    }

    printf("\n---------------------------------------------------------------\n");
    printf("********** L'ensemble des tests sont passés **********");
    printf("\n---------------------------------------------------------------\n");

    return 0;
}