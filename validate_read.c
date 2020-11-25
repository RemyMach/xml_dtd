#include "validate_read.h"

int validateRead(LinkedListTag* head, char* pathFile) {
    int good_balise_xml, valid;

    // ouverture du fichier en lecture
    FILE* pt_fichier = openFile(pathFile);
    if(pt_fichier == NULL) {
        return 0;
    }
    char* xml_tag = malloc(sizeof(char));
    int char_file;

    xml_tag = getCarracTagXml(pt_fichier);
    
    // verif validation balise xml
    printf("xml_tag -> %s\n",xml_tag);
    good_balise_xml = verifyBaliseXML(xml_tag);
    printf("good_balise -> %d\n",good_balise_xml);
    if(good_balise_xml == 0){
        printf("problème avec la balise xml\n");
        free(xml_tag);
        xml_tag = NULL;
        printf("xml_tag after free -> %s\n", xml_tag);
        return 0;
    }
    free(xml_tag);
    xml_tag = NULL;
    // de la fin de la balise XML au début de la balise root '<'
    char* xml_tag_next_tag = malloc(sizeof(char));
    xml_tag_next_tag = getCarracBeforeDelimiter(pt_fichier, '<', -1);
    printf("%s",xml_tag_next_tag);
    //verif que avant la balise root on a pas autre chose que espace et backSlash
    valid = verifyOnlySpaceOrBackSlach(xml_tag_next_tag);
    if(valid == 0) {
        printf("problème avec la balise xml\n");
        free(xml_tag_next_tag);
        xml_tag_next_tag = NULL;
        return 0;
    }
    
    free(xml_tag_next_tag);
    xml_tag_next_tag = NULL;

    //on prend la première balise avec tous ses attributs
    char* root_tag = malloc(sizeof(char));
    root_tag = getCarracTag(pt_fichier);
    if(root_tag == 0) {
        printf("problème avec la balise xml1\n");
        free(root_tag);
        root_tag = NULL;
        return 0;
    }

    //printf("root_tag -> %s\n", root_tag);

    //verif de la balise root
    valid = verifTagSynthaxe(root_tag);
    if(valid == 0) {
        printf("problème avec la balise root\n");
        free(root_tag);
        root_tag = NULL;
        return 0;
    }

    // on extrait le nom de l'élément
    int i = 0;
    char* root_tag_name_or_attribute;
    root_tag_name_or_attribute = extractTagName(root_tag, &i);
    head->name = NULL;
    free(head->name);
    head->name = malloc(sizeof(char)*strlen(root_tag_name_or_attribute)+1);
    strncpy(head->name, root_tag_name_or_attribute, strlen(root_tag_name_or_attribute));
    head->name[strlen(root_tag_name_or_attribute)] = '\0';
    
    //on extrait les attribut et on les ajoute.
    if(extractTagAttribute_ADD(root_tag, &i, head) == 0) {
        printf("ERROR ATTRIBUTE");
        free(root_tag_name_or_attribute);
        root_tag = NULL;
        free(root_tag);
        return 0;
    }
        
    free(root_tag_name_or_attribute);
    root_tag_name_or_attribute = NULL;
    free(root_tag);
    root_tag = NULL;

    printf("\n---------------------------------------\n");
    valid = readAllOtherTags(pt_fichier, head);
    if(valid == 0) {
        printf("ERROR");
        return 0;
    }

    printf("\n---------------------------------------\n");
    
    valid = verifyAllTagsClosed(head);
    if(valid == 0) {
        printf("ERROR toutes les balises ne sont pas fermées\n");
        return 0;
    }

    return 1;
}

int validateFirstPart(LinkedListTag* head, char* pathFile) {

    if(validateRead(head, pathFile) == 0) {
        printf("le fichier xml a une structure non valide\n");
        return 0;
    }else {
        printf("le fichier xml a une structure valide\n");
    }
    
    if(validateDepthSpecify(head, 1) == 1) {
        printf("la profondeur est valide\n");
    }else {
        printf("la profondeur n'est pas valdide\n");
        return 0;
    }

    if(validateNoAttributes(head) == 1) {
        printf("le fichier n'a pas d'attributes\n");
    }else {
        printf("le fichier a des attributes ce qui le rend invalide\n");
        return 0;
    }

    return 1;
}

int validateSecondPart(LinkedListTag* head, char* pathFile) {

    if(validateRead(head, pathFile) == 0) {
        printf("le fichier xml a une structure non valide\n");
        return 0;
    }else {
        printf("le fichier xml a une structure valide\n");
    }
    
    if(validateDepthSpecify(head, 1) == 1) {
        printf("la profondeur est valide\n");
    }else {
        printf("la profondeur n'est pas valdide\n");
        return 0;
    }

    return 1;
}


int readAllOtherTags(FILE* pt_fichier, LinkedListTag* head) {
    
    printf("je suis dans readAllOtherTags\n");

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
                    printf("problème avec la balise close tag\n");
                    *close_tag = NULL;
                    free(close_tag);
                    break;
                }
                valid = extractTagName_close(close_tag, head);
                if(valid == 0) {
                    printf("problème avec la balise close tag -> %s\n", close_tag);
                    *close_tag = NULL;
                    free(close_tag);
                    break;
                }
                *close_tag = NULL;
                free(close_tag);
                fseek(pt_fichier, 1, SEEK_CUR);
            }else if(char_file == '<' && char_file_next == '!') {
                //balise commentaire
                valid = getCarracComment(pt_fichier, char_file);
                if(valid == 0) {
                    printf("problème avec la balise comment\n");
                    break;
                }
                fseek(pt_fichier, 1, SEEK_CUR);
            }else if(char_file == '<') {
                //open tag
                char* open_tag = malloc(sizeof(char));
                open_tag = getCarracTag(pt_fichier);
                printf("open_tag -> %s", open_tag);
                if(strcmp(open_tag, "not_valid") == 0) {
                    *open_tag = NULL;
                    free(open_tag);
                    return 0;
                }

                //verif de la balise open tag
                valid = verifTagSynthaxe(open_tag);
               
                if(valid == 0) {
                    printf("problème avec la balise open tag\n");
                    *open_tag = NULL;
                    free(open_tag);
                    break;
                }
                // si c'est une balise unique
                /*if(valid == 2)
                    open_tag[strlen(open_tag)] = '>';
                    open_tag[strlen(open_tag)+1] = '\0';*/

                printf("attributs -> %s\n",open_tag);

                if(extractTagNameAndAttrbute_ADD(open_tag, head) == 0) {
                    printf("ERROR ATTRIBUTE OR TAG NAME\n");
                    return 0;
                }
                // si c'est une balise unique
                if(valid == 2) {
                    valid = extractTagName_close(open_tag, head);
                    if(valid == 0) {
                        printf("problème avec la balise open_tag close_tag -> %s\n", open_tag);
                        *open_tag = NULL;
                        free(open_tag);
                        break;
                    }
                }
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
                    printf("problème avec la balise text tag\n");
                    break;
                }
                extractText_ADD(text, head);
                printf("text ->%s\n", text);

            }
        }
        tour+=1;
        //test si fin fichier
        //printf("yo %c\n", char_file);
        char_file = fgetc(pt_fichier);
        //printf("yo %c\n", char_file);
        if(char_file == EOF){
            break;
        }else {
            fseek(pt_fichier, -1, SEEK_CUR);
        }

    }
    
    return valid;
}

char* concatenateCharInString(char* s, char char_file) {

    //printf("%lu", strlen(s));
    //printf("%c", char_file);
    char* new_string = malloc(sizeof(char) * strlen(s) + 2);
    strncpy(new_string, s, strlen(s));
    new_string[strlen(s)] = char_file;
    new_string[strlen(s)+1] = '\0';
    if(strlen(s) > 0) {
        *s = NULL;
        free(s);
    }
    /*if(*s != NULL) {
        *s = NULL;
    }*/
    //*s = NULL;

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

void closeFile(FILE* pt_fichier) {

    int resultat = fclose(pt_fichier);
    if(resultat != 0)
    {
        printf("Erreur lors de la fermeture du fichier\n");
    }

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

    int valid=1;
    int bloc_count=0;
    for(;*i<strlen(s);*i+=1) {

        if(s[*i] == bloc[bloc_count]) {
            bloc_count+=1;
        }else {
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

    }
    return 0;
}

int regexBracketOne(char* s,int* i) {

    int valid=1;
    if(s[*i] < 65 || s[*i] > 122){
        valid=0;
    }else if(s[*i] > 90 && s[*i] < 97){
        valid=0;
    }

    if(s[*i] == '_') {
        valid = 1;
    }
    *i+=1;
    return valid;
}

int regexBracketNumberSpecialMultiple(char* s,int* i, char delimiter1, char delimiter2, char delimiter3, char* special_characters) {

    int valid = 1;
    for(;*i<strlen(s);*i+=1) {

        if(s[*i] == delimiter1 || s[*i] == delimiter2 || s[*i] == delimiter3) {
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
    char special_characters1[] = "éèùàç.:-_\"";
    valid = regexBracketNumberSpecialMultiple(s, &i,' ', '\n','>', special_characters1);
    //printf("\ntour i -> %d\n", i);

    valid = determinateUniqueTag(valid, s, &i);
    if(valid == 2) {
        return 2;
    }

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
            if(determinateUniqueTag(0, s, &i) == 2) {
                
                return 2;
            }
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

        valid = determinateUniqueTag(valid, s, &i);
        printf("valid -> %d\n", valid);
        if(valid == 2) {
            return 2;
        }

        tour+=1;
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
    char special_characters1[] = "&^*\\;!?éèùàç.:-_$%ù!§|>/,@[{()`}']\"#+=~ \n";
    valid = regexBracketNumberSpecialMultiple(s, &i, -1, -1,'<', special_characters1);
    //printf("\ntour i -> %d\n", i);

    if(valid == 0){
        return 0;
    }


    return 1;
}

char* getCarracTagXml(FILE* pt_fichier) {

    int char_file = fgetc(pt_fichier);
    char *xml_tag1 = malloc(sizeof(char));
    //printf("xml getCarrac -> %s\n", xml_tag);
    // boucle balise xml
    while(char_file != EOF) {

        if(char_file != '>') {

            xml_tag1 = concatenateCharInString(xml_tag1, char_file);
            //printf("%s\n", xml_tag);
        }else if(char_file == '>') {

            xml_tag1 = concatenateCharInString(xml_tag1, char_file);
            //printf("%s\n", xml_tag);
            break;
        }

        char_file = fgetc(pt_fichier);
    }

    return xml_tag1;
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
    if(char_file != EOF) {
        fseek(pt_fichier, -1, SEEK_CUR);
    }
    // on fait revenir le pointeur un rank en arrière
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
                printf("vous ne pouvez pas utilisez le carractère < après le tag %s\n", root_tag);
                *root_tag = NULL;
                free(root_tag);
                root_tag = malloc(sizeof(char) * 9);
                *root_tag = "not_valid";
                return root_tag;
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

int extractTagNameAndAttrbute_ADD(char* s, LinkedListTag* head) {

    int i = 0;
    //LinkedListTag* newNode = malloc(sizeof(LinkedListTag));
    char* tag_name;
    tag_name = extractTagName(s, &i);
    printf("tag_name -> %s\n", tag_name);
    addLinkedListTags(tag_name, NULL,0, searchCurrentTag(head), NULL);
    if(extractTagAttribute_ADD(s, &i, head) == 0)
        return 0;
    
    return 1;
}

char* extractTagName(char* s, int* i) {

    char* tag_name = malloc(sizeof(char));
    *tag_name = NULL;
    for(;*i<strlen(s); *i+=1) {
        if(s[*i] != ' ' && s[*i] != '\n' && s[*i] != '>' && s[*i] != '<' && s[*i] != '/') {
           tag_name = concatenateCharInString(tag_name, s[*i]); 
        }else{
            if(s[*i] != '<') {
                break;
            }
        }
    }
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

int extractTagAttribute_ADD(char* s,int* i, LinkedListTag* head) {

    char* attribute_key;
    char* attribute_value;
    int count = 0;
    printf("extractTagAttribute_ADD name %s\n", head->name);
    while(s[*i] != '>'){

        if(count%2==0) {
            // présence espace ou retour chariot après attribut ou tagName
            regexSpaceBackSlachMultiple(s, i);
            if(s[*i] != '>') {
                //printf("tyruei -> %c after -> %c\n", s[*i], s[*i+1]);
                if(determinateUniqueTag(0, s, i) == 2) {
                
                    return 1;
                }
            }
        }else {
            attribute_key = extractTagAttributeKey(s, i);
            attribute_value = extractTagAttributeValue(s, i);
            printf("key -> %s\n", attribute_key);
            printf("value -> %s\n", attribute_value);
            if(verifyLinkedListAttribute(attribute_key, head) == 0)
                return 0;
            
            addLinkedListAttribute(attribute_key, attribute_value, head);
            printf("\n---------------------------------------\n");
        }

        count+=1;
    }

    return 1;
}


void extractText_ADD(char* s,LinkedListTag* head) {
    // on a les espaces d'après la chaine mais pas d'avant
    addTextToLinkedListTag(s, head);
    printf("extractText_ADD text -> %s\n", s);
}

int extractTagName_close(char* s, LinkedListTag* head) {

    char* tag_name_close = malloc(sizeof(char));
    *tag_name_close = NULL;
    for(int i = 0;i<strlen(s);i+=1) {
        if(s[i] != ' ' && s[i] != '\n' && s[i] != '>' && s[i] != '<' && s[i] != '/') {
           tag_name_close = concatenateCharInString(tag_name_close, s[i]); 
        }else{
            if(s[i] != '<' && s[i] != '/') {
                break;
            }
        }
    }
    //printf("extractTagName_close %s\n", tag_name_close);
    if(closeTag(tag_name_close, searchCurrentTag(head)) == -1) {
        return 0;
    }else {
        return 1;
    }
}

int validateDepthSpecify(LinkedListTag* head, int depth_max) {

    if(count_depth(head) > depth_max) {
        return 0;
    }

    return 1;
}
int validateNoAttributes(LinkedListTag* head) {

    if(present_attribute(head) == 1)
        return 0;

    return 1;
}

int getCarracComment(FILE* pt_fichier,char char_file) {

    char_file = fgetc(pt_fichier);
    int i=0;
    char actual_miness_3 = char_file;
    char actual_miness_2 = char_file;
    char actual_miness_1= char_file;
    while(char_file != EOF) {
        if(i == 3) {
            if(actual_miness_3 != '<' || actual_miness_2 != '!' || actual_miness_1 != '-'  || char_file != '-') {
                return 0;
            }
        }else if(i >= 7) {
            if(actual_miness_2 == '-' && actual_miness_1 == '-'  && char_file == '>') {
                break;
            }

        }
        actual_miness_3 = actual_miness_2;
        actual_miness_2 = actual_miness_1;
        actual_miness_1 = char_file;
        char_file = fgetc(pt_fichier);
        i+=1;
    }

    if(i<3) {
        return 0;
    }

    return 1;
}

int determinateUniqueTag(int valid,char* s,int* i) {

    if(valid == 0 && s[*i] == '/' && s[*i+1] == '>') {
        return 2;
    }

    return valid;
}

void freeChar(char* s) {

    for(int i = 0;i<strlen(s);i++) {
        s[i] = NULL;
    }
}