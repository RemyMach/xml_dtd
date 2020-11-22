#ifndef GTK_TP_GTK_FUNCTIONS_H
#define GTK_TP_GTK_FUNCTIONS_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GtkBuilder *builder;

//gchar *fileExtension;

typedef struct {
    GtkWindow *window;
    GtkLabel *is_conform;
    GtkLabel *filename_label;
    GtkEntry *file_name;
    GtkTextView *text_view;
    GtkButton *read;
    GtkButton *create;
    GtkButton *edit;
    GtkButton *validate;
    GtkFileChooserDialog *fileChooserDialog;
} App_widgets;

static App_widgets *widgets;

///////////////////////////////////////////////////////////////////////////////////////
#if defined(__WIN32) || defined(WIN32)

G_MODULE_EXPORT void on_button_read_clicked();
G_MODULE_EXPORT void on_button_create_clicked();
G_MODULE_EXPORT void on_button_edit_clicked();
G_MODULE_EXPORT void on_button_validate_clicked();

#endif
///////////////////////////////////////////////////////////////////////////////////////

void onDestroy();

void startGTK(int *argc, char ***argv, char *gladeFile);

void connectWidgets();

void gtk_init_ui();

void action_button_hide_and_show();

void read_button_hide_and_show();

void writeFile(const char **filename, gchar **contents);

static void open_dialog(GtkWidget* button, gpointer window);

gchar readFile(const char **filename);

GtkWidget* createConsoleBox();

#endif //GTK_TP_GTK_FUNCTIONS_H
