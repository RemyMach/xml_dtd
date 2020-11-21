#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "test_xml.h"

int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, "xml_test/valid_7.xml");
    freeLinkedListTag(head);
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 3 et 4\n");
    }else {
        printf("le fichier est valide\n");
    }

    LinkedListTag* head1 = intialisation("");
    valid = validateFirstPart(head1, "xml_test/valid_10.xml");
    freeLinkedListTag(head1);
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 1\n");
    }else {
        printf("le fichier est valide\n");
    }
    //return 0;

    LinkedListTag* head2 = intialisation("");
    valid = validateSecondPart(head2, "xml_test/valid_10.xml");
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