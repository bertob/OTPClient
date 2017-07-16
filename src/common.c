#include <gtk/gtk.h>

static void icon_press_cb (GtkEntry *entry, gint position, GdkEventButton *event, gpointer data);


void
set_icon_to_entry (GtkWidget *entry, const gchar *icon_name, const gchar *tooltip_text)
{
    GIcon *gicon = g_themed_icon_new_with_default_fallbacks (icon_name);
    gtk_entry_set_icon_from_gicon (GTK_ENTRY (entry), GTK_ENTRY_ICON_SECONDARY, gicon);
    gtk_entry_set_icon_activatable (GTK_ENTRY (entry), GTK_ENTRY_ICON_SECONDARY, TRUE);
    gtk_entry_set_icon_tooltip_text (GTK_ENTRY (entry), GTK_ENTRY_ICON_SECONDARY, tooltip_text);
    gtk_entry_set_visibility (GTK_ENTRY (entry), FALSE);
    g_signal_connect (entry, "icon-press", G_CALLBACK(icon_press_cb), NULL);
}


static void
icon_press_cb (GtkEntry *entry,
               gint position __attribute__((__unused__)),
               GdkEventButton *event __attribute__((__unused__)),
               gpointer data __attribute__((__unused__)))
{
    gtk_entry_set_visibility (GTK_ENTRY (entry), !gtk_entry_get_visibility (entry));
}


GtkWidget *
create_box_with_buttons (const gchar *add_btn_name, const gchar *del_btn_name)
{
    GtkWidget *box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_style_context_add_class (gtk_widget_get_style_context (box), "linked");
    GtkWidget *add_button = gtk_button_new ();
    gtk_widget_set_name (add_button, add_btn_name);
    gtk_container_add (GTK_CONTAINER (add_button), gtk_image_new_from_icon_name ("list-add-symbolic", GTK_ICON_SIZE_BUTTON));
    gtk_container_add (GTK_CONTAINER (box), add_button);
    GtkWidget *del_button = gtk_button_new ();
    gtk_widget_set_name (del_button, del_btn_name);
    gtk_container_add (GTK_CONTAINER (del_button), gtk_image_new_from_icon_name ("list-remove-symbolic", GTK_ICON_SIZE_BUTTON));
    gtk_container_add (GTK_CONTAINER (box), del_button);

    return box;
}


GtkWidget *
create_header_bar (const gchar *headerbar_title)
{
    GtkWidget *header_bar = gtk_header_bar_new ();
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header_bar), TRUE);
    gtk_header_bar_set_title (GTK_HEADER_BAR (header_bar), headerbar_title);
    gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header_bar), FALSE);

    return header_bar;
}


GtkWidget *
find_widget (GtkWidget *parent, const gchar *widget_name)
{
    GtkWidget *found_widget = NULL;
    GList *children = NULL;
    if (GTK_IS_BIN (parent)) {
        GtkWidget *header_bar = gtk_window_get_titlebar (GTK_WINDOW (parent));
        GList *child = gtk_container_get_children (GTK_CONTAINER (header_bar)); //there's only one child, a GTK_CONTAINER (box)
        children = gtk_container_get_children (GTK_CONTAINER (child->data));
        g_list_free (child);
    } else {
        children = gtk_container_get_children (GTK_CONTAINER (parent)); //children are the two buttons
    }

    do {
        // g_strcmp0 returns 0 if the strings are equal. 0 is false, thus the '!'
        if (!g_strcmp0 (gtk_widget_get_name (children->data), widget_name)) {
            found_widget = children->data;
            break;
        }
    } while ((children = g_list_next (children)) != NULL);

    g_list_free (children);

    return found_widget;
}
