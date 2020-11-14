#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "validate_read.h"


int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateFirstPart(head, "xml_test/valid_1.xml");
    if(valid == 0) {
        printf("le fichier xml n'est pas valide\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }

    //printTags(head);
    return 0;
}