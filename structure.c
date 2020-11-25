#include "structure.h"


LinkedListTag* intialisation(char* name) {

    LinkedListTag* ll = malloc(sizeof(LinkedListTag));

    ll->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(ll->name, name);
    ll->close = NULL;
    ll->present_in_dtd = NULL;
    ll->text = NULL;
    ll->parentTag = NULL;
    ll->childTags = NULL;
    ll->brotherTags = NULL;
    ll->attribute = NULL;

    return ll;
}

LinkedListDtd* intialisationDtd(char* name) {

    LinkedListDtd* ll = malloc(sizeof(LinkedListDtd));

    ll->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(ll->name, name);
    ll->text = NULL;
    ll->present_in_xml = NULL;
    ll->operator = NULL;
    ll->parentTag = NULL;
    ll->childTags = NULL;
    ll->brotherTags = NULL;
    ll->attribute = NULL;

    return ll;
}

LinkedListTag* searchCurrentTag(LinkedListTag* head) {
    
    if(head->close == 1) {
        return -1;
    }else if(head->childTags == NULL) {
        //printf("head childTags NULL -> %d\n", head->childTags);
        return head;
    }
    //printf("head childTags -> %d\n", head->childTags);

    //printf("ouloulou %d\n", head->childTags);
    int pass = 0;
    LinkedListTag* current = head;
    LinkedListTag* nextTag = head->childTags;
    
    while(pass == 0) {
        // cas balise fermée
        if(nextTag->close == 1){
            if(nextTag->brotherTags != NULL) {
                nextTag = nextTag->brotherTags;
            }else {
                pass=1;
            }
        // cas balise ouverte
        }else{ 
            if(nextTag->childTags != NULL) {
                current = nextTag;
                nextTag = nextTag->childTags;
            }else{
                current = nextTag;
                pass=1;
            }
        }
    }

    printf("la balise courante est %s\n", current->name);
    return current;

}

int closeTag(char* name, LinkedListTag* currentTag) {

    if(strcmp(name, currentTag->name) != 0 || currentTag->close != 0) {
        return -1;
    }

    printf("je ferme la balise %s\n", name);
    currentTag->close = 1;
    printf("%s close -> %d\n", currentTag->name, currentTag->close);
    return 1;
}

void addLinkedListTags(char* name, char* text, int close, LinkedListTag* parent, LinkedListTag* brotherAfter) {

    LinkedListTag* ll = malloc(sizeof(LinkedListTag));
    ll->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(ll->name, name);

    // ajout de la valeur dans la balise
    if(text != NULL){
        ll->text = malloc(sizeof(char) * strlen(text) +1 );
        strcpy(ll->text, text);
        ll->text = text;
    }else{
        ll->text = malloc(sizeof(char));
        ll->text = NULL;
    }

    // ajout de la liasion sur la balise d'après
    if(brotherAfter != NULL){
        ll->brotherTags = brotherAfter;
    }else {
        ll->brotherTags = NULL;
    }

    //attributs
    ll->attribute = NULL;

    //close
    ll->close = close;

    //present_in_dtd
    ll->present_in_dtd = NULL;

    //ajout de la liaison sur la balise parent
    ll->parentTag = parent;

    ll->childTags = NULL;

    // ajout de la liaison sur la balise d'avant
    if(parent->childTags == NULL) {
        parent->childTags = ll;
    }else {
        LinkedListTag* brother = parent->childTags;
        while(brother != NULL){

            if(brother->brotherTags == NULL) {
                brother->brotherTags = ll;
                brother = ll;
            }
            brother = brother->brotherTags;
        }
    }
}

void addLinkedListDtd(char* name, char* text, char operator, char* parent_name, char* brotherAfter, LinkedListDtd* head) {

    LinkedListDtd* ll = malloc(sizeof(LinkedListDtd));
    ll->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(ll->name, name);

    // ajout de la valeur dans la balise
    if(text != NULL){
        ll->text = malloc(sizeof(char) * strlen(text) + 1);
        strcpy(ll->text, text);
    }else{
        ll->text = malloc(sizeof(char));
        ll->text = NULL;
    }

    // ajout de la liasion sur la balise d'après
    if(brotherAfter != NULL){
        ll->brotherTags = brotherAfter;
    }else {
        ll->brotherTags = NULL;
    }

    //operator
    ll->operator = operator;

    //present_in_xml
    ll->present_in_xml = NULL;

    //attributs
    ll->attribute = NULL;

    //ajout de la liaison sur la balise parent
    ll->parentTag = searchParent(head, parent_name);

    ll->childTags = NULL;

    // ajout de la liaison sur la balise d'avant
    if(ll->parentTag->childTags == NULL) {
        ll->parentTag->childTags = ll;
    }else {
        LinkedListDtd* brother = ll->parentTag->childTags;
        while(brother != NULL){

            if(brother->brotherTags == NULL) {
                brother->brotherTags = ll;
                //brother = ll;
                break;
            }
            brother = brother->brotherTags;
        }
    }
}

LinkedListDtd* searchParent(LinkedListDtd* head, char* parent_name) {
    
    if(strcmp(head->name, parent_name) == 0) {
        //printf("head childTags NULL -> %d\n", head->childTags);
        
        return head;
    }

    LinkedListDtd* child = head->childTags;

    //printf("la balise parent est <%s>\n", head->name);
    int flagChildToParent = 0;
    while(child != NULL){
        if(flagChildToParent != 1) {
            if(strcmp(child->name, parent_name) == 0) {
                return child;
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else{ 
            child = child->childTags;
        }
    }
    return head;
}

void addLinkedListAttribute(char* key, char* value, LinkedListTag* head) {

    LinkedListTag* currentTag = searchCurrentTag(head);

    LinkedListAttribute* newAttribut = malloc(sizeof(LinkedListAttribute));
    newAttribut->key = malloc(sizeof(char) * strlen(key) + 1);
    strcpy(newAttribut->key, key);
    newAttribut->value = malloc(sizeof(char) * strlen(value) + 1);
    strcpy(newAttribut->value, value);
    newAttribut->nextAttribute = NULL;
    newAttribut->present_in_dtd = NULL;

    if(currentTag->attribute == NULL) {
        currentTag->attribute = newAttribut;
        printf("nom -> %s et value ->  %s\n", currentTag->attribute->key, currentTag->attribute->value);
        return;
    }

    LinkedListAttribute* attribute = currentTag->attribute;
    while(attribute->nextAttribute != NULL){

        attribute = attribute->nextAttribute;
    }
    attribute->nextAttribute = newAttribut;
    printf("nom -> %s et value %s\n", attribute->nextAttribute->key, attribute->nextAttribute->value);
}

void addLinkedListAttributeDtd(char* key, char* parent_tag_dtd, char operator, LinkedListDtd* head) {

    LinkedListDtd* currentTag = searchParent(head, parent_tag_dtd);
    LinkedListAttributeDtd* newAttribut = malloc(sizeof(LinkedListAttributeDtd));
    newAttribut->key = malloc(sizeof(char) * strlen(key) + 1);
    strcpy(newAttribut->key, key);
    newAttribut->operator = operator;
    newAttribut->nextAttribute = NULL;
    newAttribut->present_in_xml = NULL;

    if(currentTag->attribute == NULL) {
        currentTag->attribute = newAttribut;
        return;
    }

    LinkedListAttributeDtd* attribute = currentTag->attribute;
    while(attribute->nextAttribute != NULL){

        attribute = attribute->nextAttribute;
    }
    attribute->nextAttribute = newAttribut;
    printf("nom -> %s et operator %c\n", attribute->nextAttribute->key, attribute->nextAttribute->operator);
}

int verifyLinkedListAttribute(char* attribute_key, LinkedListTag* head){

    LinkedListTag* currentTag = searchCurrentTag(head);
    if(currentTag->attribute == NULL) {
        
        return 1;
    }

    LinkedListAttribute* attribute = currentTag->attribute;
    while(attribute != NULL){
        if(strcmp(attribute->key, attribute_key) == 0) {

            return 0;
        }

        attribute = attribute->nextAttribute;
    }

    return 1;
}

void addTextToLinkedListTag(char* text, LinkedListTag* head) {

    LinkedListTag* currentTag = searchCurrentTag(head);
    currentTag->text = NULL;
    free(currentTag->text);
    currentTag->text = malloc(sizeof(char) * strlen(text) + 1);
    strcpy(currentTag->text, text);
    printf("nom de balise -> %s et text: %s\n", currentTag->name, currentTag->text);
}

void addLinkedListBrother(char* name, char* text, LinkedListTag* brotherBefore, LinkedListTag* brotherAfter) {

    LinkedListTag* ll = malloc(sizeof(LinkedListTag));
    ll->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(ll->name, name);

    // ajout de la valeur dans la balise
    if(text != NULL){
        ll->text = malloc(sizeof(char) * strlen(text) + 1);
        strcpy(ll->text, text);
    }else{
        ll->text = NULL;
    }

    // ajout de la liasion sur la balise d'après
    if(brotherAfter != NULL){
        ll->brotherTags = brotherAfter;
    }else {
        ll->brotherTags = NULL;
    }

    ll->childTags = NULL;
    ll->attribute = NULL;
    ll->close = NULL;

    // ajout de la liasion sur la balise d'avant
    brotherBefore->brotherTags = ll;
}

void printAttribute(LinkedListAttribute* firstAttribute) {

    while(firstAttribute != NULL){

        printf("\tattribut / Key: %s -> Value: %s Present: %d\n", firstAttribute->key, firstAttribute->value, firstAttribute->present_in_dtd);
        firstAttribute = firstAttribute->nextAttribute;
    }
}

void printAttributeDtd(LinkedListAttributeDtd* firstAttribute) {

    while(firstAttribute != NULL){

        printf("\tattribut / Key: %s -> Operator: %c / present_in_xml %d\n", firstAttribute->key, firstAttribute->operator, firstAttribute->present_in_xml);
        firstAttribute = firstAttribute->nextAttribute;
    }
}

void printTags(LinkedListTag* head) {

    printf("<%s>\n", head->name);

    if(head->text != NULL) {
        printf("\ttext -> %s\n", head->text);
    }

    if(head->attribute != NULL) {
        printAttribute(head->attribute);
    }

    LinkedListTag* child = head->childTags;
    if(child == NULL) {
        printf("</%s>\n", head->name);
    }

    //printf("la balise parent est <%s>\n", head->name);
    int flagChildToParent = 0;
    while(child != NULL){
        if(flagChildToParent != 1) {
            printf("<%s> present -> %d\n", child->name, child->present_in_dtd);
            if(child->text != NULL) {
                printf("\ttext -> %s\n", child->text);
            }

            if(child->attribute != NULL) {
                printAttribute(child->attribute);
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            printf("</%s>\n", child->name);
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else{ 
            child = child->childTags;
        }
    }
}

int count_depth(LinkedListTag* head) {
    
    int count_depth_xml = 0;
    int current_depth = 0;

    LinkedListTag* child = head->childTags;
    if(child == NULL) {
        return count_depth_xml;
    }
    current_depth += 1;
    count_depth_xml += 1;

    //printf("la balise parent est <%s>\n", head->name);
    int flagChildToParent = 0;
    while(child != NULL){
        
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
                if(child != NULL)
                    current_depth -= 1;
                
            }
        // cas balise ouverte
        }else{
            child = child->childTags;

            current_depth += 1;
            if(current_depth > count_depth_xml){ 

                count_depth_xml = current_depth;
            }
        }
    }
    return count_depth_xml;
}

int present_attribute(LinkedListTag* head) {


    if(head->attribute != NULL) {
        return 1;
    }

    LinkedListTag* child = head->childTags;

    //printf("la balise parent est <%s>\n", head->name);
    int flagChildToParent = 0;
    while(child != NULL){
        if(flagChildToParent != 1) {

            if(child->attribute != NULL) {
                return 1;
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;

            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else{ 
            child = child->childTags;
        }
    }

    return 0;
}

int verifyAllTagsClosed(LinkedListTag* head) {

    if(head->close != 1) {
        return 0;
    }

    LinkedListTag* child = head->childTags;
    int flagChildToParent = 0;
    while(child != NULL){

        if(flagChildToParent != 1) {
        //printf("\tje dois apparaitre le nombre de balise -1 pour tout vérifier\n");
            if(child->close != 1) {
                return -1;
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else{ 
            child = child->childTags;
        }
    }
    return 1;
}

int presentTagInXml(LinkedListTag* head, char* name_parent_tag, char* name_tag, char operator) {

    // je récupère le tag avec name_tag
    // si son parent->name est égale à name_parent_tag 
    // alors je passe le present_in_dtd à 1
    int present = 0;
    if(name_parent_tag == NULL) {
        if(strcmp(head->name, name_tag) == 0) {
            head->present_in_dtd = 1;
            return 1;
        }
        return 0;
    }

    LinkedListTag* child = head->childTags;
    if(child == NULL) {
        //printf("</%s>\n", head->name);
    }

    //printf("la balise parent est <%s>\n", head->name);
    int flagChildToParent = 0;
    while(child != NULL){
        if(flagChildToParent != 1) {
            printf("child -> <%s>\n", child->name);
            printf("parent -> <%s>\n", child->parentTag->name);
            if(strcmp(child->name, name_tag) == 0 && strcmp(child->parentTag->name, name_parent_tag) == 0 && child->present_in_dtd == 0) {
                child->present_in_dtd = 1;
                present = 1;
                if(operator == 1 || operator == '?') {
                    return present;
                }
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            //printf("</%s>\n", child->name);
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                //si pas de frere
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else {
            child = child->childTags;
        }
    }

    //gère le cas ou l'operateur permet de ne pas être présent
    if(operator == '?' || operator == '*') {
        present = 1;
    }
    return present;
}

int matchXmlDtd(LinkedListTag* head, LinkedListDtd* head_dtd) {

    // parcourir le XML
    // parcourir la DTD
    // faire match la DTD et le XML pour chaque balise puis passé à la suivante
    // sauf quand childTag == NULL et que brotherTag != NULL
    // sauf quand on remonte sur parentTag et que brotherTag != NULL et que operator == + ou *
    // dans ces cas on passe un flag à 1 et on fait change la valeur du xml mais pas de la DTD
    // si au prochain tout les deux ne sont pas égales alors on change la DTD mais pas le XML

    printf("<%s>\n", head->name);
    if(strcmp(head->name, head_dtd->name) != 0) {
        return 0;
    }
    head->present_in_dtd = 1;
    head_dtd->present_in_xml = 1;

    if(head->attribute != NULL && head_dtd->attribute != NULL) {
        matchXmlDtdAttribute(head, head_dtd);
    }

    LinkedListTag* child = head->childTags;
    LinkedListDtd* child_dtd = head_dtd->childTags;

    if(child == NULL || child_dtd == NULL) {
        printf("</%s>\n", head->name);
        return 1;
    }

    //printf("la balise parent est <%s>\n", head->name);
    int flagChildToParent = 0;
    int flag_plus_multiple_dtd = 0;
    while(child != NULL && child_dtd != NULL){
        if(child == NULL) {
            //printf("c'est pas possible\n");
        }
        printf("<%s>\n", child->name);
        printf("dtd -> <%s>\n", child_dtd->name);
        if(flagChildToParent != 1) {
            if(strcmp(child->name, child_dtd->name) == 0) {
                child->present_in_dtd = 1;
                child_dtd->present_in_xml = 1;
                flag_plus_multiple_dtd = 0;

                //comparaison des attributs
                if(child->attribute != NULL && child_dtd->attribute != NULL) {
                    matchXmlDtdAttribute(child, child_dtd);
                }    

            }else {
                printf("normal -> %s\n", child->name);

                printf("dtd -> %s\n", child_dtd->name);
                // si l'option du + ou * n'a pas match
                if(flag_plus_multiple_dtd == 1 || child_dtd->operator == '*' || child_dtd->operator == '?') {
                    child_dtd = child_dtd->brotherTags;
                    flag_plus_multiple_dtd = 0;
                    continue;
                }

                if(child_dtd->operator == '+' || child_dtd->operator == NULL) {
                    return 0;
                }
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            //flagChildToParent = 0;
            printf("</%s>\n", child->name);
            if(child->brotherTags != NULL) {
                // le cas ou brotherTag pas Null et que un + ou un moins dans dtd
                if(child_dtd->operator == '+' || child_dtd->operator == '*') {
                    flag_plus_multiple_dtd = 1;
                }else {
                    child_dtd = child_dtd->brotherTags;
                }
                child = child->brotherTags;
                flagChildToParent = 0;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                child_dtd = child_dtd->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else{
            child = child->childTags;
            child_dtd = child_dtd->childTags;
        }
    }

    return 1;
}

void matchXmlDtdAttribute(LinkedListTag* child, LinkedListDtd* child_dtd) {

    LinkedListAttribute* attribute = child->attribute;
    LinkedListAttributeDtd* attribute_dtd = child_dtd->attribute;
    
    while(attribute != NULL && attribute_dtd != NULL){
        if(strcmp(attribute->key, attribute_dtd->key) == 0) {

            attribute->present_in_dtd = 1;
            attribute_dtd->present_in_xml = 1;
        }else {
            if(attribute_dtd->operator == '?') {
                attribute_dtd = attribute_dtd->nextAttribute;
            }
        }

        attribute = attribute->nextAttribute;
        attribute_dtd = attribute_dtd->nextAttribute;
    }
}

void printTagsDtd(LinkedListDtd* head) {

    printf("<%s>\n", head->name);

    if(head->text != NULL) {
        printf("\ttext -> %s\n", head->text);
    }

    if(head->attribute != NULL) {
        printAttributeDtd(head->attribute);
    }

    LinkedListDtd* child = head->childTags;
    if(child == NULL) {
        printf("</%s>\n", head->name);
    }

    //printf("la balise parent est <%s>\n", head->name);
    int flagChildToParent = 0;
    while(child != NULL){
        if(flagChildToParent != 1) {
            printf("<%s>\n", child->name);
            if(child->text != NULL) {
                printf("\ttext -> %s\n", child->text);
            }

            if(child->attribute != NULL) {
                printAttributeDtd(child->attribute);
            }

            if(child->operator != NULL) {
                printf("operator -> %c\n", child->operator);
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            printf("</%s>\n", child->name);
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else{ 
            child = child->childTags;
        }
    }
}

int verifyAllTagsDTD(LinkedListTag* head) {

    if(head->present_in_dtd != 1) {
        return 0;
    }

    if(head->attribute != NULL) {
        if(verifyAllAttributesTagInXml(head->attribute) != 1) {
            return 0;
        }
    }

    LinkedListTag* child = head->childTags;
    int flagChildToParent = 0;
    while(child != NULL){

        if(flagChildToParent != 1) {

            if(child->present_in_dtd != 1) {
                return 0;
            }

            if(child->attribute != NULL) {
                if(verifyAllAttributesTagInXml(child->attribute) != 1) {
                    return 0;
                }
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else{ 
            child = child->childTags;
        }
    }

    return 1;
}

int verifyAllTagsPresentDtdInXML(LinkedListDtd* head) {

    if(head->present_in_xml != 1) {
        return 0;
    }

    if(head->attribute != NULL) {
        if(verifyAllAttributesTagInDtd(head->attribute) != 1) {
            return 0;
        }
    }

    LinkedListDtd* child = head->childTags;
    int flagChildToParent = 0;
    while(child != NULL){

        if(flagChildToParent != 1) {

            if(child->present_in_xml != 1 && child->operator != '?' && child->operator != '*') {
                return 0;
            }

            if(child->attribute != NULL) {
                if(verifyAllAttributesTagInDtd(child->attribute) != 1) {
                    return 0;
                }
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
            }else {
                // si parentTag est pas NUll ça continue sinon stop
                child = child->parentTag;
                flagChildToParent = 1;
            }
        // cas balise ouverte
        }else{ 
            child = child->childTags;
        }
    }

    return 1;
}

int verifyAllAttributesTagInDtd(LinkedListAttributeDtd* firstAttribute) {

    while(firstAttribute != NULL){

        if(firstAttribute->present_in_xml != 1 && firstAttribute->operator != '?') {
            return 0;
        }
        firstAttribute = firstAttribute->nextAttribute;
    }

    return 1;
}

int verifyAllAttributesTagInXml(LinkedListAttribute* firstAttribute) {

    while(firstAttribute != NULL){

        if(firstAttribute->present_in_dtd != 1) {
            return 0;
        }
        firstAttribute = firstAttribute->nextAttribute;
    }

    return 1;
}

void freeLinkedListTag(LinkedListTag* head) {
    if(head->childTags != NULL) {
        freeLinkedListTag(head->childTags);
    }

    if(head->brotherTags != NULL) {
        freeLinkedListTag(head->brotherTags);
    }

    //printf("name free -> %s\n",head->name);
    if(head->name != NULL) {
        free(head->name);
    }
    if(head->text != NULL) {
        free(head->text);
    }

    free(head);
}

int verifymatchXmlDtd(LinkedListTag* head, LinkedListDtd* head_dtd) {

    if( matchXmlDtd(head, head_dtd) != 1 ) {
        printf("le fichier DTD n'est pas valide\n");
        return 0;
    }

    if( (verifyAllTagsDTD(head) != 1) || (verifyAllTagsPresentDtdInXML(head_dtd) != 1) ) {
        printf("le fichier DTD et le fichier XML ne correspondent pas\n");
        return 0;
    }

    return 1;
}

void displayArgDTD() {

    printf("Ce fichier accepte deux et seulement deux arguements\n");
    printf("nomFichierXML nomFichierDTD\n");
    printf("\nExemple: \n");
    printf("\t./dtd valid_1.xml valid_1.dtd\n");
}

void displayArgXML() {

    printf("Ce fichier accepte un et seulement un argument\n");
    printf("nomFichierXML\n");
    printf("\nExemple: \n");
    printf("\t./dtd valid_1.xml\n");
}