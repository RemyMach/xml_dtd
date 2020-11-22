#include "gtk_functions.h"

//////////////////////////////////////////////////////////////////////////////////////////
void on_button_read_clicked() {
    //char *filename = strdup("valid_1.xml");
    //gchar *buffer = readFile(filename);

    read_button_hide_and_show();

    gchar *buffer = NULL;
    GError *error = NULL;
    if (g_file_get_contents ("valid_1.xml", &buffer, NULL, &error) == FALSE)
    {
        g_warning ("%s", error->message);
        g_clear_error (&error);
        return;
    }

    // Ajout du contenu du fichier dans un buffer, puis ajout du buffer dans le text_view
    GtkTextBuffer *buffer2 = gtk_text_view_get_buffer (widgets->text_view);
    gtk_text_buffer_set_text (buffer2, buffer, strlen(buffer));
    gtk_text_view_set_buffer (widgets->text_view, buffer2);

    //gtk_label_set_text (widgets->is_conform, "Format XML : conforme \nDTD : non conforme");
    //gtk_label_set_text (widgets->is_conform, "Format XML : non conforme \nDTD : conforme");
    //gtk_label_set_text (widgets->is_conform, "Format XML : non conforme \nDTD : non conforme");
    //gtk_label_set_text (widgets->is_conform, "Format XML : conforme \nDTD : conforme");
    gtk_label_set_text (widgets->is_conform, "read");
}

gchar readFile(const char **filename){
    gchar *buffer = NULL;
    GError *error = NULL;
    if (g_file_get_contents ("valid_1.xml", &buffer, NULL, &error) == FALSE)
    {
        g_warning ("%s", error->message);
        g_clear_error (&error);
        return "null";
    }
    return buffer;
}

void writeFile(const char **filename, gchar **contents) {
    GError *error = NULL;
    if(g_file_set_contents (filename, contents, strlen(contents), &error) == FALSE)
    {
        g_warning ("%s", error->message);
        g_clear_error (&error);
        return;
    }
}

void on_button_validate_clicked(){
    // Recuperation du nom de fichier
    gchar *entry_text = gtk_entry_get_text (widgets->file_name);
    entry_text = strcat( entry_text, ".xml" );
    gchar *text;
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (widgets->text_view);
    char *filename = strdup(entry_text);

    // Récupération de contenu du text_view
    gtk_text_buffer_get_bounds (buffer, &start, &end);
    text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

    // Ecriture du fichier avec le contenu du textview
    writeFile(filename, text);
}

void on_button_create_clicked() {
    gtk_label_set_text (widgets->is_conform, "create");
    action_button_hide_and_show();

    GtkTextBuffer *buffer2 = gtk_text_view_get_buffer (widgets->text_view);
    gtk_text_buffer_set_text (buffer2, "", -1);
    gtk_text_view_set_buffer (widgets->text_view, buffer2);
}

void on_button_edit_clicked() {
    action_button_hide_and_show();

    // Lecture d'un fichier
    gchar *buffer = NULL;
    GError *error = NULL;
    if (g_file_get_contents ("valid_1.xml", &buffer, NULL, &error) == FALSE)
    {
        g_warning ("%s", error->message);
        g_clear_error (&error);
        return;
    }

    // Ajout du contenu du fichier dans un buffer, puis ajout du buffer dans le text_view
    GtkTextBuffer *buffer2 = gtk_text_view_get_buffer (widgets->text_view);
    gtk_text_buffer_set_text (buffer2, buffer, strlen(buffer));
    gtk_text_view_set_buffer (widgets->text_view, buffer2);

    gtk_label_set_text (widgets->is_conform, "edit");
}
//////////////////////////////////////////////////////////////////////////////////////////
void gtk_init_ui(){
    gtk_window_set_title (widgets->window, "Editeur XML");
    gtk_window_set_default_size (widgets->window, 600, 500);
    gtk_widget_show_all (GTK_WIDGET(widgets->window));
    gtk_widget_hide(widgets->file_name);
    gtk_widget_hide(widgets->validate);
    gtk_widget_hide(widgets->filename_label);
}

void action_button_hide_and_show(){
    gtk_widget_show(widgets->file_name);
    gtk_widget_show(widgets->validate);
    gtk_widget_show(widgets->filename_label);
    gtk_label_set_text(widgets->filename_label,"Nom du fichier :");
}

void read_button_hide_and_show(){
    gtk_widget_hide(widgets->file_name);
    gtk_widget_hide(widgets->validate);
    gtk_widget_hide(widgets->filename_label);
    gtk_label_set_text(widgets->filename_label,"");
}

void startGTK(int *argc, char ***argv, char *gladeFile) {
    gtk_init(argc, argv);
    builder = gtk_builder_new_from_file(gladeFile);

    connectWidgets();

    gtk_init_ui();

    g_signal_connect(widgets->window, "destroy", G_CALLBACK(onDestroy), NULL);

    gtk_builder_connect_signals(builder, NULL);


    gtk_main();

    g_slice_free(App_widgets, widgets);
}

void connectWidgets() {
    widgets = g_slice_new(App_widgets);

    widgets->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
    widgets->text_view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_view"));
    widgets->is_conform = GTK_LABEL(gtk_builder_get_object(builder, "is_conform"));
    widgets->filename_label = GTK_LABEL(gtk_builder_get_object(builder, "filename_label"));
    widgets->file_name = GTK_ENTRY(gtk_builder_get_object(builder, "file_name"));
    widgets->read = GTK_BUTTON(gtk_builder_get_object(builder, "read"));
    widgets->create = GTK_BUTTON(gtk_builder_get_object(builder, "create"));
    widgets->edit = GTK_BUTTON(gtk_builder_get_object(builder, "edit"));
    widgets->validate = GTK_BUTTON(gtk_builder_get_object(builder, "validate"));
}

void onDestroy() {
    gtk_main_quit();
}
