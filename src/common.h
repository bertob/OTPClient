#pragma once

void set_icon_to_entry (GtkWidget *entry, const gchar *icon_name, const gchar *tooltip_text);

GtkWidget *create_box_with_buttons (const gchar *add_btn_name, const gchar *del_btn_name);

GtkWidget *create_header_bar (const gchar *headerbar_title);

GtkWidget *find_widget (GtkWidget *parent, const gchar *widget_name);