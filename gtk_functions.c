#include "gtk_functions.h"

//////////////////////////////////////////////////////////////////////////////////////////

void on_button_new_clicked(){
    hide_filename_label();
    set_filename_label(widgets->filename_label,"");
    GtkTextBuffer *buffer2 = gtk_text_view_get_buffer (widgets->text_view);
    gtk_text_buffer_set_text (buffer2, "", -1);
    gtk_text_view_set_buffer (widgets->text_view, buffer2);
    printf("%s",gtk_text_view_get_input_purpose (widgets->text_view));
}

void on_button_read_clicked() {
    show_filename_label();

    gchar *text = NULL;

    text = read_file(widgets->filename_label, 1);

    set_text_view_text(widgets->text_view,text);

    g_free(text);
}

void on_button_dtd_clicked() {
    gchar *text = NULL;

    text = read_file(widgets->filename_dtd, 2);

    set_text_view_text(widgets->dtd_text_view,text);

    g_free(text);
}

void on_button_verify_clicked() {
    int conformity;

    conformity = verify_xml_off_dtd();
    if(conformity == 0){
        gtk_label_set_text (widgets->is_conform, "XML invalide.");
    }
    else if(conformity == 1){
        gtk_label_set_text (widgets->is_conform, "DTD invalide.");
    }
    else if(conformity == 2){
        gtk_label_set_text (widgets->is_conform, "XML non conforme DTD.");
    }
    else if(conformity == 3){
        gtk_label_set_text (widgets->is_conform, "XML conforme DTD.");
    }
}

void on_button_save_clicked() {

    gchar *text;

    text = get_text_view_text(widgets->text_view);

    write_file(text);

    g_free(text);
}

//////////////////////////////////////////////////////////////////////////////////////////

int verify_xml_off_dtd(){
    /*
     * 0 xml invalide
     * 1 dtd invalide
     * 2 = non conforme
     * 3 = all ok
     */

    int valid = 1;
    LinkedListTag* head = intialisation("");
    valid = validateFirstPart(head, widgets->filename_xml_save);
    if(strcmp(head->name, "") != 0)
        if(valid == 0) {
            return 0;
    }

    LinkedListDtd* head_dtd1 = getDtdTag(widgets->filename_dtd_save);
    int first_verification_1 = matchXmlDtd(head, head_dtd1);

    if(first_verification_1 != 1) {
        return 1;
    }

    if(verifyAllTagsDTD(head) != 1 && verifyAllTagsPresentDtdInXML(head_dtd1) != 1) {
        return 2;
    }

    return 3;
}

const gchar *read_file(App_widgets *file_name, int type){
    open_file();

    gchar *buffer = NULL;
    GError *error = NULL;
    gint res;

    res = gtk_dialog_run (widgets->fileChooserDialog);
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;

        filename = gtk_file_chooser_get_filename (widgets->chooser);

        /*char *str = filename;

        const char * separators = "\\";

        char * strToken = strtok ( str, separators );
        while ( strToken != NULL ) {
            printf ( "%s\n", strToken );
            strToken = strtok ( NULL, separators );
        }
        char *temp = malloc(100 * sizeof(char));
        int i;
        char *filename = widgets->filename_xml_save;

        for(i=strlen(filename); i>0; i--){
            if(filename[i] == '\\'){
                break;
            }
        }

        int nameLen = strlen(filename) - i;

        for(int j=0; j<nameLen && i<strlen(filename); j++, i++){
            strcat(temp[j],filename[i]);
        }


        printf("%s",strlen(temp));
        free(temp);*/

        set_filename_label(file_name,filename);
        if(type == 1){
            save_filename(widgets->filename_xml_save,filename);
        }
        else if(type == 2){
            save_filename(widgets->filename_dtd_save,filename);
        }

        if (g_file_get_contents (filename, &buffer, NULL, &error) == FALSE)
        {
            g_warning ("%s", error->message);
            g_clear_error (&error);
            return "null";
        }

        g_free(filename);
    }

    gtk_widget_destroy(widgets->fileChooserDialog);

    return buffer;
}

void write_file(gchar **contents) {
    save_file();

    GError *error = NULL;
    gint res;

    res = gtk_dialog_run (widgets->fileChooserDialog);
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;

        filename = gtk_file_chooser_get_filename (widgets->chooser);

        set_filename_label(widgets->filename_label,filename);

        if(g_file_set_contents (filename, contents, strlen(contents), &error) == FALSE)
        {
            g_warning ("%s", error->message);
            g_clear_error (&error);
            return;
        }

        g_free(filename);
    }

    gtk_widget_destroy(widgets->fileChooserDialog);
}

void open_file(){
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    widgets->fileChooserDialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier",
                                                              widgets->window,
                                                              action,
                                                              ("_Fermer"),
                                                              GTK_RESPONSE_CANCEL,
                                                              ("_Ouvrir"),
                                                              GTK_RESPONSE_ACCEPT,
                                                              NULL);

    widgets->chooser = GTK_FILE_CHOOSER (widgets->fileChooserDialog);
}

void save_file(){
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    widgets->fileChooserDialog = gtk_file_chooser_dialog_new ("Enregister sous un fichier",
                                                              widgets->window,
                                                              action,
                                                              ("_Fermer"),
                                                              GTK_RESPONSE_CANCEL,
                                                              ("_Enregistrer"),
                                                              GTK_RESPONSE_ACCEPT,
                                                              NULL);

    widgets->chooser = GTK_FILE_CHOOSER (widgets->fileChooserDialog);
    gtk_file_chooser_set_do_overwrite_confirmation (widgets->chooser, TRUE);

    gchar *filename = get_filename_label(widgets->filename_label);

    if(strcmp( filename, "" ) != 0){
        gtk_file_chooser_set_filename(widgets->chooser,filename);
    }
    else{
        gtk_file_chooser_set_current_name(widgets->chooser,"Nom du fichier");
    }
}

void hide_filename_label(){
    gtk_widget_hide(widgets->filename_label);
}

void show_filename_label(){
    gtk_widget_show(widgets->filename_label);
}

void save_filename(App_widgets *file_name, const char **filename){
    gtk_label_set_text(file_name,filename);
}

void set_filename_label(App_widgets *file_name, const char **filename){
    gtk_label_set_text(file_name,filename);
}

const gchar *get_filename_label(App_widgets *file_name){
    return gtk_label_get_text (file_name);
}

void set_text_view_text(App_widgets *text_view, gchar **text){
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (text_view);
    gtk_text_buffer_set_text (buffer, text, strlen(text));
    gtk_text_view_set_buffer (text_view, buffer);
}

const gchar *get_text_view_text(App_widgets *text_view){
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (text_view);
    gtk_text_buffer_get_bounds (buffer, &start, &end);
    return gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
}

void start_GTK(int *argc, char ***argv, char *gladeFile) {
    gtk_init(argc, argv);
    builder = gtk_builder_new_from_file(gladeFile);

    connect_widgets();

    gtk_init_ui();

    g_signal_connect(widgets->window, "destroy", G_CALLBACK(on_destroy), NULL);

    gtk_builder_connect_signals(builder, NULL);

    gtk_main();

    g_slice_free(App_widgets, widgets);
}

void gtk_init_ui(){
    gtk_window_set_title (widgets->window, "Editeur XML");
    gtk_window_set_default_size (widgets->window, 950, 500);
    gtk_widget_show_all (GTK_WIDGET(widgets->window));
    gtk_widget_hide(widgets->filename_label);
}

void connect_widgets() {
    widgets = g_slice_new(App_widgets);

    widgets->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
    widgets->text_view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_view"));
    widgets->dtd_text_view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "dtd_text_view"));
    widgets->is_conform = GTK_LABEL(gtk_builder_get_object(builder, "is_conform"));
    widgets->filename_label = GTK_LABEL(gtk_builder_get_object(builder, "filename_label"));
    widgets->filename_dtd = GTK_LABEL(gtk_builder_get_object(builder, "filename_dtd"));
    widgets->filename_xml_save = GTK_LABEL(gtk_builder_get_object(builder, "filename_xml_save"));
    widgets->filename_dtd_save = GTK_LABEL(gtk_builder_get_object(builder, "filename_dtd_save"));
    widgets->read = GTK_BUTTON(gtk_builder_get_object(builder, "read"));
    widgets->create = GTK_BUTTON(gtk_builder_get_object(builder, "create"));
    widgets->edit = GTK_BUTTON(gtk_builder_get_object(builder, "edit"));
    widgets->new = GTK_BUTTON(gtk_builder_get_object(builder, "validate"));
    widgets->dtd = GTK_BUTTON(gtk_builder_get_object(builder, "dtd"));
    widgets->verify = GTK_BUTTON(gtk_builder_get_object(builder, "verify"));
    widgets->fileChooserDialog = GTK_DIALOG(gtk_builder_get_object(builder, "fileChooserDialog"));
    widgets->chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "chooser"));
}

void on_destroy() {
    gtk_main_quit();
}
