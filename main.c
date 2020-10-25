#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListAttribute {
    char* key;
    char* value;
    struct LinkedListAttribute* nextAttribute;
}LinkedListAttribute;

typedef struct LinkedListTag {
    int close;
    char* name;
    char* text;
    struct LinkedListTag* childTags;
    struct LinkedListTag* brotherTags;
    struct LinkedListAttribute* attribute;
}LinkedListTag;

LinkedListTag* intialisation(char* name) {

    LinkedListTag* ll = malloc(sizeof(LinkedListTag));

    ll->name = malloc(sizeof(char) * strlen(name));
    ll->name = name;
    ll->close = NULL;
    ll->text = NULL;
    ll->childTags = NULL;
    ll->brotherTags = NULL;
    ll->attribute = NULL;

    return ll;
}

LinkedListTag* searchCurrentTag(LinkedListTag* head) {
    
    if(head->close == 1) {
        return -1;
    }else if(head->childTags == NULL) {
        return head;
    }
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

    // ajout de la liasion sur la balise d'avant
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
    printf("voici la balise %s\n", currentTag->name);
    LinkedListAttribute* newAttribut = malloc(sizeof(LinkedListAttribute));
    newAttribut->key = malloc(sizeof(char) * strlen(key));
    newAttribut->key = key;
    newAttribut->value = malloc(sizeof(char) * strlen(value));
    newAttribut->value = value;

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

void printTags(LinkedListTag* parent){

    LinkedListTag* child = parent->childTags;
    printf("la balise parent est <%s>\n", parent->name);
    while(child != NULL){
        printf("<%s>\n", child->name);
        child = child->brotherTags;
    }
}

void printAttribute(LinkedListAttribute* firstAttribute) {


    while(firstAttribute != NULL){

        printf("\tattribut / Key: %s -> Value: %s\n", firstAttribute->key, firstAttribute->value);
        firstAttribute = firstAttribute->nextAttribute;
    }
}

void printTags2(LinkedListTag* head){

    printf("<%s>\n", child->name);

    if(head->text != NULL) {
        printf("\ttext -> %s\n", head->text);
    }

    if(head->attribute != NULL) {
        printAttribute(head->attribute);
    }

    LinkedListTag* child = parent->childTags;
    printf("la balise parent est <%s>\n", parent->name);
    int pass=0;
    while(pass == 0){

        printf("<%s>\n", child->name);
        if(child->text != NULL) {
        printf("\ttext -> %s\n", child->text);
        }

        if(child->attribute != NULL) {
            printAttribute(child->attribute);
        }

        if(child->childTags == NULL){
            if(child->brotherTags != NULL) {
                child = child->brotherTags;
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

        child = child->brotherTags;
    }
}

int main() {

    LinkedListTag* head = intialisation("message");
    addLinkedListAttribute("name", "jean de la message", head);
    addLinkedListAttribute("value", "histoire de message", head);
    
    addLinkedListTags("nom", NULL,1, head, NULL);
    addLinkedListAttribute("name", "jean de la pomme", head);
    addLinkedListAttribute("value", "histoire", head);
    closeTag("nom", searchCurrentTag(head));

    addLinkedListTags("prenom",NULL,1, head, NULL);
    addTextToLinkedListTag("jean", head);
    closeTag("prenom", searchCurrentTag(head));

    addLinkedListTags("adresse",NULL,0, head, NULL);
    addLinkedListTags("cp", NULL,0, searchCurrentTag(head), NULL);
    addTextToLinkedListTag("95120", head);
    closeTag("cp", searchCurrentTag(head));

    addLinkedListTags("ville", NULL,0, searchCurrentTag(head), NULL);
    addTextToLinkedListTag("Taverny", head);
    closeTag("ville", searchCurrentTag(head));
    closeTag("adresse", searchCurrentTag(head));

    closeTag("message", searchCurrentTag(head));


    /*if(closeTag("cp", searchCurrentTag(head)) == -1){
        printf("votre fichier xml est corrompu balise qui ne se ferme pas au bon endroit");
        return -1;
    }*/
    //addLinkedListAttribute("clé", "valeur", searchCurrentTag(head));
    //addLinkedListAttribute("pomme", "tom", searchCurrentTag(head));
    //addLinkedListAttribute("jean", "de la", searchCurrentTag(head));

    //addLinkedListBrother("cp", NULL, head->childTags, head->childTags->brotherTags);
    //printf("%s\n", head->name);
    //printf("%d\n", head->childTags->brotherTags->close);

    //LinkedListTag* current = searchCurrentTag(head);
    //printf("%s\n", current->name);
    printTags(head);
    printTags(head->childTags->brotherTags->brotherTags);
    return 0;
}