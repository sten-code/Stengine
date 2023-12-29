#include "stpch.h"
#ifdef ST_PLATFORM_LINUX
#include "Stengine/Utils/PlatformUtils.h"

#include <gtk/gtk.h>

namespace Sten
{
    std::string FileDialogs::OpenFile(const char* filter)
    {
        GtkWidget* dialog;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
        gint res;

        dialog = gtk_file_chooser_dialog_new("Open File",
            NULL,
            action,
            "_Cancel",
            GTK_RESPONSE_CANCEL,
            "_Open",
            GTK_RESPONSE_ACCEPT,
            NULL);

        GtkFileFilter* file_filter = gtk_file_filter_new();
        gtk_file_filter_set_name(file_filter, filter);
        gtk_file_filter_add_pattern(file_filter, filter);
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), file_filter);

        res = gtk_dialog_run(GTK_DIALOG(dialog));
        if (res == GTK_RESPONSE_ACCEPT)
        {
            char* filename;
            filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            std::string result = filename;
            g_free(filename);
            gtk_widget_destroy(dialog);
            return result;
        }
        else
        {
            gtk_widget_destroy(dialog);
            return std::string();
        }
    }

    std::string FileDialogs::SaveFile(const char* filter)
    {
        GtkWidget* dialog;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
        gint res;

        dialog = gtk_file_chooser_dialog_new("Save File",
            NULL,
            action,
            "_Cancel",
            GTK_RESPONSE_CANCEL,
            "_Save",
            GTK_RESPONSE_ACCEPT,
            NULL);

        GtkFileFilter* file_filter = gtk_file_filter_new();
        gtk_file_filter_set_name(file_filter, filter);
        gtk_file_filter_add_pattern(file_filter, filter);
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), file_filter);

        res = gtk_dialog_run(GTK_DIALOG(dialog));
        if (res == GTK_RESPONSE_ACCEPT)
        {
            char* filename;
            filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            std::string result = filename;
            g_free(filename);
            gtk_widget_destroy(dialog);
            return result;
        }
        else
        {
            gtk_widget_destroy(dialog);
            return std::string();
        }
    }
}

#endif