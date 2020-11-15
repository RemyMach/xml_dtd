#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

LinkedListTag* intialisation(char* name) {

    LinkedListTag* ll = malloc(sizeof(LinkedListTag));

    ll->name = malloc(sizeof(char) * strlen(name));
    ll->name = name;
    ll->close = NULL;
    ll->present_in_dtd = NULL;
    ll->text = NULL;
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
    ll->name = malloc(sizeof(char) * strlen(name));
    ll->name = name;

    // ajout de la valeur dans la balise
    if(text != NULL){
        ll->text = malloc(sizeof(char) * strlen(text));
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

void addLinkedListAttribute(char* key, char* value, LinkedListTag* head) {

    LinkedListTag* currentTag = searchCurrentTag(head);

    LinkedListAttribute* newAttribut = malloc(sizeof(LinkedListAttribute));
    newAttribut->key = malloc(sizeof(char) * strlen(key));
    newAttribut->key = key;
    newAttribut->value = malloc(sizeof(char) * strlen(value));
    newAttribut->value = value;
    newAttribut->nextAttribute = NULL;

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
    currentTag->text = malloc(sizeof(char) * strlen(text));
    currentTag->text = text;
    printf("nom de balise -> %s et text: %s\n", currentTag->name, currentTag->text);
}

void addLinkedListBrother(char* name, char* text, LinkedListTag* brotherBefore, LinkedListTag* brotherAfter) {

    LinkedListTag* ll = malloc(sizeof(LinkedListTag));
    ll->name = malloc(sizeof(char) * strlen(name));
    ll->name = name;

    // ajout de la valeur dans la balise
    if(text != NULL){
        ll->text = malloc(sizeof(char) * strlen(text));
        ll->text = text;
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

        printf("\tattribut / Key: %s -> Value: %s\n", firstAttribute->key, firstAttribute->value);
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
            printf("<%s>\n", child->name);
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

void printTagsDtd(LinkedListTag* head) {

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
            printf("<%s>\n", child->name);
            if(child->text != NULL) {
                printf("\ttext -> %s\n", child->text);
            }

            if(child->attribute != NULL) {
                printAttribute(child->attribute);
            }
        }
        if(child->childTags == NULL || flagChildToParent == 1){
            flagChildToParent = 0;
            printf("</%s> -> %d\n", child->name, child->present_in_dtd);
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

    LinkedListTag* child = head->childTags; 
    int flagChildToParent = 0;
    while(child != NULL){

        if(flagChildToParent != 1) {

            if(child->present_in_dtd != 1) {
                return 0;
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