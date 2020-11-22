#include "gtk_functions.h"

int main(int argc, char **argv) {

    char *gladeFilePath = strdup("gui.glade");

    startGTK(&argc, &argv, gladeFilePath);

    free(gladeFilePath);
}