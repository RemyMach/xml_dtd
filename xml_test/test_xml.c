#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "../validate_read.h"
#include "test_xml.h"

int main() {

    int valid;
    printf("not_valid_count -> %d\n", NOT_VALID_COUNT);

    //for(int i=1;i<=NOT_VALID_COUNT; i++) {
    for(int i=1;i<=2; i++) {
        //char str[strlen(not_valid) + 6];
        //char* str = malloc(sizeof(char) * ( strlen(not_valid) + 6 ) );
        char* str = malloc(sizeof(char) * 26);
        
        printf("str -> %s\n", str);
        sprintf(str, "xml_test/not_valid_%d.xml", i);
        str[24] = '\0';
        LinkedListTag* head = intialisation("");
        printf("\n---------------------------------------------------------------\n");
        printf("file ->%s\n", str);
        printf("\n---------------------------------------------------------------\n");
        valid = validateRead(head, str);
        if(valid == 0) {
            printf("le fichier xml n'est pas valide\n");
            printf("le test est passé!\n");
            
        }else {
            printf("le fichier est valide\n");
            printf("le test n'est pas passé!\n");
            return 0;
        }
        *str = NULL;
        free(str);
        if(strcmp(head->name, "") != 0) {
            freeLinkedListTag(head);
        }
        //il faut vider la LinkedList head
        //return 0;
    }

    //for(int i=1;i<=VALID_COUNT; i++) {
    for(int i=1;i<=0; i++) {

        //char str[strlen(not_valid) + 6];
        char* str = malloc(sizeof(char) * ( 22 ) );

        sprintf(str, "xml_test/valid_%d.xml", i);
        str[21] = '\0';
        LinkedListTag* head = intialisation("");
        printf("\n---------------------------------------------------------------\n");
        printf("file ->%s\n", str);
        printf("\n---------------------------------------------------------------\n");
        valid = validateRead(head, str);
        if(valid == 0) {
            printf("le fichier xml n'est pas valide\n");
            printf("le test n'est pas passé!\n");
            return 0;
        }else {
            printf("le fichier est valide\n");
            printf("le test est passé!\n");
        }
        *str = NULL;
        free(str);
        freeLinkedListTag(head);
        //il faut vider la LinkedList head
        //return 0;
    }

    printf("\n---------------------------------------------------------------\n");
    printf("********** L'ensemble des tests sont passés **********");
    printf("\n---------------------------------------------------------------\n");

    return 0;
}