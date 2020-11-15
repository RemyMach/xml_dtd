#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "validate_read.h"


int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, "xml_test/valid_3.xml");
    if(valid == 0) {
        printf("le fichier xml n'est pas valide\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }
    presentTagInXml(head, 0, "message", 1);
    presentTagInXml(head, "message", "pomme", '+');
    presentTagInXml(head, "message", "jean", '+');
    presentTagInXml(head, "jean", "balise", 0);

    printTagsDtd(head);
    printf("verification -> %d\n",verifyAllTagsDTD(head));
    //printTags(head);
    return 0;
}