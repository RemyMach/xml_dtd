#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "validate_read.h"


int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, "example.xml");
    if(valid == 0) {
        printf("le fichier xml n'est pas valide");
    }else {
        printf("le fichier est valide\n");
    }

    printTags(head);
    return 0;
}