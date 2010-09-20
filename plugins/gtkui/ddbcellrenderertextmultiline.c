/* ddbcellrenderertextmultiline.c generated by valac, the Vala compiler
 * generated from ddbcellrenderertextmultiline.vala, do not modify */

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

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdk.h>


#define DDB_TYPE_CELL_EDITABLE_TEXT_VIEW (ddb_cell_editable_text_view_get_type ())
#define DDB_CELL_EDITABLE_TEXT_VIEW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), DDB_TYPE_CELL_EDITABLE_TEXT_VIEW, DdbCellEditableTextView))
#define DDB_CELL_EDITABLE_TEXT_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), DDB_TYPE_CELL_EDITABLE_TEXT_VIEW, DdbCellEditableTextViewClass))
#define DDB_IS_CELL_EDITABLE_TEXT_VIEW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DDB_TYPE_CELL_EDITABLE_TEXT_VIEW))
#define DDB_IS_CELL_EDITABLE_TEXT_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DDB_TYPE_CELL_EDITABLE_TEXT_VIEW))
#define DDB_CELL_EDITABLE_TEXT_VIEW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), DDB_TYPE_CELL_EDITABLE_TEXT_VIEW, DdbCellEditableTextViewClass))

typedef struct _DdbCellEditableTextView DdbCellEditableTextView;
typedef struct _DdbCellEditableTextViewClass DdbCellEditableTextViewClass;
typedef struct _DdbCellEditableTextViewPrivate DdbCellEditableTextViewPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))

#define DDB_TYPE_CELL_RENDERER_TEXT_MULTILINE (ddb_cell_renderer_text_multiline_get_type ())
#define DDB_CELL_RENDERER_TEXT_MULTILINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), DDB_TYPE_CELL_RENDERER_TEXT_MULTILINE, DdbCellRendererTextMultiline))
#define DDB_CELL_RENDERER_TEXT_MULTILINE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), DDB_TYPE_CELL_RENDERER_TEXT_MULTILINE, DdbCellRendererTextMultilineClass))
#define DDB_IS_CELL_RENDERER_TEXT_MULTILINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DDB_TYPE_CELL_RENDERER_TEXT_MULTILINE))
#define DDB_IS_CELL_RENDERER_TEXT_MULTILINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DDB_TYPE_CELL_RENDERER_TEXT_MULTILINE))
#define DDB_CELL_RENDERER_TEXT_MULTILINE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), DDB_TYPE_CELL_RENDERER_TEXT_MULTILINE, DdbCellRendererTextMultilineClass))

typedef struct _DdbCellRendererTextMultiline DdbCellRendererTextMultiline;
typedef struct _DdbCellRendererTextMultilineClass DdbCellRendererTextMultilineClass;
typedef struct _DdbCellRendererTextMultilinePrivate DdbCellRendererTextMultilinePrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _DdbCellEditableTextView {
	GtkTextView parent_instance;
	DdbCellEditableTextViewPrivate * priv;
	gboolean editing_canceled;
	char* tree_path;
};

struct _DdbCellEditableTextViewClass {
	GtkTextViewClass parent_class;
};

struct _DdbCellRendererTextMultiline {
	GtkCellRendererText parent_instance;
	DdbCellRendererTextMultilinePrivate * priv;
};

struct _DdbCellRendererTextMultilineClass {
	GtkCellRendererTextClass parent_class;
};

struct _DdbCellRendererTextMultilinePrivate {
	DdbCellEditableTextView* entry;
	gulong focus_out_id;
};


static gpointer ddb_cell_editable_text_view_parent_class = NULL;
static GtkCellEditableIface* ddb_cell_editable_text_view_gtk_cell_editable_parent_iface = NULL;
static gpointer ddb_cell_renderer_text_multiline_parent_class = NULL;

GType ddb_cell_editable_text_view_get_type (void);
enum  {
	DDB_CELL_EDITABLE_TEXT_VIEW_DUMMY_PROPERTY
};
static gboolean ddb_cell_editable_text_view_real_key_press_event (GtkWidget* base, GdkEventKey* event);
static void ddb_cell_editable_text_view_real_start_editing (GtkCellEditable* base, GdkEvent* event);
DdbCellEditableTextView* ddb_cell_editable_text_view_new (void);
DdbCellEditableTextView* ddb_cell_editable_text_view_construct (GType object_type);
static void ddb_cell_editable_text_view_finalize (GObject* obj);
GType ddb_cell_renderer_text_multiline_get_type (void);
#define DDB_CELL_RENDERER_TEXT_MULTILINE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), DDB_TYPE_CELL_RENDERER_TEXT_MULTILINE, DdbCellRendererTextMultilinePrivate))
enum  {
	DDB_CELL_RENDERER_TEXT_MULTILINE_DUMMY_PROPERTY
};
static void ddb_cell_renderer_text_multiline_gtk_cell_renderer_text_editing_done (DdbCellEditableTextView* entry, DdbCellRendererTextMultiline* _self_);
static gboolean ddb_cell_renderer_text_multiline_gtk_cell_renderer_focus_out_event (DdbCellEditableTextView* entry, GdkEvent* event, DdbCellRendererTextMultiline* _self_);
static GtkCellEditable* ddb_cell_renderer_text_multiline_real_start_editing (GtkCellRenderer* base, GdkEvent* event, GtkWidget* widget, const char* path, GdkRectangle* background_area, GdkRectangle* cell_area, GtkCellRendererState flags);
DdbCellRendererTextMultiline* ddb_cell_renderer_text_multiline_new (void);
DdbCellRendererTextMultiline* ddb_cell_renderer_text_multiline_construct (GType object_type);
static void ddb_cell_renderer_text_multiline_finalize (GObject* obj);



static gboolean ddb_cell_editable_text_view_real_key_press_event (GtkWidget* base, GdkEventKey* event) {
	DdbCellEditableTextView * self;
	gboolean result = FALSE;
	gboolean res;
	self = (DdbCellEditableTextView*) base;
	res = TRUE;
	if ((*event).keyval == GDK_Return) {
		if (((*event).state & (GDK_CONTROL_MASK | GDK_SHIFT_MASK)) != 0) {
			res = GTK_WIDGET_CLASS (ddb_cell_editable_text_view_parent_class)->key_press_event ((GtkWidget*) GTK_TEXT_VIEW (self), event);
		} else {
			gtk_cell_editable_editing_done ((GtkCellEditable*) self);
			gtk_cell_editable_remove_widget ((GtkCellEditable*) self);
			result = TRUE;
			return result;
		}
	} else {
		if ((*event).keyval == GDK_Escape) {
			self->editing_canceled = TRUE;
			gtk_cell_editable_editing_done ((GtkCellEditable*) self);
			gtk_cell_editable_remove_widget ((GtkCellEditable*) self);
			result = TRUE;
			return result;
		} else {
			res = GTK_WIDGET_CLASS (ddb_cell_editable_text_view_parent_class)->key_press_event ((GtkWidget*) GTK_TEXT_VIEW (self), event);
		}
	}
	result = res;
	return result;
}


static void ddb_cell_editable_text_view_real_start_editing (GtkCellEditable* base, GdkEvent* event) {
	DdbCellEditableTextView * self;
	self = (DdbCellEditableTextView*) base;
	g_return_if_fail (event != NULL);
}


DdbCellEditableTextView* ddb_cell_editable_text_view_construct (GType object_type) {
	DdbCellEditableTextView * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


DdbCellEditableTextView* ddb_cell_editable_text_view_new (void) {
	return ddb_cell_editable_text_view_construct (DDB_TYPE_CELL_EDITABLE_TEXT_VIEW);
}


static void ddb_cell_editable_text_view_class_init (DdbCellEditableTextViewClass * klass) {
	ddb_cell_editable_text_view_parent_class = g_type_class_peek_parent (klass);
	GTK_WIDGET_CLASS (klass)->key_press_event = ddb_cell_editable_text_view_real_key_press_event;
	G_OBJECT_CLASS (klass)->finalize = ddb_cell_editable_text_view_finalize;
}


static void ddb_cell_editable_text_view_gtk_cell_editable_interface_init (GtkCellEditableIface * iface) {
	ddb_cell_editable_text_view_gtk_cell_editable_parent_iface = g_type_interface_peek_parent (iface);
	iface->start_editing = ddb_cell_editable_text_view_real_start_editing;
}


static void ddb_cell_editable_text_view_instance_init (DdbCellEditableTextView * self) {
	self->editing_canceled = FALSE;
}


static void ddb_cell_editable_text_view_finalize (GObject* obj) {
	DdbCellEditableTextView * self;
	self = DDB_CELL_EDITABLE_TEXT_VIEW (obj);
	_g_free0 (self->tree_path);
	G_OBJECT_CLASS (ddb_cell_editable_text_view_parent_class)->finalize (obj);
}


GType ddb_cell_editable_text_view_get_type (void) {
	static volatile gsize ddb_cell_editable_text_view_type_id__volatile = 0;
	if (g_once_init_enter (&ddb_cell_editable_text_view_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (DdbCellEditableTextViewClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) ddb_cell_editable_text_view_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (DdbCellEditableTextView), 0, (GInstanceInitFunc) ddb_cell_editable_text_view_instance_init, NULL };
		static const GInterfaceInfo gtk_cell_editable_info = { (GInterfaceInitFunc) ddb_cell_editable_text_view_gtk_cell_editable_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		GType ddb_cell_editable_text_view_type_id;
		ddb_cell_editable_text_view_type_id = g_type_register_static (GTK_TYPE_TEXT_VIEW, "DdbCellEditableTextView", &g_define_type_info, 0);
		g_type_add_interface_static (ddb_cell_editable_text_view_type_id, GTK_TYPE_CELL_EDITABLE, &gtk_cell_editable_info);
		g_once_init_leave (&ddb_cell_editable_text_view_type_id__volatile, ddb_cell_editable_text_view_type_id);
	}
	return ddb_cell_editable_text_view_type_id__volatile;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void ddb_cell_renderer_text_multiline_gtk_cell_renderer_text_editing_done (DdbCellEditableTextView* entry, DdbCellRendererTextMultiline* _self_) {
	GtkTextBuffer* buf;
	GtkTextIter begin = {0};
	GtkTextIter end = {0};
	char* new_text;
	g_return_if_fail (entry != NULL);
	g_return_if_fail (_self_ != NULL);
	g_signal_handler_disconnect ((GObject*) entry, _self_->priv->focus_out_id);
	gtk_cell_renderer_stop_editing ((GtkCellRenderer*) _self_, entry->editing_canceled);
	buf = _g_object_ref0 (gtk_text_view_get_buffer ((GtkTextView*) entry));
	gtk_text_buffer_get_iter_at_offset (buf, &begin, 0);
	gtk_text_buffer_get_iter_at_offset (buf, &end, -1);
	new_text = g_strdup (gtk_text_buffer_get_text (buf, &begin, &end, TRUE));
	g_signal_emit_by_name ((GtkCellRendererText*) _self_, "edited", entry->tree_path, new_text);
	_g_object_unref0 (buf);
	_g_free0 (new_text);
}


static gboolean ddb_cell_renderer_text_multiline_gtk_cell_renderer_focus_out_event (DdbCellEditableTextView* entry, GdkEvent* event, DdbCellRendererTextMultiline* _self_) {
	gboolean result = FALSE;
	g_return_val_if_fail (entry != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	g_return_val_if_fail (_self_ != NULL, FALSE);
	entry->editing_canceled = TRUE;
	gtk_cell_editable_remove_widget ((GtkCellEditable*) entry);
	result = FALSE;
	return result;
}


static GtkCellEditable* ddb_cell_renderer_text_multiline_real_start_editing (GtkCellRenderer* base, GdkEvent* event, GtkWidget* widget, const char* path, GdkRectangle* background_area, GdkRectangle* cell_area, GtkCellRendererState flags) {
	DdbCellRendererTextMultiline * self;
	GtkCellEditable* result = NULL;
	gboolean _tmp0_;
	DdbCellEditableTextView* _tmp1_;
	char* _tmp2_;
	GtkTextBuffer* buf;
	char* _tmp4_;
	char* _tmp3_ = NULL;
	gboolean _tmp5_;
	self = (DdbCellRendererTextMultiline*) base;
	g_return_val_if_fail (event != NULL, NULL);
	g_return_val_if_fail (widget != NULL, NULL);
	g_return_val_if_fail (path != NULL, NULL);
	if (!(g_object_get ((GtkCellRendererText*) self, "editable", &_tmp0_, NULL), _tmp0_)) {
		result = GTK_CELL_EDITABLE (NULL);
		return result;
	}
	self->priv->entry = (_tmp1_ = g_object_ref_sink (ddb_cell_editable_text_view_new ()), _g_object_unref0 (self->priv->entry), _tmp1_);
	self->priv->entry->tree_path = (_tmp2_ = g_strdup (path), _g_free0 (self->priv->entry->tree_path), _tmp2_);
	buf = gtk_text_buffer_new (NULL);
	if ((_tmp5_ = (_tmp4_ = (g_object_get ((GtkCellRendererText*) self, "text", &_tmp3_, NULL), _tmp3_)) != NULL, _g_free0 (_tmp4_), _tmp5_)) {
		char* _tmp7_;
		char* _tmp6_ = NULL;
		gtk_text_buffer_set_text (buf, _tmp7_ = (g_object_get ((GtkCellRendererText*) self, "text", &_tmp6_, NULL), _tmp6_), -1);
		_g_free0 (_tmp7_);
	}
	gtk_text_view_set_buffer ((GtkTextView*) self->priv->entry, buf);
	g_signal_connect (self->priv->entry, "editing-done", (GCallback) ddb_cell_renderer_text_multiline_gtk_cell_renderer_text_editing_done, self);
	self->priv->focus_out_id = g_signal_connect_after (self->priv->entry, "focus-out-event", (GCallback) ddb_cell_renderer_text_multiline_gtk_cell_renderer_focus_out_event, self);
	gtk_widget_set_size_request ((GtkWidget*) self->priv->entry, (*cell_area).width, (*cell_area).height);
	gtk_widget_show ((GtkWidget*) self->priv->entry);
	result = GTK_CELL_EDITABLE (self->priv->entry);
	_g_object_unref0 (buf);
	return result;
}


DdbCellRendererTextMultiline* ddb_cell_renderer_text_multiline_construct (GType object_type) {
	DdbCellRendererTextMultiline * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


DdbCellRendererTextMultiline* ddb_cell_renderer_text_multiline_new (void) {
	return ddb_cell_renderer_text_multiline_construct (DDB_TYPE_CELL_RENDERER_TEXT_MULTILINE);
}


static void ddb_cell_renderer_text_multiline_class_init (DdbCellRendererTextMultilineClass * klass) {
	ddb_cell_renderer_text_multiline_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (DdbCellRendererTextMultilinePrivate));
	GTK_CELL_RENDERER_CLASS (klass)->start_editing = ddb_cell_renderer_text_multiline_real_start_editing;
	G_OBJECT_CLASS (klass)->finalize = ddb_cell_renderer_text_multiline_finalize;
}


static void ddb_cell_renderer_text_multiline_instance_init (DdbCellRendererTextMultiline * self) {
	self->priv = DDB_CELL_RENDERER_TEXT_MULTILINE_GET_PRIVATE (self);
}


static void ddb_cell_renderer_text_multiline_finalize (GObject* obj) {
	DdbCellRendererTextMultiline * self;
	self = DDB_CELL_RENDERER_TEXT_MULTILINE (obj);
	_g_object_unref0 (self->priv->entry);
	G_OBJECT_CLASS (ddb_cell_renderer_text_multiline_parent_class)->finalize (obj);
}


GType ddb_cell_renderer_text_multiline_get_type (void) {
	static volatile gsize ddb_cell_renderer_text_multiline_type_id__volatile = 0;
	if (g_once_init_enter (&ddb_cell_renderer_text_multiline_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (DdbCellRendererTextMultilineClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) ddb_cell_renderer_text_multiline_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (DdbCellRendererTextMultiline), 0, (GInstanceInitFunc) ddb_cell_renderer_text_multiline_instance_init, NULL };
		GType ddb_cell_renderer_text_multiline_type_id;
		ddb_cell_renderer_text_multiline_type_id = g_type_register_static (GTK_TYPE_CELL_RENDERER_TEXT, "DdbCellRendererTextMultiline", &g_define_type_info, 0);
		g_once_init_leave (&ddb_cell_renderer_text_multiline_type_id__volatile, ddb_cell_renderer_text_multiline_type_id);
	}
	return ddb_cell_renderer_text_multiline_type_id__volatile;
}




