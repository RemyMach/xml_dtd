#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

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
int verifTagCloseSynthaxe(char* s);
int verifyTextSynthaxe(char* s);
int regexBracketPlus(char* s,int* i);
int regexBracketOne(char* s, int* i);
int regexBracketNumberSpecialMultiple(char *s,int* i, char delimiter1, char delimiter2, char delimiter3, char* special_characters);
char* getCarracTagXml(FILE* pt_fichier);
char* getCarracTag(FILE* pt_fichier);
char* getCarracBeforeDelimiter(FILE* pt_fichier, char delimiter,int verifyCarrac);
char* getCarracTagClose(FILE* pt_fichier);
char* getCarracText(FILE* pt_fichier);
int readAllOtherTags(FILE* pt_fichier, LinkedListTag* head);
void extractTagNameAndAttrbute_ADD(char* s, LinkedListTag* head);
char* extractTagName(char* s, int* i);
void extractTagAttribute_ADD(char* s,int* i, LinkedListTag* head);
char* extractTagAttributeKey(char* s, int* i);
char* extractTagAttributeValue(char* s, int* i);

void extractTagNameAndAttrbute_ADD(char* s, LinkedListTag* head) {

    int i = 0;
    //LinkedListTag* newNode = malloc(sizeof(LinkedListTag));
    char* tag_name;
    tag_name = extractTagName(s, &i);
    printf("tag_name -> %s\n", tag_name);
    addLinkedListTags(tag_name, NULL,0, searchCurrentTag(head), NULL);
    extractTagAttribute_ADD(s, &i, head);
}

char* extractTagName(char* s, int* i) {

    char* tag_name = malloc(sizeof(char));
    for(;*i<strlen(s); *i+=1) {
        if(s[*i] != ' ' && s[*i] != '\n' && s[*i] != '>' && s[*i] != '<') {
           tag_name = concatenateCharInString(tag_name, s[*i]); 
        }else{
            if(s[*i] != '<') {
                break;
            }
        }
    }
    printf("voici tag element %s\n", tag_name);
    return tag_name;
}

char* extractTagAttributeKey(char* s, int* i) {

    char* attribute_key = malloc(sizeof(char));
    *attribute_key = NULL;
    //printf("pointeur -> %p\n", attribute_key);
    for(;*i<strlen(s); *i+=1) {
        if(s[*i] != '='){
            attribute_key = concatenateCharInString(attribute_key, s[*i]);
        }else {
            *i+=1;
            break;
        }
        
    }
    return attribute_key;
}

char* extractTagAttributeValue(char* s, int* i) {

    char* attribute_value = malloc(sizeof(char));
    *attribute_value = NULL;
    //printf("value -> %s\n", attribute_value);
    //printf("pointeur -> %p\n", attribute_value);

    int count_mark = 0;
    for(;*i<strlen(s); *i+=1) {
        if(s[*i] != '"'){
            attribute_value = concatenateCharInString(attribute_value, s[*i]);
        }else if(count_mark < 1){
            count_mark+=1;
        }else {
            *i+=1;
            break;
        }
    }

    return attribute_value;
}

void extractTagAttribute_ADD(char* s,int* i, LinkedListTag* head) {

    char* attribute_key;
    char* attribute_value;
    int count = 0;
    printf("extractTagAttribute_ADD name %s\n", head->name);

    while(s[*i] != '>'){

        if(count%2==0) {
            // présence espace ou retour chariot après attribut ou tagName
            regexSpaceBackSlachMultiple(s, i);
        }else {
            attribute_key = extractTagAttributeKey(s, i);
            attribute_value = extractTagAttributeValue(s, i);
            printf("key -> %s\n", attribute_key);
            printf("value -> %s\n", attribute_value);
            addLinkedListAttribute(attribute_key, attribute_value, head);
            printf("\n---------------------------------------\n");
        }

        count+=1;
    }

}

// gcc -o write write.c structure.c
int main() {

    int good_balise_xml, valid;

    // ouverture du fichier en lecture
    FILE* pt_fichier = openFile("example.xml");
    if(pt_fichier == NULL) {
        return -1;
    }
    char* xml_tag = malloc(sizeof(char));
    int char_file;

    //get les carractère qu'il faut pour la balise xml
    xml_tag = getCarracTagXml(pt_fichier);

    // verif validation balise xml
    good_balise_xml = verifyBaliseXML(xml_tag);
    if(good_balise_xml == 0){
        printf("problème avec la balise xml");
        return -1;
    }
    *xml_tag = NULL;
    free(xml_tag);
    
    // de la fin de la balise XML au début de la balise root '<'
    char* xml_tag_next_tag = malloc(sizeof(char));
    xml_tag_next_tag = getCarracBeforeDelimiter(pt_fichier, '<', -1);

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
    root_tag = getCarracTag(pt_fichier);

    //printf("root_tag -> %s\n", root_tag);

    //verif de la balise root
    valid = verifTagSynthaxe(root_tag);
    if(valid == 0) {
        printf("problème avec la balise xml");
        return -1;
    }

    // on extrait le nom de l'élément
    int i = 0;
    char* root_tag_name_or_attribute;
    root_tag_name_or_attribute = extractTagName(root_tag, &i);
    LinkedListTag* head = intialisation(root_tag_name_or_attribute);


    //on extrait les attribut et on les ajoute.
    extractTagAttribute_ADD(root_tag, &i, head);
    *root_tag = NULL;
    free(root_tag);
    printTags(head);

    printf("\n---------------------------------------\n");
    valid = readAllOtherTags(pt_fichier, head);
    printf("valid -> %d\n", valid);
    if(valid == 0) {
        printf("problème avec la balise xml");
        return -1;
    }


    return 0;
}

int readAllOtherTags(FILE* pt_fichier, LinkedListTag* head) {

    printf("ouloulou %d\n", head->childTags);
    
    int char_file= fgetc(pt_fichier);
    int char_file_next;
    int valid = 1;
    //printf("premier carrac -> %c", char_file);
    int tour = 0;
    // on fait revenir le pointeur un rank en arrière
    while(char_file != EOF){

        if(tour%2 == 0){
            fseek(pt_fichier, -1, SEEK_CUR);
            getCarracBeforeDelimiter(pt_fichier, '<', 1);
        }else{
            char_file = fgetc(pt_fichier);
            char_file_next = fgetc(pt_fichier);
            printf("\n%c%c\n", char_file, char_file_next);
            fseek(pt_fichier, -1, SEEK_CUR);
            fseek(pt_fichier, -1, SEEK_CUR);

            if(char_file == '<' && char_file_next == '/') {
                //balise fermante
                char* close_tag = malloc(sizeof(char));
                close_tag = getCarracTagClose(pt_fichier);

                //verif de la balise close tag
                valid = verifTagCloseSynthaxe(close_tag);
                printf("balise fermée ->%s\n", close_tag);
                if(valid == 0) {
                    printf("problème avec la balise close tag");
                    return -1;
                }
                *close_tag = NULL;
                free(close_tag);
                fseek(pt_fichier, 1, SEEK_CUR);
            }else if(char_file == '<') {
                //open tag
                char* open_tag = malloc(sizeof(char));
                open_tag = getCarracTag(pt_fichier);

                //verif de la balise open tag
                valid = verifTagSynthaxe(open_tag);
                printf("balise ouverte ->%s\n", open_tag);
                if(valid == 0) {
                    printf("problème avec la balise open tag");
                    return -1;
                }
                extractTagNameAndAttrbute_ADD(open_tag, head);
                break;
                *open_tag = NULL;
                free(open_tag);
                // on a besoin de faire ça sinon un carrac trop bas dans les autres fonctions
                fseek(pt_fichier, 1, SEEK_CUR);
            }else{
                //chaine de carractère 
                char* text = malloc(sizeof(char));
                text = getCarracText(pt_fichier);

                //verif de la synthaxe de text
                valid = verifyTextSynthaxe(text);
                if(valid == 0) {
                    printf("problème avec la balise text tag");
                    return -1;
                }
                printf("text ->%s\n", text);
                *text = NULL;
                free(text);

            }
        }
        tour+=1;
        //test si fin fichier
        char_file = fgetc(pt_fichier);
        if(char_file == EOF){
            break;
        }else {
            fseek(pt_fichier, -1, SEEK_CUR);
        }

    }
    return 1;
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

    //printf("c'est i -> %d\n", *i);
    int count_for = 0;
    int valid = 1;
    for(;*i<strlen(s);*i+=1) {
        
        //printf("i -> %c\n", s[*i]);
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
            //printf("%c", s[*i]);
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
    //printf("carrac -> %c", s[*i]);
    if(s[*i] < 65 || s[*i] > 122){
        valid=0;
    }else if(s[*i] > 90 && s[*i] < 97){
        valid=0;
    }
    *i+=1;
    return valid;
}

int regexBracketNumberSpecialMultiple(char* s,int* i, char delimiter1, char delimiter2, char delimiter3, char* special_characters) {

    int valid = 1;
    for(;*i<strlen(s);*i+=1) {

        if(s[*i] == delimiter1 || s[*i] == delimiter2 || s[*i] == delimiter3) {
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

    //printf("\ntour i -> %d\n", i);

    if(strlen(s) < i+strlen(first_bloc)){
        return 0;
    }
    //printf("\nlimite -> %lu\n", i+strlen(first_bloc));
    
    // verification premier_bloc
    valid = regexRequiredBloc(s,&i, first_bloc);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    // bloc espace retour
    valid = regexSpaceBackSlachPlus(s,&i);

    //printf("\ntour i -> %d\n", i);
    if(valid == 0){
        return 0;
    }

    // 2eme bloc
    valid = regexRequiredBloc(s,&i, secound_bloc);

    //printf("\ntour i -> %d\n", i);
    if(valid == 0){
        return 0;
    }

    // bloc espace retour
    int contain_space_backslach=0;
    regexSpaceBackSlachPlusProofNotRequired(s,&i, &contain_space_backslach);

    //printf("\nthird tour i -> %d\n", i);
    

    // third bloc not required
    if(contain_space_backslach == 1 && s[i] == 'e'){
        
        valid = regexRequiredBloc(s,&i, third_bloc);

        //printf("\ntour i -> %d\n", i);
        if(valid == 0){
            return 0;
        }

         // présence espace ou retour chariot après balise
        regexSpaceBackSlachMultiple(s, &i);
    }

    // dernier bloc
    valid = regexRequiredBloc(s,&i, fourth_bloc);

    //printf("\ntour i -> %d\n", i);
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
    char secound_bloc[] = ">";
    char attribut_bloc[] = "\"";
    int tour = 0;
    //printf("chaine ->%s\n", s);

    // verification premier_bloc
    valid = regexRequiredBloc(s,&i, first_bloc);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //vérifie le premier charactère après <
    valid = regexBracketOne(s,&i);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //vérifie les carractère qui forme le nom de la balise à part le premier
    char special_characters1[] = "éèùàç.:-_";
    valid = regexBracketNumberSpecialMultiple(s, &i,' ', '\n','>', special_characters1);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //while pour valider les attributs
    int space_for_attribut = 0;
    while(s[i] != '>'){

        if(tour%2==0) {
            space_for_attribut = 0;
            // présence espace ou retour chariot après balise
            space_for_attribut = regexSpaceBackSlachPlus(s, &i);
        }else {
            if(space_for_attribut != 1) {
                return 0;
            }
            //le prochain carractère doit-être la première lettre de l'attribut
            valid = regexBracketOne(s,&i);
            //printf("\ntour i -> %d\n", i);

            if(valid == 0){
                return 0;
            }

            //vérifie les carractère qui forme le nom de l'attribut
            char special_characters2[] = "éèùàç.-_";
            valid = regexBracketNumberSpecialMultiple(s, &i,'=', -1, -1, special_characters2);
            //printf("\ntour i -> %d\n", i);
            // faire passer au carractère après le égale
            i+=1;
            if(valid == 0){
                return 0;
            }

            //vérifie les guillements
            valid = regexRequiredBloc(s,&i, attribut_bloc);
            //printf("\ntour i -> %d\n", i);

            if(valid == 0){
                return 0;
            }

            //vérifie les carractère qui forme la valeur de l'attribut
            char special_characters3[] = "éèùàç.-_>!?;\%ù*\\$°()§^ê£ \n";
            valid = regexBracketNumberSpecialMultiple(s, &i,'"', -1, -1, special_characters3);
            //printf("\ntour i -> %d\n", i);
            // faire passer au carractère après le égale
            i+=1;

            if(valid == 0){
                return 0;
            }
        }

        tour+=1;
    }

    return 1;

    //on verifie si le carractère ferme la balise > alors fin de balise
    //printf("\ntour i -> %d\n", i);
    if(s[i] == '>'){
        //printf("balise valide\n");
        return 1;
    }

    // présence espace ou retour chariot après balise
    regexSpaceBackSlachMultiple(s, &i);

    //on verifie si le carractère ferme la balise > alors fin de balise
    //printf("\ntour i -> %d\n", i);
    if(s[i] == '>'){
        //printf("balise valide\n");
        return 1;
    }

    //le prochain carractère doit-être la première lettre de l'attribut
    valid = regexBracketOne(s,&i);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //vérifie les carractère qui forme le nom de l'attribut
    char special_characters2[] = "éèùàç.-_";
    valid = regexBracketNumberSpecialMultiple(s, &i,'=', -1, -1, special_characters2);
    //printf("\ntour i -> %d\n", i);
    // faire passer au carractère après le égale
    i+=1;

    if(valid == 0){
        return 0;
    }

    //vérifie les guillements
    valid = regexRequiredBloc(s,&i, attribut_bloc);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //vérifie les carractère qui forme la valeur de l'attribut
    char special_characters3[] = "éèùàç.-_>!?;\%ù*\\$°()§^ê£";
    valid = regexBracketNumberSpecialMultiple(s, &i,'"', -1, -1, special_characters3);
    //printf("\ntour i -> %d\n", i);
    // faire passer au carractère après le égale
    i+=1;

    if(valid == 0){
        return 0;
    }

    // présence espace ou retour chariot après fin attribut
    regexSpaceBackSlachMultiple(s, &i);

    if(s[i] == '>'){
        //printf("balise valide\n");
        return 1;
    }

    
    return 1;
}

int verifTagCloseSynthaxe(char* s) {
    int i=0;
    int valid;
    char first_bloc[] = "</";
    char secound_bloc[] = ">";

    // verification premier_bloc
    valid = regexRequiredBloc(s,&i, first_bloc);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //vérifie le premier charactère après </
    valid = regexBracketOne(s,&i);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //vérifie les carractère qui forme le nom de la balise à part le premier
    char special_characters1[] = "éèùàç.:-_";
    valid = regexBracketNumberSpecialMultiple(s, &i,' ', '\n','>', special_characters1);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }

    //on verifie si le carractère ferme la balise > alors fin de balise
    //printf("\ntour i -> %d\n", i);
    if(s[i] == '>'){
        //printf("balise valide\n");
        return 1;
    }

    // présence espace ou retour chariot après balise
    regexSpaceBackSlachMultiple(s, &i);

    //on verifie si le carractère ferme la balise > alors fin de balise
    //printf("\ntour i -> %d\n", i);
    if(s[i] == '>'){
        //printf("balise valide\n");
        return 1;
    }

    return 0;
}

int verifyTextSynthaxe(char* s) {
    int i=0;
    int valid;

    //vérifie les carractère qui forme le nom de la balise à part le premier
    char special_characters1[] = "éèùàç.:-_$%ù!§|>/ \n";
    valid = regexBracketNumberSpecialMultiple(s, &i, -1, -1,'<', special_characters1);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }


    return 1;
}

char* getCarracTagXml(FILE* pt_fichier) {

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

    return xml_tag;
}

char* getCarracBeforeDelimiter(FILE* pt_fichier, char delimiter, int verifyCarrac) {

    char special_characters3[] = "éèùàç.-_>!?;\%ù*\\$°()§^ê£";
    int present = 0;
    char* xml_tag_next_tag = malloc(sizeof(char));
    int char_file = fgetc(pt_fichier);
    //printf("ici %c\n",char_file);
    while(char_file != EOF) {

        if(char_file != delimiter) {
            if(verifyCarrac == 1) {
                if(char_file == ' ' || char_file == '\n'){

                }else if( (char_file >= 97 && char_file <= 122) || (char_file >= 65 && char_file <= 90 ) || (char_file >= 48 && char_file <= 57) ) {
                    break;
                }else{
                    for(int e = 0;e<strlen(special_characters3); e+=1) {
                        if(char_file == special_characters3[e]) {
                            present = 1;
                        }
                    }
                    if(present==1) {
                        break;
                    }
                }
            }
            xml_tag_next_tag = concatenateCharInString(xml_tag_next_tag, char_file);
        }else {
            break;
        }
        char_file = fgetc(pt_fichier);
    }
    printf("balise avant le p ->%c\n", char_file);
    // on fait revenir le pointeur un rank en arrière
    fseek(pt_fichier, -1, SEEK_CUR);
    printf("balise après le p ->%c\n", char_file); 

    return xml_tag_next_tag;
}

char* getCarracTag(FILE* pt_fichier) {

    char* root_tag = malloc(sizeof(char));
    int count_guillemet=0;
    int count_crochet_open=0;
    int char_file = fgetc(pt_fichier);
    //printf("getCarrac -> %c\n", char_file);
    while(char_file != EOF) {
        //printf("%c", char_file);
        if(char_file == '<') {
            count_crochet_open +=1;
            if(count_crochet_open == 2){
                printf("vous ne pouvez pas utilisez le carractère < après %s", root_tag);
                return NULL;
                break;
            }else{
                root_tag = concatenateCharInString(root_tag, char_file);
            }
        }else if(char_file != '>') {
            if(char_file == '"') {
                count_guillemet+=1;
            }
            root_tag = concatenateCharInString(root_tag, char_file);
        }else if(char_file == '>' && count_guillemet%2 == 0){
            root_tag = concatenateCharInString(root_tag, char_file);
            break;
        }else {
            root_tag = concatenateCharInString(root_tag, char_file);
        }
        //printf("la chaine ->%s", root_tag);
        char_file = fgetc(pt_fichier);
    }

    return root_tag;
}

char* getCarracTagClose(FILE* pt_fichier) {

    char* close_tag = malloc(sizeof(char));
    int char_file = fgetc(pt_fichier);
    //printf("getCarrac -> %c\n", char_file);
    while(char_file != EOF) {
        //printf("%c", char_file);
        if(char_file != '>') {
            close_tag = concatenateCharInString(close_tag, char_file);
        }else {
            close_tag = concatenateCharInString(close_tag, char_file);
            break;
        }
        //printf("la chaine ->%s", root_tag);
        char_file = fgetc(pt_fichier);
    }

    return close_tag;
}

char* getCarracText(FILE* pt_fichier) {

    char* text = malloc(sizeof(char));
    int char_file = fgetc(pt_fichier);
    while(char_file != EOF) {
        printf("%c", char_file);
        if(char_file != '<') {
            text = concatenateCharInString(text, char_file);
        }else {
            break;
        }
        //printf("la chaine ->%s", root_tag);
        char_file = fgetc(pt_fichier);
    }

    return text;
}

