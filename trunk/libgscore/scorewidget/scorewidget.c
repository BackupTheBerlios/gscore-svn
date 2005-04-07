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
#include "scorewidget.h"

enum
{
        PAINT,
        NEW_STAFF,
        MODIFY_STAFF,
        DEL_STAFF,
        SELECT_STAFF,
        NEW_OBJECT,
        MODIFY_OBJECT,
        DEL_OBJECT,
        SELECT_OBJET,

        LAST_SIGNAL
};

static void 
score_widget_class_init (ScoreWidgetClass * klass);

static void 
score_widget_init (ScoreWidget *scorewidget);

static void 
score_widget_destroy (GtkObject *object);

static void 
score_widget_realize (GtkWidget *widget);

static void
score_widget_size_allocate (GtkWidget *widget, GtkAllocation * allocation);

static gint 
score_widget_expose (GtkWidget *widget, GdkEventExpose *event);

static GtkWidgetClass *parent_class = NULL;
static guint signals[LAST_SIGNAL] = { 0 };

/*FIXME: make the cairo object a property as well,. and deprecate the get_cairo function */

GType
score_widget_get_type (void)
{
        static GType score_widget_type = 0;

        if ( ! score_widget_type )
                {
                        static const GTypeInfo score_widget_info = {
                                sizeof (ScoreWidgetClass),
                                NULL,
                                NULL,
                                (GClassInitFunc) score_widget_class_init,
                                NULL,
                                NULL,
                                sizeof (ScoreWidget),
                                0,
                                (GInstanceInitFunc) score_widget_init,
                        };

                        score_widget_type = g_type_register_static (GTK_TYPE_WIDGET, "ScoreWidget",
                                                                    &score_widget_info, 0);
                }

        return score_widget_type;
}

static void
score_widget_class_init (ScoreWidgetClass * class)
{
        GtkObjectClass *object_class;
        GtkWidgetClass *widget_class;

        object_class = (GtkObjectClass *) class;
        widget_class = (GtkWidgetClass *) class;

        parent_class = gtk_type_class (TYPE_SCORE_WIDGET);

        object_class->destroy = score_widget_destroy;

        widget_class->realize = score_widget_realize;
        widget_class->expose_event = score_widget_expose;
        widget_class->size_allocate = score_widget_size_allocate;

        signals[PAINT] = g_signal_new ("paint",
                                       TYPE_SCORE_WIDGET,
                                       G_SIGNAL_RUN_LAST,
                                       G_STRUCT_OFFSET (ScoreWidgetClass, paint),
                                       NULL, NULL,
                                       g_cclosure_marshal_VOID__POINTER,
                                       G_TYPE_NONE, 1, G_TYPE_POINTER);

        signals[NEW_STAFF] = g_signal_new ("new_staff",
                                           TYPE_SCORE_WIDGET,
                                           G_SIGNAL_RUN_LAST,
                                           G_STRUCT_OFFSET (ScoreWidgetClass, new_staff),
                                           NULL, NULL,
                                           g_cclosure_marshal_VOID__POINTER,
                                           G_TYPE_NONE, 1, G_TYPE_POINTER);

}

static void
score_widget_init (ScoreWidget *scorewidget)
{
        scorewidget->gdkcairo = gdkcairo_new (GTK_WIDGET (scorewidget));
}

GtkWidget *
score_widget_new (void)
{
        GtkWidget *scorewidget;
        scorewidget = GTK_WIDGET (g_object_new (TYPE_SCORE_WIDGET, NULL));

        gtk_widget_queue_draw (GTK_WIDGET (scorewidget));

        return scorewidget;
}

static void
score_widget_destroy (GtkObject *object)
{
        ScoreWidget *scorewidget;

        g_return_if_fail (object != NULL);
        g_return_if_fail (IS_SCORE_WIDGET (object));

        scorewidget = SCORE_WIDGET (object);

        gdkcairo_destroy (scorewidget->gdkcairo);

        if (GTK_OBJECT_CLASS (parent_class)->destroy)
                (*GTK_OBJECT_CLASS (parent_class)->destroy) (object);
}

static void
score_widget_realize (GtkWidget *widget)
{
        ScoreWidget *scorewidget;

        g_return_if_fail (widget != NULL);
        g_return_if_fail (IS_SCORE_WIDGET (widget));

        GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
        scorewidget = SCORE_WIDGET (widget);

        gdkcairo_realize (scorewidget->gdkcairo);
}

static void
score_widget_size_allocate (GtkWidget     *widget,
                            GtkAllocation *allocation)
{
        ScoreWidget *scorewidget;
        g_return_if_fail (widget != NULL);
        g_return_if_fail (IS_SCORE_WIDGET (widget));
        g_return_if_fail (allocation != NULL);

        scorewidget = SCORE_WIDGET (widget);

        widget->allocation = *allocation;

        gdkcairo_size_allocate (scorewidget->gdkcairo,
                                allocation->x, allocation->y,
                                allocation->width, allocation->height);
}

static gint
score_widget_expose (GtkWidget      *widget,
                     GdkEventExpose *event)
{
        ScoreWidget *scorewidget;

        g_return_val_if_fail (widget != NULL, FALSE);
        g_return_val_if_fail (IS_SCORE_WIDGET (widget), FALSE);
        g_return_val_if_fail (event != NULL, FALSE);

        scorewidget = SCORE_WIDGET (widget);

        cairo_save (score_widget_get_cairo (scorewidget));
        gdkcairo_expose (scorewidget->gdkcairo, event);
        cairo_restore (score_widget_get_cairo (scorewidget));

        return FALSE;
}

cairo_t  *
score_widget_get_cairo (ScoreWidget *scorewidget)
{
        g_return_val_if_fail (scorewidget != NULL, NULL);
        g_return_val_if_fail (IS_SCORE_WIDGET (scorewidget), NULL);
        return ((gdkcairo_t *) scorewidget->gdkcairo)->cr;
}

void
cairo_gdk_color (cairo_t  *cr,
                 GdkColor *color)
{
        double    red, green, blue;

        red = color->red / 65535.0;
        green = color->green / 65535.0;
        blue = color->blue / 65535.0;

        cairo_set_rgb_color (cr, red, green, blue);
}

int
score_backend_is_gl (ScoreWidget *scorewidget)
{
        if (((gdkcairo_t *) scorewidget->gdkcairo)->backend == GDKCAIRO_BACKEND_GL)
                return 1;

        return 0;
}

#if 0
/* FIXME: premultiply the buffer, but who should own it?
 */

cairo_surface_t *
score_widget_surface_create_for_gdk_pixbuf (const GdkPixbuf * pixbuf)
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
