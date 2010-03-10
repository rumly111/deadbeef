/*
    DeaDBeeF - ultimate music player for GNU/Linux systems with X11
    Copyright (C) 2009-2010 Alexey Yakovenko <waker@users.sourceforge.net>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include <gtk/gtk.h>
#include <string.h>
#include <assert.h>
#include "gtkui.h"
#include "support.h"
#include "interface.h"
#include "callbacks.h"

static GtkWidget *prefwin;

static char alsa_device_names[100][64];
static int num_alsa_devices;

static void
gtk_enum_sound_callback (const char *name, const char *desc, void *userdata) {
    if (num_alsa_devices >= 100) {
        fprintf (stderr, "wtf!! more than 100 alsa devices??\n");
        return;
    }
    GtkComboBox *combobox = GTK_COMBO_BOX (userdata);
    gtk_combo_box_append_text (combobox, desc);

    if (!strcmp (deadbeef->conf_get_str ("alsa_soundcard", "default"), name)) {
        gtk_combo_box_set_active (combobox, num_alsa_devices);
    }

    strncpy (alsa_device_names[num_alsa_devices], name, 63);
    alsa_device_names[num_alsa_devices][63] = 0;
    num_alsa_devices++;
}

void
on_plugin_active_toggled (GtkCellRendererToggle *cell_renderer, gchar *path, GtkTreeModel *model) {
    GtkTreePath *p = gtk_tree_path_new_from_string (path);
    if (p) {
        int *indices = gtk_tree_path_get_indices (p);
        //gtk_tree_path_free (p); // wtf?? gtk crashes on this
        if (indices) {
            DB_plugin_t **plugins = deadbeef->plug_get_list ();
            DB_plugin_t *plug = plugins[*indices];
            gboolean state;
            GtkTreeIter iter;
            gtk_tree_model_get_iter (model, &iter, p);
            gtk_tree_model_get (model, &iter, 0, &state, -1);
            if (!deadbeef->plug_activate (plug, !state)) {
                gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, !state, -1);
            }
        }
        g_free (indices);
    }
}

void
preferences_fill_soundcards (void) {
    if (!prefwin) {
        return;
    }
    const char *s = deadbeef->conf_get_str ("alsa_soundcard", "default");
    GtkComboBox *combobox = GTK_COMBO_BOX (lookup_widget (prefwin, "pref_soundcard"));
    GtkTreeModel *mdl = gtk_combo_box_get_model (combobox);
    gtk_list_store_clear (GTK_LIST_STORE (mdl));

    gtk_combo_box_append_text (combobox, "Default Audio Device");
    if (!strcmp (s, "default")) {
        gtk_combo_box_set_active (combobox, 0);
    }
    num_alsa_devices = 1;
    strcpy (alsa_device_names[0], "default");
    if (deadbeef->get_output ()->enum_soundcards) {
        deadbeef->get_output ()->enum_soundcards (gtk_enum_sound_callback, combobox);
        gtk_widget_set_sensitive (GTK_WIDGET (combobox), TRUE);
    }
    else {
        gtk_widget_set_sensitive (GTK_WIDGET (combobox), FALSE);
    }
}

void
on_preferences_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    if (prefwin) {
        return;
    }
    GtkWidget *w = prefwin = create_prefwin ();
    gtk_window_set_transient_for (GTK_WINDOW (w), GTK_WINDOW (mainwin));

    GtkComboBox *combobox = NULL;

    // output plugin selection
    const char *outplugname = deadbeef->conf_get_str ("output_plugin", "ALSA output plugin");
    combobox = GTK_COMBO_BOX (lookup_widget (w, "pref_output_plugin"));

    DB_output_t **out_plugs = deadbeef->plug_get_output_list ();
    for (int i = 0; out_plugs[i]; i++) {
        gtk_combo_box_append_text (combobox, out_plugs[i]->plugin.name);
        if (!strcmp (outplugname, out_plugs[i]->plugin.name)) {
            gtk_combo_box_set_active (combobox, i);
        }
    }

    // soundcard (output device) selection
    preferences_fill_soundcards ();

    g_signal_connect ((gpointer) combobox, "changed",
            G_CALLBACK (on_pref_output_plugin_changed),
            NULL);
    GtkWidget *pref_soundcard = lookup_widget (prefwin, "pref_soundcard");
    g_signal_connect ((gpointer) pref_soundcard, "changed",
            G_CALLBACK (on_pref_soundcard_changed),
            NULL);

    // alsa resampling
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (w, "pref_dynsamplerate")), deadbeef->conf_get_int ("playback.dynsamplerate", 0));

    // src_quality
    combobox = GTK_COMBO_BOX (lookup_widget (w, "pref_src_quality"));
    gtk_combo_box_set_active (combobox, deadbeef->conf_get_int ("src_quality", 2));

    // replaygain_mode
    combobox = GTK_COMBO_BOX (lookup_widget (w, "pref_replaygain_mode"));
    gtk_combo_box_set_active (combobox, deadbeef->conf_get_int ("replaygain_mode", 0));

    // replaygain_scale
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (w, "pref_replaygain_scale")), deadbeef->conf_get_int ("replaygain_scale", 1));

    // close_send_to_tray
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (w, "pref_close_send_to_tray")), deadbeef->conf_get_int ("close_send_to_tray", 0));

    // override colors
    int override = deadbeef->conf_get_int ("gtkui.override_theme_colors", 0);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (prefwin, "override_theme_colors")), override);
    gtk_widget_set_sensitive (lookup_widget (prefwin, "colors_table"), override);
    char color_selection[100];
    char color_dark[100];
    char color_mid[100];
    char color_light[100];
    char color_back[100];

    extern GtkWidget *mainwin;
    GtkStyle *style = mainwin->style;

    const char *clr;
    GtkWidget *clr_widget;
    GdkColor gdk_clr;
    memset (&gdk_clr, 0, sizeof (gdk_clr));

    snprintf (color_selection, sizeof (color_selection), "%d %d %d", style->base[GTK_STATE_SELECTED].red, style->base[GTK_STATE_SELECTED].green, style->base[GTK_STATE_SELECTED].blue);
    clr = deadbeef->conf_get_str ("gtkui.color.selection", color_selection);
    sscanf (clr, "%d %d %d", &gdk_clr.red, &gdk_clr.green, &gdk_clr.blue);
    clr_widget = lookup_widget (prefwin, "color_selection");
    gtk_color_button_set_color (GTK_COLOR_BUTTON (clr_widget), &gdk_clr);

    snprintf (color_dark, sizeof (color_dark), "%d %d %d", style->dark[GTK_STATE_NORMAL].red, style->dark[GTK_STATE_NORMAL].green, style->dark[GTK_STATE_NORMAL].blue);
    clr = deadbeef->conf_get_str ("gtkui.color.dark", color_dark);
    sscanf (clr, "%d %d %d", &gdk_clr.red, &gdk_clr.green, &gdk_clr.blue);
    clr_widget = lookup_widget (prefwin, "color_dark");
    gtk_color_button_set_color (GTK_COLOR_BUTTON (clr_widget), &gdk_clr);

    snprintf (color_mid, sizeof (color_mid), "%d %d %d", style->mid[GTK_STATE_NORMAL].red, style->mid[GTK_STATE_NORMAL].green, style->mid[GTK_STATE_NORMAL].blue);
    clr = deadbeef->conf_get_str ("gtkui.color.mid", color_mid);
    sscanf (clr, "%d %d %d", &gdk_clr.red, &gdk_clr.green, &gdk_clr.blue);
    clr_widget = lookup_widget (prefwin, "color_mid");
    gtk_color_button_set_color (GTK_COLOR_BUTTON (clr_widget), &gdk_clr);

    snprintf (color_light, sizeof (color_light), "%d %d %d", style->light[GTK_STATE_NORMAL].red, style->light[GTK_STATE_NORMAL].green, style->light[GTK_STATE_NORMAL].blue);
    clr = deadbeef->conf_get_str ("gtkui.color.light", color_light);
    sscanf (clr, "%d %d %d", &gdk_clr.red, &gdk_clr.green, &gdk_clr.blue);
    clr_widget = lookup_widget (prefwin, "color_light");
    gtk_color_button_set_color (GTK_COLOR_BUTTON (clr_widget), &gdk_clr);

    snprintf (color_back, sizeof (color_back), "%d %d %d", style->fg[GTK_STATE_NORMAL].red, style->fg[GTK_STATE_NORMAL].green, style->fg[GTK_STATE_NORMAL].blue);
    clr = deadbeef->conf_get_str ("gtkui.color.back", color_back);
    sscanf (clr, "%d %d %d", &gdk_clr.red, &gdk_clr.green, &gdk_clr.blue);
    clr_widget = lookup_widget (prefwin, "color_back");
    gtk_color_button_set_color (GTK_COLOR_BUTTON (clr_widget), &gdk_clr);

    // network
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (w, "pref_network_enableproxy")), deadbeef->conf_get_int ("network.proxy", 0));
    gtk_entry_set_text (GTK_ENTRY (lookup_widget (w, "pref_network_proxyaddress")), deadbeef->conf_get_str ("network.proxy.address", ""));
    gtk_entry_set_text (GTK_ENTRY (lookup_widget (w, "pref_network_proxyport")), deadbeef->conf_get_str ("network.proxy.port", "8080"));
    combobox = GTK_COMBO_BOX (lookup_widget (w, "pref_network_proxytype"));
    const char *type = deadbeef->conf_get_str ("network.proxy.type", "HTTP");
    if (!strcasecmp (type, "HTTP")) {
        gtk_combo_box_set_active (combobox, 0);
    }
    else if (!strcasecmp (type, "HTTP_1_0")) {
        gtk_combo_box_set_active (combobox, 1);
    }
    else if (!strcasecmp (type, "SOCKS4")) {
        gtk_combo_box_set_active (combobox, 2);
    }
    else if (!strcasecmp (type, "SOCKS5")) {
        gtk_combo_box_set_active (combobox, 3);
    }
    else if (!strcasecmp (type, "SOCKS4A")) {
        gtk_combo_box_set_active (combobox, 4);
    }
    else if (!strcasecmp (type, "SOCKS5_HOSTNAME")) {
        gtk_combo_box_set_active (combobox, 5);
    }

    // list of plugins
    GtkTreeView *tree = GTK_TREE_VIEW (lookup_widget (w, "pref_pluginlist"));
    GtkCellRenderer *rend_text = gtk_cell_renderer_text_new ();
#if 0
    GtkCellRenderer *rend_toggle = gtk_cell_renderer_toggle_new ();
    GtkListStore *store = gtk_list_store_new (3, G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_BOOLEAN);
    g_signal_connect ((gpointer)rend_toggle, "toggled",
            G_CALLBACK (on_plugin_active_toggled),
            store);
    GtkTreeViewColumn *col1 = gtk_tree_view_column_new_with_attributes ("Active", rend_toggle, "active", 0, "activatable", 2, NULL);
    GtkTreeViewColumn *col2 = gtk_tree_view_column_new_with_attributes ("Title", rend_text, "text", 1, NULL);
    gtk_tree_view_append_column (tree, col1);
    gtk_tree_view_append_column (tree, col2);
    DB_plugin_t **plugins = deadbeef->plug_get_list ();
    int i;
    for (i = 0; plugins[i]; i++) {
        GtkTreeIter it;
        gtk_list_store_append (store, &it);
        gtk_list_store_set (store, &it, 0, plugins[i]->inactive ? FALSE : TRUE, 1, plugins[i]->name, 2, plugins[i]->nostop ? FALSE : TRUE, -1);
    }
#else
    GtkListStore *store = gtk_list_store_new (1, G_TYPE_STRING);
    GtkTreeViewColumn *col2 = gtk_tree_view_column_new_with_attributes ("Title", rend_text, "text", 0, NULL);
    gtk_tree_view_append_column (tree, col2);
    DB_plugin_t **plugins = deadbeef->plug_get_list ();
    int i;
    for (i = 0; plugins[i]; i++) {
        GtkTreeIter it;
        gtk_list_store_append (store, &it);
        gtk_list_store_set (store, &it, 0, plugins[i]->name, -1);
    }
#endif
    gtk_tree_view_set_model (tree, GTK_TREE_MODEL (store));

    gtk_widget_set_sensitive (lookup_widget (prefwin, "configure_plugin"), FALSE);
//    gtk_widget_show (w);
    gtk_dialog_run (GTK_DIALOG (prefwin));
    gtk_widget_destroy (prefwin);
    prefwin = NULL;
}


void
on_pref_soundcard_changed              (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
    int active = gtk_combo_box_get_active (combobox);
    if (active >= 0 && active < num_alsa_devices) {
        const char *soundcard = deadbeef->conf_get_str ("alsa_soundcard", "default");
        if (strcmp (soundcard, alsa_device_names[active])) {
            deadbeef->conf_set_str ("alsa_soundcard", alsa_device_names[active]);
            deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
        }
    }
}

void
on_pref_output_plugin_changed          (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
    const char *outplugname = deadbeef->conf_get_str ("output_plugin", "ALSA output plugin");
    int active = gtk_combo_box_get_active (combobox);

    DB_output_t **out_plugs = deadbeef->plug_get_output_list ();
    DB_output_t *prev = NULL;
    DB_output_t *new = NULL;

    for (int i = 0; out_plugs[i]; i++) {
        if (!strcmp (out_plugs[i]->plugin.name, outplugname)) {
            prev = out_plugs[i];
        }
        if (i == active) {
            new = out_plugs[i];
        }
    }

    if (!new) {
        fprintf (stderr, "failed to find output plugin selected in preferences window\n");
    }
    else {
        if (prev != new) {
            deadbeef->conf_set_str ("output_plugin", new->plugin.name);
            deadbeef->sendmessage (M_REINIT_SOUND, 0, 0, 0);
        }
    }
}

void
on_pref_dynsamplerate_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    int active = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));
    deadbeef->conf_set_int ("playback.dynsamplerate", active);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}


void
on_pref_src_quality_changed            (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
    int active = gtk_combo_box_get_active (combobox);
    deadbeef->conf_set_int ("src_quality", active == -1 ? 2 : active);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}


void
on_pref_replaygain_mode_changed        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
    int active = gtk_combo_box_get_active (combobox);
    deadbeef->conf_set_int ("replaygain_mode", active == -1 ? 0 : active);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}

void
on_pref_replaygain_scale_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    int active = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));
    deadbeef->conf_set_int ("replaygain_scale", active);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}


void
on_pref_close_send_to_tray_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    int active = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));
    deadbeef->conf_set_int ("close_send_to_tray", active);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}

void
on_pref_pluginlist_cursor_changed      (GtkTreeView     *treeview,
                                        gpointer         user_data)
{
    GtkTreePath *path;
    GtkTreeViewColumn *col;
    gtk_tree_view_get_cursor (treeview, &path, &col);
    if (!path || !col) {
        // reset
        return;
    }
    int *indices = gtk_tree_path_get_indices (path);
    DB_plugin_t **plugins = deadbeef->plug_get_list ();
    DB_plugin_t *p = plugins[*indices];
    g_free (indices);
    assert (p);
    GtkWidget *w = prefwin;//GTK_WIDGET (gtk_widget_get_parent_window (GTK_WIDGET (treeview)));
    assert (w);
    GtkEntry *e = GTK_ENTRY (lookup_widget (w, "pref_plugin_descr"));
    gtk_entry_set_text (e, p->descr ? p->descr : "");
    e = GTK_ENTRY (lookup_widget (w, "pref_plugin_author"));
    gtk_entry_set_text (e, p->author ? p->author : "");
    e = GTK_ENTRY (lookup_widget (w, "pref_plugin_email"));
    gtk_entry_set_text (e, p->email ? p->email : "");
    e = GTK_ENTRY (lookup_widget (w, "pref_plugin_website"));
    gtk_entry_set_text (e, p->website ? p->website : "");

    gtk_widget_set_sensitive (lookup_widget (prefwin, "configure_plugin"), p->configdialog ? TRUE : FALSE);
}

gboolean
on_prefwin_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    prefwin = NULL;
    return FALSE;
}

void
on_pref_close_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide (prefwin);
    gtk_widget_destroy (prefwin);
}

void
on_configure_plugin_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *w = prefwin;
    GtkTreeView *treeview = GTK_TREE_VIEW (lookup_widget (w, "pref_pluginlist"));
    GtkTreePath *path;
    GtkTreeViewColumn *col;
    gtk_tree_view_get_cursor (treeview, &path, &col);
    if (!path || !col) {
        // reset
        return;
    }
    int *indices = gtk_tree_path_get_indices (path);
    DB_plugin_t **plugins = deadbeef->plug_get_list ();
    DB_plugin_t *p = plugins[*indices];
    if (p->configdialog) {
        plugin_configure (prefwin, p);
    }
}

void
on_color_light_color_set               (GtkColorButton  *colorbutton,
                                        gpointer         user_data)
{
    GdkColor clr;
    gtk_color_button_get_color (colorbutton, &clr);
    char str[100];
    snprintf (str, sizeof (str), "%d %d %d", clr.red, clr.green, clr.blue);
    deadbeef->conf_set_str ("gtkui.color.light", str);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}


void
on_color_mid_color_set                 (GtkColorButton  *colorbutton,
                                        gpointer         user_data)
{
    GdkColor clr;
    gtk_color_button_get_color (colorbutton, &clr);
    char str[100];
    snprintf (str, sizeof (str), "%d %d %d", clr.red, clr.green, clr.blue);
    deadbeef->conf_set_str ("gtkui.color.mid", str);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}


void
on_color_dark_color_set                (GtkColorButton  *colorbutton,
                                        gpointer         user_data)
{
    GdkColor clr;
    gtk_color_button_get_color (colorbutton, &clr);
    char str[100];
    snprintf (str, sizeof (str), "%d %d %d", clr.red, clr.green, clr.blue);
    deadbeef->conf_set_str ("gtkui.color.dark", str);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}


void
on_color_selection_color_set           (GtkColorButton  *colorbutton,
                                        gpointer         user_data)
{
    GdkColor clr;
    gtk_color_button_get_color (colorbutton, &clr);
    char str[100];
    snprintf (str, sizeof (str), "%d %d %d", clr.red, clr.green, clr.blue);
    deadbeef->conf_set_str ("gtkui.color.selection", str);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);

}


void
on_color_back_color_set                (GtkColorButton  *colorbutton,
                                        gpointer         user_data)
{
    GdkColor clr;
    gtk_color_button_get_color (colorbutton, &clr);
    char str[100];
    snprintf (str, sizeof (str), "%d %d %d", clr.red, clr.green, clr.blue);
    deadbeef->conf_set_str ("gtkui.color.back", str);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}

void
on_override_gtk_colors_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    int active = gtk_toggle_button_get_active (togglebutton);
    deadbeef->conf_set_int ("gtkui.override_theme_colors", active);
    gtk_widget_set_sensitive (lookup_widget (prefwin, "colors_table"), active);
    deadbeef->sendmessage (M_CONFIGCHANGED, 0, 0, 0);
}
