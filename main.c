#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "validate_read.h"


int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, "xml_test/valid_1.xml");
    if(valid == 0) {
        printf("le fichier xml n'est pas valide\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }
    int validate_depth = validate_depth_one(head);

    printf("result valdate_depth %d\n", validate_depth);
    //printTags(head);
    return 0;
}