#ifndef GTK_TP_GTK_FUNCTIONS_H
#define GTK_TP_GTK_FUNCTIONS_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GtkBuilder *builder;

typedef struct{
    GtkWindow *window;
    GtkLabel *is_conform;
    GtkLabel *filename_label;
    GtkLabel *filename_dtd;
    GtkLabel *filename_xml_save;
    GtkLabel *filename_dtd_save;
    GtkTextView *text_view;
    GtkTextView *text_view_dtd;
    GtkButton *new;
    GtkButton *read;
    GtkButton *save;
    GtkButton *read_dtd;
    GtkButton *verify_conformity;
    GtkButton *verify_xml;
    GtkButton *verify_dtd;
    GtkFileChooserDialog *fileChooserDialog;
    GtkFileChooser *chooser;
}App_widgets;

static App_widgets *widgets;

///////////////////////////////////////////////////////////////////////////////////////
#if defined(__WIN32) || defined(WIN32)

G_MODULE_EXPORT void on_button_new_clicked();
G_MODULE_EXPORT void on_button_read_clicked();
G_MODULE_EXPORT void on_button_save_clicked();
G_MODULE_EXPORT void on_button_read_dtd_clicked();
G_MODULE_EXPORT void on_button_verify_conformity_clicked();
G_MODULE_EXPORT void on_button_verify_xml_clicked();
G_MODULE_EXPORT void on_button_verify_dtd_clicked();

#endif
///////////////////////////////////////////////////////////////////////////////////////

int verify_conformity();

int verify_xml();

int verify_dtd();

const gchar *read_file(App_widgets *file_name_label, int type);

void write_file(gchar **contents);

void open_file();

void save_file();

void hide_filename_label();

void show_filename_label();

void clean_filename(App_widgets *file_name_label, char **filename);

void save_filename(App_widgets *file_name, const char **filename);

void set_filename_label(App_widgets *file_name_label, const char **filename);

const gchar *get_filename_label(App_widgets *file_name_label);

void set_text_view_text(App_widgets *text_view, gchar **text);

const gchar *get_text_view_text(App_widgets *text_view);

void start_GTK(int *argc, char ***argv, char *gladeFile);

void gtk_init_ui();

void connect_widgets();

void on_destroy();

#endif //GTK_TP_GTK_FUNCTIONS_H
