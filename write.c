#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char* filePath);
int closeFile(FILE* pt_fichier);
int readBaliseXml(char char_file);
char* concatenateCharInString(char* s, char char_file);
int verifyBaliseXML(char* s);
int verifyBaliseXML2(char* s);
int regexSpaceBackSlachMultiple(char* s,int* i);
void regexSpaceBackSlachPlus(char* s,int* i);


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
    good_balise_xml = verifyBaliseXML2(xml_tag);
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

int regexSpaceBackSlachMultiple(char* s,int* i){

    printf("c'est i -> %d\n", *i);
    int count_for = 0;
    int valid = 1;
    for(;*i<strlen(s);*i+=1) {
        
        printf("i -> %c\n", s[*i]);
        if(count_for == 0 && (s[*i] == ' ' || s[*i] == '\n')){
            count_for++;
            continue;
        }else if(count_for == 0){
            valid = 0;
            break;
        }

        if(s[*i] != ' ' && s[*i] != '\n'){
            break;
        }
    }

    return valid;
}

void regexSpaceBackSlachPlus(char* s,int* i) {

    for(;*i<strlen(s);*i+=1) {
    
        if(s[*i] != ' ' && s[*i] != '\n'){
            break;
        }
    }
}


int verifyBaliseXML2(char* s) {
    //^(' '|'\n')*<?xml(' '|'\n')+version="1.0"(' '|'\n')+(encoding="UTF-8")?(' '|'\n')*?>(' '|'\n')*$
    printf("\nbalise xml -> %s\n", s);
    char first_bloc[] = "<?xml";
    char secound_bloc[] = "version=\"1.0\"";
    char third_bloc[] = "encoding=\"UTF-8\"";
    char fourth_bloc[] = "?>";
    int bloc_count = 0;
    int count_for = 0;

    int valid = 1;
    char final_s[strlen(s)];

    int count_final_s=0;
    int i = 0;
    // présence d'espace ou retour chariot avant la balise
    regexSpaceBackSlachPlus(s, &i);
    
    printf("\ntour i -> %d\n", i);

    if(strlen(s) < i+strlen(first_bloc)){
        return 0;
    }
    printf("\nlimite -> %lu\n", i+strlen(first_bloc));
    // verification premier_bloc
    for(;i<strlen(s);i++) {

        if(s[i] == first_bloc[bloc_count]) {
            printf("%c", s[i]);
            bloc_count+=1;
        }else {
            printf("pomme \n%c", s[i]);
            valid = 0;
            break;
        }
        if(bloc_count == strlen(first_bloc)){
            i++;
            break;
        }

    }
    printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    // bloc espace retour
    valid = regexSpaceBackSlachMultiple(s,&i);

    printf("\ntour i -> %d\n", i);
    if(valid == 0){
        return 0;
    }

    // 2eme bloc
    bloc_count = 0;
    for(;i<strlen(s);i++){

        if(s[i] == secound_bloc[bloc_count]) {
            //printf("%c", s[i]);
            bloc_count+=1;
        }else {
            //printf("pomme \n%c", s[i]);
            valid = 0;
            break;
        }
        if(bloc_count == strlen(secound_bloc)){
            i++;
            break;
        }
    }

    printf("\ntour i -> %d\n", i);
    if(valid == 0){
        return 0;
    }

    // bloc espace retour
    count_for = 0;
    int contain_space_backslach=0;
    for(;i<strlen(s);i++) {
        
        printf("i -> %c\n", s[i]);
        if(count_for == 0 && (s[i] == ' ' || s[i] == '\n')){
            count_for +=1;
            contain_space_backslach +=1;
            continue;
        }else if(count_for == 0){
            
            break;
        }

        if(s[i] != ' ' && s[i] != '\n'){
            break;
        }
    }

    printf("\nthird tour i -> %d\n", i);
    

    // third bloc not required
    if(contain_space_backslach == 1 && s[i] == 'e'){
        bloc_count = 0;
        for(;i<strlen(s);i++){

            if(s[i] == third_bloc[bloc_count]) {
                //printf("%c", s[i]);
                bloc_count+=1;
            }else {
                //printf("pomme \n%c", s[i]);
                valid = 0;
                break;
            }
            if(bloc_count == strlen(third_bloc)){
                i++;
                break;
            }
        }

        printf("\ntour i -> %d\n", i);
        if(valid == 0){
            return 0;
        }

         // présence espace ou retour chariot après balise
        regexSpaceBackSlachPlus(s, &i);
    }

    // dernier bloc
    bloc_count = 0;
    for(;i<strlen(s);i++){

        if(s[i] == fourth_bloc[bloc_count]) {
            //printf("%c", s[i]);
            bloc_count+=1;
        }else {
            //printf("pomme \n%c", s[i]);
            valid = 0;
            break;
        }
        if(bloc_count == strlen(third_bloc)){
            i++;
            break;
        }
    }

    printf("\ntour i -> %d\n", i);
    if(valid == 0){
        return 0;
    }

    return 1;
}

int verifyBaliseXML(char* s) {
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
        if(s[i] == '\n'){
            continue;
        }
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
