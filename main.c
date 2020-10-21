#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList {
    char* name;
    char* text;
    struct LinkedList* childTags;
    struct LinkedList* brotherTags;
}LinkedList;

LinkedList* intialisation(char* name) {

    LinkedList* ll = malloc(sizeof(LinkedList));

    ll->name = malloc(sizeof(char) * strlen(name));
    ll->name = name;
    ll->text = NULL;
    ll->childTags = NULL;
    ll->brotherTags = NULL;

    return ll;
}

void addLinkedListTags(char* name, char* text, LinkedList* parent, LinkedList* brotherAfter) {

    LinkedList* ll = malloc(sizeof(LinkedList));
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

    // ajout de la liasion sur la balise d'avant
    if(parent->childTags == NULL) {
        parent->childTags = ll;
    }else {

        LinkedList* brother = parent->childTags;
        while(brother != NULL){

            if(brother->brotherTags == NULL) {
                brother->brotherTags = ll;
                brother = ll;
            }
            brother = brother->brotherTags;
        }
    }
}

void addLinkedListBrother(char* name, char* text, LinkedList* brotherBefore, LinkedList* brotherAfter) {

    LinkedList* ll = malloc(sizeof(LinkedList));
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

    // ajout de la liasion sur la balise d'avant
    brotherBefore->brotherTags = ll;
}

void printTags(LinkedList* parent){

    LinkedList* child = parent->childTags;
    while(child != NULL){
        printf("%s\n", child->name);
        child = child->brotherTags;
    }
}

int main() {

    LinkedList* head = intialisation("message");
    addLinkedListTags("nom", "Pomme", head, NULL);
    addLinkedListTags("prenom", "jean", head, NULL);
    addLinkedListTags("adresse", NULL, head, NULL);
    addLinkedListTags("cp", "95120", head->childTags->brotherTags->brotherTags, NULL);
    addLinkedListTags("Ville", "Taverny", head->childTags->brotherTags->brotherTags, NULL);
    //addLinkedListBrother("cp", NULL, head->childTags, head->childTags->brotherTags);
    printf("%s\n", head->name);
    printTags(head);
    printTags(head->childTags->brotherTags->brotherTags);
    return 0;
}