#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char* filePath);
int closeFile(FILE* pt_fichier);
int readBaliseXml(char char_file);
char* concatenateCharInString(char* s, char char_file);
int verifyBaliseXML(char* s);
int regexSpaceBackSlachPlus(char* s,int* i);
void regexSpaceBackSlachPlusProofNotRequired(char* s,int* i, int* proof);
void regexSpaceBackSlachMultiple(char* s,int* i);
int regexRequiredBloc(char* s,int* i, char* bloc);
int verifyOnlySpaceOrBackSlach(char* s);
int regexSpaceBackSlachOnly(char* s,int* i);
int verifTagSynthaxe(char* s);
int regexBracketPlus(char* s,int* i);
int regexBracketOne(char* s, int* i);
int regexBracketNumberSpecialMultiple(char *s,int* i);

int main() {

    int good_balise_xml, valid;

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

    
    // de la fin de la balise XML au début de la balise root '<'
    char* xml_tag_next_tag = malloc(sizeof(char));
    char_file = fgetc(pt_fichier);
    while(char_file != EOF) {

        if(char_file != '<') {
            printf("%d", 0);
            xml_tag_next_tag = concatenateCharInString(xml_tag_next_tag, char_file);
        }else {
            break;
        }
        char_file = fgetc(pt_fichier);
    }
    //printf("%s\n", xml_tag_next_tag);
    //printf("la %c\n", char_file);
    //verif que avant la balise root on a pas autre chose que espace et backSlash
    valid = verifyOnlySpaceOrBackSlach(xml_tag_next_tag);
    if(valid == 0) {
        printf("problème avec la balise xml");
        return -1;
    }
    *xml_tag_next_tag = NULL;
    free(xml_tag_next_tag);

    //on prend la première balise avec tous ses attributs
    char* root_tag = malloc(sizeof(char));
    printf("%p\n", root_tag);
    int count_guillemet=0;
    int count_crochet_open=0;
    while(char_file != EOF) {
        //printf("%c", char_file);
        if(char_file == '<') {
            count_crochet_open +=1;
            if(count_crochet_open == 2){
                printf("vous ne pouvez pas utilisez le carractère < après %s", root_tag);
                return -1;
                break;
            }else{
                printf("%d", 1);
                root_tag = concatenateCharInString(root_tag, char_file);
            }
        }else if(char_file != '>') {
            if(char_file == '"') {
                count_guillemet+=1;
            }
            printf("%d", 2);
            root_tag = concatenateCharInString(root_tag, char_file);
        }else if(char_file == '>' && count_guillemet%2 == 0){
            printf("%d", 3);
            root_tag = concatenateCharInString(root_tag, char_file);
            break;
        }else {
            printf("%d", 4);
            root_tag = concatenateCharInString(root_tag, char_file);
        }
        printf("la chaine ->%s", root_tag);
        char_file = fgetc(pt_fichier);
    }

    //printf("root_tag -> %s\n", root_tag);

    //verif de la balise root
    valid = verifTagSynthaxe(root_tag);
    if(valid == 0) {
        printf("problème avec la balise xml");
        return -1;
    }

    return 0;
}

char* concatenateCharInString(char* s, char char_file) {

    //printf("%lu", strlen(s));
    //printf("%c", char_file);
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

int regexSpaceBackSlachPlus(char* s,int* i){

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

void regexSpaceBackSlachPlusProofNotRequired(char* s,int* i, int* proof){

    int count_for = 0;
    *proof = 0;
    for(;*i<strlen(s);*i+=1) {
        
        //printf("i -> %c\n", s[*i]);
        if(count_for == 0 && (s[*i] == ' ' || s[*i] == '\n')){
            count_for +=1;
            *proof +=1;
            continue;
        }else if(count_for == 0){
            
            break;
        }

        if(s[*i] != ' ' && s[*i] != '\n'){
            break;
        }
    }
}

void regexSpaceBackSlachMultiple(char* s,int* i) {

    for(;*i<strlen(s);*i+=1) {
    
        if(s[*i] != ' ' && s[*i] != '\n'){
            break;
        }
    }
}

int regexRequiredBloc(char* s,int* i, char* bloc) {

    //printf("ça bloque -> %c\n", s[*i+1]);
    int valid=1;
    int bloc_count=0;
    for(;*i<strlen(s);*i+=1) {

        if(s[*i] == bloc[bloc_count]) {
            printf("%c", s[*i]);
            bloc_count+=1;
        }else {
            //printf("pomme \n%c", s[*i]);
            valid = 0;
            break;
        }
        if(bloc_count == strlen(bloc)){
            *i+=1;
            break;
        }
    }

    return valid;
}

int regexSpaceBackSlachOnly(char* s, int* i){
    int valid = 1;
    for(;*i<strlen(s);*i+=1) {
    
        if(s[*i] != ' ' && s[*i] != '\n'){
            valid = 0;
            *i+=1;
            break;
        }
    }

    return valid;
}

int regexBracketPlus(char* s,int* i) {

    char special_characters[] = "éèùàç.:-_";
    for(;*i<strlen(s);*i+=1) {

        //if(s[i] >)
    }
    return 0;
}

int regexBracketOne(char* s,int* i) {

    int valid=1;
    printf("carrac -> %c", s[*i]);
    if(s[*i] < 65 || s[*i] > 122){
        valid=0;
    }else if(s[*i] > 90 && s[*i] < 97){
        valid=0;
    }
    *i+=1;
    return valid;
}

int regexBracketNumberSpecialMultiple(char *s,int* i) {

    int valid = 1;
    char special_characters[] = "éèùàç.:-_";
    for(;*i<strlen(s);*i+=1) {

        if(s[*i] == ' ') {
            break;
        }else if( s[*i] < 48 || s[*i] > 122 || (s[*i] > 90 && s[*i] < 97) || (s[*i] > 57 && s[*i] < 65) ) {
            int present = 0;
            for(int e = 0;e<strlen(special_characters); e+=1) {
                if(s[*i] == special_characters[e]) {
                    present = 1;
                }
            }
            if(present == 0) {
                valid=0;
                break;
            }
        }
    }

    return valid;
}

int verifyBaliseXML(char* s) {
    //^(' '|'\n')*<?xml(' '|'\n')+version="1.0"(' '|'\n')+(encoding="UTF-8")?(' '|'\n')*?>(' '|'\n')*$
    printf("\nbalise xml -> %s\n", s);
    char first_bloc[] = "<?xml";
    char secound_bloc[] = "version=\"1.0\"";
    char third_bloc[] = "encoding=\"UTF-8\"";
    char fourth_bloc[] = "?>";

    int valid = 1;
    int i = 0;

    // présence d'espace ou retour chariot avant la balise
    regexSpaceBackSlachMultiple(s, &i);

    printf("\ntour i -> %d\n", i);

    if(strlen(s) < i+strlen(first_bloc)){
        return 0;
    }
    printf("\nlimite -> %lu\n", i+strlen(first_bloc));
    
    // verification premier_bloc
    valid = regexRequiredBloc(s,&i, first_bloc);
    printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    // bloc espace retour
    valid = regexSpaceBackSlachPlus(s,&i);

    printf("\ntour i -> %d\n", i);
    if(valid == 0){
        return 0;
    }

    // 2eme bloc
    valid = regexRequiredBloc(s,&i, secound_bloc);

    printf("\ntour i -> %d\n", i);
    if(valid == 0){
        return 0;
    }

    // bloc espace retour
    int contain_space_backslach=0;
    regexSpaceBackSlachPlusProofNotRequired(s,&i, &contain_space_backslach);

    printf("\nthird tour i -> %d\n", i);
    

    // third bloc not required
    if(contain_space_backslach == 1 && s[i] == 'e'){
        
        valid = regexRequiredBloc(s,&i, third_bloc);

        printf("\ntour i -> %d\n", i);
        if(valid == 0){
            return 0;
        }

         // présence espace ou retour chariot après balise
        regexSpaceBackSlachMultiple(s, &i);
    }

    // dernier bloc
    valid = regexRequiredBloc(s,&i, fourth_bloc);

    printf("\ntour i -> %d\n", i);
    if(valid == 0){
        return 0;
    }

    return 1;
}

int verifyOnlySpaceOrBackSlach(char* s){
    //^(' ')*$
    int i=0;
    int valid;
    valid = regexSpaceBackSlachOnly(s,&i);

    return valid;

}

int verifTagSynthaxe(char* s) {
    int i=0;
    int valid;
    char first_bloc[] = "<";
    printf("chaine ->%s\n", s);

    // verification premier_bloc
    valid = regexRequiredBloc(s,&i, first_bloc);
    printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //vérifie le premier charactère après <
    valid = regexBracketOne(s,&i);
    printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //vérifie les carractère qui forme le nom de la balise à part le premier
    valid = regexBracketNumberSpecialMultiple(s, &i);
    printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    return 1;
}
