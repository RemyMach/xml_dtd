#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "validate_read.h"
#include "christophe.h"


int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, "xml_test/valid_12.xml");
    //freeLinkedListTag(head);
    if(valid == 0) {
        printf("le fichier xml n'est pas valide\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }

    printTags(head);

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
    //presentTagInXml(head, 0, "message", 1);
    //presentTagInXml(head, "message", "pomme", '+');
    //presentTagInXml(head, "message", "jean", '+');
    //presentTagInXml(head, "jean", "balise", 0);

    //printTagsDtd(head);
    //printf("verification -> %d\n",verifyAllTagsDTD(head));
    LinkedListDtd* head_dtd = intialisationDtd("");
    char* name_head_dtd = "message";
    head_dtd->name = malloc(sizeof(char)*strlen(name_head_dtd)+1);
    strncpy(head_dtd->name, name_head_dtd, strlen(name_head_dtd));
    head_dtd->name[strlen(name_head_dtd)] = '\0';

    //exemple fichier 6
    /*addLinkedListDtd("student", NULL, '*', "college", NULL, head_dtd);
    addLinkedListDtd("firstname", NULL, '*', "student", NULL, head_dtd);
    //addLinkedListDtd("prenom", NULL, NULL, "message", NULL, head_dtd);
    addLinkedListDtd("lastname", NULL, '*', "student", NULL, head_dtd);
    addLinkedListDtd("contact", NULL, '*', "student", NULL, head_dtd);
    addLinkedListDtd("email", NULL, '*', "student", NULL, head_dtd);
    addLinkedListDtd("address", NULL, '*', "student", NULL, head_dtd);
    addLinkedListDtd("city", NULL, '*', "address", NULL, head_dtd);
    addLinkedListDtd("state", NULL, '*', "address", NULL, head_dtd);
    addLinkedListDtd("pin", NULL, '*', "address", NULL, head_dtd);*/

    
    //exemple fichier 5
    addLinkedListDtd("nom", NULL, NULL, "message", NULL, head_dtd);
    addLinkedListDtd("adresse", NULL, '+', "message", NULL, head_dtd);
    //addLinkedListDtd("prenom", NULL, NULL, "message", NULL, head_dtd);
    addLinkedListDtd("cp", NULL, '?', "adresse", NULL, head_dtd);
    addLinkedListDtd("type", NULL, NULL, "adresse", NULL, head_dtd);
    addLinkedListDtd("ville", NULL, '?', "adresse", NULL, head_dtd);
    addLinkedListDtd("maison", NULL, '?', "type", NULL, head_dtd);
    addLinkedListDtd("prenom", NULL, '*', "message", NULL, head_dtd);
    addLinkedListDtd("pomme", NULL, '*', "message", NULL, head_dtd);
    addLinkedListAttributeDtd("face", "message", '+', head_dtd);
    addLinkedListAttributeDtd("value", "message", '+', head_dtd);
    addLinkedListAttributeDtd("name", "nom", '+', head_dtd);
    addLinkedListAttributeDtd("value", "nom", '+', head_dtd);
    addLinkedListAttributeDtd("tom", "nom", '+', head_dtd);
    addLinkedListAttributeDtd("jean", "nom", '?', head_dtd);
    printTagsDtd(head_dtd);
    return 0;

    //exemple fichier 1
    /*addLinkedListDtd("pomme", NULL, '+', "message", NULL, head_dtd);
    addLinkedListDtd("jean", NULL, NULL, "message", NULL, head_dtd);
    addLinkedListDtd("balise", NULL, '?', "jean", NULL, head_dtd);*/

    int first_verification = matchXmlDtd(head, head_dtd);
    if(first_verification != 1) {
        printf("le fichier DTD n'est pas valide\n");
    }

    printf("-----------------------------------\n");
    printTagsDtd(head_dtd);
    printf("-----------------------------------\n");

    //printTags(head);
    printf("verification -> %d\n", verifyAllTagsDTD(head));
    printf("verification dtd_xml -> %d\n", verifyAllTagsPresentDtdInXML(head_dtd));
    return 0;
}