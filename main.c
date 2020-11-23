#include "gtk_functions.h"

int main(int argc, char **argv) {
#ifdef __unix__
    setenv("DISPLAY", "172.17.48.1:0", 1);
#endif
    char *gladeFilePath = strdup("gui.glade");

    start_GTK(&argc, &argv, gladeFilePath);

    free(gladeFilePath);
}