#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char* filePath);
int closeFile(FILE* pt_fichier);
int readBaliseXml(char char_file);
char* concatenateCharInString(char* s, char char_file);
int verifyBaliseXML(char* s);

int main() {

    int good_balise_xml;

    // ouverture du fichier en lecture
    FILE* pt_fichier = openFile("example.xml");
    if(pt_fichier == NULL) {
        return -1;
    }

    int char_file = fgetc(pt_fichier);
    char* xml_tag = malloc(sizeof(char));

    // boucle balise xml
    while(char_file != EOF) {

        if(char_file != '>') {

            xml_tag = concatenateCharInString(xml_tag, char_file);
            //printf("%s\n", xml_tag);
        }else if(char_file == '>') {

            xml_tag = concatenateCharInString(xml_tag, char_file);
            //printf("%s\n", xml_tag);
            break;
        }

        char_file = fgetc(pt_fichier);
    }

    // verif validation balise xml
    good_balise_xml = verifyBaliseXML(xml_tag);
    if(good_balise_xml == 0){
        printf("problème avec la balise xml");
        return -1;
    }




    return 0;
}

char* concatenateCharInString(char* s, char char_file) {

    //printf("%lu", strlen(s));
    printf("%c", char_file);
    char* new_string = malloc(sizeof(char) * strlen(s) + 2);
    strncpy(new_string, s, strlen(s));
    new_string[strlen(s)] = char_file;
    new_string[strlen(s)+1] = '\0';
    free(s);

    return new_string;
}


FILE* openFile(char* filePath) {

    FILE* pt_fichier = malloc(sizeof(FILE));
    pt_fichier = fopen(filePath, "r");

    if(pt_fichier == NULL)
    {
        printf("erreur lors de l'ouverture du fichier");
        return NULL;
    }

    return pt_fichier;
}

int closeFile(FILE* pt_fichier) {
    
    int resultat = fclose(pt_fichier);

    if(resultat != 0)
    {
        printf("Erreur lors de la fermeture du fichier\n");
        return -1;
    }

    return 1;
}

int verifyBaliseXML(char* s) {
    printf("\nbalise xml -> %s\n", s);
    int flag = 1;
    int count_guillemet = 0;
    char final_s[strlen(s)];
    int count_final_s=0;
    for(int i=0; i< strlen(s); i++) {
        if(s[i] == '"' && count_guillemet%2 == 1){
            flag=1;
            count_guillemet +=1;
        }else if(final_s[count_final_s-1] == 'l' && s[i] == ' '){
           flag=1; 
           final_s[count_final_s] = s[i];
           count_final_s += 1;
           continue;
        }else if(s[i] == '"'){
            count_guillemet +=1;
        }else if(s[i] != ' ') {
            flag = 0;
        }

        printf("tour %d, carrac %c flag %d\n", i, s[i], flag);
        if(flag == 1 && s[i] == ' '){
            s[i] = '%';
        }else if(flag == 1 && s[i] != ' '){
            final_s[count_final_s] = s[i];
            count_final_s += 1;
        }else{
            flag=0;
            final_s[count_final_s] = s[i];
            count_final_s += 1;
        }
    }
    final_s[count_final_s] = '\0';

    printf("%s\n", s);
    printf("%s\n", final_s);


    if(strcmp(final_s,"<?xml version=\"1.0\"?>") == 0) {
        return 1;
    }else {
        return 0;
    }
}

int readBaliseXml(char char_file) {

    int* enterInXml = malloc(sizeof(int));
    enterInXml = 0;
    if(enterInXml == 0 && char_file == ' '){
        return 0;
    }else if(enterInXml == 0 && char_file == '<'){
        *enterInXml = 1;
        return 0;
    }else if(enterInXml == 0 && char_file != '<'){
        return -1;
    }
    return 0;
}
