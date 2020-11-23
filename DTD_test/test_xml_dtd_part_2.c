#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "../christophe.h"

int main() {

    int valid;

    LinkedListTag* head2 = intialisation("");
    valid = validateSecondPart(head2, "xml_test/valid_10.xml");
    if(strcmp(head2->name, "") != 0) 
        freeLinkedListTag(head2);
    if(valid == 0) {
        printf("le fichier xml n'est pas valide pour la partie 2\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }
    //return 0;

    LinkedListDtd* head_dtd1 = getDtdTag("DTD_test/valid_12.dtd");
    printTagsDtd(head_dtd1);

    int first_verification_1 = matchXmlDtd(head, head_dtd1);
    if(first_verification_1 != 1) {
        printf("le fichier DTD n'est pas valide\n");
    }

    printf("verification -> %d\n", verifyAllTagsDTD(head));
    printf("verification dtd_xml -> %d\n", verifyAllTagsPresentDtdInXML(head_dtd1));

    printf("\n**********************************\n");
    if(verifyAllTagsDTD(head) == 1 && verifyAllTagsPresentDtdInXML(head_dtd1) == 1) {
        printf("le XML correspond bien à la DTD\n");
    }else {
        printf("le XML ne correspond pas à la DTD\n");
    }
    printf("**********************************\n");
    return 0;
}