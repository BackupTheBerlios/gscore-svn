/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/* scorewidget: a score widget for gscore
 *
 * (C) Sebastien Tricaud 2005
 * See AUTHORS file to see where I started from
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include <gtk/gtkmain.h>
#include <gtk/gtksignal.h>
#include <gdk/gdkx.h>

#include "gdkcairo.h"
#include "gtkcairo.h"

enum
{
        PAINT,
        NEW_STAFF,
        DEL_STAFF,
        SELECT_STAFF,
        NEW_OBJECT,
        DEL_OBJECT,
        SELECT_OBJET,
        LAST_SIGNAL
};

static void 
score_class_init (GtkCairoClass * klass);

static void 
score_init (GtkCairo *gtkcairo);

static void 
score_destroy (GtkObject *object);

static void 
score_realize (GtkWidget *widget);

static void
score_size_allocate (GtkWidget *widget, GtkAllocation * allocation);

static gint 
score_expose (GtkWidget *widget, GdkEventExpose *event);

static GtkWidgetClass *parent_class = NULL;
static guint signals[LAST_SIGNAL] = { 0 };

/*FIXME: make the cairo object a property as well,. and deprecate the get_cairo function */

GType
score_get_type (void)
{
        static GType score_type = 0;

        if (!gtk_cairo_type)
                {
                        static const GTypeInfo score_info = {
                                sizeof (GtkCairoClass),
                                NULL,
                                NULL,
                                (GClassInitFunc) score_class_init,
                                NULL,
                                NULL,
                                sizeof (GtkCairo),
                                0,
                                (GInstanceInitFunc) score_init,
                        };

                        score_type = g_type_register_static (GTK_TYPE_WIDGET, "Score",
                                                                 &score_info, 0);
                }

        return gtk_cairo_type;
}

static void
score_class_init (GtkCairoClass * class)
{
        GtkObjectClass *object_class;
        GtkWidgetClass *widget_class;

        object_class = (GtkObjectClass *) class;
        widget_class = (GtkWidgetClass *) class;

        parent_class = gtk_type_class (GTK_TYPE_WIDGET);

        object_class->destroy = score_destroy;

        widget_class->realize = score_realize;
        widget_class->expose_event = score_expose;
        widget_class->size_allocate = score_size_allocate;

        signals[PAINT] = g_signal_new ("paint",
                                       GTK_TYPE_CAIRO,
                                       G_SIGNAL_RUN_LAST,
                                       G_STRUCT_OFFSET (GtkCairoClass, paint),
                                       NULL, NULL,
                                       g_cclosure_marshal_VOID__POINTER,
                                       G_TYPE_NONE, 1, G_TYPE_POINTER);
}

static void
score_init (GtkCairo *gtkcairo)
{
        gtkcairo->gdkcairo = gdkcairo_new (GTK_WIDGET (gtkcairo));
}

GtkWidget *
score_new (void)
{
        GtkWidget *gtkcairo;
        gtkcairo = GTK_WIDGET (g_object_new (GTK_TYPE_CAIRO, NULL));

        gtk_widget_queue_draw (GTK_WIDGET (gtkcairo));

        return gtkcairo;
}

static void
score_destroy (GtkObject *object)
{
        GtkCairo *gtkcairo;

        g_return_if_fail (object != NULL);
        g_return_if_fail (GTK_IS_SCORE_WIDGET (object));

        gtkcairo = SCORE_WIDGET (object);

        gdkcairo_destroy (gtkcairo->gdkcairo);

        if (GTK_OBJECT_CLASS (parent_class)->destroy)
                (*GTK_OBJECT_CLASS (parent_class)->destroy) (object);
}

static void
score_realize (GtkWidget *widget)
{
        GtkCairo *gtkcairo;

        g_return_if_fail (widget != NULL);
        g_return_if_fail (GTK_IS_CAIRO (widget));

        GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
        gtkcairo = SCORE_WIDGET (widget);

        gdkcairo_realize (gtkcairo->gdkcairo);
}

static void
score_size_allocate (GtkWidget     *widget,
                         GtkAllocation *allocation)
{
        GtkCairo *gtkcairo;
        g_return_if_fail (widget != NULL);
        g_return_if_fail (GTK_IS_CAIRO (widget));
        g_return_if_fail (allocation != NULL);

        gtkcairo = GTK_CAIRO (widget);

        widget->allocation = *allocation;

        gdkcairo_size_allocate (gtkcairo->gdkcairo,
                                allocation->x, allocation->y,
                                allocation->width, allocation->height);
}

static gint
score_expose (GtkWidget      *widget,
                  GdkEventExpose *event)
{
        GtkCairo *gtkcairo;

        g_return_val_if_fail (widget != NULL, FALSE);
        g_return_val_if_fail (GTK_IS_SCORE (widget), FALSE);
        g_return_val_if_fail (event != NULL, FALSE);

        gtkcairo = GTK_CAIRO (widget);

        cairo_save (gtk_cairo_get_cairo (gtkcairo));
        gdkcairo_expose (gtkcairo->gdkcairo, event);
        cairo_restore (gtk_cairo_get_cairo (gtkcairo));
        return FALSE;
}

cairo_t  *
score_get_cairo (GtkCairo *gtkcairo)
{
        g_return_val_if_fail (gtkcairo != NULL, NULL);
        g_return_val_if_fail (GTK_IS_SCORE (gtkcairo), NULL);
        return ((gdkcairo_t *) gtkcairo->gdkcairo)->cr;
}

void
score_set_gdk_color (cairo_t  *cr,
                     GdkColor *color)
{
        double    red, green, blue;

        red = color->red / 65535.0;
        green = color->green / 65535.0;
        blue = color->blue / 65535.0;

        cairo_set_rgb_color (cr, red, green, blue);
}

int
score_backend_is_gl (GtkCairo *gtkcairo)
{
        if (((gdkcairo_t *) gtkcairo->gdkcairo)->backend == GDKCAIRO_BACKEND_GL)
                return 1;
        return 0;
}

#if 0
/* FIXME: premultiply the buffer, but who should own it?
 */

cairo_surface_t *
gtk_cairo_surface_create_for_gdk_pixbuf (const GdkPixbuf * pixbuf)
{
        cairo_surface_t *self;
        char     *data;
        cairo_format_t format;
        int       width;
        int       height;
        int       stride;

        if (!pixbuf)
                return NULL;
        data = gdk_pixbuf_get_pixels (pixbuf);
        width = gdk_pixbuf_get_width (pixbuf);
        height = gdk_pixbuf_get_height (pixbuf);
        format = CAIRO_FORMAT_ARGB32;
        stride = gdk_pixbuf_get_rowstride (pixbuf);

        self = cairo_surface_create_for_image (data, format, width, height, stride);
        return self;
}
#endif
