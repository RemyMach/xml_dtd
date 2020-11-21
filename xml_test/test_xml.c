#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "test_xml.h"

int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, "xml_test/valid_9.xml");
    freeLinkedListTag(head);
    if(valid == 0) {
        printf("le fichier xml n'est pas valide\n");
    }else {
        printf("le fichier est valide\n");
    }
    return 0;

    printf("\n---------------------------------------------------------------\n");
    printf("********** L'ensemble des tests sont passés **********");
    printf("\n---------------------------------------------------------------\n");

    return 0;
}