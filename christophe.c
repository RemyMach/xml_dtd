#include "christophe.h"

int getDtdTag(LinkedListDtd* head_dtd, char* pathfile) {
    
    FILE* f=fopen(pathfile,"r");

    if (f != NULL) // On peut lire et Ècrire dans le fichier
    {
        /* variables */
        char tmp;
        int cpt=0;
        int cptchild=0;
        int cptoper=0;

        /* Calcul nombre de lignes du fichier */
        //printf("\n-------------Affichage des donnees du fichier------------- \n\n");
        int nbLignes=calcLignes(pathfile);
        //printf("Nombre de lignes du fichier =%d\n",nbLignes);

        /* Calcul nombre de caractËres par lignes du fichier ainsi que du nombre max de caractËre pour une ligne */
        int nbCarMax=calcCarL(pathfile,nbLignes);

        /* variables resultat */
        char tempnom[nbCarMax];
        char tempchild[nbCarMax];
        char tempoper[nbCarMax];
        char temparent[nbCarMax];
        char attnom[nbCarMax];
        char attoper;
        char attparent[nbCarMax];

        rewind(f);

        /* rÈcupÈration des lignes sÈparÈs dans un tableau de strings */
        printf("\n-------------Affichage des chaines de caracteres du tableau strings avant modifications------------- \n\n");
        char strings[nbLignes][nbCarMax];
        for(int i=0;i<nbLignes;i++){
            fgets(strings[i],nbCarMax,f);
        }

        /* separation ELEMENT et ATTLIST*/
        int cptE=0; //element
        int cptA=0; //attlist

        for(int i=0;i<nbLignes;i++){
            for(int j=0;j<nbCarMax;j++){
                if(strings[i][j]=='E' && strings[i][j+1]=='L'&& strings[i][j+2]=='E'&& strings[i][j+3]=='M'&& strings[i][j+4]=='E'&& strings[i][j+5]=='N'&& strings[i][j+6]=='T'){
                    cptE++;
                }
                if(strings[i][j]=='A' && strings[i][j+1]=='T'&& strings[i][j+2]=='T'&& strings[i][j+3]=='L'&& strings[i][j+4]=='I'&& strings[i][j+5]=='S'&& strings[i][j+6]=='T'){
                    cptA++;
                }
            }
        }

        char stringE[cptE][nbCarMax];
        char stringA[cptA][nbCarMax];

        int cptElem=0;
        int cptAtt=0;
        for(int i=0;i<nbLignes;i++){ //copie dans 2 chaines diffÈrentes
            for(int j=0;j<nbCarMax;j++){
                if(strings[i][j]=='E' && strings[i][j+1]=='L'&& strings[i][j+2]=='E'&& strings[i][j+3]=='M'&& strings[i][j+4]=='E'&& strings[i][j+5]=='N'&& strings[i][j+6]=='T'){
                    strcpy(stringE[cptElem],strings[i]);
                    cptElem++;
                }
                if(strings[i][j]=='A' && strings[i][j+1]=='T'&& strings[i][j+2]=='T'&& strings[i][j+3]=='L'&& strings[i][j+4]=='I'&& strings[i][j+5]=='S'&& strings[i][j+6]=='T'){
                    strcpy(stringA[cptAtt],strings[i]);
                    cptAtt++;
                }
            }
        }

        for(int i=0;i<cptE;i++){
            printf("StringE: %s\n",stringE[i]);
        }


        /*------------------------------------------------ELEMENT------------------------------------------------------------*/

        /* suppression des < > !*/
        for(int k=0;k<nbCarMax;k++){
            for(int i=0;i<cptE;i++){
                for(int j=0;j<strlen(stringE[i]);j++){
                    if(stringE[i][j]=='<' || stringE[i][j]=='>' || stringE[i][j]=='!' ){
                        while(j<strlen(stringE[i])){
                            stringE[i][j]=stringE[i][j+1];
                            j++;
                        }
                    }
                }
            }
        }

        /* suppression des espaces */
        for(int k=0;k<nbCarMax;k++){
            for(int i=0;i<cptE;i++){
                for(int j=0;j<strlen(stringE[i]);j++){
                    if(stringE[i][j]==' '){
                        while(j<strlen(stringE[i])){
                            stringE[i][j]=stringE[i][j+1];
                            j++;
                        }
                    }
                }
            }
        }

        /* suppression ELEMENT*/
        for(int k=0;k<nbCarMax;k++){
            for(int i=0;i<cptE;i++){
                for(int j=0;j<strlen(stringE[i]);j++){
                    if(stringE[i][j]=='E' && stringE[i][j+1]=='L'&& stringE[i][j+2]=='E'&& stringE[i][j+3]=='M'&& stringE[i][j+4]=='E'&& stringE[i][j+5]=='N'&& stringE[i][j+6]=='T'){
                        while(j<strlen(stringE[i])){
                            stringE[i][j]=stringE[i][j+7];
                            j++;
                        }
                    }
                }
            }
        }

        /* suppression EMPTY*/
        int empty[cptE];
        for(int i=0;i<cptE;i++){
            empty[i]=0;
        }
        for(int k=0;k<nbCarMax;k++){
            for(int i=0;i<cptE;i++){
                for(int j=0;j<strlen(stringE[i]);j++){
                    if(stringE[i][j]=='E' && stringE[i][j+1]=='M'&& stringE[i][j+2]=='P'&& stringE[i][j+3]=='T'&& stringE[i][j+4]=='Y'){
                        empty[i]=1;
                        while(j<strlen(stringE[i])){
                            stringE[i][j]=stringE[i][j+5];
                            j++;
                        }
                    }
                }
            }
        }

        /*Affichage des chaines de caracteres du tableau strings */
        printf("\n-------------Affichage des chaines de caracteres du tableau strings apres modifications------------- \n\n");

        /* Stockage des donnÈes dans les listes */
        printf("\n-------------Affichage ELEMENT ------------- \n\n");

        for(int i=0;i<cptE;i++){

            /* extraction nom  */
            while(stringE[i][cpt]!='(' && stringE[i][cpt]!='>' ){
                tempnom[cpt]=stringE[i][cpt];
                cpt++;
            }
            tempnom[cpt]='\0';
            cpt++;

            /* extraction child  */
            if(empty[i]==1){
                tempchild[0]='0';
                tempchild[1]='\0';

            }else{
                while(stringE[i][cpt]!=',' && stringE[i][cpt]!=')' && stringE[i][cpt]!='#' && stringE[i][cpt]!='|'&& stringE[i][cpt]!='+'&& stringE[i][cpt]!='?'&& stringE[i][cpt]!='*' && stringE[i][cpt]!='\0'){ //extraction childTag
                    tempchild[cptchild]=stringE[i][cpt];
                    cpt++;
                    cptchild++;
                }
                tempchild[cptchild]='\0';
            }

            /*   extraction signe   */
            cpt=0;
            cptchild=0;
            cptoper=0;
            tempoper[0]='0';
            tempoper[1]='\0';
            for(int j=0;j<i;j++){
                for(int k=0;k<strlen(stringE[j]);k++){
                    if(stringE[j][k]==tempnom[cptoper]){
                        cptoper++;
                    }
                    if(cptoper==strlen(tempnom)){
                        strcpy(tempoper,stringE[j]);
                        strcpy(temparent,stringE[j]);
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

            char * result = strstr( tempoper, tempnom );
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
                if(i==0){
                    temparent[0]='0';
                    temparent[1]='\0';
                }
            }


            if(i == 0) {
                head_dtd->name = malloc(sizeof(char)*strlen(tempnom)+1);
                strcpy(head_dtd->name, tempnom);
                /*printf("nom LinkedListTag: %s\n",tempnom);
                printf("child: %s\n",tempchild);
                printf("parent: %s strlen -> %d\n",temparent, strlen(temparent));
                printf("oper: %s\n\n",tempoper);
                printTagsDtd(head_dtd);
                printf("----------------------\n");*/
                cpt=0;
                tmp=0;
                cptoper=0;
                /*printf("----------------------\n");
                printf("----------------------\n");
                printTagsDtd(head_dtd);
                printf("----------------------\n");
                printf("----------------------\n");*/
                continue;
            }
            char *p_backSlash = strchr(tempnom, '\n');
            if (p_backSlash != NULL) {
                int e = 0;
                for(int i = 0; i<strlen(tempnom); i++) {
                    if(tempnom[i] != '\n') {
                        tempnom[e] = tempnom[i];
                        e++;
                    }
                }
                tempnom[e] = '\0';
            }
            if(tempoper[0] == '0') {
                addLinkedListDtd(tempnom, NULL, NULL, temparent, NULL, head_dtd);
            }else {
                addLinkedListDtd(tempnom, NULL, tempoper[0], temparent, NULL, head_dtd);
            }

            /*printf("nom LinkedListTag: %s\n",tempnom);
            printf("child: %s\n",tempchild);
            printf("parent: %s strlen -> %d\n",temparent, strlen(temparent));
            printf("oper: %s\n\n",tempoper);
            printTagsDtd(head_dtd);
            printf("----------------------\n");*/
            cpt=0;
            tmp=0;
            cptoper=0;
            /*printf("----------------------\n");
            printf("----------------------\n");
            printTagsDtd(head_dtd);
            printf("----------------------\n");
            printf("----------------------\n");*/

        }
        /*------------------------------------------------ATTLIST------------------------------------------------------------*/
        /*printf("\n-------------Affichage ATTLIST ------------- \n\n");
        printf("\n");*/
        for(int i=0;i<cptA;i++){
            printf("StringA: %s\n",stringA[i]);
        }

        /* suppression des < > !*/
        for(int k=0;k<nbCarMax;k++){
            for(int i=0;i<cptA;i++){
                for(int j=0;j<strlen(stringA[i]);j++){
                    if(stringA[i][j]=='<' || stringA[i][j]=='>' || stringA[i][j]=='!' ){
                        while(j<strlen(stringA[i])){
                            stringA[i][j]=stringA[i][j+1];
                            j++;
                        }
                    }
                }
            }
        }

        /* suppression ATTLIST*/
        for(int k=0;k<nbCarMax;k++){
            for(int i=0;i<cptA;i++){
                for(int j=0;j<strlen(stringA[i]);j++){
                    if(stringA[i][j]=='A' && stringA[i][j+1]=='T'&& stringA[i][j+2]=='T'&& stringA[i][j+3]=='L'&& stringA[i][j+4]=='I'&& stringA[i][j+5]=='S'&& stringA[i][j+6]=='T'){
                        while(j<strlen(stringA[i])){
                            stringA[i][j]=stringA[i][j+7];
                            j++;
                        }
                    }
                }
            }
        }

        /* remplacement des espaces */
        for(int k=0;k<nbCarMax;k++){
            for(int i=0;i<cptA;i++){
                for(int j=0;j<strlen(stringA[i]);j++){
                    if(stringA[i][j]==' '){
                        stringA[i][j]='|';
                    }
                }
            }
        }

        /* suppression CDATA*/
        for(int k=0;k<nbCarMax;k++){
            for(int i=0;i<cptA;i++){
                for(int j=0;j<strlen(stringA[i]);j++){
                    if(stringA[i][j]=='C' && stringA[i][j+1]=='D'&& stringA[i][j+2]=='A'&& stringA[i][j+3]=='T'&& stringA[i][j+4]=='A'){
                        while(j<strlen(stringA[i])){
                            stringA[i][j-1]=stringA[i][j+5];
                            j++;
                        }
                    }
                }
            }
        }

        for(int i=0;i<cptA;i++){
            printf("StringA modified: %s\n",stringA[i]);
        }

        for(int i=0;i<cptA;i++){

            cpt=0;
            /* extraction nom  */
            while(stringA[i][cpt+1]!='|'){
                attparent[cpt]=stringA[i][cpt+1];
                cpt++;
            }
            attparent[cpt]='\0';

            /* suppression nom dans StringA */
            cpt=0;
            for(int j=strlen(attparent)+2;j<strlen(stringA[i]);j++){
                stringA[i][cpt]=stringA[i][j];
                cpt++;
            }
            stringA[i][cpt]='\0';

            /* extraction parent */
            cpt=0;
            while(stringA[i][cpt]!='|'){
                attnom[cpt]=stringA[i][cpt];
                cpt++;
            }
            attnom[cpt]='\0';

            /* suppression parent dans StringA */
            cpt=0;
            for(int j=strlen(attnom)+1;j<strlen(stringA[i]);j++){
                stringA[i][cpt]=stringA[i][j];
                cpt++;
            }
            stringA[i][cpt]='\0';

            /* def de l'operateur */
            if(stringA[i][0]=='#' && stringA[i][1]=='R'&& stringA[i][2]=='E'&& stringA[i][3]=='Q'&& stringA[i][4]=='U'&& stringA[i][5]=='I'&& stringA[i][6]=='R'&& stringA[i][7]=='E'&& stringA[i][8]=='D'){
                attoper='+';
            }else if(stringA[i][0]=='#' && stringA[i][1]=='I'&& stringA[i][2]=='M'&& stringA[i][3]=='P'&& stringA[i][4]=='L'&& stringA[i][5]=='I'&& stringA[i][6]=='E'&& stringA[i][7]=='D'){
                attoper='?';
            }

            addLinkedListAttributeDtd(attnom, attparent, attoper, head_dtd);

            /*printf("nom de l'attribut: %s\n",attnom);
            printf("parent: %s\n",attparent);
            printf("oper: %c\n\n",attoper);*/
        }
    }else{
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s\n", pathfile);
        return 0;
    }
    
    fclose(f);

    return 1;
}


/*----------------------------------------------------------------------FONCTIONS------------------------------------------------------------*/
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
        //printf("Nombre de caractere a la ligne %d: %d\n",i+1,nbCar[i][0]);
        if(nbCar[i][0]>nbCarMax){
            nbCarMax=nbCar[i][0];
        }
    }
    fclose(f);
    return nbCarMax+2;
}