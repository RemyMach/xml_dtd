#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "validate_read.h"
#include "christophe.h"

/*typedef struct LinkedListTag {
    int close;
    char* name;
    char* text;
    struct LinkedListTag* parentTag;
    struct LinkedListTag* childTags;
    struct LinkedListTag* brotherTags;
    struct LinkedListAttribute* attribute;
}LinkedListTag;*/

int calcLignes(char*);
int calcCarL(char*,int);
void filterOne(char*,int,int);
LinkedListDtd* getDtdTag(char* pathfile);

/*int main() {

    LinkedListDtd* head_dtd_1 = getDtdTag("DTD_test/valid_3.dtd");
    printTagsDtd(head_dtd_1);
    return 0;
}*/

LinkedListDtd* getDtdTag(char* pathfile) {

    LinkedListDtd* head_dtd;

    /* Calcul nombre de lignes du fichier */
    printf("\n-------------Affichage des donnees du fichier------------- \n\n");
    int nbLignes=calcLignes(pathfile);
    printf("Nombre de lignes du fichier =%d\n",nbLignes);

    /* Calcul nombre de caractËres par lignes du fichier ainsi que du nombre max de caractËre pour une ligne */
    int nbCarMax=calcCarL(pathfile,nbLignes);

    FILE* f=fopen(pathfile,"r"); //Ouverture du fichier en lecture
    rewind(f);

    /* rÈcupÈration des lignes sÈparÈs dans un tableau de strings */
    printf("\n-------------Affichage des chaines de caracteres du tableau strings avant modifications------------- \n\n");
    char strings[nbLignes][nbCarMax];
    for(int i=0;i<nbLignes;i++){
        fgets(strings[i],nbCarMax,f);
        printf("Chaine %d: %s\n",i,strings[i]);
    }

    /* suppression des < > !*/
    for(int k=0;k<nbLignes;k++){
        for(int i=0;i<nbLignes;i++){
            for(int j=0;j<nbCarMax;j++){
                if(strings[i][j]=='<' || strings[i][j]=='>' || strings[i][j]=='!' ){
                    while(j<strlen(strings[i])){
                        strings[i][j]=strings[i][j+1];
                        j++;
                    }
                }
            }
        }
    }

    /* suppression des espaces */
    for(int k=0;k<nbLignes;k++){
        for(int i=0;i<nbLignes;i++){
            for(int j=0;j<nbCarMax;j++){
                if(strings[i][j]==' '){
                    while(j<strlen(strings[i])){
                        strings[i][j]=strings[i][j+1];
                        j++;
                    }
                }
            }
        }
    }

    /* suppression ELEMENT*/
    for(int k=0;k<nbLignes;k++){
        for(int i=0;i<nbLignes;i++){
            for(int j=0;j<nbCarMax;j++){
                if(strings[i][j]=='E' && strings[i][j+1]=='L'&& strings[i][j+2]=='E'&& strings[i][j+3]=='M'&& strings[i][j+4]=='E'&& strings[i][j+5]=='N'&& strings[i][j+6]=='T'){
                    while(j<strlen(strings[i])){
                        strings[i][j]=strings[i][j+7];
                        j++;
                    }
                }
            }
        }
    }

    /* suppression EMPTY*/
    for(int k=0;k<nbLignes;k++){
        for(int i=0;i<nbLignes;i++){
            for(int j=0;j<nbCarMax;j++){
                if(strings[i][j]=='E' && strings[i][j+1]=='M'&& strings[i][j+2]=='P'&& strings[i][j+3]=='T'&& strings[i][j+4]=='Y'){
                    while(j<strlen(strings[i])){
                        strings[i][j]=strings[i][j+5];
                        j++;
                    }
                }
            }
        }
    }

    /*Affichage des chaines de caracteres du tableau strings */
    printf("\n-------------Affichage des chaines de caracteres du tableau strings apres modifications------------- \n\n");
    for(int i=0;i<nbLignes;i++){
        printf("%s\n",strings[i]);
    }

    /* Stockage des donnÈes dans les listes */
    printf("\n-------------Affichage LinkedListTag------------- \n\n");
    char tempnom[nbCarMax];
    char tempchild[nbCarMax];
    char tempoper[nbCarMax];
    char temparent[nbCarMax];
    char tmp;
    int cpt=0;
    int cptchild=0;
    int cptoper=0;
    for(int i=1;i<nbLignes;i++){ //ignorance de la ligne 1
        if(strings[i][0]!=']' && strlen(strings[i])>1){
            /* extraction nom linkedListTag */
            while(strings[i][cpt]!='(' && strings[i][cpt]!='>' ){
                tempnom[cpt]=strings[i][cpt];
                cpt++;
            }
            tempnom[cpt]='\0';
            cpt++;

            /* extraction child linkedListTag */
            while(strings[i][cpt]!=',' && strings[i][cpt]!=')' && strings[i][cpt]!='#' && strings[i][cpt]!='|'&& strings[i][cpt]!='+'&& strings[i][cpt]!='?'&& strings[i][cpt]!='*'){ //extraction childTag
                tempchild[cptchild]=strings[i][cpt];
                cpt++;
                cptchild++;
            }
            tempchild[cptchild]='\0';



            /*   extraction signe linkedListTag  */
            cpt=0;
            cptchild=0;
            cptoper=0;
            tempoper[0]='0';
            tempoper[1]='\0';
            for(int j=1;j<i;j++){
                for(int k=0;k<strlen(strings[j]);k++){
                    if(strings[j][k]==tempnom[cptoper]){
                        cptoper++;
                    }
                    if(cptoper==strlen(tempnom)){
                        strcpy(tempoper,strings[j]);
                        strcpy(temparent,strings[j]);
                    }
                }
                cptoper=0;
            }

            for(int j=0;j<strlen(tempoper);j++){//suppression de ce qui est apres l'operateur
                if(tempoper[j]=='+' || tempoper[j]=='?' || tempoper[j]=='*'){
                    tempoper[j+1]='\0';
                }
            }
            for(int j=0;j<(strlen(tempoper));j++){//suppression de ce qui est avant la derniere parenthese
                if(tempoper[j]=='('){
                    for(int k=0;k<(strlen(tempoper)-j);k++){
                       tempoper[k]=tempoper[k+j];
                       cptoper=k;
                    }
                    tempoper[cptoper+1]='\0';
                    j=0;
                }
            }

            char* result = strstr( tempoper, tempnom );

            // Affichage reponse operateur.
            if ( result == NULL ) {
                tempoper[0]='0';
                tempoper[1]='\0';
            }else{
                tmp=0;
                cptoper=0;
                int flag=0;
                char res='0';
                for(int j=0;j<strlen(tempoper);j++){//si il y a un signe dans le string tempoper
                    if(tempoper[j]=='+' || tempoper[j]=='?' || tempoper[j]=='*'){
                        flag=1;
                        tmp=j;
                        res=tempoper[j];
                    }
                }
                if(flag==0){
                    tempoper[0]='0'; //si il n'y a pas de signe
                    tempoper[1]='\0';
                }else{
                    for(int j=tmp;j>0;j--){//si il y a un signe dans le string tempoper
                        if(tempoper[j]==','){
                            cptoper=j;
                        }
                    }
                    cpt=0;
                    for(cptoper;cptoper<=tmp;cptoper++){
                        tempoper[cpt]=tempoper[cptoper];
                        cpt++;
                    }
                    tempoper[cpt]='\0';

                    // Affichage reponse operateur.
                    char * result = strstr( tempoper, tempnom );
                    if ( result == NULL ){
                        tempoper[0]='0';
                        tempoper[1]='\0';
                    }else{
                        cpt=0;
                        for(int j=0;j<strlen(tempoper);j++){
                            if(tempoper[j]==tempnom[cpt]){
                                cpt++;
                                if(cpt==strlen(tempnom)){
                                    if(((tempoper[j+1]==',')||(tempoper[j+1]==')')||(tempoper[j+1]==res)||(tempoper[j+1]=='|'))&&((tempoper[j-cpt]==',')||(tempoper[j-cpt]==')')||(tempoper[j-cpt]=='|')||(tempoper[j-cpt]=='('))){
                                        tempoper[0]=res;
                                        tempoper[1]='\0';
                                        j+=100;
                                    }else{
                                        tempoper[0]='0';
                                        tempoper[1]='\0';
                                    }
                                }
                            }
                        }
                    }
                }
            }

            /* Extraction parent */
            for(int j=0;j<strlen(temparent);j++){
                if(temparent[j]=='('){
                    temparent[j]='\0';
                }
                if(i==1){
                    temparent[0]='0';
                    temparent[1]='\0';
                }
            }

            if(i == 1) {
                printf("tour -> i -> %d\n", i);
                printf("je rentre ici\n");
                head_dtd = intialisationDtd("");
                head_dtd->name = malloc(sizeof(char)*strlen(tempnom)+1);
                strncpy(head_dtd->name, tempnom, strlen(tempnom));
                head_dtd->name[strlen(tempnom)] = '\0';
                printf("nom LinkedListTag: %s\n",tempnom);
                printf("child: %s\n",tempchild);
                printf("parent: %s strlen -> %d\n",temparent, strlen(temparent));
                printf("oper: %s\n\n",tempoper);
                printTagsDtd(head_dtd);
                printf("----------------------\n");
                cpt=0;
                tmp=0;
                cptoper=0;
                continue;
            }
            if(tempoper[0] == '0') {
                addLinkedListDtd(tempnom, NULL, NULL, temparent, NULL, head_dtd);
            }else {
                addLinkedListDtd(tempnom, NULL, tempoper[0], temparent, NULL, head_dtd);
            }

            printf("nom LinkedListTag: %s\n",tempnom);
            printf("child: %s\n",tempchild);
            printf("parent: %s strlen -> %d\n",temparent, strlen(temparent));
            printf("oper: %s\n\n",tempoper);
            printTagsDtd(head_dtd);
            printf("----------------------\n");
            cpt=0;
            tmp=0;
            cptoper=0;
        }
    }

    printTagsDtd(head_dtd);
    printf("----------------------\n");
    fclose(f);
    return head_dtd;
}

int calcLignes(char* str){
    FILE* f=fopen(str,"r"); //Ouverture du fichier en lecture
    rewind(f);
    int c1=0;
    int c2=0;
    int nLignes=0;
    while((c1=fgetc(f)) != EOF){
        if(c1=='\n'){
            nLignes++;
        }
        c2 = c1;
    }
    if(c2 != '\n'){ //Ici, c2 est Ègal au caractËre juste avant le EOF
        nLignes++; //DerniËre ligne non finie
    }
    fclose(f);
    return nLignes;
}

int calcCarL(char* str,int nLignes){
    int nbCar[nLignes][1];
    FILE* f=fopen(str,"r");
    rewind(f);
    int c1=0;

    for(int i=0;i<nLignes;i++){
        nbCar[i][0]=0;
    }

    int k=0;
    while((c1=fgetc(f)) != EOF){
        if(c1=='\n'){
           k++;
        }
        if(c1!='\n'){
            nbCar[k][0]+=1;
        }
    }
    int nbCarMax=0;
    for(int i=0;i<nLignes;i++){
        printf("Nombre de caractere a la ligne %d: %d\n",i+1,nbCar[i][0]);
        if(nbCar[i][0]>nbCarMax){
            nbCarMax=nbCar[i][0];
        }
    }
    fclose(f);
    return nbCarMax+2;
}
