#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "validate_read.h"


int main() {

    int valid;
    LinkedListTag* head = intialisation("");
    valid = validateRead(head, "xml_test/valid_5.xml");
    if(valid == 0) {
        printf("le fichier xml n'est pas valide\n");
        return 0;
    }else {
        printf("le fichier est valide\n");
    }
    //presentTagInXml(head, 0, "message", 1);
    //presentTagInXml(head, "message", "pomme", '+');
    //presentTagInXml(head, "message", "jean", '+');
    //presentTagInXml(head, "jean", "balise", 0);

    //printTagsDtd(head);
    //printf("verification -> %d\n",verifyAllTagsDTD(head));

    LinkedListDtd* head_dtd = intialisationDtd("");
    char* name_head_dtd = "message";
    printf("%d\n", strlen(name_head_dtd));
    head_dtd->name = malloc(sizeof(char)*strlen(name_head_dtd)+1);
    strncpy(head_dtd->name, name_head_dtd, strlen(name_head_dtd));
    head_dtd->name[strlen(name_head_dtd)] = '\0';
    
    //exemple fichier 5
    addLinkedListDtd("nom", NULL, NULL, "message", NULL, head_dtd);
    addLinkedListDtd("adresse", NULL, '+', "message", NULL, head_dtd);
    //addLinkedListDtd("prenom", NULL, NULL, "message", NULL, head_dtd);
    addLinkedListDtd("cp", NULL, '?', "adresse", NULL, head_dtd);
    addLinkedListDtd("type", NULL, NULL, "adresse", NULL, head_dtd);
    addLinkedListDtd("ville", NULL, '?', "adresse", NULL, head_dtd);
    addLinkedListDtd("maison", NULL, '?', "type", NULL, head_dtd);
    addLinkedListDtd("prenom", NULL, '+', "message", NULL, head_dtd);
    addLinkedListDtd("pomme", NULL, '*', "message", NULL, head_dtd);

    //exemple fichier 1
    /*
    addLinkedListDtd("pomme", NULL, NULL, "message", NULL, head_dtd);
    addLinkedListDtd("jean", NULL, NULL, "message", NULL, head_dtd);
    addLinkedListDtd("balise", NULL, '?', "jean", NULL, head_dtd);*/
    //printTagsDtd(head_dtd);

    int first_verification = matchXmlDtd(head, head_dtd);
    if(first_verification != 1) {
        printf("le fichier DTD n'est pas valide\n");
    }
    printTags(head);
    printf("verification -> %d\n", verifyAllTagsDTD(head));
    printf("verification2 -> %d\n", verifyAllTagsPresentDtdInXML(head_dtd));
    return 0;
}