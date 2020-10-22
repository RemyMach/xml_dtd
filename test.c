#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE* pt_fichier = malloc(sizeof(FILE));
    pt_fichier = fopen("example.xml", "r");

    if(pt_fichier == NULL)
    {
        printf("erreur lors de l'ouverture du fichier");
        return 0;
    }

    char char_file = fgetc(pt_fichier);

    while(char_file != EOF) {

        printf("%c",char_file);
        char_file = fgetc(pt_fichier);
    }

    int resultat = fclose(pt_fichier);

    if(resultat != 0)
    {
        printf("Erreur lors de la fermeture du fichier\n");
        return -1;
    }
    return 0;
}